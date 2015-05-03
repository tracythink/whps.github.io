#ifndef LEX_H
#define LEX_H 1
struct tok_re {
	list re;
	list id;
};

struct lexunit {
	char *matched;
	int tokid;
};

struct tok_re get_userdef(char *filename);
void output_tok(list, char * filename);
struct nfa *dfa2nfa(struct dfa *dfa);
struct dfa *lex_machine(struct tok_re ll);
int lex();
void lexin(char *filename);
void lex_automaton(char *filename);
void plexu();
#define UNMATCHED -1
#define FILEEND -2
#define TOKENS_H "./include/tokens.h"
#endif