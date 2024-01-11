#include <stdio.h>
#include <ctype.h>

// Определяем структуру для хранения выражения и текущей позиции в нем
typedef struct {
    char* expression; // указатель на массив символов, содержащий выражение
    size_t position; // текущая позиция в выражении
} ExpressionConverter;

// Объявляем функции
void E(ExpressionConverter* converter);
void T(ExpressionConverter* converter);
void EPrime(ExpressionConverter* converter);
void TPrime(ExpressionConverter* converter);
void F(ExpressionConverter* converter);

// Функция для преобразования в постфиксную форму
void ToPostfix(ExpressionConverter* converter) {
    E(converter); // начинаем с выражения E
    printf("\n"); // выводим символ новой строки
}

// Функция для обработки выражения E
void E(ExpressionConverter* converter) {
    T(converter); // вызываем функцию для обработки терма
    EPrime(converter); // вызываем функцию для обработки оставшейся части выражения E
}

// Функция для обработки терма T
void T(ExpressionConverter* converter) {
    F(converter); // вызываем функцию для обработки фактора
    TPrime(converter); // вызываем функцию для обработки оставшейся части терма T
}

// Функция для обработки оставшейся части выражения E
void EPrime(ExpressionConverter* converter) {
    if (converter->expression[converter->position] == '+' || converter->expression[converter->position] == '-') {
        char op = converter->expression[converter->position]; // сохраняем оператор
        converter->position++; // увеличиваем текущую позицию
        T(converter); // вызываем функцию для обработки терма
        EPrime(converter); // вызываем функцию для обработки оставшейся части выражения E
        printf("%c ", op); // выводим оператор
    }
}

// Функция для обработки оставшейся части терма T
void TPrime(ExpressionConverter* converter) {
    if (converter->expression[converter->position] == '*' || converter->expression[converter->position] == '/') {
        char op = converter->expression[converter->position]; // сохраняем оператор
        converter->position++; // увеличиваем текущую позицию
        F(converter); // вызываем функцию для обработки фактора
        TPrime(converter); // вызываем функцию для обработки оставшейся части терма T
        printf("%c ", op); // выводим оператор
    }
}

// Функция для обработки фактора F
void F(ExpressionConverter* converter) {
    if (isdigit(converter->expression[converter->position])) { // если текущий символ - цифра
        printf("%c ", converter->expression[converter->position]); // выводим цифру
        converter->position++; // увеличиваем текущую позицию
    } else if (converter->expression[converter->position] == '(') { // если текущий символ - открывающая скобка
        converter->position++; // увеличиваем текущую позицию
        E(converter); // вызываем функцию для обработки выражения в скобках
        if (converter->expression[converter->position] == ')') { // если следующий символ - закрывающая скобка
            converter->position++; // увеличиваем текущую позицию
        } else {
            // Обработка ошибки: не найдена закрывающая скобка
        }
    } else {
        // Обработка ошибки: неизвестный символ
    }
}

int main() {
    char infixExpression[100];
    printf("Введите инфиксиное выражение: ");
    scanf("%s", infixExpression); // вводим инфиксное выражение
    ExpressionConverter converter;
    converter.expression = infixExpression; // передаем в структуру введенное выражение
    converter.position = 0; // устанавливаем начальную позицию
    ToPostfix(&converter); // вызываем функцию для преобразования в постфиксную форму
    return 0;
}

