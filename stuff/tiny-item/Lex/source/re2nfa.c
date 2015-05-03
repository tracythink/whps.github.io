#include "util.h"
#include "list.h"
#include "graph.h"
#include "stack.h"
#include "parse_regex.h"
#include <assert.h>
#include <string.h>
#include "re2nfa.h"
#include "extend_re.h"

re2x transptr[] = {re2series, re2shunt, re2kleene, re2basic};
static int state_id = 256; // more than 2^8-1

struct nfa *re2nfa(char *regex, int token)
{
	int token_id = 0;
	char *p2token_id = (char*)&token_id;
	struct graph *g = newgraph();
	struct gnode 
		*start = newgnode(Char(START)),
		*final;
	struct gnode 
		*gn1 = newgnode(Char(++state_id)),  
		*gn2 = newgnode(Char(++state_id));
	struct nfa * n = (struct nfa *)cmalloc(sizeof *n);
	//pfmt_string(in2post(regex));
	list r = dispart(in2post(regex));
	p2token_id[0] = FINAL;
	p2token_id[1] = (char)token; //HACK
	final = newgnode(Char(token_id));
	if (regex == "") return NULL;
	n->start = start;
	n->final = final;
	n->blackbox = g;
	addgraph(n->blackbox, start);
	addgraph(n->blackbox, final);
	addgraph(n->blackbox, gn1);
	addgraph(n->blackbox, gn2);
	addedge(n->blackbox, start, gn1, Char(EMPTY));
	addedge(n->blackbox, gn2, final, Char(EMPTY));
	transptr[*(int*)r->value](r->next, n->blackbox, gn1, gn2);
	return n;
}

void re2series
(list regex, struct graph *blackbox, struct gnode *head, struct gnode *tail)
{
	struct gnode 
		*ntail = newgnode(Char(++state_id)),
		*nhead = newgnode(Char(++state_id));
	list r1, r2;
	assert(blackbox && regex && regex->next);
	addgraph(blackbox, ntail);
	addgraph(blackbox, nhead);
	addedge(blackbox, ntail, nhead, Char(EMPTY));
	r1 = dispart((char *)regex->value);
	r2 = dispart((char *)regex->next->value);
	transptr[*(int*)r1->value](r1->next, blackbox, head, ntail);
	transptr[*(int*)r2->value](r2->next, blackbox, nhead, tail);
}

void re2shunt
(list regex, struct graph *blackbox, struct gnode *head, struct gnode *tail)
{
	struct gnode
		*nhead1 = newgnode(Char(++state_id)),
		*nhead2 = newgnode(Char(++state_id)),
		*ntail1 = newgnode(Char(++state_id)),
		*ntail2 = newgnode(Char(++state_id));
	list r1, r2;
	assert(blackbox && regex && regex->next);
	addgraph(blackbox, nhead1);
	addgraph(blackbox, nhead2);
	addgraph(blackbox, ntail1);
	addgraph(blackbox, ntail2);
	addedge(blackbox, head, nhead1, Char(EMPTY));
	addedge(blackbox, head, nhead2, Char(EMPTY));
	addedge(blackbox, ntail1, tail, Char(EMPTY));
	addedge(blackbox, ntail2, tail, Char(EMPTY));
	r1 = dispart((char *)regex->value);
	r2 = dispart((char *)regex->next->value);
	transptr[*(int*)r1->value](r1->next, blackbox, nhead1, ntail1);
	transptr[*(int*)r2->value](r2->next, blackbox, nhead2, ntail2);
}

void re2kleene
(list regex, struct graph *blackbox, struct gnode *head, struct gnode *tail)
{
	struct gnode 
		*ntail = newgnode(Char(++state_id)),
		*nhead = newgnode(Char(++state_id));
	list r1;
	assert(regex && blackbox);
	addgraph(blackbox, ntail);
	addgraph(blackbox, nhead);
	addedge(blackbox, head, nhead, Char(EMPTY));
	addedge(blackbox, ntail, tail, Char(EMPTY));
	addedge(blackbox, head, tail, Char(EMPTY));
	addedge(blackbox, tail, head, Char(EMPTY));
	r1 = dispart((char*)regex->value);
	transptr[*(int*)r1->value](r1->next, blackbox, nhead, ntail);
}

void re2basic
(list regex, struct graph *blackbox, struct gnode *head, struct gnode *tail)
{
	int a;
	assert(regex && blackbox);
	a = *(int *)regex->value;
	addedge(blackbox, head, tail, Char(a));
}


