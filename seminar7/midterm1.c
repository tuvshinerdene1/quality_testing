#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_SIZE 101
int hashTable[HASH_SIZE] = {0};
int hash(int key)
{
    return abs(key) % HASH_SIZE;
}
bool check_and_insert(int key)
{
    int index = hash(key);
    int original_index = index;
    while (hashTable[index] != 0)
    {
        if (hashTable[index] == key)
        {
            return false;
        }
        index = (index + 1) % HASH_SIZE;
        if (index == original_index)
        {
            return false;
        }
    }
    hashTable[index] = key;
    return true;
}
int main()
{
    int n;
    printf("Enter array size (n): ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid size input or n <= 0.\n");
        return 1;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));
    if (arr == NULL || result == NULL)
    {
        printf("Memory allocation failed.\n");
        free(arr);
        free(result);
        return 1;
    }
    printf("\nInput elements:\n");
    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }
    int unique_count = 0;
    for (int i = 0; i < n; i++)
    {
        if (check_and_insert(arr[i]))
        {
            result[unique_count] = arr[i];
            unique_count++;
        }
    }
    printf("\nUnique elements (Original Order, O(N) average): ");
    for (int i = 0; i < unique_count; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(arr);
    free(result);
    return 0;
}