
struct edge {
	struct gnode *from;
	struct gnode *to;
	void *value;
};

struct gnode {
	list preds;
	list succs;
	void *info;
};

struct graph {
	list nodes;
	list edges;
	int node_nr;
	int edge_nr;
};

#define GNODE_NR 1024
#define GNODE_UNIT (sizeof (struct gnode))
#define GNODE_SIZE GNODE_NR*GNODE_UNIT

struct graph *newgraph();
void addgraph(struct graph *g, struct gnode *gn);
void addedge(struct graph *, struct gnode *from, struct gnode *to, void *);
void rmedge(struct graph *, struct gnode *from, struct gnode *to);
struct edge *isgoto(struct gnode *from, struct gnode *to);
struct gnode *newgnode(void *info);
void graphdumpn(struct graph *g, void (*f)(void *));
void pgnode(void *gn);
void graphdumpe(struct graph *g, void (*f) (void *));
void pedge(void *edge);
void graphdump(struct graph *g, void (*pn)(void *), void (*pe)(void *));
struct gnode *gsearch_int(struct graph *g, int v);
void mergegraph(struct graph *g1, struct graph *g2);
