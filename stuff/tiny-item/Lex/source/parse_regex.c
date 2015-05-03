#include "list.h"
#include "stack.h"
#include "util.h"
#include <assert.h>
#include <string.h>
#include "set.h"
#include "alphabet.h"
#include "parse_regex.h"
#include "extend_re.h"

struct set *alphabet = NULL;

char re2nfa_call[128];

static int islink(int c) {
	return c == LINK;
}

static void do_operation
(struct stack *stack, int *p2i, int input, char *post)
{
	int c, i = *p2i;
	/* Note: there is a principle that :
	 * i should delay the assign as possible as  
	 * OR may be visit the empty pointer */
	while (!isempty(stack) 
		&& (c=*(char*)top(stack)) != LP
		&& LESSTHAN(input, c)) {
		post[i++] = *(char*)pop(stack);
	}
	*p2i = i;
	push(stack, Char(input));
}

static void do_rightparenthsis
(struct stack *stack, int *p2i, char *post) 
{
	int i = *p2i, c;
	if (isempty(stack))	 assert("err `()` match!" && 0);
	else {
		while (!isempty(stack) && (c = *(char *)pop(stack)) != LP) {
			post[i++] = c;
		}
		if (c != LP) assert(0 && "`(` match err");
	}
	*p2i = i;
}

char *in2post(char *regex)
{
	char *post = (char*)cmalloc(strlen(regex)<<1);
	int i;
	struct stack * stack = newstack();
	/*to be honest i'm :( add the statements  
	 * do repeat times is 4 not influence other moudle */
	INIT_re2nfa_call; // should mv somewhere
	if (regex == NULL) return NULL;
	for (i = 0; *regex; regex++) {//`*regex` not `regex`
		if (ISOPERAND(*regex)) {
			post[i++] = *regex;
			ADD_ALPHABET(*regex);
		} else if (*regex == LP) {
			push(stack, Char(*regex));
		} else if (*regex == RP) {
			do_rightparenthsis(stack, &i, post);
		} else if (ISOPERATION(*regex)) {
			do_operation(stack, &i, *regex, post);
		} else assert("unkonwn regex" && 0);
	}
	while (!isempty(stack)) {
		post[i++] = *(char*)pop(stack);
		if (post[i-1]==LP) assert("unmatch `()`");
	}
	post[i] = '\0';
	return post;
}

#define DO_POP(LR) \
if ((LR = pop(stack)) == POPEMPTY) { \
	assert("err post expr"); \
}

#define DOUBLE_POP DO_POP(right) DO_POP(left)

#define PUSH2(STR) \
push (stack, \
s = Strtail(Strcat((char *) left, (char *)right), STR)) \

#define PUSH1(STR) \
push(stack, Strtail((char *)left, (STR)))

static void dispatch_op(int op, struct stack *stack)
{
	char *s;
	void *left,*right;
	switch(op) { 
	case STAR:
		DO_POP(left); PUSH1(STAR); break;
	case LINK:  
		DOUBLE_POP; PUSH2(LINK); break;
	case OR:
		DOUBLE_POP; PUSH2(OR); break;
	default: assert("unkonwn op" && 0);
	}
}

#define LIST1(p2call_nr, string) \
r = newnode(string); \
addlist(&r, p2call_nr)

#define LIST2(p2call_nr, left, right) \
r = newnode(right); \
addlist(&r, left); \
addlist(&r, p2call_nr)

static list fmt_result(int end, struct stack *stack)
{
	list r = NULL;
	void *left, *right;
	if (ISOPERAND(end) && isempty(stack)) {
		LIST1(Char(3), Char(end));
		return r;
	}
	switch(end) {
	case STAR:
		DO_POP(left); 
		LIST1(Char(re2nfa_call[end]), left);
		break; 
	case LINK: case OR:  
		DOUBLE_POP;
		LIST2(Char(re2nfa_call[end]), left, right);
		break;
	default: assert("unkonwn op" && 0);
	}
	return r;
}

/* Note:before call dispart,mksure arg is post_regex,
 * that means you may call in2post fitst*/ 
list dispart(char *post_re)
{
	struct stack *stack = newstack();
	if (post_re == NULL) return NULL;
	for (; post_re[1]; post_re++) {
		if (ISOPERAND(*post_re)) {
			push(stack, Stringl(post_re, 1));
		} else if (ISOPERATION(*post_re)) {
			dispatch_op(*post_re, stack);
		} else assert("unkonw @bet" && 0);
	}
	return fmt_result(*post_re, stack);
}