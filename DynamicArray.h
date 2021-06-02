#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
template <class T>
class DynamicArray {
private:
    //����
    T* m_DATA;
    int m_size;
    int m_capacity;
public:
    //��������
    DynamicArray() {//����������� �� ���������
        m_DATA = NULL;
        m_size = 0;
        m_capacity = 0;
    }


    void Delete() {
        delete[] this->m_DATA;
    }
    DynamicArray(int size) {//����������� � ������ ���������
        m_size = size;
        m_capacity = size;
        m_DATA = new T[size];
    }

    DynamicArray(T* items, int count) {//���������� ��������
        if (items == nullptr) {
            m_DATA = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else {
            m_size = count;			//�� ����������� �������
            m_capacity = count;
            m_DATA = new T[count];
            for (int i = 0; i < count; ++i)
            {
                m_DATA[i] = items[i];
            }
        }
    }

    DynamicArray(const DynamicArray<T>& dynamicArray) {//���������� �����������
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

    //��������
    void Resize(int newSize) {//����������������� ������
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

    T Get(int index) {
        if (index < 0 || index >= m_capacity)
            throw "\nGet Message : Index Out Of Range\n";
        //std::cout << "\nGet index = " << index << "\n";
        return m_DATA[index];
    }

    void Set(int index, T value) {//������ ������� �� �������
        if (index < 0 || index > m_capacity)
            throw "\nSet Message : Index Out Of Range\n";
        //std::cout << "\nSet DATA = " << value << " index = "<< index <<"\n";
        m_DATA[index] = value;

    }

    int GetSize() const {//�������� ������ �������
        return m_size;
    }

    void Append(T val) {//���������� �������� � ����� �������
        //std::cout << "\nAppend DATA = " << val;
        Resize(m_size + 1);//��������� ��� ������ ��� �������������
        m_DATA[m_size - 1] = val;
    }

    void Prepend(T val) {//���������� �������� � ������ �������
        //std::cout << "\nPrepend DATA = " << val << "\n";
        Resize(m_size + 1);//��������� ��� ������ ��� �������������
        for (int i = m_size - 2; i >= 0; --i)
        {
            m_DATA[i + 1] = m_DATA[i];
        }
        m_DATA[0] = val;
    }

    T& operator [] (int i) {//���������� ��������� "[]" ��� �������� ������
        return m_DATA[i];
    }

    void Print() {
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

    std::string array_to_string() {
        std::string result_str = "";
        for (int i = 0; i < m_size; ++i)
        {
            result_str += std::to_string(m_DATA[i]) + " ";
        }
        return result_str;
    }
};