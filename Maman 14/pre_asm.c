#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "files.h"
#include "parser.h"
#include "error.h"
#include "pre_asm.h"



macro_list* create_macro_list(){
	 macro_list* list = (macro_list*) malloc (sizeof(macro_list));
	 
	 if (list) {
	 	list->head = NULL;
	 	list->name = (char*) malloc (sizeof(char)*81);
	 	if(list->name)
	 		return list;
	 	free(list->name);
	 } else
	 	fatal_error("MEMORY");
}

/* TODO !!!*/
void free_macro_lists(){
	int i = 0;
}

void generate_macro_lists()
{
	int i;
	for(i = 0; i < StartNumOfMacros; i++){
		lists[i] = create_macro_list();
	}
}


void add_to_list(macro_list* list, macro_line* node) /*TODO conect 2 func of add_to_list from lists handling */
{
	if(list->head == NULL)
        	list->head = node;
        
        else 
        {
		macro_line* p = list->head;
		
		while(1){
			
			if(p->next == NULL){
				p->next = node;
				break;
			}
			
			p = p->next;
		};
	}

}

void print_macro(char* m_word){
	int i = 0;
	printf("print_macro\n");
	for (i=0; i < StartNumOfMacros; i++) {
		if (strcmp(m_word, lists[i]->name) == 0) {
			printf("**********\n");
			macro_line* p = lists[i]->head;
			while (p != NULL) {

				fputs(p->l, parser_data.file);
				p = p->next;
			}
			
		}
		else
			i += 1;
	}
	
}

int check_word(char* new_name){
	printf("5\n");
	int i;
	for (i = 0; i < StartNumOfMacros; i++) {
		printf("$ lists[i]->name : %s -- %s\n", lists[i]->name, new_name);
		if (strcmp(new_name, lists[i]->name) == 0) {
			return 1;
		}
		i += 1;
	}
	return 0;
}


void get_macro_lines(macro_list* list , FILE* fp)
{
	char line[LINE_LEN];
	int curr;
	char* first_word = (char*)malloc(sizeof(char)* LINE_LEN);
	if (first_word) {
		printf("in get_macro lines\n");
		while (fgets(line, LINE_LEN, fp)) {
			curr = 0;
			get_next_word(line, first_word, &curr);
			if (strcmp(first_word, "endmacro")) /* not endmacro */
			{
				printf("%s\n", line);
				macro_line* node = (macro_line*)malloc(sizeof(macro_line));
				if(node) {
					strcpy(node->l, line);
					add_to_list(list, node);
				}
			}
			else {
				free(first_word);
				break;
			}
		}
		
	}
	else {
		free(first_word);
		fatal_error("MEMORY");
	}
	
} 



void pre_assembler()
{
	int curr, m_index = -1, i;
	char line[LINE_LEN];
	char* first_word, *name;
	
	first_word = (char*)malloc(sizeof(char)* LINE_LEN);
	name = (char*)malloc(sizeof(char)* LINE_LEN);
	generate_macro_lists();
	
	/* check allocation */
	if (first_word && name) {
		
		/* open original file. */
		FILE* fp = open_file(parser_data.nameOfFile, MainFileEnding ,ReadFile);
		/* open new file to write in. */
		parser_data.file = open_file(parser_data.nameOfFile, AfterMacroEnding ,WirtingToFile);
		
		if (fp && parser_data.file) {
			/* read line by line */
			while (fgets(line, LINE_LEN, fp)) {
				printf("1\n%s\n", line);
				curr = 0;
				get_next_word(line, first_word, &curr);
				/* check if the first name is "macro" */
				if(strcmp("macro", first_word) == 0)
				{
					/*TODO add to table */
					printf("2\n");
					get_next_word(line, name, &curr);
					strcpy(lists[++m_index]->name, name);
					printf("%s\n", lists[m_index]->name); /*Del*/
					printf("2*\n");
					get_macro_lines(lists[m_index], fp); /* add macro lines to list */
				}
				/* check if its macro name, if it is so print it to file. */
				else if (check_word(first_word)) {
					print_macro(first_word);/*print any line of the macro */
					
				}
				else
					fputs(line, parser_data.file);
					
			}
			fseek(fp, 0, SEEK_SET);
			/*DEBUGGGGG*/
			int i;
			/*for(i=0; i < StartNumOfMacros; i++){
				printf("%s\n", lists[i]->name);
			}*/
		}
		else
			fatal_error("CANT OPEN FILE");
		fclose(fp);
	}
	free(first_word);
	free(name);
}

