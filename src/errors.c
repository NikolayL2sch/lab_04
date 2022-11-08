#include "constants.h"

void print_error(int rc)
{
    switch (rc)
    {
        case EXIT_FAILURE:
            printf("\nОШИБКА! Введенно неправильное значение.");
            break;
        case DATA_EMPTY_ERR:
            printf("\nОШИБКА! Данные пусты!");
            break;
        case FILE_NOT_FOUND:
            printf("\nОШИБКА! ФАЙЛ не найден");
            break;
        case MAIN_STRING_OVERFLOW:
            printf("\nОШИБКА! ФАЙЛ - одна из строк переполнена");
            break;
        case INCORRECT_CHOICE:
            printf("\nОШИБКА! Некорректный выбор в меню.");
            break;
        case INCORRECT_FILENAME:
            printf("\nОШИБКА! Некорректно задано имя файла.");
            break;
        case STACK_IS_FULL:
            printf("\nОШИБКА! Стек заполнен.");
            break;
        case STACK_EMPTY:
            printf("\nОШИБКА! Стек пуст.");
            break;
        case STACK_EMPTY_FILE:
            break;
    }
}
