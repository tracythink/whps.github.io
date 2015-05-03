#include "util.h"
#include "list.h"
#include "parse_regex.h"
#include <assert.h>
#include "string.h"
#include "extend_re.h"

#define IS_OPERAND(C) \
(((C)=='*' || (C)=='|' || (C)=='(' || (C)==')') \
? 0 : 1)

static int islinkform(int c1, int c2) {
	if ((c2) == '\0') return 0; // except end of string 
	if (IS_OPERAND(c1) && IS_OPERAND(c2)) {
		return 1;
	} else if ((c1) == '*' && (c2) == '(') {
		return 1;
	} else if ((c1) == ')' && (c2) == '(') {
		return 1;
	} else if ((c1) == '*' && IS_OPERAND(c2)) {
		return 1;
	} else if (IS_OPERAND(c1) && c2 == '(') {
		return 1;
	} else return 0;
}

static int meta_symbol(char *buf, int *p2i, char i1, char i2)
{
	int i = *p2i, ri = *p2i, is = 0;
	if (i1 == '*') buf[i++] = (is = STAR);
	if (i1 == '|') buf[i++] = (is = OR);
	if (i1 == '(') buf[i++] = (is = LP);
	if (i1 == ')') buf[i++] = (is = RP);
	if (islinkform(i1, i2)) {
		if (!is) buf[i++] = i1;
		buf[i++] = LINK;
	}
	*p2i = i;
	return i - ri;
}
#define REPLACE_STRING(STR) \
	assert(STR); \
	strcpy(buf + i, STR); \
	i += strlen(STR); \
	break;

/* [s, e) */
static char *asc_string(int c, int length)
{
	char *p = cmalloc(length*2);
	int i = 0, j = 0;
	if (length == 0) return NULL;
	for (; i < length; i++) {
		p[j++] = c + i;
		p[j++] = OR;
	}
	p[j-1] = 0;
	return p;
}

static char *alphau = NULL;
static char *alphal = NULL;
static char *alpha_bet = NULL;
static char *digits = NULL;

void extend_reinit()
{
	if (!alphau) alphau = asc_string('A', 26);
	if (!alphal) alphal = asc_string('a', 26);
	if (!digits) digits = asc_string('0', 10);
	if (!alpha_bet) alpha_bet = asc_string(' ' + 1, 94); // 94
}

static void do_backslash(char *buf, int *p2i, char real)
{
	int i = *p2i;
	switch (real) {
	case 'n':
		buf[i++] = '\n';
		break;
	case 't':
		buf[i++] = '\t';
		break;
	case '*': 
	case '|':
	case '(':
	case ')':
		buf[i++] = real;
		break;
	case 'd':
		REPLACE_STRING(digits);
	case 'a':
		REPLACE_STRING(alphal);
	case 'A':
		REPLACE_STRING(alphau);
	case '.':
		REPLACE_STRING(alpha_bet);
	default: assert("unsurpport backslash"&&0);
	}
	*p2i = i;
}
static int ex2 = 0;

char *fmt_re(char *re)
{
	char buf[MAX_LINE * 2];
	int i = 0;
	for (; *re; re++) {
		if (*re == '\\') {
			do_backslash(buf, &i, *(++re));
		} else if (meta_symbol(buf, &i, *re, re[1])) {
			// DO NOTHING
		} else {
			buf[i++] = *re;
		}
	}
	buf[i] = '\0';
	return String(buf);
}

void pfmt_string(char *s)
{
	for(; *s; s++) {
		if (*s < 9) printf("%d ", *s);
		else if (*s == '\n') printf("\\n ");
		else if (*s == '\t') printf("\\t ");
		else printf("%c ", *s);
	}
	puts("");
}

