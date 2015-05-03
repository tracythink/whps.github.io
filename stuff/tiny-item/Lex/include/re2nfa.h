struct nfa {
	struct gnode *start;
	struct gnode *final;
	struct graph *blackbox;
};

#define START 'S' // 83
#define FINAL 'F' // 70
#define EMPTY 'E' // 69

typedef void (*re2x) (list, struct graph* ,struct gnode *, struct gnode *);

struct nfa *re2nfa(char *regex, int token);
void re2series
(list reex, struct graph *blackbox, struct gnode *head, struct gnode *tail);
void re2shunt
(list reex, struct graph *blackbox, struct gnode *head, struct gnode *tail);
void re2kleene
(list regex, struct graph *blackbox, struct gnode *head, struct gnode *tail);
void re2basic
(list regex, struct graph *blackbox, struct gnode *head, struct gnode *tail);
