#ifndef PARSER_H_
#define PARSER_H_

#include "list_handling.h"
#define LINE_LEN 81

typedef enum {
	immediateOperand,
	SymbolOperand,
	RealativeOperand,
	RegisterOperand
} operandType;



typedef struct {
	operandType type; /* Type of operand */
	union
	{
		int immediateNum; /* Number for immediate addres */
		char* Symbol; /* If there is a symbol in the operand */
		int numOfRegister; /* Number of register in operand - for register type */

	} operandValue; /* What inside the operand */

} operand;



typedef struct {
	int numOfCommand; /* number of the command from the commandsTypes */
	operand FirstOperand; /* origin operand */
	operand SecondOperand; /* destination operand */
	int address; /* the address of command */

} command;




void forward(char* line ,int *ptr_curr);
void get_next_word(char* line, char* word, int* ptr_curr);
int check_comma(char* line, int *ptr_curr);
void jump_comma(char* line, int *ptr_curr);
void parse_line(char* line, int l_cnt, label_list* symbols);


#endif
