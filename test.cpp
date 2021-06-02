#include "pch.h"
#include <gtest/gtest.h>
#include "LinkedList.h"
#include "DynamicArray.h"
TEST(append_test, test1) {//�������� ���������� ��������� � ���������� ������
    LinkedList<int> a;
    for (int i = 0; i < 10; ++i)
    {
        a.Append(i + 1);
    }
    EXPECT_EQ(a.list_to_string(),"1 2 3 4 5 6 7 8 9 10 ");
    EXPECT_TRUE(true);
    
}
TEST(insert_test, test2) {//�������� ������� �� �������
    LinkedList<int> a;
    for (int i = 0; i < 10; ++i)
    {
        a.Append(i + 1);
    }
    a.InsertAt(95, 4);
    EXPECT_EQ(a.Get(4), 95);
    EXPECT_TRUE(true);
}
TEST(remove_test, test3) {//�������� �������� �� �������
    LinkedList<int> a;
    for (int i = 0; i < 10; ++i)
    {
        a.Append(i + 1);
    }
    a.removeAt(4);
    EXPECT_EQ(a.Get(3), 4);
    EXPECT_TRUE(true);
}
TEST(get_first_test, test4) {//�������� ��������� ������� ��������
    LinkedList<int> a;
    for (int i = 0; i < 10; ++i)
    {
        a.Append(i + 1);
    }
    
    EXPECT_EQ(a.GetFirst(), 1);
    EXPECT_TRUE(true);
}
TEST(get_last_test, test5) {//�������� ��������� ���������� ��������
    LinkedList<int> a;
    for (int i = 0; i < 10; ++i)
    {
        a.Append(i + 1);
    }

    EXPECT_EQ(a.GetLast(), 10);
    EXPECT_TRUE(true);
}
TEST(pop_front_test, test6) {//�������� �������� ������� ��������
    LinkedList<int> a;
    for (int i = 0; i < 10; ++i)
    {
        a.Append(i + 1);
    }
    a.pop_front();
    EXPECT_EQ(a.GetFirst(), 2);
    EXPECT_TRUE(true);
}
TEST(pop_back_test, test7) {//�������� �������� ���������� ��������
    LinkedList<int> a;
    for (int i = 0; i < 10; ++i)
    {
        a.Append(i + 1);
    }
    a.pop_back();
    EXPECT_EQ(a.GetLast(), 9);
    EXPECT_TRUE(true);
}
TEST(concat_test, test8) {//�������� ������������
    LinkedList<int>* a = new LinkedList<int>();
    for (int i = 0; i < 10; ++i)
    {
        a->Append(i + 1);
    }
    LinkedList<int>* b = new LinkedList<int>();
    for (int i = 0; i < 10; ++i)
    {
        b->Append(i + 1);
    }
    LinkedList<int>* result = a->Concat(b);
    EXPECT_EQ(result->list_to_string(), "1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10 ");
    EXPECT_TRUE(true);
}
TEST(get_sub_linked_list_test, test9) {//�������� ���������� ��������� �� ��������
    LinkedList<int>* a = new LinkedList<int>();
    for (int i = 0; i < 10; ++i)
    {
        a->Append(i + 1);
    }
    LinkedList<int>* result = a->GetSubLinkedList(3, 6);
    EXPECT_EQ(result->list_to_string(),"4 5 6 7 ");
    EXPECT_TRUE(true);
}
//=====================================================================================================================//
TEST(append_test, test10) {//�������� ���������� ��������� � ����� ������������� �������
    DynamicArray<int> a;
    for (int i = 0; i < 10; i++)
    {
        a.Append(i + 1);
    }
    EXPECT_EQ(a.array_to_string(), "1 2 3 4 5 6 7 8 9 10 ");
    EXPECT_TRUE(true);
}
TEST(prepend_test, test11) {//�������� ���������� �������� � ������ ������������� �������
    DynamicArray<int> a;
    for (int i = 0; i < 10; i++)
    {
        a.Prepend(i + 1);
    }
    EXPECT_EQ(a.array_to_string(), "10 9 8 7 6 5 4 3 2 1 ");
    EXPECT_TRUE(true);
}
TEST(get_test, test12) {//�������� ���������� �������� � ������ ������������� �������
    DynamicArray<int> a;
    for (int i = 0; i < 10; i++)
    {
        a.Append(i + 1);
    }
    EXPECT_EQ(a.Get(5), 6);
    EXPECT_TRUE(true);
}