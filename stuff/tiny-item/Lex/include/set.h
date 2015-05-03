#define MAX_SETSIZE 1024
#define SET_ARRAYL 1

#ifdef SET_ARRAYL

struct set {
	void **p;
	int length;
	int curr;
};

struct set *newset(int length);
/************** optimize macros **************/
//int addtail(struct set *s, void *value);
#define addtail(S, V) \
	if ((++(S->curr)) >= S->length) assert("oversize"&&0); \
	S->p[S->curr - 1] = V;

//void clear_set(struct set *s1);
#define clear_set(S) \
	S->curr = 0

#endif

#ifdef SET_LIST
struct set {
	list s;
	list tail;
};
struct set *newset();
#endif

void *binsch_int(struct set *s, int v);
void addset_int(struct set*s, int *value);
struct set *copyto(struct set *from, struct set *to);
struct set *copyset(struct set *s);
void addset(struct set *s, void *value);
struct set *set_union(struct set *s1, struct set *s2);
struct set *intersect(struct set *s1, struct set *s2);
void setdump(struct set *s, void(*f)(void*));
int isempty_set(struct set *s);
int isdeepeq(struct set *s1, struct set *s2);

#define SET_UNIT sizeof(struct set)
#define SET_NR 65536*4
#define SET_SIZE (SET_UNIT)*(SET_NR)
