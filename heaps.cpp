#include <bits/stdc++.h>

using namespace std;

const int HEADER_INDEX = -11111111;

typedef struct heap{
    vector<int> array;
    int count;
}heap;

heap *makeheap(){
    heap *newheap = (heap*)malloc(sizeof(heap)*1);
    newheap->array.push_back(HEADER_INDEX);
    newheap->count = 0;

    return newheap;
}



void swap(int *pt1, int* pt2)
{
	int temp = *pt1;
	*pt1 = *pt2;
	*pt2 = temp;
}

void heapify(heap *heap){

    for(int i = heap->count/2; i > 1; i--){
        int nodepos = i;
        int value = heap->array[i];
        bool isheap = false;

        while(!heap && 2*nodepos < heap->count){
            int childpos = 2*nodepos;
            if(childpos < heap->count){
                if(heap->array[childpos] < heap->array[childpos+1]){childpos++;}
            }
            if(value >= heap->array[childpos]){isheap = true;}
            else{
                heap->array[nodepos] = heap->array[childpos];
                nodepos = childpos;
            }
        }
        heap->array[nodepos] = value;
    };
}

void heap_insert(heap* myheap, int value){
    myheap->array.push_back(value);
    myheap->count++;
    heapify(myheap);
}

void heap_delete(heap* heap, int key){
    int *pos = find(&(heap->array[1]), &(heap->array[heap->count]), key);
    if(key == *pos){
        swap(pos, &(heap->array[heap->count]));
        heap->count--;
    };
}

int main(){
    int size;
    scanf("%d", &size);

    heap* heap = makeheap();

    for(int i = 1; i < size+1; i++){
        int data;
        scanf("%d", &data);
        heap_insert(heap, data);
    }

    printf("array here ");
    for(int j = 1; j < size+1; j++){
        printf("%d ", heap->array[j]);
    }
    printf("\n");
}