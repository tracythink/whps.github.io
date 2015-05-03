#include <assert.h>
#include "util.h"
struct bigds {
	void *p;
	int size;
	int curr;
	int unit;
};

struct bigds *newbigds(int size, int unit)
{
	struct bigds *p = cmalloc(sizeof *p);
	p->p = cmalloc(size);
	p->size = size;
	p->unit = unit;
	p->curr = 0;
	return p;
}

void *alloc_unit(struct bigds *big)
{
	int r;
	void *p;
	assert(big && big->p);
	r = big->curr + big->unit;
	if (r > big->size) {
		assert("count anther size"&&0);
	}
	p = (char*)big->p+big->curr;
	big->curr = r;
	return p;
}
