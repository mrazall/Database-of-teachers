#include <stdio.h>
#include "file_work.h"
#include <string.h>
#include <stdlib.h>

char filename[] = "f.bin";
TEACHER *db;
typedef enum
{
    SORT_BY_LASTNAME = 1,
    SORT_BY_FIRSTNAME,
    SORT_BY_SURNAME,
    SORT_BY_KAFEDRA,
    SORT_BY_POST,
    SORT_BY_ADRESS,
    SORT_BY_PHONE,
    SORT_BY_COURSES,
    SORT_BY_ID
} ENUM_SORT_BY;

// Добавления преподавателя в базу
void teacher_create(TEACHER *teacher)
{
    FILE *fptr = file_open();
    teacher->id = file_max_id(fptr) + 1;
    file_locate(fptr, 0);
    file_write(fptr, teacher);
    file_close(fptr);
}
// Удаление учителя из базы
void teacher_delete(int id)
{
    FILE *fptr = file_open();
    if (file_locate(fptr, id))
    {
        file_delete(fptr);
    }
    file_close(fptr);
}
// Функция для удаления \n в конце строк
void string_strip(char *str)
{
    int n = strlen(str);
    if (str[n - 1] == '\n')
    {
        str[n - 1] = '\0';
    }
}
//Чистка записей от \n
void teacher_strip(TEACHER *teacher)
{
    string_strip(teacher->lastname);
    string_strip(teacher->firstname);
    string_strip(teacher->surname);
    string_strip(teacher->kafedra);
    string_strip(teacher->post);
    string_strip(teacher->adress);
    string_strip(teacher->phone);
    string_strip(teacher->courses);
}
// Ввод преподавателя
void teacher_input(TEACHER *teacher)
{

    while ((getchar()) != '\n')
        ;
    printf("\tФамилия: ");
    fgets(teacher->lastname, 20, stdin);
    printf("\tИмя: ");
    fgets(teacher->firstname, 20, stdin);
    printf("\tОтчество: ");
    fgets(teacher->surname, 20, stdin);
    printf("\tКафедра: ");
    fgets(teacher->kafedra, 30, stdin);
    printf("\tДолжность: ");
    fgets(teacher->post, 30, stdin);
    printf("\tАдрес : ");
    fgets(teacher->adress, 30, stdin);
    printf("\tНомер телефона: ");
    fgets(teacher->phone, 20, stdin);
    printf("\tЧитаемые курсы: ");
    fgets(teacher->courses, 300, stdin);
    teacher_strip(teacher);
}
// Запись в файл
void teacher_write(TEACHER *teacher)
{
    FILE *fptr = file_open();
    file_locate(fptr, teacher->id);
    file_write(fptr, teacher);
    file_close(fptr);
}
// Функция для menu, в которой уже вызываются функции низшей структуры tacher
void menu_create()
{
    TEACHER teacher;
    teacher_input(&teacher);
    teacher_create(&teacher);
}
// Функция для menu, удаляющая
void menu_delete()
{
    TEACHER teacher;
    int id, i = 0;

    printf("Введит id:");
    scanf("%d", &id);

    teacher_delete(id);
}
// Функция для сравнения записи по заданному типу
int cmp(TEACHER *a, TEACHER *b, ENUM_SORT_BY type)
{
    switch (type)
    {
    case SORT_BY_ID:
        return (a->id < b->id ? -1 : (a->id > b->id ? 1 : 0));
    case SORT_BY_FIRSTNAME:
        return strcmp(a->firstname, b->firstname);
    case SORT_BY_LASTNAME:
        return strcmp(a->lastname, b->lastname);
    case SORT_BY_SURNAME:
        return strcmp(a->surname, b->surname);
    case SORT_BY_KAFEDRA:
        return strcmp(a->kafedra, b->kafedra);
    case SORT_BY_POST:
        return strcmp(a->post, b->post);
    case SORT_BY_ADRESS:
        return strcmp(a->adress, b->adress);
    case SORT_BY_PHONE:
        return strcmp(a->phone, b->phone);
    case SORT_BY_COURSES:
        return strcmp(a->courses, b->courses);
    default:
        return (a->id < b->id ? -1 : (a->id > b->id ? 1 : 0));
    }
}
// Сортировка записей пузырьком
void quick_sort(TEACHER *db, ENUM_SORT_BY type, int db_size)
{
    for (int i = 0; i < db_size - 1; i++)
    {
        for (int j = i + 1; j < db_size; j++)
        {
            if (cmp(&db[i], &db[j], type) > 0)
            {
                TEACHER tmp = db[i];
                db[i] = db[j];
                db[j] = tmp;
            }
        }
    }
}
// Функция красивого вывода
void teacher_print(TEACHER *teacher)
{
    printf("%-3d │ %-10s │ %-10s │ %-17s │ %-15s │ %-30s \n"
           "    ├────────────┴────────────┼───────────────────┼─────────────────┴───────────────────────────────\n"
           "    │ %-23s │ %-17s │ %-40s\n",
           teacher->id,
           teacher->lastname,
           teacher->firstname,
           teacher->surname,
           teacher->phone,
           teacher->adress,
           teacher->kafedra,
           teacher->post,
           teacher->courses);
}
// Поиск записи в файле
void teacher_find(int k, char *str)
{
    FILE *fptr = file_open();
    TEACHER teacher;
    while (!feof(fptr))
    {
        file_read(fptr, &teacher);
        if (!feof(fptr))
        {
            switch (k)
            {
            case 1:

                if (strstr(teacher.lastname, str) != 0)
                {
                    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
                    teacher_print(&teacher);
                    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
                }
                break;
            case 2:

                if (strstr(teacher.firstname, str) != 0)
                {
                    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
                    teacher_print(&teacher);
                    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
                }
                break;
            case 3:

                if (strstr(teacher.surname, str) != 0)
                {
                    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
                    teacher_print(&teacher);
                    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
                }
                break;
            case 4:

                if (strstr(teacher.kafedra, str) != 0)
                {
                    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
                    teacher_print(&teacher);
                    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
                }
                break;
            case 5:

                if (strstr(teacher.post, str) != 0)
                {
                    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
                    teacher_print(&teacher);
                    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
                }
                break;
            case 6:

                if (strstr(teacher.adress, str) != 0)
                {
                    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
                    teacher_print(&teacher);
                    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
                }
                break;
            case 7:

                if (strstr(teacher.phone, str) != 0)
                {
                    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
                    teacher_print(&teacher);
                    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
                }
                break;
            case 8:

                if (strstr(teacher.courses, str) != 0)
                {
                    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
                    teacher_print(&teacher);
                    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
                }
                break;
            case 9:

                if (teacher.id == atoi(str))
                {
                    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
                    teacher_print(&teacher);
                    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
                }
                break;
            default:
                printf("Попробуйте другой код команды");
                break;
            }
        }
    }
}

void print_db(TEACHER *db, int size)
{
    for (int i = 0; i < size; i++)
    {
        teacher_print(&db[i]);
    }
}
// Функция для сортировки по заданному типу
void teacher_sort(int k)
{

    FILE *fptr = file_open();
    int db_size = file_size(fptr);
    TEACHER *db = (TEACHER *)malloc(sizeof(TEACHER) * db_size);
    file_load(fptr, db);
    quick_sort(db, k, db_size);
    file_save(fptr, db, db_size);
    free(db);
    file_close(fptr);
}
// Фунция для menu, которая определяет тип сортировки
void menu_sort()
{
    int k;
    printf("Выберите по какому полю будет произведена сортировка:\n\t"
           "1) Фамилия\n\t"
           "2) Имя\n\t"
           "3) Отчество\n\t"
           "4) Кафедра\n\t"
           "5) Должность\n\t"
           "6) Домашний адрес\n\t"
           "7) Номер телефона\n\t"
           "8) Читаемые курсы\n\t"
           "9) ID\n "
           "Ваш выбор: ");
    scanf("%d", &k);
    teacher_sort(k);
}
// Функция для menu, поиск записи по определенному полю
void menu_find()
{
    int k;
    printf("Выберите по какому полю будет произведен поиск:\n\t"
           "1) Фамилия\n\t"
           "2) Имя\n\t"
           "3) Отчество\n\t"
           "4) Кафедра\n\t"
           "5) Должность\n\t"
           "6) Домашний адрес\n\t"
           "7) Номер телефона\n\t"
           "8) Читаемые курсы\n\t"
           "9) ID\n "
           "Ваш выбор: ");
    scanf("%d", &k);
    printf("Строка для поиска: ");
    while ((getchar()) != '\n')
        ;
    char str[300];
    fgets(str, 300, stdin);
    string_strip(str);
    teacher_find(k, str);
}
// Функция для menu, редактирующая запись
void menu_edit()
{
    TEACHER teacher;
    printf("Введите id пользователя: ");
    scanf("%d", &teacher.id);
    teacher_input(&teacher);
    teacher_write(&teacher);
}
// Функция вывода всего файла
void teacher_print_file()
{
    FILE *fptr = file_open();
    TEACHER teacher;
    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
    printf("%-3s │ %-10s │ %-10s │ %-17s │ %-15s │ %-30s \n"
           "    ├────────────┴────────────┼───────────────────┼─────────────────┴───────────────────────────────\n"
           "    │ %-23s │ %-17s │ %-40s\n",
           "ID",
           "Фамилия",
           "Имя",
           "Отчество",
           "Телефон",
           "Домашний адрес",
           "Кафедра",
           "Должность",
           "Читаемые курсы");
    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
    printf("────┬────────────┬────────────┬───────────────────┬─────────────────┬───────────────────────────────\n");
    while (!feof(fptr))
    {
        file_read(fptr, &teacher);
        if (!feof(fptr))
        {

            teacher_print(&teacher);
            printf("────┼────────────┬────────────┼───────────────────┼─────────────────┬───────────────────────────────\n");
        }
    }
    printf("────┴─────────────────────────┴───────────────────┴─────────────────────────────────────────────────\n");
}
// Само меню
void menu()
{
    while (1)
    {
        printf("-----------------------------\n"
               "Выберите дейстиве:\n\t"
               "1) Добавить запись в базу\n\t"
               "2) Удалить запись из базы\n\t"
               "3) Поиск записи\n\t"
               "4) Редактирование записи в базе\n\t"
               "5) Сортировка записей в базе\n\t"
               "6) Вывод базы данных\n"
               "Ваш выбор: ");
        int k = 0;
        scanf("%d", &k);
        switch (k)
        {
        case 1:
            menu_create();
            break;
        case 2:
            menu_delete();
            break;
        case 3:
            menu_find();
            break;
        case 4:
            menu_edit();
            break;
        case 5:
            menu_sort();
            break;
        case 6:
            teacher_print_file();
            break;
        default:
            break;
        }
    }
}

int main()
{
    menu();
    return 0;
}