#include <iostream>
#include <math.h>
template <class T>
class DynamicArray {
private:
    //поля
    T* m_DATA;
    int m_size;
    int m_capacity;
public:
    //создание
    DynamicArray() {//конструктор по умолчанию
        m_DATA = NULL;
        m_size = 0;
        m_capacity = 0;
    }


    void Delete() {
        delete[] this->m_DATA;
    }
    DynamicArray(int size) {//конструктор с числом элементов
        m_size = size;
        m_capacity = size;
        m_DATA = new T[size];
    }

    DynamicArray(T* items, int count) {//копировать элементы
        if (items == nullptr) {
            m_DATA = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else {
            m_size = count;         //из переданного массива
            m_capacity = count;
            m_DATA = new T[count];
            for (int i = 0; i < count; ++i)
            {
                m_DATA[i] = items[i];
            }
        }
    }

    DynamicArray(const DynamicArray<T>& dynamicArray) {//копирующий конструктор
        if (&dynamicArray == nullptr) {
            m_DATA = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else {
            m_size = dynamicArray.m_size;
            m_capacity = m_size;
            m_DATA = new T[m_size];
            for (int i = 0; i < dynamicArray.m_size; ++i)
            {
                m_DATA[i] = dynamicArray.m_DATA[i];
            }
        }
    }

    //операции
    void Resize(int newSize) {//перераспределение памяти
        if (newSize > m_capacity) {
            int new_capacity = std::max(2 * m_size, newSize);
            T* new_DATA = new T[new_capacity];
            for (int i = 0; i < m_size; ++i)
            {
                new_DATA[i] = m_DATA[i];
            }
            delete[] m_DATA;
            m_DATA = new_DATA;
            m_capacity = new_capacity;
        }
        m_size = newSize;
    }

    T Get(int index) {//получить элемент по индексу
        if (index < 0 || index >= m_capacity)
            throw "\nGet Message : Index Out Of Range\n";
        //std::cout << "\nGet index = " << index << "\n";
        return m_DATA[index];
    }

    void Set(int index, T value) {//задать значение элемента по индексу
        if (index < 0 || index > m_capacity)
            throw "\nSet Message : Index Out Of Range\n";
        //std::cout << "\nSet DATA = " << value << " index = "<< index <<"\n";
        m_DATA[index] = value;

    }

    int GetSize() const {//получить размер массива
        return m_size;
    }

    void Append(T val) {//добавление элемента в конец массива
        //std::cout << "\nAppend DATA = " << val;
        Resize(m_size + 1);//выделение доп памяти при необходимости
        m_DATA[m_size - 1] = val;
    }

    void Prepend(T val) {//добавление элемента в начало массива
        //std::cout << "\nPrepend DATA = " << val << "\n";
        Resize(m_size + 1);//выделение доп памяти при необходимости
        for (int i = m_size - 2; i >= 0; --i)
        {
            m_DATA[i + 1] = m_DATA[i];
        }
        m_DATA[0] = val;
    }

    T& operator [] (int i) {//перегрузка оператора "[]" для удобства вывода(возвращает i-й элемент)
        return m_DATA[i];
    }

    void Print() {//распечатать массив
        if (m_size > 0 && m_DATA != nullptr) {
            std::cout << std::endl;
            for (int i = 0; i < m_size; ++i) {
                std::cout << m_DATA[i] << "\t";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "\nObject is empty!\n";
        }
    }
};

template<typename T>
class Vector {
private:
    DynamicArray<T>* DATA;
    int size;
public:
    Vector() {//конструктор по умолчанию
        DATA = nullptr;
        size = 0;
    }
    Vector(T* items, int count) {//конструктор вектора через массив значений
        DATA = new DynamicArray<T>(items, count);
        size = count;
    }
    void Print() {//печать вектора
        if (this != nullptr && size != 0 && DATA != nullptr)
            DATA->Print();
    }
    int GetSize() {//получить размер вектора
        return DATA->GetSize();
    }
    T Get(int index) {//получить элемент по индексу
        return DATA->Get(index);
    }
    Vector<T>* Sum(Vector<T>* second) {//сумма двух векторов - данного вектора и переданного в качестве параметра
        if (size == second->GetSize()) {
            T* items = new T[size];
            for (int i = 0; i < size; ++i) {
                items[i] = DATA->Get(i) + second->Get(i);
            }
            Vector<T>* result = new Vector<T>(items, size);
            return result;
        }
        else {
            std::cout << "Can't sum ! \n";
            return nullptr;
        }

    }
    Vector<T>* ScalarMultiplication(Vector<T>* second) {//скалярное произведение данного вектора на переданный в качестве параметра
        if (size == second->GetSize()) {
            T* items = new T[size];
            for (int i = 0; i < size; ++i) {
                items[i] = DATA->Get(i) * second->Get(i);
            }
            Vector<T>* result = new Vector<T>(items, size);
            return result;
        }
        else {
            std::cout << "Can't scalar multiply ! \n";
            return nullptr;
        }

    }
    void MultiplicationByScalar(T num) {//умножение на скаляр
        for (int i = 0; i < size; ++i) {
            DATA->Set(i, DATA->Get(i) * num);
        }
    }
    T CalculatingTheVectorNorm() {//вычисление нормы вектора
        T result = 0;
        for (int i = 0; i < size; ++i) {
            result += DATA->Get(i) * DATA->Get(i);
        }

        result = sqrt(result);

        return result;
    }

};
template <typename T>
std::ostream& operator << (std::ostream& out, DynamicArray<T> a) {//перегрузка оператора << для вывода
    for (int i = 0; i < a.GetSize(); ++i) {
        out << a[i] << " ";
    }
    return out;
}
//==================================================================================================================//
template<typename T>
class Node {
public:
    Node* pNext;
    Node* pPrev;
    T DATA;
    Node(T DATA = T(), Node* pPrev = nullptr, Node* pNext = nullptr) {//конструктор
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


    LinkedList(T* items, int count) {//конструктор с помощью считывания значений из переданного массива
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


    LinkedList(const LinkedList<T>& list) {//копирующий конструктор
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


    T Get(int index) {//получить элемент по индексу
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


    T GetFirst() {//получить первый элемент
        if (Size == 0)
            throw "\nGetFirst Message : Index Out Of Range\n";
        //std::cout<<"\nGetFirst:\n";
        return Get(0);
    }


    T GetLast() {//получить последний элемент
        if (Size == 0)
            throw "\nGetLast Message : Index Out Of Range\n";
        //std::cout<<"\nGetLast:\n";
        return Get(Size - 1);
    }


    LinkedList<T>* GetSubLinkedList(int startIndex, int endIndex) {//получить подсписок: начиная с startIndex - заканчивая endIndex
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



    void Append(T DATA) {//добавление нового элемента в конец списка
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


    void Prepend(T DATA) {//добавление нового элемента в начало списка
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


    void pop_front() {//удалить элемент с начала списка
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


    void pop_back() {//удалить элемент с конца списка
        Node<T>* tmp = TAIL;
        TAIL = TAIL->pPrev;
        TAIL->pNext = nullptr;
        delete[] tmp;
        Size--;
    }

    //усовершенствован для двусвязного списка
    void InsertAt(T DATA, int index) {//вставить новый элемент  DATA по индексу index
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
    void removeAt(int index) {//удалить элемент по индексу
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
private:
    int Size;
    Node<T>* HEAD;
    Node<T>* TAIL;
};

//==================================================================================================================//
//эти три функции используются для классов Stack и Deque
template<typename T>//возведение в квадрат
T sqr(T value) {
    return value * value;
}

template<typename T>//проверка "больше семи"
bool is_more_than_7(T value) {
    if (value >= 7)
        return true;
    return false;
}

template<typename T>//сумма двух элементов
T sum(T first, T second) {
    return first + second;
}
//==================================================================================================================//
template<typename T>
class Stack {
private:
    LinkedList<T>* DATA;
    int size;
public:
    Stack() {//конструктор по умолчанию
        DATA = nullptr;
        size = 0;
    }
    Stack(LinkedList<T>* items, int count) {//конструктор по экземпляру класса двусвязного списка(копирование его данных в наш стек)
        DATA = items;
        size = count;
    }
    Stack(T* items, int count) {//конструктор по массиву элементов
        DATA = new LinkedList<T>(items, count);
        size = count;
    }

    int GetSize() {//получение размера стека
        return size;
    }

    T Get(int index) {//получение элемента по индексу
        return DATA->Get(index);
    }

    void Append(T value) {//добавление элемента в конец стека
        DATA->Append(value);
    }
    void PopBack() {
        DATA->pop_back();
    }
    void Print() {//печать стека
        if (this != nullptr && DATA != nullptr && size != 0)
            DATA->PrintFromEnd();//у стека нет возможности идти с начала(тк все операции происходят на последних элементах)
    }

    //map, where, reduce
    void Map(T(*func)(T)) {//возведение в квадрат
        for (int i = 0; i < size; i++) {
            DATA->ChangeValue(i, func(DATA->Get(i)));
            //изменяем значение по данному индексу
        }
    }

    Stack<T>* Where(bool(*func)(T)) {//фильтрация элементов по условию функции func(в данном случае сравнение с 7)
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if (!func(DATA->Get(i))) {
                count++;
            }
        }
        if (count > 0) {
            T* items = new T[count];
            int index = 0;
            for (int i = 0; i < size; ++i) {
                if (!func(DATA->Get(i))) {
                    items[index] = DATA->Get(i);
                    index++;
                }
            }
            Stack<T>* result = new Stack<T>(items, count);
            return result;
        }
        else {
            std::cout << "There are no elements which bigger than 7 !\n";
            return nullptr;
        }

    }

    T Reduce(T(*func)(T, T)) {//последовательное применение к каждому элементу стека функции func
        // (в нашем случае применяется суммирующая функция,так что результат - сумма всех элементов)
        T sum = 0;
        for (int i = 0; i < size; ++i) {
            sum = func(sum, DATA->Get(i));
            //передаем в функцию суммирования
            //два аргумента - старое значение sum и значение текущего элемента
            //в результате получается сумма всех элементов стека
        }
        return sum;
    }

    Stack<T>* Concat(Stack<T>* example) {//соединение двух стеков( Concat([1,2,3] , [4,5]) = [1,2,3,4,5])
        T* items = new T[size + example->GetSize()];//поэлементно копируем в этот массив элементы из обоих стеков
        for (int i = 0; i < size; ++i) {
            items[i] = DATA->Get(i);
        }
        for (int i = 0; i < example->GetSize(); ++i) {
            items[size + i] = example->Get(i);
        }

        Stack<T>* result = new Stack<T>(items, size + example->GetSize());
        return result;
    }

    //извлечение подпоследовательности из стека
    Stack<T>* GetSubsequenceFromStack(int start, int end) {
        Stack<T>* result = new Stack<T>(DATA->GetSubLinkedList(start, end), end - start + 1);
        return result;
    }
    void Set(int index, T value) {
        DATA->ChangeValue(index, value);
    }
};
//==================================================================================================================//
template<typename T>
class Sequence {
public:
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual int GetLength() = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;

    virtual void Print() = 0;
};
//==================================================================================================================//
template<typename T>
class ArraySequence : public Sequence<T> {
public:
    ArraySequence() {//конструктор по умолчанию
        DynamicArray<T>* tmp = new DynamicArray<T>();
        DATA = *tmp;
    }

    ArraySequence(T* item, int count) {//конструктор по массиву элементов

        DynamicArray<T>* tmp = new DynamicArray<T>(item, count);
        DATA = *tmp;

    }

    ArraySequence(ArraySequence<T>& array) {//копиконструктор для параметра ArraySequence

        DynamicArray<T>* tmp = new DynamicArray<T>(array.DATA);//конструктор копирует соответствующее поле
        DATA = *tmp;
    }

    ArraySequence(LinkedList<T>& list) {//копиконструктор для параметра LinkedList
        T* items;
        items = (T*)malloc(sizeof(T) * (list.GetLength()));
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }

        DynamicArray<T>* tmp = new DynamicArray<T>(items, list.GetLength());
        DATA = *tmp;
    }
    int GetLength() {
        return DATA.GetSize();
    }
    T Get(int index) {
        return DATA.Get(index);
    }
    T GetFirst() {
        return DATA.Get(0);
    }
    T GetLast() {
        return DATA.Get(DATA.GetSize() - 1);
    }

    void Append(T item) {
        DATA.Append(item);
    }
    void Prepend(T item) {
        DATA.Prepend(item);
    }
    void InsertAt(T item, int index) {//void Set(int index,T value)
        if (index >= DATA.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        DATA.Resize(DATA.GetSize() + 1);
        for (int i = DATA.GetSize() - 2; i >= index; --i) {
            DATA.Set(i + 1, DATA.Get(i));
        }
        DATA.Set(index, item);
    }
    void Print() {
        DATA.Print();
    }

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) {//получить подпоследовательность: начиная со startIndex - заканчивая endIndex
        T* items = (T*)malloc(sizeof(T) * (endIndex - startIndex));
        for (int i = startIndex; i < endIndex; ++i) {
            items[i - startIndex] = DATA.Get(i);
        }
        ArraySequence<T>* result = new ArraySequence<T>(items, endIndex - startIndex);
        return result;
    }

    ArraySequence<T>* Concat(Sequence<T>* list) {//конкатенация двух последовательностей
        if (list->GetLength() != 0) {
            T* items = (T*)malloc(sizeof(T) * (DATA.GetSize() + list->GetLength()));
            for (int i = 0; i < DATA.GetSize(); ++i) {
                items[i] = DATA.Get(i);
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                items[i + DATA.GetSize()] = list->Get(i);
            }
            ArraySequence<T>* result = new ArraySequence<T>(items, DATA.GetSize() + list->GetLength());

            return result;
        }
        else {
            ArraySequence<T>* result = new ArraySequence<T>(*this);
            return result;
        }

    }
private:
    DynamicArray<T> DATA;
};
//==================================================================================================================//
template<typename T>
class LinkedListSequence : public Sequence<T> {
public://информация о размере хранится в поле DATA
    LinkedListSequence() {//конструктор по умолчанию
        LinkedList<T>* tmp = new LinkedList<T>();
        DATA = *tmp;
    }
    LinkedListSequence(T* items, int count) {//конструктор по массиву
        LinkedList<T>* tmp = new LinkedList<T>(items, count);
        DATA = *tmp;

    }

    //переопределение не охватывает соответствующую функцию из LinkedList,
    // так как требуется общность первого параметра,вследствие чего нет возможности получить данные
    LinkedListSequence<T>* Concat(Sequence<T>* list) {//(конкатенация)
        for (int i = 0; i < list->GetLength(); ++i) {//добавляю в DATA все элементы из list,её Size увеличивается
            DATA.Append(list->Get(i));
        }
        T* items;
        items = (T*)malloc(sizeof(T*) * (DATA.GetLength() + list->GetLength()));
        for (int i = 0; i < DATA.GetLength(); ++i) {//записываю все элементы из DATA  в массив
            items[i] = DATA.Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items, DATA.GetLength());//создание нового экземпляра
        return result;
    }

    LinkedListSequence(const LinkedList<T>& list) {//конструктор по объекту
        LinkedList<T>* tmp = new LinkedList<T>(list);
        std::cout << "Constructor by object . . .\n";
        DATA = *tmp;
    }
    LinkedListSequence<T>* GetSubsequence(int startIndex, int endIndex) {//получить подпоследовательность: начиная со startIndex - заканчивая endIndex
        LinkedList<T>* tmp = DATA.GetSubLinkedList(startIndex, endIndex);//создаем экземляр с указанными индексами
        T* items;
        items = (T*)malloc(sizeof(T*) * (endIndex - startIndex));
        for (int i = 0; i < endIndex - startIndex; ++i) {
            items[i] = tmp->Get(i);
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(items, endIndex - startIndex);

        return result;
    }
    int GetLength() {
        return DATA.GetLength();
    }
    T GetFirst() {
        DATA.GetFirst();
    }
    T GetLast() {
        DATA.GetLast();
    }
    T Get(int index) {
        DATA.Get(index);
    }

    void Append(T item) {
        DATA.Append(item);
    }
    void Prepend(T item) {
        DATA.Prepend(item);
    }
    void InsertAt(T item, int index) {
        DATA.InsertAt(item, index);
    }
    void removeAt(int index) {
        DATA.removeAt(index);
    }
    void Print() {
        DATA.PrintFromBegin();
    }
private:
    LinkedList<T> DATA;
};
//==================================================================================================================//

template <typename T>
class Queue {//класс
private:
    int size;
    Stack<T> DATA;
public:
    
    Queue() {//конструктор по умолчанию
        size = 0;
        Stack<T>* tmp = new Stack<T>();
        DATA = *tmp;
    }
    Queue(int size, T* values) {//конструктор по массиву и количеству элементов в нём
        this->size = size;
        Stack<T>* tmp = new Stack<T>(values, size);
        DATA = *tmp;
    }
    Queue(Stack<T>* example, int size_of_example) {//конструктор по стеку и количеству элементов
        this->size = size_of_example;
        DATA = *example;
    }
    //------------------------------------------------------------------------//геттеры
    T GetFirst() {
        return DATA.Get(0);
    }
    T GetLast() {
        return DATA.Get(size - 1);
    }
    int GetSize() {
        return size;
    }
    Stack<T>* GetDATA() {
        return &DATA;
    }
    //------------------------------------------------------------------------//
    void Append(T value) { //метод добавления нового элемента
        DATA.Append(value);//добавляем элемент в начало
        DATA.PopBack();//и удаляем элемент с конца
    }
    //------------------------------------------------------------------------//
    //map
    //where
    //reduce
    void Map(T(*func)(T)) {
        DATA.Map(func);
    }
    void Where(bool(*func)(T)) {
        DATA = *DATA.Where(func);
    }
    T Reduce(T(*func)(T, T)) {
        return DATA.Reduce(func);
    }
    //------------------------------------------------------------------------//
    void Print() {
        DATA.Print();
    }
    //------------------------------------------------------------------------//
    //извлечение подпоследовательности из очереди
    Queue<T>* GetSubQueue(int start, int end) {
        Stack<T>* tmp = (DATA.GetSubsequenceFromStack(start, end));
        Queue<T>* result = new Queue<T>(tmp, tmp->GetSize());
        return result;
    }

    void BubbleSortQueue() {//сортировка очереди по возрастанию элементов
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (DATA.Get(i) <= DATA.Get(j)) {
                    T tmp = DATA.Get(i);
                    DATA.Set(i, DATA.Get(j));
                    DATA.Set(j, tmp);
                }
            }
        }
    }
    //------------------------------------------------------------------------//
    bool IsSubQueue(T* sequence, int size_of_sequence) {//поиск на вхождение подпоследовательности в очередь
        if (size_of_sequence > size)
            return false;

        int index = 0;
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if (DATA.Get(i) == sequence[index]) {
                index++;
                count++;
            }
        }

        if (count == size_of_sequence)
            return true;

        return false;
    }
    //------------------------------------------------------------------------//
    Queue* Concat(Queue<T>* example) {
        DATA = *DATA.Concat(example->GetDATA());
        Queue<T>* result = new Queue<T>(&DATA, size + example->GetSize());
        return result;
    }
};
int main() {
    int flag;
    std::cout << "Testing a stack or a vector,or maybe queue ? (1 - stack , 2 - vector, 3 - queue)\n";
    std::cin >> flag;
    if (flag == 1) {
        //==============================================================//начало демонстрации работы класса Stack
        int n;
        std::cout << "Enter size of stack : \n";
        std::cin >> n;
        std::cout << "Enter " << n << " elements of stack : \n";
        int* tmp1 = new int[n];
        for (int i = 0; i < n; ++i) {
            int elem;
            std::cin >> elem;
            tmp1[i] = elem;
        }
        Stack<int>* first = new Stack<int>(tmp1, n);
        first->Print();//элементы печатаются с конца, так как все операции стека должны происходить и начинаться на последнем элементе

        std::cout << "Enter size of stack : \n";
        std::cin >> n;
        std::cout << "Enter " << n << " elements of stack : \n";
        int* tmp2 = new int[n];
        for (int i = 0; i < n; ++i) {
            int elem;
            std::cin >> elem;
            tmp2[i] = elem;
        }
        Stack<int>* second = new Stack<int>(tmp2, n);
        second->Print();

        int begin, end;
        std::cout << "Enter the start and end indices to get a subsequence on the first stack :\n";
        std::cin >> begin >> end;
        try {//демонстрация работы метода получения подпоследовательности из стека,в случае некорректных индексов выбрасывается исключение
            Stack<int>* sub = first->GetSubsequenceFromStack(begin, end);
            sub->Print();
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
        std::cout << "The result of concatenating the first and second stacks :\n";
        Stack<int>* concat = first->Concat(second);//демонстрация работы функции конкатенации
        concat->Print();
        std::cout << "The first stack after squaring it's elements :\n";
        first->Map(sqr);//возведение всех элементов в квадрат
        first->Print();

        std::cout << "Concatenation result after removing all elements, greater than 7 :\n";
        Stack<int>* for_where = concat->Where(is_more_than_7);
        for_where->Print();

        std::cout << "Sum of all elements in the first stack : " << first->Reduce(sum) << std::endl;
        //==============================================================//окончание демонстрации работы класса Stack

    }
    else {
        if (flag == 2) {
            //==============================================================//начало демонстрации работы класса Vector
            int n;
            std::cout << "Enter size of vector : \n";
            std::cin >> n;
            std::cout << "Enter " << n << " elements of vector : \n";
            int* tmp1 = new int[n];
            for (int i = 0; i < n; ++i) {
                int elem;
                std::cin >> elem;
                tmp1[i] = elem;
            }

            Vector<int>* first = new Vector<int>(tmp1, n);
            first->Print();

            std::cout << "Enter size of vector : \n";
            std::cin >> n;
            std::cout << "Enter " << n << " elements of vector : \n";
            int* tmp2 = new int[n];
            for (int i = 0; i < n; ++i) {
                int elem;
                std::cin >> elem;
                tmp2[i] = elem;
            }
            Vector<int>* second = new Vector<int>(tmp2, n);
            second->Print();

            Vector<int>* sum = first->Sum(second);//демонстрация суммы
            std::cout << "\nSum first and second : \n";
            sum->Print();

            Vector<int>* mult = first->ScalarMultiplication(second);//демонстрация скалярного произведения
            std::cout << "\nScalar Multiplication first on second : \n";
            mult->Print();

            int scalar;
            std::cout << "Enter scalar : \n";
            std::cin >> scalar;

            first->MultiplicationByScalar(scalar);//демонстрация произведения на число
            std::cout << "\nMultiplication first by scalar " << scalar << ":\n";
            first->Print();

            std::cout << "\nCalculating The Vector Norm for first after multiplication by scalar : " << first->CalculatingTheVectorNorm() << "\n";//демонстрация вычисления нормы первого вектора
            //ранее умноженного на скаляр
            //==============================================================//окончание демонстрации работы класса Vector
        }
        else {
            if (flag == 3) {


                int n;
                std::cout << "Enter size of queue : \n";
                std::cin >> n;
                std::cout << "Enter " << n << " elements of queue : \n";
                int* tmp1 = new int[n];
                for (int i = 0; i < n; ++i) {
                    int elem;
                    std::cin >> elem;
                    tmp1[i] = elem;
                }
                Queue<int> first(n, tmp1);
                std::cout << "Queue :\n";
                first.Print();

                int* test_is_sub = new int[4]{ 1,2,3,4 };
                if (first.IsSubQueue(test_is_sub, 4))//демонстрация проверки вхождения последовательности 1 2 3 4 в первую очередь
                    std::cout << "{1, 2, 3, 4} is subqueue of first queue !\n";
                else
                    std::cout << "{1, 2, 3, 4} is not subqueue of first queue !\n";
                std::cout << "Result of BubbleSortQueue :\n";
                first.BubbleSortQueue();
                first.Print();

                std::cout << "Result of Reduce ( sum of all elements in queue ) :\n";
                std::cout << first.Reduce(sum) << std::endl;//+

                std::cout << "Enter start and end indices to get subqueue :\n";//нужно вводить числа,не превышающие размеры очереди
                int start, end;
                std::cin >> start >> end;
                Queue<int>* sub = first.GetSubQueue(start, end);
                sub->Print();

                first.Where(is_more_than_7);//+
                std::cout << "Result of Where ( more than 7 - deleted ) :\n";
                first.Print();

                std::cout << "Result of Map ( sqr ):\n";
                first.Map(sqr);//+
                first.Print();
                //проверка конкатенации
                std::cout << "Test the concatenation of two queues ? Y / N (1 / 2)\n";
                std::cin >> flag;
                if (flag == 1) {
                    int n;
                    std::cout << "Enter size of queue : \n";
                    std::cin >> n;
                    std::cout << "Enter " << n << " elements of queue : \n";
                    int* tmp1 = new int[n];
                    for (int i = 0; i < n; ++i) {
                        int elem;
                        std::cin >> elem;
                        tmp1[i] = elem;
                    }
                    Queue<int> first(n, tmp1);
                    std::cout << "Queue :\n";
                    first.Print();


                    std::cout << "Enter size of queue : \n";
                    std::cin >> n;
                    std::cout << "Enter " << n << " elements of queue : \n";
                    int* tmp2 = new int[n];
                    for (int i = 0; i < n; ++i) {
                        int elem;
                        std::cin >> elem;
                        tmp2[i] = elem;
                    }
                    Queue<int> first2(n, tmp2);
                    std::cout << "Queue :\n";
                    first2.Print();

                    Queue<int>* concat = first.Concat(&first2);
                    concat->Print();
                }
            }
        }
    }

    return 0;
}