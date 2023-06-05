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

