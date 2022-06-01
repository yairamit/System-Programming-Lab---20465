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
	 }
	 else {
	 	free(list);
	 	fatal_error("MEMORY");
	 }
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


void get_macro_lines(macro_list* list , FILE* fp)
{
	char line[LINE_LEN];
	int curr;
	char* first_word = (char*)malloc(sizeof(char)* LINE_LEN);
	if (first_word) {
		
		while (fgets(line, LINE_LEN, fp)) {
			curr = 0;
			get_next_word(line, first_word, &curr);
			if (strcmp(first_word, "endmacro")) /* not endmacro */
			{
				printf("%s\n", line);
				macro_line* node = (macro_line*)malloc(sizeof(macro_line));
				if(node)
				{
					strcpy(node->l, line);
					add_to_list(list, node);
				}
			}
			else
			{
				free(first_word);
				break;
			}
		}
		
	}
	else{
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
	
	if (first_word && name) {
		
		/* open original file. */	
		FILE* fp = open_file(parser_data.nameOfFile, MainFileEnding ,ReadFile);
		/* open new file to write in. */
		parser_data.file = open_file(parser_data.nameOfFile, AfterMacroEnding ,WirtingToFile);
		printf("after opening\n");
		if (fp && parser_data.file) {
			
			while (fgets(line, LINE_LEN, fp)) {
				
				curr = 0;
				get_next_word(line, first_word, &curr);
				/* TODO check if there is macro with this name. */
				printf("first : %s\n", first_word);
				/* check if the first name is "macro" */
				if(strcmp("macro", first_word) == 0)
				{
					/*TODO add to table */
					get_next_word(line, name, &curr);
					printf("macro name : %s\n", name);
					strcpy(lists[++m_index]->name, name);
					get_macro_lines(lists[m_index], fp);
				}
				/*else
					fputs(line, parser_data.file);*/
			}
			fseek(fp, 0, SEEK_SET);
			
		}
		 else
			fatal_error("CANT OPEN FILE");
		fclose(fp);
	}
	free(first_word);
	free(name);
}




/*
void pre_assembler()
{
	int curr = 0;
	char line[LINE_LEN];
	char* first_word = (char*)malloc(sizeof(char)* LINE_LEN);
	char* macro_name = (char*)malloc(sizeof(char)* LINE_LEN);

	FILE* fp = open_file(parser_data.nameOfFile, MainFileEnding ,ReadFile);
	parser_data.file = open_file(parser_data.nameOfFile, AfterMacroEnding ,WirtingToFile);
	
	macro_list* mlist = (macro_list*)malloc(sizeof(macro_list));

	if(fp && parser_data.file && mlist)
	{
		mlist->head = NULL;
		while(fgets(line, LINE_LEN, fp))
		{

			get_next_word(line, first_word, &curr);
			if(!strcmp(first_word, "macro"))
			{
				macro_line* new_line = (macro_line*)malloc(sizeof(macro_line));
    				if(!macro_line)
					fatal_error(ErrorMemoryAlloc);
				
				get_next_word(line, macro_name, &curr);
				while(fgets(line, LINE_LEN, fp))
				{
					get_next_word(line, first_word, &curr);
					/*if(strcmp(first_word, "endmacro")
				}
			}
		}
	}
	
	fclose(fp);
	free(mlist);
	fclose(parser_data.file);
}*/
