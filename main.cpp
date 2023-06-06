// ---------------------------------------//
// Infix calculator with queue and stack  //
// ---------------------------------------//

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

class Stack_char {
public:
    List_char stack;  // стек как экземпляр списка
    int size = 0;
    void push(char x) {
        stack.add_first(x);
        size++;
    }
    Node_char* top() {
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
    List_char queue;  // стек как экземпляр списка
    int size = 0;
    void push(char x) {
        queue.add_last(x);
        size++;
    }
    Node_char* front() {
        return queue.search_position(0);
    }
    Node_char* back() {
        return queue.search_position(size-1);
    }
    void pop() {
        queue.delete_position(0);
        size--;
    }
    char pos(int i) {
        return queue.search_position(i)->data;
    }
};


class Calculator
{
public:
    static int priority(char);
    static Queue change_expr(const std::string&);
    static int calc(const std::string&);

};


// Вычисление приоритета операции
int Calculator :: priority(char op) {
    if (op == '*' || op == '/') {
        return 1;
    }
    if (op == '+' || op == '-') {
        return 2;
    }
    return 10; // для "("
}

// Перевод инфиксного выражения в постфиксное
Queue Calculator :: change_expr(const std::string& expr) {
    Stack_char expr_st;
    Queue expr_q;
    for (char v: expr) {
        if (v == ' ' || isdigit(v)) {
            expr_q.push(v);
        }
        else if (v == '(') {
            expr_st.push(v);
        }
        else if (v == ')') {
            // помещение стека в очередь до ")"
            while (expr_st.top()->data != '(') {
                expr_q.push(expr_st.top()->data);
                expr_st.pop();
            }
            expr_st.pop();
        }
        else {
            // помещение в стек пока не встретим оператор с меньш приоритетом
            while (!expr_st.empty() && (priority(v) >= priority(expr_st.top()->data))) {
                expr_q.push(expr_st.top()->data);
                expr_st.pop();
            }
            expr_q.push(' ');
            // текущий оператор - в стек
            expr_st.push(v);
        }
    }

    // помещение в стек оставшихся операторов
    while (!expr_st.empty()) {
        expr_q.push(expr_st.top()->data);
        expr_st.pop();
    }


    return expr_q;
}

// Вычисление
int Calculator :: calc(const std::string& expr) {
    Queue ex = change_expr(expr);
    Stack calc_stack;
    int len = ex.size;

    // check
    for (int i = 0; i < len; i++) {
        std::cout << ex.pos(i);
    }
    std::cout << std::endl;

    for (int i = 0; i < len; i++) {
        if (ex.pos(i) == ' ') {
            continue;
        }
            // считывание операнда до пробела/оператора
        else if (isdigit(ex.pos(i))) {
            int x = 0;
            while (isdigit(ex.pos(i))) {
                // приведение к типу int,- '0' удаление смещения при переходе из char в int
                x = x * 10 + (ex.pos(i) - '0');
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

            if (ex.pos(i) == '+') {
                calc_stack.push(a+b);
            }
            else if (ex.pos(i) == '-') {
                if (!pos) {
                    // для случая, если первое число в выражении - отрицательное
                    calc_stack.push(0-a);
                }
                else {
                    calc_stack.push(b-a);
                }
            }
            else if (ex.pos(i) == '*') {
                calc_stack.push(a*b);
            }
            else if (ex.pos(i) == '/') {
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
        // check
        // return calc_stack.top()->data;
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



// можно было бы создавать несколько экземпляров класса калькулятор, в атрибутах сделать expr и два метода - вычисление и проверка
