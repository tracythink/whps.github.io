#ifndef LIST_H
#define LIST_H 1
typedef struct slist *list;

struct slist {
	void *value;
	list next;
};

list newnode(void *);
list newlist();

void addlist(list *, void *);

list search(list, void*);

int getv_int(list);

void listdump(list, void(*)(void*));

void rmlistv(list *l, void *value);
void rmlistp(list *l, list p2v);
void insert(list *l, void *value);
int list_length(list l);
void *get_searchv(list sl);
list reverse_list(list l);

#define HEADPOINT (list)0x33
#define EMPTYLIST (void*)0x89

#define LIST_UNIT sizeof(struct slist)
#define LIST_NR 65536*256
#define LIST_SIZE (LIST_NR)*(LIST_UNIT)
#endif
