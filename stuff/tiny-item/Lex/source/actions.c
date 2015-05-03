#include "util.h"
void ptok_id(int tok_id) {
	//printf("tok_id is %d\n", tok_id);
}

/* Note: there are many reasons use `void f(int)`
 * & at most 9 action 
 * & hope use global-var conmunication */
act_ptr actions_ptr[][10] = {
	{NULL}, // IGN index 1
	{ptok_id, NULL},
	{ptok_id, NULL},
	{ptok_id, NULL},
	{ptok_id, NULL},
	{ptok_id, NULL},
	{ptok_id, NULL},
	NULL
};