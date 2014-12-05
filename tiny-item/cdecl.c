/*
** version 1.0
** whps
** 14.9.4
** short error deal
** make sure defination is right or raise big error
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/*
 *debug info
 */
#define DEBUG
#undef  DEBUG
#define DEBUG_P printf("file: %s\nline: %d\n", __FILE__, __LINE__)
/*
**
*/
#define POP (top--)
#define PUSH(t) (stack[++top] = (t))
/*
 * const value
 */
#define DESC_LEN 20
#define STACK_SIZE 30
enum type_tag { ID_VAR, QUALIFIER, BS_TYPE };
char const * const bs_type[] = {"void", "char", "int", "float", "double", NULL};

struct token
{
    char type;
    char desc [DESC_LEN];
};

static void read_to_idvar();
static void deal_array();
static void deal_func();
static void deal_lparen();
static void deal_ptr();
static void deal_bstype();

static int top = -1;
static char * to_deal;
static struct token cur;
static struct token stack[STACK_SIZE];
static void (*nextstate) (void) = read_to_idvar;

static void init_to_deal(char * source_str)
{
    to_deal = source_str;
}

static enum type_tag classify_string()
{
    char ** p;

    if (!strcmp(cur.desc, "const")) {
        strcpy(cur.desc, "只读");
        return QUALIFIER;
    }

    for (p = bs_type; *p; p++) {

        if (!strcmp(cur.desc, *p)) {
            return BS_TYPE;
        }
    }

    return ID_VAR;
}

static void get_token()
{
    char * p = cur.desc;

    while (*to_deal && (*p = *to_deal++) == ' ');

    if (isalnum(*p)) {
        #ifdef DEBUG
            /*DEBUG_P;*/
        #endif
        while(isalnum((*++p = *to_deal++)));
        to_deal--;
        *p = '\0';
        cur.type = classify_string();
    } else if (*p == '*') {
        strcpy(cur.desc, "指针 该指针指向");
        cur.type = '*';
    } else {
        cur.desc[1] = '\0';
        cur.type = *p;
    }
}

static void read_to_idvar()
{
    get_token();
    while (cur.type != ID_VAR) {
        PUSH(cur);
        get_token();
    }
    printf("%s 是: ", cur.desc);
    get_token();
    nextstate = deal_array;
    #ifdef DEBUG
        DEBUG_P;
    #endif
}

static void deal_array()
{
    nextstate = deal_func;
    while (cur.type == '[') {
        printf("%s", "数组");
        //puts("数组 ");
        get_token();
        if (isdigit(cur.desc[0])) {
            printf(" 数组大小为%d ", atoi(cur.desc));
            get_token();
        }
        get_token();
        //puts("的");
        printf("%s", " 数组内容为");
        nextstate = deal_lparen;
    }
    #ifdef DEBUG
        DEBUG_P;
    #endif
}

static void deal_func()
{
    nextstate = deal_lparen;
    if (cur.type == '(') {
        while(cur.type != ')') {
            get_token();
        }
        get_token();
        //puts("函数返回");
        printf("%s", "函数 该函数返回");
    }
    #ifdef DEBUG
        DEBUG_P;
    #endif
}

static void deal_lparen()
{
    nextstate = deal_ptr;
    if (top >= 0) {
        if (stack[top].type == '(') {
            POP;
            get_token();
            nextstate = deal_array;
        }
    }
    #ifdef DEBUG
        DEBUG_P;
    #endif
}

static void deal_ptr()
{
    nextstate = deal_bstype;
    if (stack[top].type == '*' || stack[top].type == QUALIFIER) {
        printf("%s", stack[top].desc);
        POP;
        nextstate = deal_lparen;
    }
    #ifdef DEBUG
        DEBUG_P;
    #endif
}

static void deal_bstype()
{
    nextstate = NULL;
    while (top >= 0) {
        printf("%s", stack[top].desc);
        POP;
    }
    #ifdef DEBUG
        DEBUG_P;
    #endif
}
/*
**intface
*/
void cdecl(char * source) {
    init_to_deal(source);
    while (nextstate) {
        nextstate();
    }
}
/*test*/
/*
int main()
{
    init_to_deal("char * const * (*next[15]) (int)");
    while (nextstate) {
        nextstate();
    }
    return 0;
}
*/

