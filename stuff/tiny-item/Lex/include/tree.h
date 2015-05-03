#define LEFT 0x21
#define RIGHT 0x43

typedef struct stree *tree;

struct stree{
	void *value;
	void *left;
	void *right;
};

int addtree(tree t, void *value, int flag);
tree newtree(void *value);

#define PREORDER 1
#define INORDER 2
#define POSTORDER 3

void treedump(tree root, void (*f)(void *));