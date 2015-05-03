#include <string.h>
#include "list.h"
#include "util.h"
#include <assert.h>
#include "mm.h"

list newnode(void * first) 
{
	list p = cmalloc(sizeof *p);
	p->value = first;
	p->next = NULL;
	return p;
}

list reverse_list(list l)
{
	list tmp, head = l, to;
	if (l) {
		while ((to = l->next)) {
			tmp = head;
			head = to;
			l->next = to->next;
			head->next = tmp;
		}
		return head;
	} else return l;
}

void addlist(list *l, void * value)
{
	if (*l) { /* you sure konw pointer ? Mr.WHPS */
		list tmp = (*l);
		(*l) = newnode(value);
		(*l)->next = tmp;
	} else {
		(*l) = newnode(value);
	}
} 


void rmlistv(list * l, void * value)
{
	list t;
	assert(*l);
	t = search(*l, value);
	if (t == NULL) assert("no such value" && 0);
	if (t == HEADPOINT) {
		*l = (*l)->next; //free(*l)
	} else {
		t->next = t->next->next; // free(t)
	}
}

void rmlistp(list * l, list p2v)
{
	assert(*l && p2v);
	if (p2v == HEADPOINT) {
		*l = (*l)->next;
	} else {
		p2v->next = p2v->next->next;
	}
}

/* Note:
   here return a pointer who p->next->value = p */
list search(list l, void * value)
{
	if (l && l->value == value) return HEADPOINT;
	while (l) {
		if (l->next && l->next->value == value) {
			return l;
		}
		l = l->next;
	}
	return NULL;
}

void *get_searchv(list sl)
{
	assert(sl);
	if (sl == HEADPOINT) return sl->value;
	return sl->next->value;
}

#define GETV(TYPE) \
TYPE getv_##TYPE(list l) \
{ \
	return *(TYPE*)(l->value); \
}

GETV(int)

void listdump(list l, void(*f)(void *))
{
	putchar(' ');
	while (l) {
		f(l->value);
		putchar(' ');
		l = l->next;
	}
	putchar('\n');
}

int list_length(list l)
{
	int i = 0;
	for (; l; l = l->next) {
		i++;
	}
	return i;
}

/* insert by order */
void insert(list *l, void * value)
{
	list tmp = *l, p2v;
	if (*l) {
		if (tmp->value >= value) {
			tmp = (*l);
			(*l) = newnode(value);
			(*l)->next = tmp;
			return;
		}
		while (tmp) {
			if (tmp->next && tmp->next->value >= value) {
in:				p2v = tmp->next;
				tmp->next = newnode(value);
				tmp->next->next = p2v;
				return;
			}
			if (tmp->next == NULL) goto in; 
			tmp = tmp->next;
		}
	} else {
		(*l) = newnode(value);
	}
}