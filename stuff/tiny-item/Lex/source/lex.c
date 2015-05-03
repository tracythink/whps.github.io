/* give a settings file such as lang.l 
 * tok_id start from 1 & ++ & like : 
 ******************************************************
	#define ID ab*                    #define ID 1
	#define STRING (abd)*      ==>    #define STRING 2
	#define CHAR a|b|c|d              #define CHAR 3
	#define NR (1|2|3)(1|2|3)*        #define NR 4
	...                               ...
 ******************************************************
 * you need add "tokens.h" 
 * you need add a "actions.c" source file */
#include "list.h"
#include "re2nfa.h"
#include "set.h"
#include "graph.h"
#include <assert.h>
#include "util.h"
#include "nfa2dfa.h"
#include "array.h"
#include "alphabet.h"
#include "tokens.h"
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "extend_re.h"

extern struct set* alphabet;

struct tok_re get_userdef(char *filename)
{
	char buf[MAX_LINE], *p, *pid;
	FILE *fp;
	list r = NULL, id = NULL;
	int j = 0;
	struct tok_re ll;
	if (!(fp = fopen(filename, "r"))) {
		assert(0&&"open file err");
	}
	while(fgets(buf, MAX_LINE, fp) != NULL) {
		for (j = 0, p = buf; *p; p++) {
			if (*p == ' ') {
				j++;
				while (*p && *p == ' ') p++;
			}
			if (j == 1) {
				pid = p;
				while (*p && *p != ' ') p++;
				addlist(&id, Stringl(pid, p - pid));
				p--;
			}
			if (j == 2) {
				pid = p;
				while (*p && *p != '\n') p++;
				addlist(&r, Stringl(pid, p - pid));
				break;
			}
		}
	}
	ll.id = reverse_list(id);
	ll.re = reverse_list(r);
	fclose(fp);
	extend_reinit();
	return ll;
}

void output_tok(list tmpid, char *filename)
{
	char buf[MAX_LINE];
	int i = 0;
	FILE *fp;
	if (!(fp = fopen(filename, "w"))) {
		assert(0&&"open file err");
	}
	for (; tmpid; tmpid=tmpid->next) {
		sprintf(buf, "#define %s %d\n", tmpid->value, ++i);
		fputs(buf, fp);
	}
	fclose(fp);
}
/* awsome :) why pass ? */
struct nfa *dfa2nfa(struct dfa *dfa)
{
	void **p2 = alphabet->p, **end = alphabet->curr + p2;
	int idx, *state, i, *c;
	struct nfa *nfa = (struct nfa *)cmalloc(sizeof *nfa);
	struct graph *g = newgraph();
	struct gnode *from, *to;
	char *p = (char *)&idx;
	assert(dfa);
	nfa->blackbox = g;
	nfa->start = newgnode(Char(1));
	addgraph(g, nfa->start);
	nfa->final = NULL;
	for (i = 2; i <= dfa->states_nr; i++) {
		from = newgnode(Char(i));
		addgraph(g, from);
	}
	for (i = 1; i <= dfa->states_nr; i++) {
		from = gsearch_int(nfa->blackbox, i);
		assert(from);
		for (; p2 < end; p2++) {
			c = (int *)(*p2);
			idx = td2od(i, *c-IGN_ALPHABET_NR, STD_ALPHABET_NR);
			state = (int *)index(dfa->trans, idx);
			if (state) {
				to = gsearch_int(g, *state);
				assert(to);
				addedge(g, from, to, c);
			}
		}
	}
	for (i = 1, idx = 0; i <= dfa->states_nr; i++) {
		state = (int *)index(dfa->finals, i);
		if (state) {
			from = gsearch_int(g, i);
			assert(from);
			p[0] = FINAL;
			p[1] = *state;
			from->info = Char(idx);
		}
	}
	return nfa;
}

struct dfa *dfa_machine = NULL;

struct dfa *lex_machine(struct tok_re ll)
{
	list tmpid = ll.id, tmpre = ll.re;
	char *re;
	int id = 0;
	struct nfa
		*nfa, 
		*gnfa = (struct nfa *)cmalloc(sizeof *nfa);
	struct dfa *dfa;
	gnfa->blackbox = newgraph();
	gnfa->start = newgnode(Char(START));
	addgraph(gnfa->blackbox, gnfa->start);
	for (; tmpre && tmpid; tmpre=tmpre->next) {
		re = (char *)tmpre->value;
		nfa = re2nfa(re, ++id);
		dfa = nfa2dfa(nfa);
		nfa = dfa2nfa(dfa);
		mergegraph(gnfa->blackbox, nfa->blackbox);
		addedge(gnfa->blackbox, gnfa->start, nfa->start, Char(EMPTY));
		tmpid=tmpid->next;
	}
	return (dfa_machine = nfa2dfa(gnfa));
}

static int do_lex(struct dfa *dfa, int start, int c) 
{
	int idx, *state;
	idx = td2od(start, c-IGN_ALPHABET_NR, STD_ALPHABET_NR);
	state = (int *)index(dfa->trans, idx);
	if (state) return *state;
	else return 0;
}

static int is_final(struct array *finals, int state)
{
	int *s;
	assert(finals);
	if (state == -1) return 0;
	s = (int *)index(finals, state);
	if (s) return *s;
	else return 0;
}

extern act_ptr actions_ptr[][10];

static void do_action(int tok_id)
{
	act_ptr *tmp; int i = 0;
	assert(tok_id > 0);
	tmp = actions_ptr[tok_id];
	for (; *tmp; tmp++) {
		(*tmp)(tok_id);
	}
}

struct lexunit lexu = {NULL, -1};
FILE *fp = NULL;
char *err_string= NULL;

void lexin(char *filename)
{
	if (!fp) {
		fp = fopen(filename, "r");
		if (!fp) assert(0 && "file open err");
	}
}

void lex_automaton(char *filename)
{
	struct tok_re ll;
	ll = get_userdef(filename);
	output_tok(ll.id, TOKENS_H);
	lex_machine(ll);
}

int lex()
{
	struct dfa *dfa = dfa_machine;
	int c, start = 1, last_state = -1, 
		offs = 0, roffs = 0, tok_id, rtok_id;
	char buf[MAX_LINE];
	assert(dfa && fp);
	
	while ((c = fgetc(fp)) != EOF) {
		buf[offs++] = c;
		start = do_lex(dfa, start, c);
		if (start) {
			tok_id = is_final(dfa->finals, start);
			if (tok_id) {
				last_state = start;
				roffs = offs;
				rtok_id = tok_id;
			}
		} else break;
	}
	buf[offs] = '\0';
	err_string = String(buf);
	lexu.matched = Stringl(buf, roffs);
	fseek(fp, roffs-offs, SEEK_CUR);
	if (last_state == -1) {
		if (c == EOF) return FILEEND;
		return UNMATCHED;
	}
	do_action(lexu.tokid = rtok_id);
	return roffs;
}

void plexu()
{
	char *fmt = "%s: return %d\n";
	printf(fmt, lexu.matched, lexu.tokid);
}