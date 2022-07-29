#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "error.h"
#include "parser.h"
#include "files.h"
#include "lists.h"

struct {
	char* name;
	int numOfOperands;
	unsigned int opcode:4;
	
} cmds[] = {
	{"mov", 2, 0},
	{"cmp", 2, 1},
	{"add", 2, 2},
	{"sub", 2, 3},
	{"not", 1, 4},
	{"clr", 1, 5},
	{"lea", 2, 6},
	{"inc", 1, 7},
	{"dec", 1, 8},
	{"jmp", 1, 9},
	{"bne", 1, 10},
	{"get", 1, 11},
	{"prn", 1, 12},
	{"jsr", 1, 13},
	{"rts", 0, 14},
	{"hlt", 0, 15},

};

char** registers = {"r0","r1","r2","r3","r4","r5","r6","r7"};


/* global variables */





void forward(char* line ,int *ptr_curr)
{
	int curr = *ptr_curr;
    	while( isspace(line[curr]) && line[curr] != '\n')
		curr++;
	*ptr_curr = curr;
}


int check_comma(char* line, int *ptr_curr)
{
    int curr = *ptr_curr, comma = 0;;
    forward(line, &curr);
    
    if(line[curr] == ',')
	    comma = 1;
    return comma;
}


void jump_comma(char* line, int *ptr_curr)
{
    	int curr = *ptr_curr;
    	forward(line, &curr);
	if(line[curr] == ',')
		curr++;
	
	forward(line, &curr);
	*ptr_curr = curr;
}


void get_next_word(char* line, char* word, int* ptr_curr){
	
int curr = *ptr_curr, j;	
    	forward(line, &curr);

	for(j = 0; !isspace(line[curr]) && line[curr] != '\n' && line[curr] != ','; curr++)
		word[j++] = line[curr];
	word[j] = '\0';

	forward(line, &curr);
	*ptr_curr = curr; 
}


void call_func_to_11(char* line, int l_cnt)
{
	if (parser_data.ext_flag != 0) {
	/* skelton for ext print*/
		FILE* ext_file = open_file(parser_data.nameOfFile, ExternFileEnding, WirtingToFile);
		fclose(ext_file);
	}
	
}

void parse_line( char* line)
{
	int label_flag = 0;
	int curr = 0;
	char* first_word = (char*)malloc(sizeof(char)* LINE_LEN);  /* hold the first word in line */
	char* sec_word = (char*)malloc(sizeof(char)* LINE_LEN);  /* hold the second word in line */
	if(!first_word || !sec_word)
		fatal_error(ErrorMemoryAlloc);
	printf("ic = %d\n", parser_data.IC); /* debug*/
	puts(line); /*Debag*/
	
	if (line[curr] != '\n' && line[curr] != ";") /* check not comment line */
	{
		parser_data.line_num++;
		get_next_word(line, first_word, &curr); /* read the first word in the line */
		
		if (first_word[strlen(first_word)-1] == ':') /* check if lebel */
		{
			label_flag = 1;
			first_word[strlen(first_word)-1] = '\0';
			
			get_next_word(line, sec_word, &curr);
			if (sec_word[0] == '.') /*check if data line data ,struct, string*/
			{
				parse_data(line, first_word, sec_word ,&curr); /*TODO - check if string, extern ect..*/
				label_flag = 0;
			}
			else
			{
				add_label_to_list(parser_data.Shead, first_word, parser_data.IC, INSTRUCTION, NULL);
				parse_instruction(line, sec_word,&curr);
			}
		}
		else if (first_word[0] == '.') /* extern or entry line */
		{
			if (strcmp(first_word, ".extern")==0) 
			{
				parser_data.ext_flag = 1;
				parse_extern(line, &curr);
			}
			if (strcmp(first_word, ".entry")==0) 
			{
				printf("entry\n");
				parser_data.ent_flag = 1;
				/*parse_entry(line, &curr);*/
				
			}
			/*parse_data(line, first_word, NULL ,&curr);*/
		}
		/* instruction line. */
		else 
		{
			parse_instruction(line, first_word, &curr);
			
		}
		
		/* free memory */
		free(sec_word);
		free(first_word);
	}/* comment line condition */
}


void parse_data(char* line, char* first_word, char* sec_word, int *ptr_curr)
{
	int curr = *ptr_curr, count = 0,i;
	char* data = (char*)malloc(sizeof(char)* LINE_LEN);
	if(!data)
		fatal_error(ErrorMemoryAlloc);
		
	get_next_word(line, data, &curr);/* TODO - change it- instad of get_next, get the rest of line.. */
	add_label_to_list(parser_data.Shead, first_word, parser_data.IC, DATA, data);
	
	for(i = 0; i < strlen(data); i++) {
		if(isalnum(data[i]) || data[i] == '.' || data[i] == '-') /* for the-" */
			count++;
	}

	parser_data.IC += count;
	parser_data.DC += count;
	*ptr_curr = curr;
	free(data);
}

void parse_extern(char* line, int* ptr_curr)
{
	int curr = *ptr_curr;
	char* label = (char*)malloc(sizeof(char)* LINE_LEN);
	if(!label)
		fatal_error(ErrorMemoryAlloc);
	
	while (line[curr] != '\n' && line[curr] != '\0')
	{
		get_next_word(line, label, &curr);
		add_label_to_list(parser_data.Shead, label, parser_data.DC, EXTERN, NULL);
	}
	*ptr_curr = curr;
	free(label);
	
}


void parse_instruction(char* line, char* command_name,int* ptr_curr)
{
	int curr = *ptr_curr, i,j;
	
	for(i = 0; i < NUM_OF_COMMANDS ; i++)
	{
		if(!strcmp(command_name, cmds[i].name)) {
			break;
		}
	}
	
	if(i == 16) {
		error_log(InvalidCommand, parser_data.line_num);
		return;
	} else {
		for(j = 0; j < cmds[i].numOfOperands; j++)
		{/*
			if (cmds[i].numOfOperands > 0)
			{
				char* p = strchr(line, '.');
				if (p != NULL)
					parser_data.IC++;
			}
		*/}
		 
		parser_data.IC += (cmds[i].numOfOperands+1);
	}
	*ptr_curr = curr;
}




void setParserData(){
	parser_data.DC = 0;
    	parser_data.IC = 100;
    	parser_data.line_num = 0;
    	parser_data.file = NULL;
    	parser_data.err_count = 0;
    	parser_data.Shead = create_label_list();
    	parser_data.Dhead = create_data_list();
}

void freeParserData()
{
	parser_data.DC = 0;
	parser_data.IC = 100;
	parser_data.line_num = 0;
	parser_data.file = NULL;
	parser_data.err_count = 0;
	deleteList(parser_data.Shead);
	
	free(parser_data.nameOfFile);
}




