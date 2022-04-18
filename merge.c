#include <stdio.h>

int main()
{
void merge(struct grade ptr[100], int l, int m, int r) {
    Assume:
    L[n1] is the left array with size n1 and is filled up already
    R[n2] is the right array with size n2 and filled up already
   
    i = 0; // tracker for L array
    j = 0; // tracker for R array 
    k = l; // tracker for merged array

while (i < n1 && j < n2)
{
if (L[i].exam < R[j].exam)
{
grades[k].exam = L[i].exam;
grades[k].quiz = L[i].quiz;
i++;
k++;
}
else if(L[i].exam == R[j].exam)
{
if(L[i].quiz < R[j].quiz)
{
grades[k].exam = L[i].exam;
grades[k].quiz = L[i].quiz;
i++;
k++;
  
}
else
{
grades[k].exam = R[j].exam;
grades[k].quiz = R[j].quiz;
j++;
k++;
}
}
else
{
grades[k].exam = R[j].exam;
grades[k].quiz = R[j].quiz;
j++;
k++;   
}
  
}
    while (i < n1)
    {
        ptr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        ptr[k] = R[j];       
        j++;
        k++;
    }
}
}

