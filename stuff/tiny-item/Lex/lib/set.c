#include "array.h"
#include "list.h"
#include "util.h"
#include "assert.h"
#include "set.h"
#include "mm.h"

#ifdef SET_ARRAYL
struct set *newset(int length)
{
	struct set *n = cmalloc(sizeof*n);
	n->length = length;
	n->p = cmalloc(length);
	n->curr = 0;
	return n;
}

void addset_int(struct set*s, int *value)
{
	void **p, **end;
	assert(s);
	p = s->p, end = p + s->curr;
	for (; p < end; p++) {
		if (*(int *)p == *value) return;
		if (*(int*)*p > *value) break;
	}
	if ((++s->curr) >= s->length) assert("overlength" && 0);
	for (; end > p; end--) {
		*end = *(end - 1);
	}
	*p = value;
}

void addset(struct set *arrl, void *value)
{
	void **p, **end;
	assert(arrl);
	p = arrl->p, end = p + arrl->curr;
	for (; p < end; p++) {
		if (*p == value) return;
		if (*p > value) break;
	}
	if ((++arrl->curr) >= arrl->length) assert("overlength" && 0);
	for (; end > p; end--) {
		*end = *(end - 1);
	}
	*p = value;
}

void setdump(struct set *arrl, void(*f)(void *))
{
	void **p, **end;
	assert(arrl);
	p = arrl->p, end = p + arrl->curr;
	for (; p < end; p++) {
		f(*p);
		putchar(' ');
	}
	putchar('\n');
}

void *binsch_int(struct set *s, int v)
{
	void **p = s->p;
	int *tmp;
	int l = 0, h = s->curr - 1, mid = (l + h) >> 1;
	while (h >= l) {
		tmp = (int *)p[mid];
		if (*tmp == v) return tmp;
		else if (*tmp > v) {
			h = mid - 1;
		} else {
			l = mid + 1;
		}
		mid = (l + h) >> 1;
	}
	return 0;
}

int isempty_set(struct set *s)
{
	assert(s);
	return s->curr ? 0 : 1;
}

struct set *copyto(struct set *from, struct set *to)
{
	void **p, **end;
	assert(from && to);
	clear_set(to);
	p = from->p, end = p + from->curr;
	for (; p < end; p++) {
		addtail(to, *p);
	}
	return to;
}

/* optimize a macro set.h
void clear_set(struct set* s)
{
	assert(s);
	s->curr = 0;
} */

static struct set *tmp4ch = NULL;

struct set *set_union(struct set *s1, struct set *s2)
{
	//assert(s1 && s2);
	void 
		**p1 = s1->p, **p2 = s2->p, 
		**rest = NULL, **end = NULL;
	void **end1 = p1 + s1->curr, **end2 = p2 + s2->curr;
	if (!tmp4ch) tmp4ch = newset(MAX_SETSIZE);
	clear_set(tmp4ch); // bug fix!!!
	if (isempty_set(s1)) return copyto(s2, s1);
	if (isempty_set(s2)) return s1;
	for (; (p1 < end1) && (p2 < end2);) {
		if (*p1 > *p2) {
			addtail(tmp4ch, *p2);
			p2++;
		} else if (*p1 < *p2) {
			addtail(tmp4ch, *p1);
			p1++;
		} else {
			addtail(tmp4ch, *p1);
			p1++;
			p2++;
		}
	}
	if (p1 < end1) (rest = p1, end = end1);
	if (p2 < end2) (rest = p2, end = end2);
	
	for (; rest && rest < end; rest++) {
		addtail(tmp4ch, *rest);
	}
	copyto(tmp4ch, s1);
	return s1;
}

int isdeepeq(struct set *s1, struct set *s2)
{
	void **p, **end, **p2;
	assert(s1 && s2);
	if (s1->curr != s2->curr) return 0;
	p = s1->p, end = p + s1->curr;
	p2 = s2->p;
	for (; p < end; p++, p2++) {
		 if (*p != *p2) return 0;
	}
	return 1;
}
#endif
#ifdef SET_LIST

struct set *newset()
{
	struct set *n = (struct set *)cmalloc(sizeof *n);
	n->s = NULL;
	n->tail = NULL;
	return n;
}

void addtail(struct set *s, void *value)
{
	assert(s);
	if (s->s) {
		s->tail->next = newnode(value);
		s->tail = s->tail->next;
	}
	else {
		s->tail = s->s = newnode(value);
	}
}

struct set *copyset(struct set *s)
{
	struct set *n = newset();
	list tmp, tail = NULL;
	assert(s);
	for (tmp = s->s; tmp; tmp = tmp->next) {
		addtail(n, tmp->value);
	}
	return n;
}

/*Note: set remove dupi elements means
 *Pointer is SAME, you should always keep alloc only one */
void addset(struct set *s, void * value)
{
	list tmp, p2v;
	assert(s);
	if ((tmp = s->s)) {
		if (tmp->value == value) return;
		/* without head point so must recongnize */
		if (tmp->value > value) {
			s->s = newnode(value);
			s->s->next = tmp;
			return;
		}
		while (tmp) {
			/* excately how insert */
			if (tmp->next && tmp->next->value >= value) {
				if (tmp->next->value == value) return;
				p2v = tmp->next;
				tmp->next = newnode(value);
				tmp->next->next = p2v;
				return;
			}
			if (tmp->next == NULL) {
				addtail(s, value);
				return;
			}
			tmp = tmp->next;
		}
	}
	else addtail(s, value);
}

struct set *_union(struct set *s1, struct set *s2)
{
	assert(s1 && s2);
	struct set *s = newset();
	list l1 = s1->s, l2 = s2->s, rest = NULL;
	if (s1->s == NULL) return s2;
	if (s2->s == NULL) return s1;
	for (; l1 && l2;) {
		if (l1->value == l2->value) {
			addtail(s, l1->value);
			l1 = l1->next;
			l2 = l2->next;
		}
		else if (l1->value < l2->value) {
			addtail(s, l1->value);
			l1 = l1->next;
		}
		else {
			addtail(s, l2->value);
			l2 = l2->next;
		}
	}
	if (l1) rest = l1;
	if (l2) rest = l2;
	for (; rest; rest = rest->next) addtail(s, rest->value);
	return s;
}
/* if use set_union tail is uncertail */
struct set *set_union(struct set *s1, struct set *s2)
{
	list l2;
	assert(s1 && s2);
	if (isempty_set(s1)) return (s2);
	if (isempty_set(s2)) return (s1);
	l2 = s2->s;
	while (l2) {
		insert(&(s1->s), l2->value);
		l2 = l2->next;
	}
	return s1;	
}

struct set *intersect(struct set *s1, struct set *s2)
{
	list l1, l2;
	struct set *s = newset();
	assert(s1 && s2);
	if ((l1 = s1->s) && (l2 = s2->s)) {
		while (l1 && l2) {
			if (l1->value == l2->value) {
				addtail(s, l1->value);
				l1 = l1->next;
				l2 = l2->next;
			}
			else if (l1->value > l2->value) {
				l2 = l2->next;
			}
			else l1 = l1->next;
		}
	}
	return s;
}

int isempty_set(struct set *s)
{
	assert(s);
	if (s->s == s->tail && s->s == NULL) {
		return 1;
	}
	else return 0;
}

void clear_set(struct set *s1)
{
	assert(s1);
	s1->s = s1->tail = NULL;
}

int isdeepeq(struct set *s1, struct set *s2)
{
	list tmp1, tmp2;
	assert(s1 && s2);
	tmp1 = s1->s;
	tmp2 = s2->s;
	for (; tmp1 && tmp2;) {
		if (tmp1->value != tmp2->value) return 0;
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	if (tmp1 == tmp2 && tmp1 == NULL) return 1;
	return 0;
}

void setdump(struct set *s, void(*f)(void*))
{
	assert(s);
	listdump(s->s, f);
}

int set_size(struct set *s)
{
	assert(s);
	return list_length(s->s);
}
#endif