#include <stdlib.h>
#include <stdio.h>
#include "list_handling.h"
#include "error.h"


label_list* create_list() {
    label_list* list = (label_list*)malloc(sizeof(label_list));
    list->head = NULL;
    return list;
}


void add_label_to_list(label_list* list, char label[], int ic)
{
    	label_node* new_label = (label_node*)malloc(sizeof(label_node));
    	if(!new_label)
		fatal_error(ErrorMemoryAlloc);
	
	strcpy(new_label->label, label);
	new_label->ic = ic;
	new_label->next = NULL;
	
	if(list->head == NULL){
        	list->head = new_label;
        	printf("added at beginning\n");
    	} else {
		label_node* curr = list->head;
		
		while(1){
			
			if(!strcmp(new_label->label, curr->label))
				fatal_error("Label Already Exist");
			
			else if(curr->next == NULL){
				curr->next = new_label;
				printf("add to end\n");
				break;
			}
			
			curr = curr->next;
		};
		
	}
}


void print_label(label_node* node)
{
    printf(" [ %s , %d ] ", node->label, node->ic);
}


void print_label_table(label_list* list){
    printf("head-->");
	
	label_node* p;
	for (p = list->head; p != NULL; p = p->next) {
		print_label(p);
		printf(" --> ");
	}
	printf(" |NULL|\n");
}


void deleteList(label_list* list)
{
	label_node* p = list->head;

	while (list->head != NULL) {
		list->head = list->head->next;
		printf("delete %s\n", p->label);
		free(p);
		p = list->head;
	}

}
