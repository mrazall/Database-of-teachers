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

// ���������� �९�����⥫� � ����
void teacher_create(TEACHER *teacher)
{
    FILE *fptr = file_open();
    teacher->id = file_max_id(fptr) + 1;
    file_locate(fptr, 0);
    file_write(fptr, teacher);
    file_close(fptr);
}
// �������� ��⥫� �� ����
void teacher_delete(int id)
{
    FILE *fptr = file_open();
    if (file_locate(fptr, id))
    {
        file_delete(fptr);
    }
    file_close(fptr);
}
// �㭪�� ��� 㤠����� \n � ���� ��ப
void string_strip(char *str)
{
    int n = strlen(str);
    if (str[n - 1] == '\n')
    {
        str[n - 1] = '\0';
    }
}
//���⪠ ����ᥩ �� \n
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
// ���� �९�����⥫�
void teacher_input(TEACHER *teacher)
{

    while ((getchar()) != '\n')
        ;
    printf("\t�������: ");
    fgets(teacher->lastname, 20, stdin);
    printf("\t���: ");
    fgets(teacher->firstname, 20, stdin);
    printf("\t����⢮: ");
    fgets(teacher->surname, 20, stdin);
    printf("\t��䥤�: ");
    fgets(teacher->kafedra, 30, stdin);
    printf("\t���������: ");
    fgets(teacher->post, 30, stdin);
    printf("\t���� : ");
    fgets(teacher->adress, 30, stdin);
    printf("\t����� ⥫�䮭�: ");
    fgets(teacher->phone, 20, stdin);
    printf("\t��⠥�� �����: ");
    fgets(teacher->courses, 300, stdin);
    teacher_strip(teacher);
}
// ������ � 䠩�
void teacher_write(TEACHER *teacher)
{
    FILE *fptr = file_open();
    file_locate(fptr, teacher->id);
    file_write(fptr, teacher);
    file_close(fptr);
}
// �㭪�� ��� menu, � ���ன 㦥 ��뢠���� �㭪樨 ���襩 �������� tacher
void menu_create()
{
    TEACHER teacher;
    teacher_input(&teacher);
    teacher_create(&teacher);
}
// �㭪�� ��� menu, 㤠�����
void menu_delete()
{
    TEACHER teacher;
    int id, i = 0;

    printf("������ id:");
    scanf("%d", &id);

    teacher_delete(id);
}
// �㭪�� ��� �ࠢ����� ����� �� ��������� ⨯�
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
// ����஢�� ����ᥩ ����쪮�
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
// �㭪�� ��ᨢ��� �뢮��
void teacher_print(TEACHER *teacher)
{
    printf("%-3d � %-10s � %-10s � %-17s � %-15s � %-30s \n"
           "    ������������������������������������������������������������������������������������������������\n"
           "    � %-23s � %-17s � %-40s\n",
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
// ���� ����� � 䠩��
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
                    printf("����������������������������������������������������������������������������������������������������\n");
                    teacher_print(&teacher);
                    printf("����������������������������������������������������������������������������������������������������\n");
                }
                break;
            case 2:

                if (strstr(teacher.firstname, str) != 0)
                {
                    printf("����������������������������������������������������������������������������������������������������\n");
                    teacher_print(&teacher);
                    printf("����������������������������������������������������������������������������������������������������\n");
                }
                break;
            case 3:

                if (strstr(teacher.surname, str) != 0)
                {
                    printf("����������������������������������������������������������������������������������������������������\n");
                    teacher_print(&teacher);
                    printf("����������������������������������������������������������������������������������������������������\n");
                }
                break;
            case 4:

                if (strstr(teacher.kafedra, str) != 0)
                {
                    printf("����������������������������������������������������������������������������������������������������\n");
                    teacher_print(&teacher);
                    printf("����������������������������������������������������������������������������������������������������\n");
                }
                break;
            case 5:

                if (strstr(teacher.post, str) != 0)
                {
                    printf("����������������������������������������������������������������������������������������������������\n");
                    teacher_print(&teacher);
                    printf("����������������������������������������������������������������������������������������������������\n");
                }
                break;
            case 6:

                if (strstr(teacher.adress, str) != 0)
                {
                    printf("����������������������������������������������������������������������������������������������������\n");
                    teacher_print(&teacher);
                    printf("����������������������������������������������������������������������������������������������������\n");
                }
                break;
            case 7:

                if (strstr(teacher.phone, str) != 0)
                {
                    printf("����������������������������������������������������������������������������������������������������\n");
                    teacher_print(&teacher);
                    printf("����������������������������������������������������������������������������������������������������\n");
                }
                break;
            case 8:

                if (strstr(teacher.courses, str) != 0)
                {
                    printf("����������������������������������������������������������������������������������������������������\n");
                    teacher_print(&teacher);
                    printf("����������������������������������������������������������������������������������������������������\n");
                }
                break;
            case 9:

                if (teacher.id == atoi(str))
                {
                    printf("����������������������������������������������������������������������������������������������������\n");
                    teacher_print(&teacher);
                    printf("����������������������������������������������������������������������������������������������������\n");
                }
                break;
            default:
                printf("���஡�� ��㣮� ��� �������");
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
// �㭪�� ��� ���஢�� �� ��������� ⨯�
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
// ���� ��� menu, ����� ��।���� ⨯ ���஢��
void menu_sort()
{
    int k;
    printf("�롥�� �� ������ ���� �㤥� �ந������� ���஢��:\n\t"
           "1) �������\n\t"
           "2) ���\n\t"
           "3) ����⢮\n\t"
           "4) ��䥤�\n\t"
           "5) ���������\n\t"
           "6) ����譨� ����\n\t"
           "7) ����� ⥫�䮭�\n\t"
           "8) ��⠥�� �����\n\t"
           "9) ID\n "
           "��� �롮�: ");
    scanf("%d", &k);
    teacher_sort(k);
}
// �㭪�� ��� menu, ���� ����� �� ��।�������� ����
void menu_find()
{
    int k;
    printf("�롥�� �� ������ ���� �㤥� �ந������ ����:\n\t"
           "1) �������\n\t"
           "2) ���\n\t"
           "3) ����⢮\n\t"
           "4) ��䥤�\n\t"
           "5) ���������\n\t"
           "6) ����譨� ����\n\t"
           "7) ����� ⥫�䮭�\n\t"
           "8) ��⠥�� �����\n\t"
           "9) ID\n "
           "��� �롮�: ");
    scanf("%d", &k);
    printf("��ப� ��� ���᪠: ");
    while ((getchar()) != '\n')
        ;
    char str[300];
    fgets(str, 300, stdin);
    string_strip(str);
    teacher_find(k, str);
}
// �㭪�� ��� menu, ।�������� ������
void menu_edit()
{
    TEACHER teacher;
    printf("������ id ���짮��⥫�: ");
    scanf("%d", &teacher.id);
    teacher_input(&teacher);
    teacher_write(&teacher);
}
// �㭪�� �뢮�� �ᥣ� 䠩��
void teacher_print_file()
{
    FILE *fptr = file_open();
    TEACHER teacher;
    printf("����������������������������������������������������������������������������������������������������\n");
    printf("%-3s � %-10s � %-10s � %-17s � %-15s � %-30s \n"
           "    ������������������������������������������������������������������������������������������������\n"
           "    � %-23s � %-17s � %-40s\n",
           "ID",
           "�������",
           "���",
           "����⢮",
           "����䮭",
           "����譨� ����",
           "��䥤�",
           "���������",
           "��⠥�� �����");
    printf("����������������������������������������������������������������������������������������������������\n");
    printf("����������������������������������������������������������������������������������������������������\n");
    while (!feof(fptr))
    {
        file_read(fptr, &teacher);
        if (!feof(fptr))
        {

            teacher_print(&teacher);
            printf("����������������������������������������������������������������������������������������������������\n");
        }
    }
    printf("����������������������������������������������������������������������������������������������������\n");
}
// ���� ����
void menu()
{
    while (1)
    {
        printf("-----------------------------\n"
               "�롥�� ����⨢�:\n\t"
               "1) �������� ������ � ����\n\t"
               "2) ������� ������ �� ����\n\t"
               "3) ���� �����\n\t"
               "4) ������஢���� ����� � ����\n\t"
               "5) ����஢�� ����ᥩ � ����\n\t"
               "6) �뢮� ���� ������\n"
               "��� �롮�: ");
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