#define STATES_NR 1024

struct dfa {
	struct array *trans;
	struct array *finals;
	int states_nr;
};

struct set *closure(struct set *set);
struct set *edges(struct gnode *gnode, void *c);
struct set *dfa_edge(struct set *s, int c);
struct dfa *nfa2dfa(struct nfa *nfa);
void pdfa(struct dfa *dfa);
struct dfa *divide_eqclass(struct dfa *dfa);
void *tbindex(struct array *arr, int row, int col, int col_nr);