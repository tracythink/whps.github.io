#include <assert.h>
#include "list.h"
#include "hash.h"
#include "util.h"
#include "tree.h"
#include "graph.h"
#include "stack.h"
#include <stdlib.h>
#include "re2nfa.h"
#include "parse_regex.h"
#include "array.h"
#include "set.h"
#include "nfa2dfa.h"
#include "alphabet.h"
#include "lex.h"
#include "extend_re.h"
#include "mm.h"
extern struct set *alphabet;
extern struct lexunit lexu;

#include "listtest.h"
#include "graphtest.h"
#include "stacktest.h"
#include "re2nfatest.h"
#include "arraytest.h"
#include "settest.h"
#include "nfa2dfatest.h"
#include "lextest.h"

extern int calltimes;

void extend_retest()
{/*
	struct tok_re tr = get_userdef("lang.l");
	int i = 0;
	//printf("%s\n", tr.re->value); 
	//pfmt_string(tr.re->value);
	char *p, *pu;
	extend_reinit();
	p = fmt_re(tr.re->value);*/
}

nofptr ptr[] = {
	listtest, graphtest, stacktest, 
	re2nfatest, 
	arraytest, settest, nfa2dfatest, 
	lextest, extend_retest, NULL
};

int main()
{
	int i = 0;
	for (;ptr[i];i++) ptr[i]();
	printf("AC"); 
	//getchar();
	return 0;
}