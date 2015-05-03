#include <assert.h>
#include "util.h"
#include "list.h"
#include "graph.h"
#include "mm.h"

static struct bigds *biggnode = NULL;

struct graph *newgraph()
{
	struct graph *g = (struct graph *)cmalloc(sizeof *g);
	g->nodes = NULL;
	g->edges = NULL;
	g->edge_nr = 0;
	g->node_nr = 0;
	return g;
}

struct gnode *newgnode(void *info)
{
	struct gnode *gn;
	if (!biggnode) biggnode = newbigds(GNODE_SIZE, GNODE_UNIT);
	//struct gnode *gn = (struct gnode *)cmalloc(sizeof *gn);
	gn = alloc_unit(biggnode);
	gn->info = info;
	gn->preds = NULL;
	gn->succs = NULL;
	return gn;
}

void addgraph(struct graph *g, struct gnode *gn)
{
	assert(g && gn);
	addlist(&g->nodes, gn);
	g->node_nr++;
}

void mergegraph(struct graph *g1, struct graph *g2)
{
	list tmp;
	assert(g1 && g1);
	g1->edge_nr += g2->edge_nr;
	g1->node_nr += g2->node_nr;
	for (tmp=g2->nodes; tmp; tmp=tmp->next) {
		addgraph(g1, (struct gnode *)tmp->value);
	}
	for (tmp=g2->edges; tmp; tmp=tmp->next) {
		addlist(&g1->edges, tmp->value);
	}
}

void addedge(struct graph *g, struct gnode *from, struct gnode *to, void *value)
{
	struct edge *n;
	assert(from && to);
	assert(search(g->nodes, from));
	assert(search(g->nodes, to));
	if (isgoto(from,to)) return;
	n = (struct edge *)cmalloc(sizeof(*n));
	n->from = from;
	n->to = to;
	n->value = value;
	addlist(&from->succs, n);
	addlist(&to->preds, n);
	addlist(&g->edges, n); 
	g->edge_nr++;
}

void rmedge(struct graph *g, struct gnode *from, struct gnode *to)
{
	struct edge *tmp;
	assert(g && from && to);
	if ((tmp = isgoto(from, to)) == NULL) return;
	rmlistv(&from->succs, tmp);
	rmlistv(&to->preds, tmp);
	rmlistv(&g->edges, tmp);
	g->edge_nr--;
}

struct gnode *gsearch_int(struct graph *g, int v)
{
	list tmp;
	void * info;
	assert(g);
	for (tmp = g->nodes; tmp; tmp = tmp->next) {
		info = ((struct gnode *)tmp->value)->info;
		if (info && *(int *)info == v) {
			return (struct gnode *)tmp->value;
		}
	}
	return NULL;
}

struct edge *isgoto(struct gnode *from, struct gnode *to)
{
	list l;
	assert(from && to);
	for (l = from->succs; l; l = l->next) {
		if (((struct edge *)l->value)->to == to) 
			return (struct edge *)l->value;
	}
	return NULL;
}

void graphdump(struct graph *g, void (*pn)(void *), void (*pe)(void *))
{
	list nodes, tmp, visit = NULL;
	assert(g);
	for (nodes = g->nodes; nodes; nodes = nodes->next) {
		if ((tmp = search(visit, nodes->value)) == NULL) {
			printf("node: \n");
			pn(nodes->value);
			printf("succs-edges: \n");
			listdump(((struct gnode *)nodes->value)->succs, pe);
			putchar('\n');
			addlist(&visit, tmp);
		}
	}
}

void graphdumpn(struct graph *g, void (*f)(void *))
{
	assert(g);
	printf("the graph have: %d nodes, %d edges\nnodes-info:", g->node_nr, g->edge_nr);
	listdump(g->nodes, f);
}

void graphdumpe(struct graph *g, void (*f) (void *))
{
	assert(g);
	printf("the graph have: %d nodes, %d edges\nedges-val:", g->node_nr, g->edge_nr);
	listdump(g->edges, f);
}

void pgnode(void *gn)
{
	printf("%p ", gn);
	pint(((struct gnode *)gn)->info);
	puts("");
}

void pedge(void *edge)
{
	struct edge * tmp = (struct edge *)edge;
	//printf("%p ", tmp);
	printf("%p ", tmp->from);
	pint(tmp->value);
	printf("%p ", tmp->to);
	puts("");
}