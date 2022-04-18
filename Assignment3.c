/* COP 3502 Programming Assignment 3
This program is written by: Showad Huda */

//Pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Parameters
int x,y,n,s,t;
struct points{
	float distance;
	int x_num;
	int y_num;
};

//Merge sort with left, middle, right
void merge(struct points arr[], int l, int m, int r){
	int n1 = m - l + 1;
	int n2 = r - m;
	struct points L[n1], R[n2];
	
	//Left and right 
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	int i = 0;

	int j = 0;
	int k = l;

	while (i < n1 && j < n2) {
	if (L[i].distance < R[j].distance) {
		arr[k] = L[i];
		i++;
	}
	else if(L[i].distance == R[j].distance){
		if(L[i].x_num < R[j].x_num) {
			arr[k] = L[i];
			i++;
	}
	else if(L[i].x_num == R[j].x_num) {
		if(L[i].y_num <= R[j].y_num) {
			arr[k] = L[i];
			i++;
		}
	else {
			arr[k] = R[j];
			j++;
		}
	}
	else{
		arr[k] = R[j];
		j++;
		}
	}
	else {
		arr[k] = R[j];
		j++;
	}
k++;
}

while (i < n1) {
	arr[k] = L[i];
	i++;
	k++;
}

while (j < n2) {
	arr[k] = R[j];
	j++;
	k++;
	}
}

//Insertion sort 
void insertion(struct points arr[], int n){
	int i,j;
	struct points key;
	for (i = 1; i < n; i++){
		key = arr[i];
		j = i - 1;

		while (j >= 0 && (arr[j].distance > key.distance || ((arr[j].distance == key.distance) && (arr[j].x_num > key.x_num)) || ((arr[j].distance == key.distance) && (arr[j].x_num == key.x_num) && (arr[j].y_num > key.y_num)))){
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		}
}

//Sorting values
void doSort(struct points arr[],int l,int r){
	if(l>=r){
	return;
	}	
	if(r-l+1<=t){
		insertion(arr, r-l+1);
	}
	else{
		int m =l+ (r-l)/2;
		doSort(arr,l,m);
		doSort(arr,m+1,r);
		merge(arr,l,m,r);
	}
}

//compareTo function
/* 
int compareTo(const coord *ptrPt1,const coord *ptrPt2) {
    int cmp;

    do {
        // compare distance
        cmp = dist(p1) - dist(p2);
        if (cmp)
            break;
    return cmp;
}
*/

//First value in plane
int first(struct points arr[], int low, int high, int x, int n){
	if (high >= low) {
		int mid = low + (high - low) / 2;
	if ((mid == 0 || x > arr[mid - 1].distance) && arr[mid].distance == x)
		return mid;
	else if (x > arr[mid].distance)
		return first(arr, (mid + 1), high, x, n);
	else
		return first(arr, low, (mid - 1), x, n);
	}
return -1;
}

//Last value in plane
int last(struct points arr[], int low, int high, int x, int n){
	if (high >= low) {
		int mid = low + (high - low) / 2;
	if ((mid == n - 1 || x < arr[mid + 1].distance) && arr[mid].distance == x)
		return mid;
	else if (x < arr[mid].distance)
		return last(arr, low, (mid - 1), x, n);
	else
		return last(arr, (mid + 1), high, x, n);
	}
return -1;
}

//Find values and see if found or not with pointer coordinate postions
void find(struct points arr[], int a,int b){
	int first_index = first(arr,0,n-1,(x-a)*(x-a)+(y-b)*(y-b),n);
	int last_index = last(arr,0,n-1,(x-a)*(x-a)+(y-b)*(y-b),n);
	if(first_index==-1){
		printf("%d %d not found\n",a,b);
	return;
	}
	for(int i=first_index ; i <= last_index; i++){
	if(arr[i].x_num == a && arr[i].y_num == b){
		printf("%d %d found at rank %d\n",a,b,i);
	return;
	}
	}
	printf("%d %d not found\n",a,b);
}

/*struct point* ReadData(FILE *infile, int *xcen, int *ycen, int *r, int *N){
int i;

fscanf(infile, "%d", xcen);
fscanf(infile, "%d", ycen);
fscanf(infile, "%d", r);
fscanf(infile, "%d", N);

struct point* list = (struct point*) malloc(*N * sizeof(struct point));

for(i = 0; i < *N; i++){
	fscanf(infile, "%d", &list[i].x);
	fscanf(infile, "%d", &list[i].y);

}
return list;
}*/



//Main function
int main(void) {
   
   //ReadData()
   /*FILE * fPointer;
   fPointer = fopen("Assignment3input.txt", "r");
   char singleLine[150];
   
   while(!feof(fPointer)){
		fgets(singleLine, 150, fPointer);
		puts(singleLine);
   }
   
   fclose(fPointer);
   return 0;
   */
   
   scanf("%d%d%d%d%d",&x,&y,&n,&s,&t);
   struct points point_arr[n];
   int a;
   int b;
   for(int i=0;i<n;i++){
		scanf("%d%d",&a,&b);
		point_arr[i].distance = (x-a)*(x-a)+(y-b)*(y-b);
		point_arr[i].x_num=a;
		point_arr[i].y_num=b;
   }
   doSort(point_arr, 0, n-1);
  
   for(int i=0;i<n;i++){
		printf("%d %d\n",point_arr[i].x_num, point_arr[i].y_num);
   }
  
   for(int i=0;i<s;i++){
		scanf("%d%d",&a,&b);
		find(point_arr, a, b);
   }
  
}