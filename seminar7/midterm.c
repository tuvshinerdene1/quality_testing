#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    printf("n = ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    int *sub = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }
    sub[0] = arr[0];
    int size = 1;
    for (int i = 1; i < n; i++)
    {
        int j;
        for (j = 0; j < size; j++)
        {
            if (arr[i] == sub[j])
            {
                break;
            }
        }
        if (j == size)
        {
            sub[j] = arr[i];
            size++;
        }
    }
    for (int i = 0; i < size; i++)
    {
        printf("%d ", sub[i]);
    }
    free(arr);
    free(sub);
    return 0;
}