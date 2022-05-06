#ifndef ITEM_LIST_HANDLING_H
#define ITEM_LIST_HANDLING_H



typedef struct Node {
	char label[100];
	int ic;
	struct Node* next;
} label_node;


typedef struct List {
	label_node* head;
} label_list;


label_list* create_list();
void add_label_to_list(label_list* list, char label[], int ic);
void print_label(label_node* node);
void print_label_table(label_list* list);
void deleteList(label_list* list);


#endif 
