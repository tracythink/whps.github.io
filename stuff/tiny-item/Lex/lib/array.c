#include "util.h"
#include <assert.h>
#include <stdlib.h>
#include "array.h"

/* Note : daynamic array is dangrous so :
 * because save void * when you visit a pointer 
 * this gona be a very careful, but make is :
 * dont worry the length over 
 * ok , add null_array() user have more info that unassigned */
struct array * newarray()
{
	struct array * n = (struct array *)cmalloc(sizeof *n);
	n->length = ARRAYSIZE;
	n->p = (void **)cmalloc(ARRAYSIZE * sizeof(void *));
	/* hey, why fucking put the stm after return, 
	 * take me 1 fuck hour, Mr WHPS */
	null_array(n, 0, n->length);
	return n;
} 

void assign(struct array *arr, int index, void *value)
{
	int resize, oldsize;
	assert(arr);
	if (index >= arr->length) {
		for (resize=arr->length; resize<=index; resize+=ARRAYSIZE);
		arr->p = (void **)realloc(arr->p, resize * sizeof(void *));
		oldsize = arr->length;
		arr->length = resize;
		null_array(arr, oldsize, arr->length);
	}
	(arr->p)[index] = value;
}

/* [s, e) */
void null_array(struct array *arr, int s, int e)
{
	void **t, **end;
	assert(arr);
	end = arr->p + e;
	for (t = arr->p + s; t < end; t++) {
		*t = NULL;
	}
	//putchar('\n');
}

void *index(struct array *arr, int index)
{
	assert(arr);
	assert(index >= 0);
	assert(index < arr->length);
	return (arr->p)[index];
}

void arraydump(struct array *arr, void(*f)(void *))
{
	void **t, **end;
	assert(arr && f);
	end = arr->p + arr->length;
	for (t = arr->p; t < end; t++) {
		if (*t) f(*t);
	}
	putchar('\n');
}