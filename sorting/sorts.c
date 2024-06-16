#include <stdio.h>
#include <stdlib.h>

void swap(int *pt1, int* pt2)
{
	int temp = *pt1;
	*pt1 = *pt2;
	*pt2 = temp;
}

void bubblesort(int *array, int size)
{


	for(int i = 0; i < size; i++){
		int* biggest = &array[0];

		for(int j = 1; j < (size - i + 1); j++){
			if(array[j] <= *biggest){
				swap(biggest, &array[j]);
			}
			else{
				biggest = &array[j];
			}
		}
	}
}

void selection_sort(int *array, int size)
{
	for(int i = 0; i < size; i++){
		int* smallest = &array[i];
		for(int j = i+1; j < size - i; j++){
			if(array[j] < *smallest){
				smallest = &array[j];
			}
		}
		swap(&array[i], smallest);
	} 
}

void insertionsort(int *array, int size)
{
	for(int i = 1; i < size - 1; i++){
		int* unordered = &array[i];
		int j = i - 1;
		while(j >= 0 && array[j] > *unordered){
			swap(unordered, &array[j]);
			j--;
		}
	}
}

void merge(int *array, int left, int right)
{
	int array_size = (right - left + 1);
	int middle = (array_size - 1)/2;
	printf("middle: %d \n", middle);
	int* temp = (int *)malloc(sizeof(int) * array_size);
	
	for(int i = 0; i < array_size; i++){
		printf("left: %d, i: %d, left + i: %d \n", left, i, (left+i));
		temp[i] = array[left + i];
	}


	for(int i = left; i <= right; i++) {printf("%d ", array[i]);}; printf("\n"); // debug print	
	int i1 = 0; int i2 = middle + 1;


	for(int curr = left; curr <= right; curr++){
		if(i1 == middle + 1){
			array[curr] = temp[i2];
			i2++;
		}
		else if (i2 >= array_size) {
			array[curr] = temp[i1];
			i1++;
		}

		else if (temp[i1] <= temp[i2]) {
			array[curr] = temp[i1];
			i1++;
		}
		else{
			array[curr] = array[left +i2];	
			i2++;
		}



	}

	for(int i = left; i <= right; i++) {printf("%d ", array[i]);}; printf("\n"); // debug print	
	free(temp);
}

void mergesort(int *array, int left, int right)
{	
	if(left < right){
		printf("teste \n");
		int middle = (left + right)/2;
//		printf("left: %d, middle: %d, right: %d \n", left, middle, right); // debug print
//		for(int i = left; i <= right; i++) {printf("%d ", array[i]);}; printf("\n"); // debug print	
		mergesort(array, left, middle);
		mergesort(array, middle + 1, right);
		merge(array, left, right);
	}
}

int main()
{
	int size;
	scanf("%d", &size);
	int* array = malloc(sizeof(int) + size);
	for(int i = 0; i < size; i++){
		scanf("%d", &array[i]);
		printf("%d \n", array[i]);
	}

	mergesort(array, 0, size-1);
	for(int i = 0; i < size; i++){
		printf("%d", array[i]);
		printf(" ");
	};
	free(array);
	return 0;
}
