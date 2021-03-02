#define MAX_SIZE 256
#define MAX_STR 256
#define NUM_SUBJECTS 15
#include <ctype.h>

void clearArray(char *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = '\0';
    }
}

void enterArrayName(char *array)
{
    char buffer;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        buffer = getchar();
        if (buffer == '\n')
        {
            array[i] = ' ';
            break;
        }
        else
        {
            array[i] = buffer;
        }
    }
}

int checkArrayName(char *array)
{
    int k = strlen(array)-1;
    for (int i = 0; i < k; i++)
    {
        if (!isalpha(array[i]))
        {
            printf("Нет такого имени. Попробуйте ещё раз\n");
            clearArray(array, MAX_SIZE);
            return 0;
        }
    }
    return 1;
}

void clearALL(char *all_string, char *num_Group, char *email)
{
    clearArray(all_string, MAX_STR);
    clearArray(num_Group, MAX_SIZE);
    clearArray(email, MAX_SIZE);
}

void swapNumbers(int *num1, int *num2)
{
    char buffer = '\0';
    buffer = *num1;
    *num1 = *num2;
    *num2 = buffer;
}

void sort(int *num, int size)
{
    int min, buff;
    for (int i = 0; i < size - 1; i++)
    {
        min = i; 
        for (int j = i + 1; j < size; j++)  
        {
            if (num[j] < num[min]) 
                min = j;       
        }
        buff = num[i];      
        num[i] = num[min];
        num[min] = buff;
    }
}