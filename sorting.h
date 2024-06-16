#include <stdlib.h>
#include <stdio.h>

int* swap(int* array, int pos1, int pos2)
{
    int* ret = (int *)malloc(sizeof(array));

    int array_lenght = (int)(sizeof(ret)/sizeof(ret[0])) - 1;

    for(int i = 0; i < array_lenght; i ++)
    {
        ret[i] = array[i];
    }

    printf("%d", ret[0]);

    return ret;
}