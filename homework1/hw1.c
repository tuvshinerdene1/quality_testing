#include <stdio.h>
#include <stdlib.h>
#include <string.h>
float converterToDec(char *num1, int sys1)
{
    if (sys1 <= 16)
    {
        float dec = 0;
        int length = strlen(num1);
        float base = 1.0;
        int dotIndex = -1;
        int intLimit = length;
        int current;
        for (int i = 0; i < length; i++)
        {
            if (num1[i] == '.')
            {
                dotIndex = i;
                break;
            }
        }
        if (dotIndex != -1)
        {
            intLimit = dotIndex;
        }

        for (int i = intLimit - 1; i >= 0; i--)
        {
            if (num1[i] >= '0' && num1[i] <= '9')
            {
                current = num1[i] - '0';
            }
            if (num1[i] >= 'A' && num1[i] <= 'F')
            {
                current = num1[i] - 'A' + 10;
            }
            dec += current * base;
            base *= sys1;
        }
        if (dotIndex != -1)
        {
            base = 1.0 / sys1;
            for (int i = dotIndex + 1; i < length; i++)
            {
                if (num1[i] >= '0' && num1[i] <= '9')
                {
                    current = num1[i] - '0';
                }
                if (num1[i] >= 'A' && num1[i] <= 'F')
                {
                    current = num1[i] - 'A' + 10;
                }
                dec += current * base;
                base /= sys1;
            }
        }

        return dec;
    }
    else
    {
        printf("Out of bound\n");
        return -1;
    }
}

char *converter(float dec, int sys2)
{
    if (dec == 0)
    {
        char *result = (char *)malloc(2);
        strcpy(result, "0");
        return result;
    }

    char temp[100];
    int i = 0;
    int tempdigit = (int)dec;
    while (dec > 0)
    {
        int remainder = tempdigit % sys2;
        if (remainder < 10)
        {
            temp[i] = remainder + '0';
        }
        else
        {
            temp[i] = remainder - 10 + 'A';
        }
        i++;
        tempdigit /= sys2;
    }
    float fraction = dec - (int)dec;
    if (fraction != 0)
    {
        temp[i] = '.';
        i++;
    }
    while (fraction != 0)
    {
        int digit = (int)fraction * sys2;
        printf("%d\n", digit);

        if (digit < 10)
        {
            temp[i] = digit + '0';
        }
        else
        {
            temp[i] = digit - 10 + 'A';
        }

        i++;
        fraction -= digit;
    }

    temp[i] = '\0';

    int length = strlen(temp);
    char *result = (char *)malloc(length + 1);
    for (int j = 0; j < length; j++)
    {
        result[j] = temp[length - 1 - j];
    }
    result[length] = '\0';

    return result;
}

int main()
{
    char num[100];
    int numsys, numsys2;

    printf("Enter number: ");
    scanf("%s", num);

    printf("Enter its numeric system (base): ");
    scanf("%d", &numsys);

    printf("%f\n", converterToDec(num, numsys));

    printf("Enter the numeric system to convert to (base): ");
    scanf("%d", &numsys2);

    if (numsys < 2 || numsys > 16 || numsys2 < 2 || numsys2 > 16)
    {
        printf("Error: Numeric systems must be between 2 and 16.\n");
        return 1;
    }

    int dec = converterToDec(num, numsys);

    if (dec == -1)
    {
        printf("Error: Invalid number for the given numeric system.\n");
        return 1;
    }

    char *final_result = converter(dec, numsys2);

    printf("The number %s in base %d is %s in base %d.\n", num, numsys, final_result, numsys2);

    free(final_result);

    return 0;
}