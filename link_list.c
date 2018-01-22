#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct list_node_s 
{
	int data;
	struct list_node_s * next;
};

int Member(int value, struct list_node_s* head_p){
	struct list_node_s* current_node = head_p;

	while (current_node != NULL && current_node->data < value)
		current_node = current_node->next;

	if (current_node == NULL || current_node->data > value){
		return 0;
	} else {
		return 1;
	}
} /* Member */

int Insert(int value, struct list_node_s** head_pp){
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
	 	temp_node->data = value;
	 	temp_node->next = current_node;

	 	if (pre_node == NULL){  /* If this is the first node */
	 		*head_pp = temp_node;
	 	}else {
	 		pre_node->next = temp_node;
	 		return 1;	
	 	}

	} else {
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


int main(){
	printf("Hello from the Main\n");
	return 0;
}