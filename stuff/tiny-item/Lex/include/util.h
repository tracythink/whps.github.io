#define TRUE 0
#define FALSE -1
#define MAX_LINE 1024

#include <stdio.h>

void *cmalloc(int);
char *String(char*);

void pint(void *);
void pchar(void *v);
void pself(void *v);
int *Char(int c);
char *Strcat(char *s1, char *s2);
char *Stringl(char *, int);
char *Strtail(char *s, int c);
void pstring(void *v);
void *isalloc_int(int);
int td2od(int row, int col, int col_nr);
typedef void(*nofptr)();
typedef void(*act_ptr)(int);