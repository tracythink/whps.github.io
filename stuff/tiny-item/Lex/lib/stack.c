#include "util.h"
#include <assert.h>
#include <stdlib.h>
#include "stack.h"

#define ELESIZE (sizeof(void*))

struct stack *newstack()
{
	struct stack *n = (struct stack *)cmalloc(sizeof *n);
	/* Note:element size is DIFFIRENT with byte-size! */
	void **p = (void **)cmalloc(STACKSIZE * ELESIZE);
	n->p = p;
	n->top = p - 1;
	n->currsize = -1;
	n->size = STACKSIZE;
	return n;
}

int isempty(struct stack *s)
{
	assert(s);
	/* what are you fucking doing, such forget return ?*/
	return (s->top == (s->p - 1)) ? 1 : 0;
}

void push(struct stack *stack, void *value)
{
	void **p = stack->p;
	int resize;
	assert(stack);
	/* bound condition CAREFUL !!!*/
	if ((++stack->currsize) >= stack->size) {
		resize = stack->size + STACKSIZE;
		p = (void **)realloc(stack->p, resize * ELESIZE);
		stack->p = p;
		stack->size = resize;
	}
	stack->top = &p[stack->currsize];
	*stack->top = value;
}

void *top(struct stack *stack)
{
	assert(stack);
	if ((stack->p - 1)  == stack->top) {
		return (void *)POPEMPTY;
	}
	return *stack->top;
}

void *pop(struct stack *stack)
{
	void *r;
	assert(stack);
	if ((stack->p - 1) == stack->top) {
		return (void *)POPEMPTY;
	}
	r  = *stack->top;
	stack->currsize--;
	stack->top--;
	return r;
}

void stackdump(struct stack *s, void (*f)(void *))
{
	void *v;
	if (s == NULL) return;
	while (!isempty(s)) {
		v = pop(s);
		f(v);
	}
}