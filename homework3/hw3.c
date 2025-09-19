#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int compare_asc(int *a, int *b)
{
    if (*a <= *b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int compare_desc(int *a, int *b)
{
    if (*a > *b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void sortBySelection(int *arr, int size, int (*compare)(int *, int *))
{
    for (int i = 0; i < size - 1; i++)
    {
        int current = i;
        for (int j = i + 1; j < size; j++)
        {
            if (compare(&arr[j], &arr[current]))
            {
                current = j;
            }
        }
        swap(&arr[i], &arr[current]);
    }
}
void sortByInsertion(int *arr, int size, int (*compare)(int *, int *))
{
}
int main()
{
    int size;
    printf("Size = ");
    scanf("%d", &size);
    int *arr = (int *)malloc(size * (sizeof(int)));
    for (int i = 0; i < size; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }
    sortBySelection(arr, size, compare_desc);
    for (int i = 0; i < size; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}