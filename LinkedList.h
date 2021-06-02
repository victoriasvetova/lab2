#pragma once
#include <iostream>
#include <stdio.h>

template<typename T>
class Node {
public:
    Node* pNext;
    Node* pPrev;
    T DATA;
    Node(T DATA = T(), Node* pPrev = nullptr, Node* pNext = nullptr) {
        this->DATA = DATA;
        this->pPrev = pPrev;
        this->pNext = pNext;
    }
};

template<typename T>
class LinkedList {
public:



    ~LinkedList() {
        clear();
    }


    LinkedList() {
        Size = 0;
        HEAD = nullptr;
    }

    //считывание значений из переданного массива
    LinkedList(T* items, int count) {
        if (items == nullptr) {
            Size = 0;
            HEAD = nullptr;
        }
        else {
            Size = 0;
            this->HEAD = nullptr;
            this->TAIL = nullptr;
            for (int i = 0; i < count; ++i) {
                Append(items[i]);
            }
        }
    }


    LinkedList(const LinkedList<T>& list) {
        Size = 0;
        this->HEAD = nullptr;//для корректного отрабатывания Append
        Node<T>* current = list.HEAD;
        for (int i = 0; i < list.Size; ++i) {//заменил Size на GetLength()
            this->Append(current->DATA);
            current = current->pNext;
        }
        //std::cout << "CopyConstructor done . . .\n";
    }


    LinkedList<T>* Concat(LinkedList<T>* list) {//разобраться,что происходит с длиной(разобрался и переделал,ошибка была в том,что не было обновления TAIL у текущего объекта)
        //вызывающий объединяю с переданным в качестве параметра
        //при этом тот,что передан в качестве параметра,остается в памяти как отдельный
        //однако вызывающий воспринимает его как свою часть
        this->TAIL->pNext = list->HEAD;
        list->HEAD->pPrev = this->TAIL;
        this->TAIL = list->TAIL;
        Size += list->Size;

        return this;
    }


    T Get(int index) {
        if (index < 0 || index >= Size)
            throw "\nGet Message : Index Out Of Range\n";

        Node<T>* current;

        if (index < Size / 2) {
            current = HEAD;
            for (int i = 0; i < index; ++i) {
                current = current->pNext;
            }
        }
        else {
            current = TAIL;
            for (int i = 0; i < Size - index - 1; ++i) {
                current = current->pPrev;
            }
        }
        return current->DATA;

    }


    T GetFirst() {
        if (Size == 0)
            throw "\nGetFirst Message : Index Out Of Range\n";
        //std::cout<<"\nGetFirst:\n";
        return Get(0);
    }


    T GetLast() {
        if (Size == 0)
            throw "\nGetLast Message : Index Out Of Range\n";
        //std::cout<<"\nGetLast:\n";
        return Get(Size - 1);
    }


    LinkedList<T>* GetSubLinkedList(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex < 0 || startIndex >= Size || endIndex >= Size)
            throw "\nGetSubLinkedList Message : Index Out Of Range\n";
        //std::cout<<"\nGetSubLinkedList\n";
        Node<T>* current = this->HEAD;
        for (int i = 0; i < startIndex; ++i) {
            current = current->pNext;
        }
        T* items;
        items = (T*)malloc(sizeof(T*) * (endIndex - startIndex + 1));
        for (int i = 0; i < endIndex - startIndex + 1; ++i) {
            items[i] = current->DATA;
            current = current->pNext;
        }

        LinkedList<T>* result = new LinkedList<T>(items, endIndex - startIndex + 1);
        return result;

    }


    void PrintFromEnd() {//печать с конца списка
        //std::cout << std::endl;
        Node<T>* tmp = this->TAIL;
        if (Size == 1)
            std::cout << TAIL->DATA << " ";
        else {
            while (tmp != nullptr) {
                std::cout << tmp->DATA << " ";
                tmp = tmp->pPrev;
            }
        }
        std::cout << std::endl;
    }


    void PrintFromBegin() {//печать с начала списка
        if (HEAD != nullptr) {
            //std::cout << std::endl;
            Node<T>* tmp = this->HEAD;
            if (Size == 1)
                std::cout << HEAD->DATA << " ";
            else {
                while (tmp != nullptr) {
                    std::cout << tmp->DATA << " ";//std::endl;
                    tmp = tmp->pNext;
                }
            }
            std::cout << std::endl;
        }
    }



    void Append(T DATA) {
        if (HEAD == nullptr) {//если только один элемент,то заполняем HEAD
            HEAD = new Node<T>(DATA);
            this->TAIL = HEAD;

        }
        else {//если больше,то добавляем и присваиваем TAIL этот элемент
            Node<T>* current = this->HEAD;//временная переменная
            Node<T>* tmp;
            while (current->pNext != nullptr) {
                tmp = current;
                current = current->pNext;
                current->pPrev = tmp;
            }

            this->TAIL = new Node<T>(DATA, current, current->pNext);//вставка между current и nullptr
            current->pNext = TAIL;
        }
        Size++;
    }


    void Prepend(T DATA) {
        if (HEAD == nullptr) {
            HEAD = new Node<T>(DATA);
            this->TAIL = HEAD;
        }
        else {
            Node<T>* one_more = new Node<T>(DATA, HEAD->pPrev, HEAD);//создание нового узла(следующий - HEAD,предыдущего нет)
            HEAD->pPrev = one_more;
            this->HEAD = one_more;
            Node<T>* current = HEAD;
            while (current->pNext != nullptr) {
                current = current->pNext;
            }
            this->TAIL = current;
        }
        Size++;
    }


    void pop_front() {
        if (Size == 1) {
            delete[] TAIL;
            Size--;
        }
        else {
            Node<T>* tmp = HEAD;//запоминаем ссылку,по которой находится текущий HEAD
            HEAD = HEAD->pNext;//сдвиг HEAD к концу на один элемент
            HEAD->pPrev = nullptr;//"обнуление" указателя на предыдущий элемент
            delete[] tmp;//удаление старого HEAD
            Size--;
        }

    }


    void pop_back() {
        Node<T>* tmp = TAIL;
        TAIL = TAIL->pPrev;
        TAIL->pNext = nullptr;
        delete[] tmp;
        Size--;
    }

    //усовершенствован для двусвязного списка
    void InsertAt(T DATA, int index) {
        if (index < 0 || index >= Size)
            throw "\nInsertAt Message : Index Out Of Range\n";
        Node<T>* previous;
        Node<T>* new_elem;
        Node<T>* tmp;
        //std::cout << "\nInsertAt DATA = " << DATA << " index = " << index << "\n";
        if (index <= Size / 2) {//идём сначала
            if (index == 0)
                Prepend(DATA);
            previous = HEAD;
            for (int i = 0; i < index - 1; ++i) {
                previous = previous->pNext;
            }
        }
        else {//идём с конца

            previous = TAIL;
            for (int i = 0; i < Size - index; ++i) {
                previous = previous->pPrev;
            }
        }
        tmp = previous->pNext;//запоминаем адрес следующего узла
        new_elem = new Node<T>(DATA, previous, previous->pNext);//создаем новый узел
        previous->pNext = new_elem;//обновляем указатель на следующий узел у предыдущего
        tmp->pPrev = new_elem;//обновляем указатель на предыдущий узел у следующего

        Size++;
    }

    //усовершенствован для двусвязного списка
    void removeAt(int index) {
        if (index < 0 || index >= Size)
            throw "removeAt Message : Index Out Of Range\n";
        //std::cout << "\nremoveAt index = " << index << "\n";
        if (index == 0)
            pop_front();
        else {
            if (index == Size - 1)
                pop_back();
            else {
                Node<T>* previous;
                Node<T>* toDelete;
                if (index <= Size / 2) {
                    previous = HEAD;
                    for (int i = 0; i < index - 1; ++i) {
                        previous = previous->pNext;
                    }
                }
                else {
                    previous = TAIL;
                    for (int i = 0; i < Size - index; ++i) {
                        previous = previous->pPrev;
                    }
                }

                toDelete = previous->pNext;//запоминаем ссылку на удаляемый узел
                previous->pNext = toDelete->pNext;//изменяем поле следующего узла у идущего перед удаляемым
                toDelete->pNext->pPrev = previous;//изменяем поле предыдущего узла у идущего после удаляемого

                delete[] toDelete;//очистка памяти по ссылке удаляемого узла
            }
            Size--;
        }
    }
    void ChangeValue(int index, T value) {//изменяет по заданному индексу значение на value
        Node<T>* curr = HEAD;
        for (int i = 0; i < index; ++i) {//i + 1 < index вместо i < index - 1 для того,чтобы избежать переполнения числа
            curr = curr->pNext;
        }
        curr->DATA = value;
    }
    //очистка памяти
    void clear() {
        while (Size) {
            pop_front();
        }
    }

    //усовершенствован для двусвязного списка
    T& operator[](const int index) {//перегрузка оператора []
        //для нахождения элемента с номером index
        int counter;
        Node<T>* current;
        if (index <= Size / 2) {//идём с начала
            counter = 0;
            current = this->HEAD;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->pNext;
                counter++;
            }
        }
        else {//идём с конца
            counter = Size - 1;
            current = this->TAIL;
            while (current != nullptr) {
                if (counter == index) {
                    return current->DATA;
                }
                current = current->pPrev;
                counter--;
            }
        }
    }
    std::string list_to_string() {

        Node<T>* curr = this->HEAD;

        std::vector<std::string> result;

        std::string result_str = "";

        if (Size == 1)
            result.push_back(std::to_string(curr->DATA));
        else {
            while (curr != nullptr) {
                result.push_back(std::to_string(curr->DATA));
                curr = curr->pNext;
            }
        }
        for (int i = 0; i < Size; ++i)
        {
            result_str += result[i] + " ";
        }
        return result_str;
    }
    
private:
    int Size;
    Node<T>* HEAD;
    Node<T>* TAIL;
};

