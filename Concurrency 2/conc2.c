/*CS411 Concurrency Assignment 2
4/30/14
Nicholas Jordan
Bryce Holley
Lei Wang
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t buff_lock;
sem_t buff_count; //slots available to consume from
sem_t buff_spaces;//slots available to produce into

struct node {
	int id;
	struct node *next;
};

struct fifo {
	struct node *head;
	struct node *tail;
} list;

int incr = 0;

void push_node(int id){
	struct node *newnode;
	newnode = malloc(sizeof(struct node));
	newnode->id = id;
	newnode->next = NULL;

	if(list.head == NULL){
		list.head = newnode;
	}
	else{
		list.tail->next = newnode;
	}

	list.tail = newnode;
}

int consume_node(){
	int ret_id;
	struct node *popnode;
	popnode = list.head;

	list.head = popnode->next;

	if(list.head == NULL){
		list.tail == NULL;
	}
	
	ret_id = popnode->id;
	free(popnode);
	return ret_id;
}

void display_fifo(){
	struct node *cur;
	cur = list.head;
	printf("Current state of fifo:");
	while (cur != NULL){
		printf(" %d", cur->id);
		cur = cur->next;
	}
	printf("\n");
}

void * prod_task()
{	

	int i;
	for (i = 0;i<5;i++){
		sem_wait(&buff_spaces);

		sem_wait(&buff_lock);

		/* add item to buffer here */
		printf("Thread: %d : Produced ID: %d\n", pthread_self(), incr);
		push_node(incr);
		incr++;
		display_fifo();
		sem_post(&buff_lock);

		sem_post(&buff_count); 
	}
}


void * cons_task()
{


        int cons_id;

	sem_wait(&buff_count);

	sem_wait(&buff_lock);

	/* consume item from buffer here */
	cons_id = consume_node();
	printf("Thread: %d : Consumed ID: %d \n", pthread_self(), cons_id);
	display_fifo();
	sem_post(&buff_lock);

	sem_post(&buff_spaces);
	
}


int main()
{
	sem_init(&buff_lock, 0, 1);
	sem_init(&buff_count, 0, 0);
	sem_init(&buff_spaces, 0, 5);

	pthread_t p0, p1;
	pthread_t c0, c1, c2;
	
	pthread_create(&p0, NULL, prod_task, NULL);
	pthread_create(&p1, NULL, prod_task, NULL);
	pthread_create(&c0, NULL, cons_task, NULL);
	pthread_create(&c1, NULL, cons_task, NULL);
       	pthread_create(&c2, NULL, cons_task, NULL);
	
	pthread_join(p0, NULL);
	pthread_join(p1, NULL);
	pthread_join(c0, NULL);
	pthread_join(c1, NULL);
	pthread_join(c2, NULL);
	
	
	return 0;
}
