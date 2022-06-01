#ifndef PARSER_H_
#define PARSER_H_

#include <stdlib.h>
#include "list_handling.h"
#define LINE_LEN 81

typedef enum { immediateOperand, SymbolOperand, RealativeOperand, RegisterOperand} operandType;

enum { dataLine, InstructionLine };

typedef struct {
	label_list* Shead; /* Head of symbol table */
	unsigned int err_count;
	char* nameOfFile;
	FILE* file;
	/* Command and data counters. */
	int line_number;
	unsigned int IC;
	unsigned int DC;
} ParserData;

ParserData parser_data;



/*
* Jump over white characters and lines.
*/
void forward(char* line ,int *ptr_curr);

/*
* extruct the next word from the line.
*/
void get_next_word(char* line, char* word, int* ptr_curr);

/*
* check if there is a comma .
* the func won't move the 'curr' pointer.
* return int as boolean flag.
*/
int check_comma(char* line, int *ptr_curr);

/*
* jump over comma and white chars.
* should came after 'check comma' method.
*/
void jump_comma(char* line, int *ptr_curr);

/*
* first parse of the assembler.
* check ic and dc counters, add symbol to table and looking for bugs in the inputs.
*/
void parse_line(char* line);

/*
* count dc and ic for label line with .data or .string.
*/
void parse_instruction(char* line, char* command_name,int* ptr_curr);

/*
* count ic and check valid command and operands.
*/
void parse_data(char* line, char* sec_word,int *ptr_curr);
int parse_operands(char* line, char* command, int* ptr_curr);
void call_func_to_11(char* line, int l_cnt);
void setParserData();
void freeParserData();


#endif
