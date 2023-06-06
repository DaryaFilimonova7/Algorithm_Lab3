#include <iostream>
#include <string>


class Node
{
public:
    int data;
    class Node* next;
};


class List
{
    // Указатели на первый и последний эл-ты списка
    Node *first;
    Node *last;

public:
    // Инициализация списка по умолчанию
    List()
    {
        first = nullptr;
        last = nullptr;
    }

    Node* add_first(int);
    Node* add_last(int);
    Node* add_position(int,int);
    void delete_value(int);
    void delete_position(int);
    Node* search_value(int);
    Node* search_position(int);
    void print_list();
};



class Node_char
{
public:
    char data;
    class Node_char* next;
};

class List_char
{
    // Указатели на первый и последний эл-ты списка
    Node_char *first;
    Node_char *last;

public:
    // Инициализация списка по умолчанию
    List_char()
    {
        first = nullptr;
        last = nullptr;
    }

    Node_char* add_first(char);
    Node_char* add_last(char);
    Node_char* add_position(char,int);
    void delete_value(char);
    void delete_position(int);
    Node_char* search_value(char);
    Node_char* search_position(int);
    void print_list();
};
