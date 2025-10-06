#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int countString(const char *string1, const char *string2)
{
    if (string1 == NULL || string2 == NULL)
        return 0;

    int length1 = strlen(string1);
    int length2 = strlen(string2);

    if (length2 == 0 || length2 > length1)
        return 0;

    int count = 0;

    for (int i = 0; i <= length1 - length2; i++)
    {
        int j;
        for (j = 0; j < length2; j++)
        {
            if (string1[i + j] != string2[j])
            {
                break;
            }
        }
        if (j == length2)
        {
            count++;
        }
    }

    return count;
}
int main()
{
    clock_t begin = clock();
    int words;

    printf("Enter the number of words: ");
    scanf("%d", &words);

    char **string_array = (char **)malloc(words * sizeof(char *));

    for (int i = 0; i < words; i++)
    {
        string_array[i] = (char *)malloc(100 * sizeof(char));
        printf("arr[%d] = ", i);
        scanf("%s", string_array[i]);
    }

    char *word_to_find = (char *)malloc(100 * sizeof(char));
    printf("Enter the word to find = ");
    scanf("%s", word_to_find);

    for (int i = 0; i < words - 1; i++)
    {
        int current = i;
        for (int j = i + 1; j < words; j++)
        {
            if (countString(string_array[j], word_to_find) < countString(string_array[current], word_to_find))
            {
                current = j;
            }
        }
        char *temp = string_array[i];
        string_array[i] = string_array[current];
        string_array[current] = temp;
    }

    for (int i = 0; i < words; i++)
    {
        printf("%s ", string_array[i]);
    }
    printf("\n");
    for (int i = 0; i < words; i++)
    {
        printf("%d ", countString(string_array[i], word_to_find));
    }
    printf("\n");

    int len_word = strlen(word_to_find);

    for (int i = 0; i < words; i++)
    {
        int len_str = strlen(string_array[i]);

        for (int j = 0; j <= len_str - len_word; j++)
        {
            int k;

            for (k = 0; k < len_word; k++)
            {

                if (string_array[i][j + k] != word_to_find[k])
                {
                    break;
                }
            }

            if (k == len_word)
            {
                printf("%d ", j);
            }
        }
        printf(" | ");
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n");
    printf("total runtime = %f\n", time_spent);
    free(string_array);
    return 0;
}