#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "files.h"
#include "lists.h"
#define ReadFile "r"

int main(int argc, char* argv[])
{
	int i = 1;
	if(argc >= 2)
		for(i = 1; i < argc; i++){
			printf("name of file %s\n", argv[i]); 
			handle_file(argv[i], ReadFile);
	}
	else
		fatal_error(ErrorMissingArgument);
	
/*
	MachineCodeBits m1;
	MachineCodeBits m2;
	MachineCodeBits m3;
	m1.opcode = 1;
	m1.source = 1;
	m1.target = 1;
	m1.ARE = 1;
	
	m2.opcode = 2;
	m2.source = 2;
	m2.target = 2;
	m2.ARE = 2;
	
	m3.opcode = 3;
	m3.source = 3;
	m3.target = 3;
	m3.ARE = 3;
	
	LineData_list* D = create_data_list();
	add_data_to_list(D ,1 , m1);
	add_data_to_list(D ,2 , m2);
	add_data_to_list(D ,3 , m3);
	print_debbug_data(D);
	deleteListData(D);
*/
	
	
	return 0;
}


