struct bigds {
	void *p;
	int size;
	int curr;
	int unit;
};

struct bigds *newbigds(int size, int unit);
void *alloc_unit(struct bigds *big);