
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int n;  /*Inital population of linked list*/
int m;	/*Random operation done on the list*/

// int mInsert;
// int mDelete;
// int mMember;

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

int Fill_Linked_List( struct list_node_s *head_p){
	printf("%d hello form the Fill_Linked_List\n", n );

	int c, r;
 
  	for (c = 1; c <= n; c++) {
    	r = rand() % 65535;
    	if(!Insert(r, &head_p)){   /* If the number is already inserted reduce the counter  */
    		c--;
    	}

  	}
} /* Fill a linked list with given number of nodes */

int main(int argc, char* argv[]){

	/* Take command line arguments n and m */
	if ( argc != 3 ){  
		printf("Required argumaents are not supplied\n");
		exit(1);

	} else {
		n = (int) strtol(argv[1], (char **)NULL, 10);
		m = (int) strtol(argv[2], (char **)NULL, 10);
	}

	printf("Welcome to the Linked List Implementation Serial Program\n");
	
	/* Start the clock to get execution time */
	clock_t t;
	t = clock();

	struct list_node_s * head = NULL; /* initializing head node */
	
	if (!head)
	{
		printf("ERROR: Memory cannot be allocated\n");
		
	}

	Fill_Linked_List(head);  /* Fill the linked list with n random numbers */
	

	for (int i = 0; i < m; ++i)
	{
		int r;
	}
	
	/* Calculate the execution time */
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf("fun() took %f seconds to execute \n", time_taken);

 	free(head);  /* Free the allocated space for linked list */
	return 0;
}