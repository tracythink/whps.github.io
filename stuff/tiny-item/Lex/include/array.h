#define ARRAYSIZE 256

struct array {
	int length;
	void **p;
};

struct array *newarray();
void assign(struct array *arr, int index, void *value);
void *index(struct array *arr, int index);
void arraydump(struct array *arr, void(*f)(void *));
void null_array(struct array *arr, int s, int e);
struct arrayl *newarrayl(int length);
void assignl(struct arrayl *arrl, void *value);
void arrayldump(struct arrayl *arrl, void(*f)(void *));