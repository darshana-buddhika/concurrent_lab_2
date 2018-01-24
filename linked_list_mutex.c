
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int n;  /*Inital population of linked list*/
int m;	/*Random operation done on the list*/

float mInsert;
float mDelete;
float mMember;

int * operation;

long count_member;
long count_insert;
long count_delete;

const int MAX_THREAD_COUNT = 1024;  /* Maximum number of threads supported by the cpu */

int thread_count;   /* Take from command line argument */
pthread_mutex_t mutex;

// struct list_node_s * head = NULL; /* initializing head node */

struct list_node_s 
{
	int data;
	struct list_node_s * next;
};



int Member(int value, struct list_node_s* head_p){

	printf("Hello from Member function\n");
	struct list_node_s* current_node = head_p;

	while (current_node != NULL && current_node->data < value){
		// printf("Current_node value: %d\n", current_node->data);
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

	 	// printf("Data inserted to the list: %d\n", value );

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

	printf("Hello from Delete funtion \n");
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

void shuffle(int *array, size_t n){
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
} /* Shuffle the array */

int Fill_Linked_List( struct list_node_s *head_p){
	printf("%d hello form the Fill_Linked_List\n", n );

		int c, r;
 
  	for (c = 1; c <= n; c++) {
    	r = rand() % 65535 + 1;
    	if(!Insert(r, &head_p)){   /* If the number is already inserted reduce the counter  */
    		c--;
    	}

  	}

  	operation = malloc (m * sizeof(int));

  	printf("M :%d\n", m);
  	printf("minsert: %f mdelete: %f mmember: %f\n", mInsert,mDelete,mMember);

	count_insert = m * mInsert;
	count_delete = m * mDelete;
	count_member = m * mMember;

	printf("member :%lu  Insert: %lu  Delete: %lu\n", count_member,count_insert,count_delete );

	for (int i = 0; i < count_member; ++i)
	{
		operation[i] = 0;
	}

	for (int i = 0; i < count_insert; ++i)
	{
		operation[count_member+i] = 1;
	}

	for (int i = 0; i < count_delete; ++i)
	{
		operation[count_member + count_insert + i] = 2;
	}

	// for (int i = 0; i < m; ++i)
	// {
		
	// 	printf(" list value :%d\n", operation[i]);
	// }

	shuffle(operation, m);  /* Shuffle the array */

	for (int i = 0; i < m; ++i)
	{
		
		printf(" list value :%d\n", operation[i]);
	}

} /* Fill a linked list with given number of nodes */

void* thread_operation(void * rank){
	long my_rank = (long) rank;
	// long my_m = m/thread_count;    /* Devide m operations among created threads
				
										/*Assume this is perfectly devidable */

	printf("hello from thread %lu\n", my_rank);
	long s = my_rank * (m / thread_count);
	long e = s + (m / thread_count);
	int r;
	long i;

	printf("Start :%lu End: %lu\n",s,e );
	for (i = s; i < e; i++)
	{
		r = rand() % 65535 + 1;
        int b = operation[i];
		switch(b){
			case 0:
				// printf("inside member: %lu\n",i );
				pthread_mutex_lock(&mutex);
				Member(r, head);
				pthread_mutex_unlock(&mutex);
				break;

			case 1:
				pthread_mutex_lock(&mutex);
				Insert(r, &head);
				pthread_mutex_unlock(&mutex);
				break;

			case 2:
				pthread_mutex_lock(&mutex);
				Delete(r, &head);
				pthread_mutex_unlock(&mutex);
				break;
		}      
        
	}
}

int main(int argc, char* argv[]){

	/* Take command line arguments n and m */
	if ( argc != 7 ){  
		printf("Required argumaents are not supplied\n");
		exit(1);

	} else {
		n = (int) strtol(argv[1], (char **)NULL, 10);
		m = (int) strtol(argv[2], (char **)NULL, 10);
		mMember = (float) atof(argv[3]);
		mInsert = (float) atof(argv[4]);
		mDelete = (float) atof(argv[5]);
		thread_count = (int) strtol(argv[6], (char **)NULL, 10);
	}

	printf("Welcome to the Linked List Implementation Serial Program\n");
	
	// if (!head)
	// {
	// 	printf("ERROR: Memory cannot be allocated\n");
		
	// }
	struct list_node_s * head = malloc(sizeof(struct list_node_s)); /* initializing head node */
	
	pthread_t* thread_handles;

	Fill_Linked_List(head);  /* Fill the linked list with n random numbers */

	thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
	
	/* Start the clock to get execution time */
	clock_t t;
	t = clock();	

	pthread_mutex_init(&mutex, NULL);
    
	printf("thread count: %d\n", thread_count);

	long thread;

    for (thread = 0; thread < thread_count; thread++)  
    {
        pthread_create(&thread_handles[thread], NULL,thread_operation , (void*)thread);  
    }
     
    for (thread = 0; thread < thread_count; thread++) 
    {
        pthread_join(thread_handles[thread], NULL); 
    }

    pthread_mutex_destroy(&mutex);
	
	/* Calculate the execution time */
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf("fun() took %f seconds to execute \n", time_taken);

 	free(head);  /* Free the allocated space for linked list */
	return 0;
}