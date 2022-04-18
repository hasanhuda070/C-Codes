//Showad Huda COP3502C-0V05 Spring 2021 Lab 4

#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1

struct node{
	int data;
	struct node* next;
};

struct queue{
	struct node* front;
	struct node* back;
};

void init(struct queue* qptr);
int enQueue(struct queue* qptr, int val);
int deQueue(struct queue* qptr);
int empty(struct queue* qptr);
int front(struct queue* qptr);
void displayq(struct queue* myqptr);
	
int main(){
	struct queue* myqptr = (struct queue*)malloc(sizeof(struct queue));
	init(myqptr);
	
	int choice;
	int data;
	
	int i;
	
	while(1){
		printf("\n1. Insert into the queue \n");
		printf("2. Delete the element from the queue \n");
		printf("3. Display the elements in the queue \n");
		printf("4. Exit \n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
	
		switch(choice){
			case 1:
				printf("\nEnter the data you want to put in the Queue: ");
				scanf("%d", &data);
				enQueue(myqptr, data);
				displayq(myqptr);
				break;
			
			case 2:
				data = deQueue(myqptr);
				if(data != EMPTY){
					printf("\n%d deleted from the queue\n", data);
					displayq(myqptr);
				}
				else
					printf("Empty queue\n");
				break;
		
			case 3:
				displayq(myqptr);
				break;
		
			case 4:
				exit(1);
			
			default:
				printf("Wrong choice \n");
		}
	}
	return 0;
	
}
void displayq(struct queue* myqptr){
	struct node *t = myqptr -> front;
	while(t){
		printf("%d", t -> data);
		t = t -> next;
	}
}

void init(struct queue* qptr){

	qptr -> front = NULL;
	qptr -> back = NULL;

}

int enQueue(struct queue* qptr, int val){

	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	
	if(temp != NULL){
		temp -> data = val;
		temp -> next = NULL;
		
		if(qptr -> back != NULL)
			qptr -> back -> next = temp;
		
		qptr -> back = temp;
		
		if(qptr -> front == NULL)
			qptr -> front = temp;
	
		return 1;
	}
	
	else
		return 0;

}

int deQueue(struct queue* qptr){
	struct node* temp;
	int retval;
	
	if(qptr -> front == NULL)
		return EMPTY;
	
	retval = qptr -> front -> data;
	
	temp = qptr -> front;
	
	qptr -> front = qptr -> front -> next;
	
	if(qptr -> front == NULL)
		qptr -> back = NULL;
	
	free(temp);
	
	return retval;
	
}

int empty(struct queue* qptr){
	return qptr -> front == NULL;
}

int front(struct queue* qptr){
	if(qptr -> front != NULL)
		return qptr -> front -> data;
	else
		return EMPTY;
		
}
