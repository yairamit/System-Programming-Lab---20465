#ifndef PRE_ASM_H_
#define PRE_ASM_H_

#define StartNumOfMacros 4

typedef struct Macro {
	char l[LINE_LEN];
	struct Macro* next;
} macro_line;

/* macros table */
typedef struct MacroSec {
	macro_line* head;
	char* name;
} macro_list;


/*typedef struct macro_list * list_ptr;*/

macro_list* lists[StartNumOfMacros]; /* TODO change to pointer */

void pre_assembler();
void get_macro_lines(macro_list* list , FILE* fp);
void generate_macro_lists();
macro_list* create_macro_list();
void add_to_list(list, node);
#endif
