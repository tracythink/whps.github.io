#define IGN_ALPHABET_NR 8
#define STD_ALPHABET_NR (128 - IGN_ALPHABET_NR)
#define ADD_ALPHABET(C) \
if (!alphabet) alphabet = newset(MAX_SETSIZE);\
addset(alphabet, Char(C))