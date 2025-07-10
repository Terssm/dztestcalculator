#include "SimpleCalculator.h"
#include "InMemoryHistory.h"
#include <clocale>
#include <iostream>
#include <limits>

int main() {
    setlocale(LC_ALL, "Russian");
    calc::InMemoryHistory history;
    calc::SimpleCalculator calculator(history);
   
    while (true) {
        int a, b;
        char op;

        std::cout << "\nВведите первое число (или q для выхода): ";
        if (!(std::cin >> a)) break;

        std::cout << "Введите оператор (+ - * /): ";
        std::cin >> op;

        std::cout << "Введите второе число: ";
        std::cin >> b;

        try {
            int result = 0;
            switch (op) {
            case '+':
                result = calculator.Add(a, b);
                break;
            case '-':
                result = calculator.Subtract(a, b);
                break;
            case '*':
                result = calculator.Multiply(a, b);
                break;
            case '/':
                if (b == 0) throw std::invalid_argument("Деление на ноль запрещено!");
                result = calculator.Divide(a, b);
                break;
            default:
                std::cout << "Неизвестный оператор." << std::endl;
                continue;
            }

            std::cout << "Результат: " << result << std::endl;
        }
        catch (const std::exception& ex) {
            std::cout << "Ошибка: " << ex.what() << std::endl;
        }

        std::cout << "\nПоследние операции:" << std::endl;
        for (const auto& entry : history.GetLastOperations(5)) {
            std::cout << entry << std::endl;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\nЗавершение работы калькулятора." << std::endl;
    return 0;
}
