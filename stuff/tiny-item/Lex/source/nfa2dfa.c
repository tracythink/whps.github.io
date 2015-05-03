#include "list.h"
#include "re2nfa.h"
#include "set.h"
#include "graph.h"
#include <assert.h>
#include "util.h"
#include "nfa2dfa.h"
#include "array.h"
#include "alphabet.h"

/* Note: for efficient
 * here not check node is belongs a graph O(n*n) */

struct dfa *newdfa()
{
	struct dfa *dfa = (struct dfa *)cmalloc(sizeof *dfa);
	dfa->finals = NULL;
	dfa->states_nr = 0;
	dfa->trans = NULL;
	return dfa;
}

static struct set *u = NULL;

static void union_edges(struct set *tmp,void *c)
{
	struct gnode *gn;
	struct set *e;
	void ** p = tmp->p, **end = p + tmp->curr;
	assert(u);
	clear_set(u);
	//setdump(tmp, pgnode);
	for (; p < end; p++) {
		gn = (struct gnode *)(*p);
		//puts("u"); setdump(u, pgnode);
		e = edges(gn, c);
		//puts("e"); setdump(e, pgnode);
		set_union(u, e);
		//puts("u"); setdump(u, pgnode);
	}
	//puts("###DONE###/////////////");
}
static struct set *t = NULL;
static struct set *tt = NULL;
#define CHK_ISNULL(S) \
	if (!S) {S = newset(MAX_SETSIZE);} \
	else {clear_set(S);}
struct set *closure(struct set * set)
{
	//assert(set);
	int i = 0;
	//if (isempty_set(set)) return set;
	CHK_ISNULL(tt);
	if (!u) u = newset(MAX_SETSIZE);
	CHK_ISNULL(t);
	copyto(set, t);
	//setdump(set, pgnode);
	do {
		//if (i++ > 1) break;
		copyto(t, tt);
		//setdump(tt, pgnode);
		union_edges(tt, Char(EMPTY));
		//puts("u"); setdump(u, pgnode);
		copyto(set_union(u, tt), t);
		//puts("tt"); setdump(tt, pgnode);
		//puts("t"); setdump(t, pgnode);
	} while (!isdeepeq(t, tt)); // `!`
	//setdump(t, pgnode);
	return t;
}

static struct set *tmps = NULL;
struct set *edges(struct gnode *gnode, void *c)
{
	list tmp;
	struct edge *e;
	assert(gnode);
	if (!tmps) tmps = newset(MAX_SETSIZE);
	else clear_set(tmps);
	//pgnode(gnode); 
	//printf("%p %p\n", c, Char(EMPTY));
	for (tmp = gnode->succs; tmp; tmp = tmp->next) {
		e = (struct edge *)tmp->value;
		//pedge(e);
		//printf("%p %p %p\n", e->from, e->value, e->to);
		if (e && e->value == c) addset(tmps, e->to);
	}
	//puts("+");
	//setdump(tmps, pgnode);
	return tmps;
}

struct set *dfa_edge(struct set *s, int c)
{
	assert(s);
	if (!u) u = newset(MAX_SETSIZE);
	union_edges(s, Char(c));
	//setdump(u, pgnode);
	//puts("Begin");
	return closure(u);
}

extern struct set *alphabet;
#define TOKEN_NR 127 // because short 0

static int is_finalstate(struct set *s)
{
	char *p2info;
	int max = 0;
	//assert(s);
	void **p = s->p, **end = s->p + s->curr;
	for (; p < end; p++) {
		p2info = (char*)((struct gnode *)*p)->info;
		if (p2info[0] == FINAL) {
			max = max < p2info[1] ? p2info[1] : max;
		}
	}
	if (max != -1) return max;
	return 0;
}

struct dfa *nfa2dfa(struct nfa *nfa)
{
	struct dfa *dfa = newdfa();
	struct array 
		*states = newarray(), 
		*trans = newarray(), 
		*finals = newarray();
	int j = 1, p = 1, *c, i, idx, token_id, addid, states_nr = 0;
	void **p2 = alphabet->p, **end = p2 + alphabet->curr;
	struct set *s1 = newset(MAX_SETSIZE), *e, *n = newset(MAX_SETSIZE);
	assert(alphabet);
	addset(s1, nfa->start);
	//setdump(s1, pgnode);
	assign(states, j, copyto(e = closure(s1), n));
	//setdump(e, pgnode);
	if ((token_id = is_finalstate(n))) {
		assign(finals, j, Char(token_id));
	}
	//return 0;
	//setdump(e, pgnode);
	while (j <= p) {
		for (p2 = alphabet->p; p2 < end; p2++) {
			//printf("%d\n", j);
			c = (int *)(*p2);
			//setdump(index(states, j), pgnode);
			e = dfa_edge((struct set*)index(states, j), *c);
			//setdump(e, pgnode);
			if (isempty_set(e)) continue; //i ign this condition
			for (i = 1; i <= p; i++) {
				if (isdeepeq(e, (struct set*)index(states, i))) {
					addid = i;
					break;
				}
			}
			if (i == p + 1) {
				n = newset(MAX_SETSIZE);
				assign(states, ++p, copyto(e, n));
				addid = p;
			}
			if ((token_id = is_finalstate(e))) {
				assign(finals, addid, Char(token_id));
			}
			idx = td2od(j, *c - IGN_ALPHABET_NR, STD_ALPHABET_NR);
			//printf("%d %d\n", j, *c);
			assign(trans, idx, Char(addid));
		}
		//printf("j:%d p:%d\n", j, p);
		j++;
		//printf("j:%d p:%d\n",j , p);
	}
	states_nr = p;
	idx = td2od(states_nr + 1, STD_ALPHABET_NR - 1, STD_ALPHABET_NR);
	assign(trans, idx, NULL); //still bound condition
	assign(finals, states_nr + 1, NULL); // FUCK bound
	dfa->finals = finals;
	dfa->states_nr = p;
	dfa->trans =trans;
	return dfa;
}

void *tbindex(struct array *arr, int row, int col, int col_nr)
{
	int idx = td2od(row, col, col_nr);
	assert(arr);
	return index(arr, idx);
}

static void pint2char(void *v)
{
	printf("%-3c", *(int*)v);
}


static void pindex(struct array *arr, int length)
{
	int i, *c;
	assert(arr);
	for (i = 1; i <= length; i++) {
		c = (int *)index(arr, i);
		if (c) printf("%-4d", i);
	}
	putchar('\n');
	printf("final tok_id is:");
	for (i = 1; i <= length; i++) {
		c = (int *)index(arr, i);
		if (c) printf("%-4d", *c);
	}
	putchar('\n');
}

void pdfa(struct dfa *dfa)
{
	void **p = alphabet->p, **end = alphabet->curr + p;
	int i, *c, idx;
	assert (dfa);
	printf("all states is: %d\n", dfa->states_nr);
	printf("final states is:");
	pindex(dfa->finals, dfa->states_nr);
	printf("    ");
	setdump(alphabet, pint2char);
	for (i = 1; i <= dfa->states_nr; i++) {
		printf("s%-2d:", i);
		for (p = alphabet->p; p < end; p++) { //big error no init p
			idx = td2od(i, *(int*)(*p) - IGN_ALPHABET_NR, STD_ALPHABET_NR);
			c = (int*)index(dfa->trans, idx);
			if (c) printf("%-4d", *c);
			else printf("%-4c", ' ');
		}
		puts("");
	}
}