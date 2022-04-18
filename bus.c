#include <stdio.h>

#include <stdlib.h>

//declare structure tree node

struct tree_node

{

    int income; //variable to store income

    int count; //variable to store number of employees

    struct tree_node* left; //pointer to left node

    struct tree_node* right; //pointer to right node

};

//Function to insert the node into BST

struct tree_node* insert(struct tree_node* root, struct tree_node* element){

    if(root == NULL){ //If root is null, element should be inserted as root

        root = element;

        return root;

    }else{

        //if newnode's income is greter than root node, add to right of root

        if(element->income > root->income){

            if(root->right != NULL)

                root->right = insert(root->right,element); //

            else

                root->right = element;

        }

        else if(element->income < root->income){ //if newnode's income is lesser than root node, add to left of root

            if(root->left != NULL)

                root->left = insert(root->left,element);

            else

                root->left = element;

        }

        return root; //return root

    }

   

}

//function to print inoder traversal of BST

void inorder(struct tree_node *root,FILE *output)

{

    if (root != NULL)

    {

        inorder(root->left,output); //inorder traversal of left subtree

        printf("(%d,%d), ", root->income,root->count); //print root to console

        fprintf(output,"(%d,%d), ", root->income,root->count); //print root to file

        inorder(root->right,output); //inorder traversal of right subtree

    }

}

// funtion to find the highest income

struct tree_node* findHighestIncome(struct tree_node* node)

{

    /* loop down to find the rightmost leaf, that will be the highest value */

    struct tree_node* current = node;

    while (current->right != NULL)

        current = current->right;

    return current;    //return the right most node

}

//function to find no: of single child nodes

int totalSingleChild(struct tree_node* root)

{

    if (root == NULL)

       return 0;

    int res = 0;

    if ((root->left == NULL && root->right != NULL) || //check if left/right pointer == NULL and //right/left pointer

         (root->left != NULL && root->right == NULL)) //right/left pointer != NULL

       res++; //Then increment count

      

     //recursively call for left and right subtree and add both the count

    res += (totalSingleChild(root->left) + totalSingleChild(root->right)); //recursively call for left and right subtree

    return res; //return the count

}

//Function to find total income in the area

int totalIncome(struct tree_node *root)

{

    if (root == NULL)

        return 0;

    return ((root->income * root -> count) + totalIncome(root->left) + totalIncome(root->right));

}

int main()

{

    //variable declration

    int N, i;

    int income,count;

   

    //structure pointer declaration

    struct tree_node *root = NULL;

    struct tree_node *node1 = NULL;

   

     FILE *input = fopen("in.txt", "r"); //open file in read mode

    if(input == NULL){

        printf("Unable to open file, enter a new name: "); //print error if file not found and exit

        exit(1);       

    }

    fscanf(input, "%d", &N); //read file integer in file as N

    i = 0; //initialize loop variable

    while ( i < N){ //loop untill N values are read from file

        fscanf(input, "%d %d", &income,&count); //read income and count from file

        struct tree_node *element = (struct tree_node*)malloc(sizeof(struct tree_node)); //allocate memory for node

        element->income = income; // set income

        element->count = count; //set count

        element->left = NULL; //set left pointer as null

        element->right = NULL; //set right pointer as null

        root = insert(root, element); //cvall insert() to insert the node

        i++; //increment loop variable

    }

    fclose(input); //close the FILE

   

    FILE *output = fopen("out.txt", "w"); // open file in write mode

   

  printf("Tree constructed from the file\n");

    fprintf(output,"Tree constructed from the file\n");

   

    inorder(root,output); //call inoder function with root and file pointer as arguments

    node1 = findHighestIncome(root); //call findHighestIncome function with root as arguments

    printf("\nHighest income: %d Total people with highest income: %d",node1->income,node1->count);

    fprintf(output,"\nHighest income: %d Total people with highest income: %d",node1->income,node1->count);

    count = totalSingleChild(root); //call totalSingleChild function with root as arguments

    printf("\nTotal single children in the tree: %d",count);

    fprintf(output,"\nTotal single children in the tree: %d",count);

    count = totalIncome(root); //call totalIncome function with root as arguments

    printf("\nTotal income in the area: %d",count);

    fprintf(output,"\nTotal income in the area: %d",count);

    fclose(output); //close the file

    return 0;

}