#define STACKSIZE 256
#define POPEMPTY (void*)0x1323

struct stack {
	void **p;
	void **top;
	int currsize;
	int size;
};

struct stack *newstack();
void push(struct stack *stack, void *value);
void *pop(struct stack *stack);
void stackdump(struct stack *s, void (*f)(void *));
int isempty(struct stack *s);
void *top(struct stack *stack);