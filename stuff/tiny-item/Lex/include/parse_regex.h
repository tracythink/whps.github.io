#define STAR 1 // 74  => 1 '*'
#define OR 3   // 124 => 3 '|'
#define LINK 2 // 90  => 2 '_'
#define LP 4   //          '('
#define RP 5   //          ')'

#define INIT_re2nfa_call \
re2nfa_call[STAR] = 2; \
re2nfa_call[OR] = 1; \
re2nfa_call[LINK] = 0

#define ISOPERAND(C) \
(((C)==STAR || (C)==OR || (C)==LINK || (C)==LP || (C)==RP) \
? 0 : 1)

#define ISOPERATION(C) !ISOPERAND(C)

#define LESSTHAN(C1, TOP) ((C1 - TOP) > 0 ? 1 : 0)

char *in2post(char *);
list dispart(char *regex);