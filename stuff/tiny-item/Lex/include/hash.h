typedef void** hashtable;

hashtable newtable();

int ishash(hashtable, void *, void *, int);
int hash(void *);
void addtable(hashtable, void *, void *);
void hashdump(hashtable, void (*)(void*));

