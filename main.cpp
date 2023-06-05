#include "header.h"


class Stack {
public:
    List stack;  // стек как экземпляр списка
    int size = 0;
    void push(int x) {
        stack.add_first(x);
        size++;
    }
    Node* top() {
        return stack.search_position(0);
    }
    void pop() {
        stack.delete_position(0);
        size--;
    }
    bool empty() {
        if (size == 0)
            return true;
        else
            return false;
    }
};

class Queue {
public:
    List queue;  // стек как экземпляр списка
    int size = 0;
    void push(int x) {
        queue.add_last(x);
        size++;
    }
    Node* front() {
        return queue.search_position(0);
    }
    Node* back() {
        return queue.search_position(size-1);
    }
    void pop() {
        queue.delete_position(0);
        size--;
    }
    bool empty() {
        if (size == 0)
            return true;
        else
            return false;
    }
};


class Calculator
{
public:
    static std::string change_expr(std::string);
    static int calc(std::string);

};

std::string Calculator :: change_expr(std::string expr) {
    Stack expr_st;
    Queue expr_q;
    int len = expr.length();
    for (int i = 0; i < len; i++) {
        if (expr[i] == ' ') {
            continue;
        }
        else if (isdigit(expr[i])) {
            int x = 0;
            while (isdigit(expr[i])) {
                x = x * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            expr_q.push(x);
        }
        else if (expr[i] == '(') {
            expr_st.push(expr[i]);
        }
        else if (expr[i] == ')') {
            // помещение стека в очередь до ")"
            while (expr_st.top()->data != ')') {
                expr_q.push(expr_st.top()->data);
                expr_st.pop();
            }
            expr_st.pop();
        }
        else {
            // помещение в стек пока не встретим оператор с меньш приоритетом
            while (!expr_st.empty() && (( (expr[i]=='*' || expr[i]=='/') && expr_st.top()->data == '+') || ((expr[i]=='*' || expr[i]=='/') && expr_st.top()->data == '-'))) {
                expr_q.push(expr_st.top()->data);
                expr_st.pop();
            }
            // текущий оператор - в стек
            expr_st.push(expr[i]);
        }

    }

    // помещение в стек оставшихся операторов
    while (!expr_st.empty()) {
        expr_q.push(expr_st.top()->data);
        expr_st.pop();
    }

    std::string ex;
    while (!expr_q.empty()) {
        ex.push_back(expr_q.front()->data);
        ex.push_back(' ');
        expr_q.pop();
    }
    return ex;

}

int Calculator :: calc(std::string expr) {
    std::string ex = change_expr(expr);
    Stack calc_stack;
    int len = expr.length();
    for (int i = 0; i < len; i++) {
        if (expr[i] == ' ') {
            continue;
        }
            // считывание операнда до пробела
        else if (isdigit(expr[i])) {
            int x = 0;
            while (isdigit(expr[i])) {
                // приведение к типу int,- '0' удаление смещения при переходе из char в int
                x = x * 10 + (expr[i] - '0');
                i++;
            }
            i--; // возврат к концу числа
            calc_stack.push(x);
        }
            // считывание оператора
        else {
            // извлечение 2-х верхних чисел из стека
            int a = calc_stack.top()->data;
            calc_stack.pop();
            int b = 0;
            bool pos = false;
            if (calc_stack.size != 0) {
                b = calc_stack.top()->data;
                calc_stack.pop();
                pos = true;
            }

            if (expr[i] == '+') {
                calc_stack.push(a+b);
            }
            else if (expr[i] == '-') {
                if (!pos) {
                    // для случая, если первое число в выражении - отрицательное
                    calc_stack.push(0-a);
                }
                else {
                    // отрицательные числа в выражении
                    if (expr[i+1]== '+' || expr[i+1]=='-' || expr[i+1]=='/' || expr[i+1]=='*') {
                        calc_stack.push(a);
                        calc_stack.push(0-b);
                    }
                    else {
                        calc_stack.push(b-a);
                    }
                }
            }
            else if (expr[i] == '*') {
                calc_stack.push(a*b);
            }
            else if (expr[i] == '/') {
                if (a == 0) {
                    std::cout << "Incorrect expression. ";
                    return 0;
                } else {
                    calc_stack.push(b/a);
                }
            }
        }
    }
    // Результат - единственное оставшееся число в стеке
    if (calc_stack.size == 1) {
        return calc_stack.top()->data;
    }
    else {
        std::cout << "Incorrect expression. ";
        return 0;
    }
}

int main() {

    Calculator calculator;

    bool correct;
    std::string expr;
    while (expr != "s") {
        correct = true;
        std::cout << "\n Enter the expression \n or enter 's' to stop " << std::endl;
        std::getline(std::cin, expr);

        // проверка ввода
        for (char i : expr) {
            if ((i >= 'A' && i <= 'Z' || i >= 'a' && i <= 'z') && expr != "s") {
                std::cout << "Incorrect input" << std::endl;
                correct = false;
                break;
            }
        }

        if (expr != "s" && correct) {
            std::cout << calculator.calc(expr);
            std::cout << std::endl;
        }
    }

    return 0;
}


