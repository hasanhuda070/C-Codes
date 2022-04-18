/* COP 3502C Assignment 2
This program is written by: Showad Huda */

//Directives
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>			//limits.h to define max and min sizes

//Time properties
#define TIME_PAST -1      
#define TIME_FUTURE INT_MAX         
int currTime;     
                      
//Requirements for the assignment
typedef char customerName[9];
//Customer parameters for nume, line position, time, and items
typedef struct customer {
    customerName name;                 
    int lineNumber;                  
    int time;                        
    int numItems;    
} customer;

//Doubly linked list setup for queue to back

#ifndef QBACK
#define QBACK 1
#endif

//for queue to size
#ifndef QSIZE
#define QSIZE 1
#endif

//for queue to link
#ifndef DLINK
#define DLINK 0
#endif

//#undef to remove current definition of identifier
#if DLINK
#undef QBACK
#define QBACK 1
#endif

//Signly linked with pointer to data for next and previous items.
typedef customer *queueItem;
typedef struct node {
    queueItem data;     
    struct node *next;      
	#if DLINK
		struct node *prev;     
	#endif
} node;

//Signly linked for queue to point to first and last nodes in list
typedef struct queue {
    node *front;          
	#if QBACK
		node *back;                
	#endif
	#if QSIZE
		int size;             
	#endif
} queue;

//Number of total lines at the store
#define NUMLINES 12
queue queue_list[NUMLINES];

//Initialize queue
void queueInit(queue *q)
{
    q -> front = NULL;
	#if QSIZE
		q -> size = 0;
	#endif

	#if QBACK
		q -> back = NULL;
	#endif
}

//Empty queue
int queueEmpty(queue *q)
{
	#if 0
    return (q -> size == 0);
	#else
    return (q -> front == NULL);
	#endif
}

//enQueue setup with new node 
void enQueue(queue *q, queueItem data)
{
    node *newNode;
    node *prev;

    newNode = malloc(sizeof(node));
    newNode -> next = NULL;
    newNode -> data = data;

	#if QBACK
		prev = q -> back;
	#else
  
    prev = NULL;
    for (node *curr = q -> front;  curr != NULL;  curr = curr -> next)
        prev = curr;
	#endif

    if (prev != NULL)
        prev -> next = newNode;
    else
        q -> front = newNode;

	#if DLINK
		newNode -> prev = prev;
	#endif

	#if QBACK
		q -> back = newNode;
	#endif

	#if QSIZE
		q -> size += 1;
	#endif
}

//deQueue from front of queue list
queueItem
deQueue(queue *q)
{
    node *currNode;
    node *nextNode;
    queueItem data;

    do {
        //first node
        currNode = q -> front;

        if (currNode == NULL) {
            data = NULL;
            break;
        }
		
        data = currNode -> data;

        //points to next node
        nextNode = currNode -> next;

	#if QBACK
        node *back = q -> back;
	#if DLINK
        currNode -> prev = back;
	#endif
        if (currNode == back)
            q -> back = nextNode;
	#endif
        q -> front = nextNode;

	#if QSIZE
        q -> size -= 1;
	#endif
        free(currNode);
    } while (0);

    return data;
}

//queueFront to check front of queue
queueItem
queueFront(queue *q)
{
    node *currNode;
    queueItem data;

    currNode = q -> front;
    if (currNode != NULL)
        data = currNode -> data;
    else
        data = NULL;

    return data;
}

//customerFind to find who to check next
customer*
customerFind(void)
{
    int pass;
    int qfirst;
    queue *q;
    int minTime;
    int more;
    customer *cstmr;
    customer *best;

    for (pass = 1;  pass <= 2;  ++pass) {
        best = NULL;
        minTime = TIME_FUTURE;
        more = 0;

        //Scans for first customer
        for (qfirst = 0; qfirst < NUMLINES; ++qfirst) {
            q = &queue_list[qfirst];

            //Get first customer in line
            cstmr = queueFront(q);
            if (cstmr == NULL)
                continue;

            //Waiting list
            more = 1;

            //Minimum time
            if (cstmr -> time < minTime)
                minTime = cstmr -> time;

            if (cstmr -> time > currTime)
                continue;

            if (best == NULL) {
                best = cstmr;
                continue;
            }

            //Best customer is with least items to checkout
            if (cstmr->numItems < best->numItems) {
                best = cstmr;
                continue;
            }
        }

        //No more customers to serve
        if (!more)
            break;
        //DeQueue and free node
        if (best != NULL) {
            q = &queue_list[best->lineNumber - 1];
            deQueue(q);
            break;
        }

        //No best match found
        //Customers are in the future time
        currTime = minTime;
    }

    return best;
}

//Check out customer function
void cstmrdo(customer *cstmr)
{
    int lap;

    if (currTime < cstmr->time)
        currTime = cstmr->time;

    //Amount of time it takes to service
    lap = 0;
    lap += 30;
    lap += cstmr->numItems * 5;

    //Current time equals same as servicing the customer
    currTime += lap;

    printf("%s from line %d checks out at time %d.\n",
        cstmr->name,cstmr->lineNumber,currTime);

    //Free storage
    free(cstmr);
}

//Read and run fils and test cases
void testCase(FILE *f)
{
    queue *q;
    customer *cstmr;

    //Reset all queues
    for (int qfirst = 0;  qfirst < NUMLINES;  ++qfirst) {
        q = &queue_list[qfirst];
        queueInit(q);
    }

    //Number of customers for this case
    int numCustomers;
    fscanf(f, " %d", &numCustomers);

    //Read info of customers
    for (int incstmr = 0;  incstmr < numCustomers;  ++incstmr) {
        cstmr = malloc(sizeof(*cstmr));

        fscanf(f, " %d", &cstmr -> time);
        fscanf(f, " %d", &cstmr -> lineNumber);
        fscanf(f, " %s", cstmr -> name);
        fscanf(f, " %d", &cstmr -> numItems);

        //Add customer to queue
        q = &queue_list[cstmr->lineNumber - 1];
        enQueue(q, cstmr);
    }

    //Current time to past
    currTime = TIME_PAST;

    while (1) {
        //Find next customer
        cstmr = customerFind();

        //No more customers
        if (cstmr == NULL)
            break;

        //Service customer
        cstmrdo(cstmr);
    }
}

//Main function
int main(int argc, char **argv)
{
    char *ifile;
    FILE *f;

    --argc;
    ++argv;

    // open the input file
    if (argc > 0)
        ifile = *argv;
    else
        ifile = "input.txt";
    f = fopen(ifile,"r");
    if (f == NULL) {
        perror(ifile);
        exit(1);
    }

    //Get number of test cases
    int testCases;
    fscanf(f, " %d", &testCases);

    //Process test cases
    for (;  testCases > 0;  --testCases)
        testCase(f);

    fclose(f);

    return 0;
}