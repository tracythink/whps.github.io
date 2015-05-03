#include "util.h"
#include "tree.h"

int addtree(tree t, void *value, int flag)
{
	if (flag == LEFT) {
		if (!t->left) {
			t->left = (void *)newtree(value);
			return 0;
		} else return 1; // left node already exist
	} else if (flag == RIGHT){
		if (!t->right) {
			t->right = (void *)newtree(value);
			return 0;
		} else return 2; // right node already exist
	} else return 3; // which i should add ?
}

tree newtree(void *value)
{
	tree p = (tree)cmalloc(sizeof(struct stree));
	p->left = p->right = NULL;
	p->value = value;
	return p;
}

#define PREORDER 1
#define INORDER 2
#define POSTORDER 3

void treedump(tree root, void (*f)(void *))
{
	if (root) {
		f(root->value);
		treedump((tree)root->left, f);
		treedump((tree)root->right, f);
	}
}

