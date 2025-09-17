#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void getMinMax(int *arr, int size, int *min, int *max)
{
    int start;
    int l_min, l_max;
    if (size % 2)
    {
        l_min = arr[0];
        l_max = arr[0];
        start = 1;
    }
    else
    {
        if (arr[0] >= arr[1])
        {
            l_max = arr[0];
            l_min = arr[1];
        }
        else
        {
            l_max = arr[1];
            l_min = arr[0];
        }
        start = 2;
    }
    for (int i = start; i < size - 1; i += 2)
    {
        if (arr[i] <= arr[i + 1])
        {
            if (arr[i] < l_min)
            {
                l_min = arr[i];
            }
            if (arr[i + 1] > l_max)
            {
                l_max = arr[i + 1];
            }
        }
        else
        {
            if (arr[i + 1] < l_min)
            {
                l_min = arr[i + 1];
            }
            if (arr[i] > l_max)
            {
                l_max = arr[i];
            }
        }
    }
    *min = l_min;
    *max = l_max;
}

int main()
{
    clock_t begin = clock();

    int size;
    int min, max;
    printf("size = ");
    scanf("%d", &size);
    int *arr;
    arr = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }
    getMinMax(arr, size, &min, &max);

    printf("min = %d\nmax = %d\n", min, max);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("runtime = %f\n", time_spent);
    free(arr);
    return 0;
}
