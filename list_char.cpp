#include "header.h"



Node_char* List_char :: add_first(char number)
{
    Node_char *element = new Node_char();
    element->data = number;

    // список пустой
    if (first == nullptr)
    {
        element->next = nullptr;
        first = element;
        last = element;
    }
    else
    {
        element->next = first; // за новым элементом следует тот, что был началом
        first = element; // теперь element принимает статус первого
    }
    return element;

}

Node_char* List_char :: add_last(char number)
{
    Node_char *element = new Node_char();
    element->data = number; // помещаем число в data этого узла
    element->next = nullptr; // обозначаем, что этот узел ни на что не указывает

    // список пустой
    if (first == nullptr)
    {
        first = element;
        last = element;
    }
    else
    {
        // узел, который до этого был последним, теперь указывает не на nullptr, а на созданный element
        last->next = element;
        last = element;
    }
    return element;
}

Node_char* List_char :: add_position(char number, int position)
{
    Node_char *element = new Node_char();
    // добавление первого элемента
    if (position == 0)
    {
        add_first(number);
    }

    else
    {
        Node_char *before_element = search_position(position-1);
        // добавление последнего элемента
        if (before_element == last)
        {
            add_last(number);
        }
            // добавление любого другого элемента
        else
        {
            element->data = number;

            // вкладываем в element ссылку на следующий, которую берем из i-1 элемента
            element->next = before_element->next;
            // в i-1 заменяем ссылку на element
            before_element->next = element;
        }
    }
    return element;
}

void List_char :: delete_value(char value)
{
    while (search_value(value) != nullptr)
    {
        Node_char *element = first;
        if (first->data == value)
        {
            first = element->next;
            delete element;
        }
        else
        {
            if (last->data == value)
            {
                while (element->next != last) {element = element->next;}
                // предпоследний эл-т
                element->next = nullptr;
                delete last;
                last = element;
            }
            else
            {
                Node_char *before_element = first;
                element = first->next;
                // перебор элементов
                while (element->data != value)
                {
                    before_element = before_element->next;
                    element = before_element->next;
                }

                before_element->next = element->next; // связь между i-1 и i+1
                delete element;
            }
        }
    }

}

void List_char :: delete_position(int position)
{
    Node_char *element = new Node_char();
    // удаление первого элемента
    if (position == 0)
    {
        element = first;
        first = element->next;
        delete element;
    }
        // удаление любого другого элемента
    else
    {
        Node_char *before_element = search_position(position-1);
        element = before_element->next;
        if (element == last)
        {
            before_element->next = nullptr;
            delete last;
            last = before_element;
        }
        else
        {
            before_element->next = element->next;
            delete element;
        }
    }
}

Node_char* List_char :: search_value(char value)
{
    Node_char *x = first;
    while (x->data != value)
    {
        x = x->next;
        if (x == nullptr)
        {
            return nullptr;
        }
    }
    return x;
}

Node_char* List_char :: search_position(int position)
{
    Node_char *x = first;
    for (int i = 0; i<position;i++)
    {
        x = x->next;
        if (x == nullptr)
        {
            return nullptr;
        }
    }
    return x;
}

void List_char :: print_list()
{
    if (first == nullptr)
    { std::cout << "The list is empty." << std::endl; }
    else
    {
        Node_char *x = first;
        while (x != nullptr)
        {
            std::cout << x->data << " ";
            x = x->next;
        }
        std::cout << std::endl;
    }
}
