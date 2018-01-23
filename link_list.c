
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct list_node_s 
{
	int data;
	struct list_node_s * next;
};

int Member(int value, struct list_node_s* head_p){

	printf("Hello from Member function\n");
	struct list_node_s* current_node = head_p;

	while (current_node != NULL && current_node->data < value){
		printf("Current_node value: %d\n", current_node->data);
		current_node = current_node->next;
	}

	if (current_node == NULL || current_node->data > value){
		return 0;

	} else {
		printf("Member found: %d\n", value );
		return 1;
		
	}
} /* Member */

int Insert(int value, struct list_node_s** head_pp){

	printf("Hello from Insert fuction\n");

	struct list_node_s *current_node = *head_pp;
	struct list_node_s *pre_node = NULL;
	struct list_node_s *temp_node = NULL;

	while (current_node != NULL && current_node->data < value){
		pre_node = current_node;
		current_node = current_node->next;
	}
	if (current_node == NULL || current_node->data > value){
	 	temp_node = (struct list_node_s*)malloc(sizeof(struct list_node_s));
	 	if (!temp_node){ 							/* Check memory is allocated properly */ 
	 		printf("ERROR: out of memory\n");
	 		return 1;
	 	}

	 	printf("Data inserted to the list: %d\n", value );

	 	temp_node->data = value;
	 	temp_node->next = current_node;

	 	if (pre_node == NULL){  /* If this is the first node */
	 		*head_pp = temp_node;
	 	}else {
	 		pre_node->next = temp_node;
	 		return 1;	
	 	}


	} else {
		printf("Value already exsists in the list: %d\n", value );
		return 0; /* Value already in the list */
	}

}/* Insert */

int Delete(int value, struct list_node_s** head_pp){
	struct list_node_s *current_node = *head_pp;
	struct list_node_s *pre_node = NULL;
	// struct list_node_s *temp_node = NULL;

	while (current_node != NULL && current_node->data < value){
		pre_node = current_node;
		current_node = current_node->next;
	}

	if (current_node != NULL && current_node->data == value){
		if (pre_node == NULL){
			*head_pp = current_node->next;
			free(current_node);
		} else {
			pre_node->next = current_node->next;
			free(current_node);

		}
		return 1;

	} else { /* Value isn't in the list */
		return 0;
	}
} /* Delete */

int Fill_Linked_List(int random,  struct list_node_s *head_p){
	printf("%d hello form the Fill_Linked_List\n", random );

	struct list_node_s ** head_pp;
	head_pp = &head_p;

	int c, n;
  	printf("%d random numbers in [1,100]\n", random);
 
  	for (c = 1; c <= random; c++) {
    	n = rand() % random + 1;
    	printf("%d\n", n);
    	Insert(n, head_pp);
  	}
} /* Fill a linked list with given number of nodes */

int main(){
	printf("Welcome to the Linked List Implementation Serial Program\n");
	
	clock_t t;
	t = clock();

	struct list_node_s * p = (struct list_node_s *)malloc(sizeof(struct list_node_s)); /* initializing head node */

	p->next = NULL;
	p->data = 0;
	
	if (!p)
	{
		printf("ERROR: Memory cannot be allocated\n");
		
	}

	Fill_Linked_List(10, p);  /* Fill the linked list with 10 random numbers */
	
	/* Code */

	Member(4, p);
	
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf("fun() took %f seconds to execute \n", time_taken);

 	free(p);  /* Free the allocated space for linked list */
	return 0;
}