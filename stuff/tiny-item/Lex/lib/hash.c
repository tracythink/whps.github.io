#include "list.h"
#include "util.h"
#include "hash.h"

#define TABLESIZE 127

hashtable newtable()
{
	hashtable p, i;
	p = (hashtable)cmalloc(sizeof(void *)*TABLESIZE);
	for (i = p; i < p + TABLESIZE; i++) {
		(*i) = NULL;	
	}
	return p;
}

int ishash(hashtable h, void * key, void * v, int size)
{
	int index = hash(key);
	if (search((list)h[index], v)) {
		return TRUE;
	}
	return FALSE;
}

int hash(void * key)
{
	int h=0; char * s = (char*)key;
	for (; *s; s++){
		h = h * 65599 + *s;
	}
	return h % TABLESIZE;
}

void addtable(hashtable h, void * key, void * value) 
{
	int index = hash(key);
	addlist((list*)&(h[index]), value);
}

void hashdump(hashtable h, void (*f)(void*))
{
	hashtable tmp = h;
	while (tmp < h + TABLESIZE) {
		if (!(*tmp)) { 
			printf("0");
		} else {
			f(*tmp);
		}
		tmp++;
	}
}

#define PLIST(TYPE, FN) \
void plist_##TYPE(void * l) { \
	listdump((list)l, FN); \
}

PLIST(int, pint)