#include <stdlib.h>
#include "util.h"
#include <string.h>
#include "list.h"
#include "set.h"
#include "graph.h"
#include "mm.h"

void *cmalloc(int size)
{
	void *p = malloc(size);
	if (!p) {
		fprintf(stderr, "RUN OUT OF MEMORY\n");
		exit(1);
	}
	return p;
}

static list charp_list = NULL;
static void *isalloc_charp(char * str)
{
	list tmp = charp_list;
	for (; tmp; tmp = tmp->next) { 
		if (!strcmp(str, (char *)tmp->value)) 
			return tmp->value;
	}
	return NULL;
}

char *String(char *s)
{
	char *p;
	if ((p = (char *)isalloc_charp(s))) return p;
	p = (char *)cmalloc(strlen(s)+1);
	strcpy(p, s);
	addlist(&charp_list, p);
	return p;
}

char *Stringl(char *s, int length)
{
	char * p = (char *)cmalloc(length+1),*tmp;
	for (tmp = p; tmp < p+length; tmp++, s++) {
		  *tmp = *s;
	}
	*tmp = '\0';
	if ((tmp = (char *)isalloc_charp(p))) {
		 // FREE(P)
		return tmp;
	} else addlist(&charp_list, p);
	return p;
}

char *Strcat(char *s1, char *s2)
{
	char *p = (char *)cmalloc(strlen(s1)+strlen(s2)+1);
	char *tmp;
	strcpy(p, s1);
	strcat(p, s2);
	if ((tmp = (char *)isalloc_charp(p))) {
		return tmp;
	}
	else addlist(&charp_list, p);
	return p;
}

static list int_list = NULL;
static void *isalloc_int(int c)
{
	list tmp = int_list;
	//listdump(tmp, pint);
	for (; tmp; tmp = tmp->next) {
	//	printf("@%p %d %d\n", tmp->value, *(int *)tmp->value, c);
		if (c ==  *(int *)tmp->value) {
			//puts("sss");
			return tmp->value;
		}
	}
	return NULL;
}

int *Char(int c)
{
	int *p;
	if ((p = (int *)isalloc_int(c))) {
	//	printf("$%p\n", p);
		return p;
	}
	p = (int *)cmalloc(sizeof *p);
	*p = c;
	addlist(&int_list, p);
	return p;
}

char *Strtail(char *s, int c)
{
	int length = strlen(s);
	char *p = (char *)cmalloc(length + 2);
	char *tmp;
	strcpy(p, s);
	p[length] = c;
	p[length + 1] = '\0';
	if ((tmp = (char *)isalloc_charp(p))) {
		// FREE(P)
		return tmp;
	}
	else addlist(&charp_list, p);
	return p;
}

void pint(void *x)
{
	printf("%d ", *(int*)x);
}

void pchar(void *v)
{
	printf("%c ", *(char*)v);
}

void pstring(void *v)
{
	printf("%s \n", (char*)v);
}

void pself(void *v)
{
	printf("%p ", v);
}

int td2od(int row, int col, int col_nr)
{
	return row * col_nr + col;
}