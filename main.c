#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "function.c"
#include <windows.h>
#include <locale.h>
#define MAX_SIZE 256
#define MAX_STR 256
#define NUM_SUBJECTS 15

#define GROUP_CONST !isalpha((unsigned int)student.num_Group[0]) || !isalpha((unsigned int)student.num_Group[2]) || !isalpha((unsigned int)student.num_Group[7]) || !isdigit(student.num_Group[1]) || !isdigit(student.num_Group[4]) || !isdigit(student.num_Group[5]) || !isdigit(student.num_Group[6]) || !isdigit(student.num_Group[9]) || !isdigit(student.num_Group[10])

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    if (GetConsoleCP() != 1251)
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
    }

    FILE *files = NULL;
    int finish = 0, dog = 0, size = 0, check = 0, count = 0;
    float sum = 0.0;
    int *massive;
    char buffer_array[MAX_STR];
    char buffer;
    struct studentstruct
    {
        char all_string[MAX_STR];
        char name2[MAX_SIZE];
        char name1[MAX_SIZE];
        char name3[MAX_SIZE];
        char num_Group[MAX_SIZE];
        char email[MAX_SIZE];
        int marks_size;
        float marks[MAX_STR];
        char result_marks[MAX_STR];
        float middle_mark;
        int *array; //динамическое выделение памяти
        char s_array[MAX_SIZE];
    };
    struct studentstruct student;
    clearALL(student.all_string, student.num_Group, student.email);
    clearArray(student.name2, MAX_SIZE);
    clearArray(student.name1, MAX_SIZE);
    clearArray(student.name3, MAX_SIZE);
    clearArray(student.s_array, MAX_SIZE);
    clearArray(student.result_marks, MAX_SIZE);
    system("cls");
    do
    {
        printf("\n1 - Ввести информацию о студенте в файл\n2 - Очистить файл\n3 - Вывести содержимое файла\n4 - Выход из программы\n");
        printf("Выберите действие: ");
        char inp = getchar();
        fflush(stdin);
        printf("\n");
        switch (inp)
        {
        case '1':
        {
            clearALL(student.all_string, student.num_Group, student.email);
            count = 0;
            int i = 0;
            files = fopen("database.txt", "a");
            printf("Введите фамилию:\n");
            do
            {
                enterArrayName(student.name2);
            } while (checkArrayName(student.name2) == 0);
            printf("Введите имя\n");
            do
            {
                enterArrayName(student.name1);
            } while (checkArrayName(student.name1) == 0);
            printf("Введите отчество\n");
            do
            {
                enterArrayName(student.name3);
            } while (checkArrayName(student.name3) == 0);
            student.name2[0] = toupper(student.name2[0]);
            student.name1[0] = toupper(student.name1[0]);
            student.name3[0] = toupper(student.name3[0]);
            buffer = '\0';
            fflush(stdin);

            printf("Введите номер группы\n");
            do
            {
                clearArray(student.num_Group, MAX_SIZE);
                fgets(student.num_Group, sizeof(student.num_Group), stdin);
                if (GROUP_CONST)
                {
                    printf("Группа введена неправильно. Попробуйте ещё раз.\n");
                }
            } while (GROUP_CONST);
            student.num_Group[0] = toupper(student.num_Group[0]);
            student.num_Group[2] = toupper(student.num_Group[2]);
            student.num_Group[7] = toupper(student.num_Group[7]);
            fflush(stdin);
            printf("Введите почту\n");
            do
            {
                clearArray(student.email, MAX_SIZE);
                buffer = '\0';
                i = 0;
                dog = 0;
                clearArray(student.email, MAX_SIZE);

                do
                {
                    buffer = getchar();
                    student.email[i] = buffer;
                    if (buffer == '@')
                    {
                        dog++;
                    }
                    i++;
                } while (buffer != '\n');
                int eLen = strlen(student.email) - 1;

                if ((student.email[0] != '@') && (student.email[eLen - 1] != '@') && (student.email[eLen - 2] != '@') && ((student.email[eLen - 3] == '.') || (student.email[eLen - 4] == '.')) && (student.email[eLen - 4] != '@') && (dog == 1))
                {
                    count = 1;
                }
                else
                {
                    clearArray(student.email, MAX_SIZE);
                    printf("Такой почты не существует. Попробуйте ещё раз.\n");
                }
            } while (count == 0);
            fflush(stdin);
            sum = 0;
            printf("Введите количество оценок студента: ");
            do
            {
                scanf("%d", &student.marks_size);
                if (student.marks_size < 0 || student.marks_size > 256) printf("Количество оценок должно быть положительным и в пределах разумного.");
            } while (student.marks_size < 0 || student.marks_size > 256);
            for (int b = 0; b < student.marks_size; b++)
            {
                do
                {
                    printf("Введите %d оценку: ", b + 1);
                    scanf("%f", &student.marks[b]);
                    if (student.marks[b] < 1 || student.marks[b] > 5)
                        printf("Оценка не может быть меньше 1 или больше 5, попробуйте ещё раз.\n");
                } while (student.marks[b] < 1 || student.marks[b] > 5);
                sum += student.marks[b];
            }
            student.middle_mark = sum / student.marks_size;

            fflush(stdin);
            printf("Введите размер массива для сортировки\n");
            do{
            scanf("%d", &size);
            if (size<0) printf("Массив должен содержать хотя бы один элемент");
            }while(size < 0); 
            fflush(stdin);
            massive = (int *)malloc(size * sizeof(int));
            printf("Введите элементы массива:\n");
            for (i = 0; i < size; i++)
            {
                printf("a[%d] = ", i + 1);
                scanf("%d", &massive[i]);
            }

            sort(massive, size);

            clearArray(buffer_array, MAX_STR);
            for (i = 0; i < size; i++)
            {
                sprintf(buffer_array, "%d ", massive[i]);
                strcat(student.s_array, buffer_array);
            }

            clearArray(buffer_array, MAX_STR);

            for (i = 0; i < student.marks_size; i++)
            {
                sprintf(buffer_array, "%.0f ", student.marks[i]);
                strcat(student.result_marks, buffer_array);
            }
            fflush(stdin);
            strcat(student.all_string, "Имя студента:");
            strcat(student.all_string, student.name2);
            strcat(student.all_string, student.name1);
            strcat(student.all_string, student.name3);
            strcat(student.all_string, student.num_Group);
            strcat(student.all_string, " почта студента:");
            strcat(student.all_string, student.email);
            strcat(student.all_string, " оценки студента: ");
            strcat(student.all_string, student.result_marks);
            strcat(student.all_string, " средняя оценка студента: ");
            sprintf(buffer_array, "%.2f ", student.middle_mark);
            strcat(student.all_string, buffer_array);
            strcat(student.all_string, " Отсортированный массив: ");
            strcat(student.all_string, student.s_array);
            fprintf(files, "%s\n", student.all_string);
            fclose(files);
            clearArray(student.all_string, MAX_STR);
            break;
        }
        case '2':
        {
            clearALL(student.all_string, student.num_Group, student.email);
            files = fopen("database.txt", "w");
            fclose(files);
            break;
        }
        case '3':
        {
            files = fopen("database.txt", "r");
            printf("Список студентов:\n");
            while (!feof(files))
            {
                fgets(student.all_string, MAX_SIZE, files);
                if (!feof(files))
                {
                    int size = strlen(student.all_string);
                    for (int i = 0; i < size; i++)
                    {
                        printf("%c", student.all_string[i]);
                    }
                }
            }
            fclose(files);
            break;
        }
        case '4':
        {
            finish = 1;
            break;
        }
        default:
        {
            printf("Ошибка, нет такой команды\nПопробуйте ещё раз.");
            break;
        }
        }

    } while (finish == 0);
}