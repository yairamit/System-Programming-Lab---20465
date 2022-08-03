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
	
	printf("");
}


/***********************new!***************************/
void parse_line( char* line)
{
	int label_flag = 0, curr = 0, tmp;
	char* first_word = (char*)malloc(sizeof(char)* LINE_LEN);  /* hold the first word in line */
	char* sec_word = (char*)malloc(sizeof(char)* LINE_LEN);  /* hold the second word in line */
	if(!first_word || !sec_word)
		fatal_error(ErrorMemoryAlloc);
	puts(line); /*Debag*/
	
	if (line[curr] != '\n' && line[curr] != ";") /* check not comment line */
	{
	    parser_data.line_num++;
		get_next_word(line, first_word, &curr); /* read the first word in the line */
		if (first_word[strlen(first_word)-1] == ':') /* check if lebel */
		{
		    label_flag = 1;
		    tmp = curr;
		    get_next_word(line, sec_word, &tmp); /*check if need tmp or curr.*/ 
		    printf("%s\n", sec_word);
		    /* label of data (DC)*/
			if (sec_word[0] == '.' && (!strcmp(sec_word, ".struct") || !strcmp(sec_word, ".data") || !strcmp(sec_word, ".string")))
			{ 
			    add_label_to_list(parser_data.Shead, first_word, parser_data.DC, DATA);
                parse_data(line, sec_word, &curr);
                
			} 
			else{ /* label of INSTRUCTION (IC)*/
			    add_label_to_list(parser_data.Shead, first_word, parser_data.IC++, INSTRUCTION);
		        	handle_instruction(line, sec_word, &tmp);
			}
		}
		else if(first_word[0] == '.'){ /* extern or entry line */
    			printf("first start with .\n");
    			if (strcmp(first_word, ".extern") == 0) 
    			{
    				printf("extern\n");
    				parse_extern(line, &curr);
    			}
    			else if (strcmp(first_word, ".entry") == 0) 
    			{
    				printf("entry\n");
    				/*parse_entry(line, &curr);*/	
    			}
		}
		else
		    handle_instruction(line, first_word, &curr);
		   
		/*parser_data.IC += parser_data.IC;  לא כאן - להעביר לסוף קובץ*/    
		label_flag = 0;
		free(first_word);
	} /* End of Empty or Comment Line */
}

/*************Extern**and**Entry***********************/

parse_extern(char* line, int* ptr){
    int curr = *ptr;
    char* s = (char*)malloc(sizeof(char)*32);
    while (s){
        get_next_word(line, s, &curr);
        add_label_to_list(parser_data.Shead,s, 0, EXTERN);
        if(check_comma(line, &curr)){
            jump_comma(line, &curr);
        }
        else
            break;
    }
    *ptr = curr;
    free(s);
}

/***************Data**String**Or**Struct*********************/
void parse_data(char* line, char* sec, int *ptr)
{
	printf("in parse data\n");
	int curr = *ptr;
    char* str = (char*) malloc (sizeof(char)*32);
    if (str)
    {
        get_next_word(line, str, &curr);
        if (!strcmp(sec, ".struct")){
            handle_struct(line, str, &curr);
        }
        else if (!strcmp(sec, ".string")){
            handle_string(line, str, &curr);
        }
        else {
            handle_data(line, str, &curr);
        }
    }
}

void handle_struct(char* line, char* str,  int *ptr)
{
	printf("in handle struct\n");
	int curr = *ptr;
	if(str){
	    while(1)
	    {
		if(str[0] == "\"")
		    handle_string(line, &str, &curr);
		else
		    handle_data(line, &str, &curr);
		printf("back after data/string\n");
		if(check_comma(line, &curr)){
		    jump_comma(line, &curr);
		    printf("after comma handle\n");
			get_next_word(line, &str, &curr);
			printf("after get next word\n");
		    }
		else
			break;
	    }
	}
}

void handle_data(char* line, char* str,  int *ptr)
{
	printf("in handle data\n");
	int curr = *ptr, n;
	while (1) 
	{
		printf("in while\n");
		MachineCodeWord _mc;
		_mc.word = get_next_num(line, &curr);
		printf("after get next num\n");
		add_data_to_list(parser_data.Dhead, ++(parser_data.IC), _mc, WORD);
		parser_data.DC++;
		printf("after adding to data list\n");
		if(!check_comma(line, &curr))
			break;
		else
			jump_comma(line, &curr);
	}
	printf("end of handle data\n");
}


int get_next_num(char* line, int* ptr_curr){
    	int curr = *ptr_curr, j;
        char num[LINE_LEN];
    	for(j = 0; !isspace(line[curr]) && line[curr] != '\n'  && ( isalnum(line[curr]) || line[curr] == '+' || line[curr] == '-' ); curr++)
			{
			    num[j] = line[curr];
			    j++;
			}
		num[j] = '\0';
    	forward(line, &curr);
    	*ptr_curr = curr;
    	printf("%s\n", num);
        return atoi(num);
}

void handle_string(char* line, char* str, int *ptr)
{
    int i = 0;
    while(str[i])
    {
        if(isalnum(str[i])){
            parser_data.DC++;
            MachineCodeWord _mc;
            _mc.word = str[i];
            add_data_to_list(parser_data.Dhead, ++(parser_data.IC), _mc, WORD);
        }   
        i++;
    }
}

/******************************************************/
handle_instruction(char* line,char* command, int* ptr)
{
    int curr = *ptr;
    int command_num = parse_command(line, command ,&curr);
    MachineCodeWord m;
    /* func that build line in data list of what in operand, its diferend from parse operand! */
    if(cmds[command_num].numOfOperands == 1)
    {
        operand_handle(line, &curr);
    }
    else if(cmds[command_num].numOfOperands == 2)
    {
        operand_handle(line, &curr);
        printf("%c%c%c\n", line[curr], line[curr++], line[curr++]);
        if(check_comma(line, &curr)){
            jump_comma(line, &curr);
            operand_handle(line, &curr);
        }
        else
            fatal_error("Missing Comma");
    }
}

operand_handle(char* line, int* ptr)
{
    int curr = *ptr;
    MachineCodeWord mc;
    char* op = (char*)malloc(sizeof(char)*32);
    if (op)
    {
        get_next_word(line, op, &curr);
        printf("%s\n", op);
        /*if(is_register(op)){
            
        }*/
    } else
        fatal_error("Memmo");
    *ptr = curr;
}

int parse_command(char* line,char* command, int* ptr_curr)
{
    int curr = *ptr_curr, command_num = 0, tmp;
    MachineCodeWord _mc;
    if(command)
    {
        for(command_num = 0; command_num < 16; command_num++)
            if (strcmp(command ,cmds[command_num].name) == 0)
                break;

        if (command_num == 16)
            fatal_error("UndefinedCommand");
            
        else
        {
            _mc.bits.opcode = command_num;
            tmp = curr;
            if(check_num_of_operands(line, command_num, &tmp))
            {
                tmp = curr;
                if(cmds[command_num].numOfOperands == 0){
                    if (cmds[command_num].numOfOperands < 2)
                        _mc.bits.source = 0;
                    else{
                        _mc.bits.source = parse_operand(line, command_num, &tmp, 1);
                    }
                    _mc.bits.target = parse_operand(line, command_num, &tmp, 2); /* only check if register or label or etc*/
                }
                _mc.bits.target = 0;
                _mc.bits.source = 0;
                /*_mc.ARE = parse_direct();*/
            }
            add_data_to_list(parser_data.Dhead, parser_data.IC, _mc, BITS);
            return command_num;
        }
    }
    else
        fatal_error("there is no command");
}

int check_num_of_operands(char* line, int command_num, int* ptr)
{
    int count = 0, excepted = cmds[command_num].numOfOperands, curr = *ptr , i;
    char* s = line;
    for(i = 0 ; s[i] ; i++)
    {
    	if(s[i] == 44){
    	    count++;
    	}
 	}
 	if(i>0)
 	    count++;
 	return !(count-(cmds[command_num].numOfOperands));
}


parse_operand(char* line, int commandIndex, int* ptr, int opNumber)
{   
    int curr = *ptr;
    if (cmds[commandIndex].numOfOperands < 2 && opNumber == 1)
        return 0;
    
    else {
        
        char* op = (char*) malloc (sizeof(char)*32);
        if (!op)
            fatal_error("Memory");
            
        get_next_word(line, op, &curr);
        
        if (is_imidiate(op))
            return 0;
        else if (is_direct(op))
            return 1;
        else if (is_register(op))
            return 3;
        else/* is_labelA was delete because i want to do it in the second round of the algorithm. */
            return 2;
        
    }
}



/********Directory**************/
int is_imidiate (char* op){
    if (op[0] == '#')
        return 1;
    return 0;
}

int is_direct(char* op){
    printf("\n");
}

int is_labelA(char* op){
    printf("\n");
}

int is_register(char* op){
    return strlen(op) == 2 && op[0] == 'r' && op[1] >= '0' && op[1] <= '7';
}


/***********Start**Func**********/
void setParserData(){
	parser_data.DC = 0;
    	parser_data.IC = 100;
    	parser_data.line_num = 0;
    	parser_data.file = NULL;
    	parser_data.err_count = 0;
    	parser_data.Shead = create_label_list();
    	parser_data.Dhead = create_data_list();
}
void freeParserData(){
	parser_data.file = NULL;
	deleteList(parser_data.Shead);
	deleteListData(parser_data.Dhead);
	free(parser_data.nameOfFile);
}

	
