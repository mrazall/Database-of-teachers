#include <stdio.h>
#include "teacher.h"

#include <sys/types.h>

// Функция для открытия файла
FILE *file_open()
{
    FILE *fptr = fopen("f.bin", "rb+");

    if (fptr == NULL)
    {
        // Если файл не существует, создаем его
        fptr = fopen("f.bin", "wb+");
        if (fptr == NULL)
        {
            printf("Ошибка при открытии файла.\n");
            return NULL;
        }
    }
    return fptr;
}

// Функция для чтения данных из файла
void file_read(FILE *fptr, TEACHER *teacher)
{
    if (fptr == NULL)
    {
        return;
    }
    fread(teacher, sizeof(TEACHER), 1, fptr);
}

// Функция для записи данных в файл
void file_write(FILE *fptr, TEACHER *teacher)
{
    if (fptr == NULL)
    {
        return;
    }
    fwrite(teacher, sizeof(TEACHER), 1, fptr);
}

// Функция для определения позиции в файле по идентификатору
int file_locate(FILE *fptr, int id)
{
    if (fptr == NULL)
    {
        return 0;
    }
    if (id == 0)
    {
        // Если идентификатор равен 0, перемещаем указатель в конец файла
        fseek(fptr, 0, SEEK_END);
        return 1;
    }
    TEACHER teacher;
    fseek(fptr, 0, SEEK_SET);
    while (!feof(fptr))
    {
        file_read(fptr, &teacher);
        if (feof(fptr))
        {
            break;
        }
        if (teacher.id == id)
        {
            // Если идентификатор найден, перемещаем указатель назад на размер структуры
            fseek(fptr, -((long)sizeof(TEACHER)), SEEK_CUR);
            return 1;
        }
    }
    return 0;
}

// Функция для определения размера файла (количество записей)
int file_size(FILE *fptr)
{
    int i = 0;
    TEACHER teacher;
    fseek(fptr, 0, SEEK_SET);
    while (!feof(fptr))
    {
        file_read(fptr, &teacher);
        if (!feof(fptr))
            i++;
    }
    return i;
}

// Функция для удаления записи из файла
void file_delete(FILE *fptr)
{
    if (fptr == NULL)
    {
        return;
    }
    TEACHER teacher;
    file_read(fptr, &teacher);
    while (!feof(fptr))
    {
        file_read(fptr, &teacher);
        if (!feof(fptr))
        {
            // Перемещаем указатель назад на размер двух записей, записываем текущую запись поверх предыдущей,
            // а затем перемещаем указатель на следующую запись
            fseek(fptr, -((long)sizeof(TEACHER) * 2), SEEK_CUR);
            file_write(fptr, &teacher);
            fseek(fptr, sizeof(TEACHER), SEEK_CUR);
        }
    }
    ftruncate(fileno(fptr), (file_size(fptr) - 1) * (long)sizeof(TEACHER));
}

// Функция для определения максимального идентификатора в файле
int file_max_id(FILE *fptr)
{
    int max = 0;
    TEACHER teacher;
    while (!feof(fptr))
    {
        file_read(fptr, &teacher);
        if (teacher.id > max)
        {
            max = teacher.id;
        }
    }
    return max;
}

// Функция для закрытия файла
void file_close(FILE *fptr)
{
    if (fptr == NULL)
    {
        return;
    }
    fclose(fptr);
}

// Функция для загрузки данных из файла в массив структур
void file_load(FILE *fptr, TEACHER *db)
{
    fseek(fptr, 0, SEEK_SET);
    TEACHER teacher;
    int i = 0;
    while (!feof(fptr))
    {
        file_read(fptr, &teacher);
        if (!feof(fptr))
        {
            db[i] = teacher;
            i++;
        }
    }
}

// Функция для сохранения данных из массива структур в файл
void file_save(FILE *fptr, TEACHER *db, int db_size)
{
    fseek(fptr, 0, SEEK_SET);
    fwrite(db, sizeof(TEACHER), db_size, fptr);
}
