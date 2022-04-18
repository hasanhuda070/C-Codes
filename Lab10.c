//Showad Huda COP3502C Lab 10

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXVAL 1000000

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n-1; i++)
	for (j = 0; j < n-i-1; j++)
	if (arr[j] > arr[j+1])
		swap(&arr[j], &arr[j+1]);
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
  
	for (i = 0; i < n-1; i++)
	{
		min_idx = i;
		for (j = i+1; j < n; j++)
		if (arr[j] < arr[min_idx])
		min_idx = j;
  
		swap(&arr[min_idx], &arr[i]);
	}
}

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;
  
	while (j >= 0 && arr[j] > key) {
		arr[j + 1] = arr[j];
		j = j - 1;
	}
	arr[j + 1] = key;
	}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];
  
	for (i = 0; i < n1; i++)
	L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
	R[j] = arr[m + 1+ j];
  
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
	else
	{
		arr[k] = R[j];
		j++;
	}
	k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
	j++;
	k++;
	}
}
  
void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l+(r-l)/2;
  
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
  
		merge(arr, l, m, r);
	}
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);
  
	for (int j = low; j <= high- 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
  
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void arrayCopy(int arr[], int temp[], int n)
{
	int i,j;
	for(i=0;i<n;i++)
	temp[i] = arr[i];
}

long timediff(clock_t t1, clock_t t2)
{
	long elapsed;
	elapsed = ((double)t2-t1) / CLOCKS_PER_SEC *1000;
	return elapsed;
}

void amountTime(int n)
{
	clock_t t1,t2;
	srand(time(0));
	int arr[n],i;
	for(i=0;i<n;i++)
	arr[i] = rand();
	int temp[n];
	arrayCopy(arr,temp,n);

	t1 = clock();
	bubbleSort(temp,n);
	t2 = clock();
	printf("\nSorting %d values takes %ld milliseconds for Bubble Sort \n",n,timediff(t1,t2));

	arrayCopy(arr,temp,n);

	t1 = clock();
	selectionSort(temp,n);
	t2 = clock();
	printf("\nSorting %d values takes %ld milliseconds for Selection Sort \n",n,timediff(t1,t2));

	arrayCopy(arr,temp,n);

	t1 = clock();
	insertionSort(temp,n);
	t2 = clock();
	printf("\nSorting %d values takes %ld milliseconds for Insertion Sort \n",n,timediff(t1,t2));

	arrayCopy(arr,temp,n);

	t1 = clock();
	quickSort(temp,0,n-1);
	t2 = clock();
	printf("\nSorting %d values takes %ld milliseconds for Quick Sort \n",n,timediff(t1,t2));

	arrayCopy(arr,temp,n);

	t1 = clock();
	mergeSort(temp,0,n-1);
	t2 = clock();
	printf("\nSorting %d values takes %ld milliseconds for Merge Sort \n",n,timediff(t1,t2));
}

int main()
{
amountTime(10000);
amountTime(20000);
amountTime(30000);
amountTime(40000);
amountTime(50000);
amountTime(100000);
return 0;
}


