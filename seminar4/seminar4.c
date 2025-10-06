#include <stdio.h>
#include <stdlib.h>
#include <time.h>
long long decToBin(int num)
{
    long long digit = 1;
    long long result = 0;
    unsigned int temp = num;
    while (temp > 0)
    {

        result += digit * (temp % 2);
        digit *= 10;
        temp /= 2;
    }
    return result;
}
int countOne(long long num)
{
    int count = 0;
    unsigned int temp = num;
    while (temp > 0)
    {
        if (temp & 1)
        {
            count++;
        }
        temp >>= 1;
    }
    return count;
}
int main()
{
    clock_t begin = clock();
    int size, *arr;
    printf("Enter size: ");
    scanf("%d", &size);
    arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < size - 1; i++)
    {
        int current = i;
        for (int j = i + 1; j < size; j++)
        {
            if (countOne(arr[j]) < countOne(arr[current]))
            {
                current = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[current];
        arr[current] = temp;
    }

    for (int i = 0; i < size; i++)
    {
        printf("%lld ", decToBin(arr[i]));
    }
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("total runtime = %f\n", time_spent);
    free(arr);
    return 0;
}