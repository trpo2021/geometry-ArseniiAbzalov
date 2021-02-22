#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct obj {
    double x;
    double y;
    double radius;
} circle;

int main()
{
    char str[30];
    char* cursor = str;    //первый курсор
    char* endcursor = str; //второй курсор
    int check = 0, check2 = 0,
        check3 = 0; //переменные для поиска символов '(',',',')'

    fgets(str, sizeof(str), stdin); //ввод строки

    while (*cursor == ' ') { //пропускаем пробелы перед словом
        cursor++;
        endcursor++;
    }
    if (isalpha(*cursor) != 0) { //ставим второй курсор на конец слова
        while (isalpha(*endcursor) != 0) {
            endcursor++;
        }
    }

    if (strncasecmp(cursor, "circle", endcursor - cursor) == 0) { //делаем проверку слова на совпадение
        char* newcursor = endcursor;
        char* end;

        while (*newcursor != 10) //проверка на наличие '('
        {
            if (*newcursor == '(') {
                check = 1;
                newcursor = endcursor;
                break;
            }
            newcursor++;
        }
        if (check == 0) {
            printf("expected '('\n");
            return 0;
        }

        while (isdigit(*newcursor) == 0) { //проверка после скобки до первого числа

            if ((*newcursor == ' ') || (*newcursor == '(')) {
                newcursor++;
            } else {
                printf("expected '<double>'\n");
                return 0;
            }
        }

        if (isdigit(*newcursor) != 0) { //запись первого числа в структуру
            circle.x = strtod(newcursor, &end);
            newcursor = end;
            printf("%f\n", circle.x);
        }

        while (isdigit(*newcursor) == 0) { //проверка перед вторым

            if (*newcursor == ' ') {
                newcursor++;
            } else {
                printf("expected '<double>'\n");
                return 0;
            }
        }

        if (isdigit(*newcursor) != 0) { //запись второго числа в структуру
            circle.y = strtod(newcursor, &end);
            newcursor = end;
            printf("%f\n", circle.y);
        }

        char* helpcursor = newcursor; //вспомогательный курсор

        while (*newcursor != 10) //проверка на наличие запятой
        {
            if (*newcursor == ',') {
                check2 = 1;
                newcursor = helpcursor;
                break;
            }
            newcursor++;
        }
        if (check2 == 0) {
            printf("expected ','\n");
            return 0;
        }

        while (*newcursor != ',') { //проверка перед запятой

            if (*newcursor == ' ') {
                newcursor++;
            } else {
                printf("expected '<double>'\n");
                return 0;
            }
        }

        if (*newcursor == ',') //проверка если сразу стоим на запятой
        {
            newcursor++;
        }

        if (*newcursor != ' ') { //проверка пробела после запятой
            printf("expected ' ' after ','\n");
            return 0;
        } else {
            newcursor++;
        }

        while (isdigit(*newcursor) == 0) { //проверка перед третьим числом

            if (*newcursor == ' ') {
                newcursor++;
            } else {
                printf("expected '<double>'\n");
                return 0;
            }
        }

        if (isdigit(*newcursor) != 0) { //запись третьего числа в структуру
            circle.radius = strtod(newcursor, &end);
            newcursor = end;
            printf("%f\n", circle.radius);
        }

        char* helpcursor2;
        helpcursor2 = newcursor;

        while (*newcursor != 10) //проверка на наличие ')'
        {
            if (*newcursor == ')') {
                check3 = 1;
                newcursor = helpcursor2;
                break;
            }
            newcursor++;
        }
        if (check3 == 0) {
            printf("expected ')'\n");
            return 0;
        }

        while (*newcursor != ')') { //проверка после третьего числа

            if (*newcursor == ' ') {
                newcursor++;
            } else {
                printf("expected '<double>'\n");
                return 0;
            }
        }

        if (*newcursor == ')') { // проверка после ')' до конца строки
            newcursor++;
            if (*newcursor == 10) {
                return 0;
            }
        }

        while (*newcursor != 10) {
            if (*newcursor != ' ') {
                printf("unexpected token\n");
                return 0;
            }
            newcursor++;
        }

    } else {
        printf("^\n");
        printf("Error at column 0: expected 'circle'\n");
    }
    return 0;
}
