#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("arr[%d] = %d , ", i, arr[i]);
    }
    printf("\n");
}
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
    print(arr, size);
    clock_t begin = clock();

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
        print(arr, size);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sorted in %f\n", time_spent);
}
void sortByInsertion(int *arr, int size, int (*compare)(int *, int *))
{
    print(arr, size);
    clock_t begin = clock();
    for (int i = 1; i < size; i++)
    {
        int j = i;
        while (j > 0 && compare(&arr[j], &arr[j - 1]))
        {
            swap(&arr[j], &arr[j - 1]);
            print(arr, size);
            j -= 1;
        }
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sorted in %f\n", time_spent);
}
int main()
{
    clock_t begin = clock();
    int size, choice, choice1;
    printf("Size = ");
    scanf("%d", &size);
    int *arr = (int *)malloc(size * (sizeof(int)));
    for (int i = 0; i < size; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }
    while (1)
    {
        printf("1.print 2.sort by selection 3. sort by insertion 4.exit\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            print(arr, size);
        }
        else if (choice == 2)
        {
            printf("1. ascending order 2. descending order\n");
            scanf("%d", &choice1);
            if (choice1 == 1)
            {
                sortBySelection(arr, size, compare_asc);
            }
            else if (choice1 == 2)
            {
                sortBySelection(arr, size, compare_desc);
            }
            else
            {
                printf("Invalid input\n");
            }
        }

        else if (choice == 3)
        {
            printf("1. ascending order 2. descending order\n");
            scanf("%d", &choice1);
            if (choice1 == 1)
            {
                sortByInsertion(arr, size, compare_asc);
            }
            else if (choice1 == 2)
            {
                sortByInsertion(arr, size, compare_desc);
            }
            else
            {
                printf("Invalid input\n");
            }
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            printf("Invalid input\n");
        }
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("total runtime = %f\n", time_spent);
    free(arr);
    return 0;
}