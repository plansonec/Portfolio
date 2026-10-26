#include <iostream>
#include <string>
#include <cassert>
#include "LinkedList.hpp"

using namespace std;

int main()
{
    cout << "Starting int tests:" << endl;

    //Test constructors
    LinkedList<int> list1;

    cout << "Testing isEmpty, getSize..." << endl;
    assert(list1.isEmpty() == true);
    assert(list1.getSize() == 0);

    cout << "Testing pushBack, popBack, getBack..." << endl;
    list1.pushBack(10);
    assert(list1.isEmpty() == false);
    assert(list1.getSize() == 1);
    assert(list1.getBack() == 10);

    list1.pushBack(20);
    assert(list1.getSize() == 2);
    assert(list1.getBack() == 20);

    list1.popBack();
    assert(list1.getSize() == 1);
    assert(list1.getBack() == 10);

    list1.pushBack(30);
    assert(list1.getSize() == 2);
    assert(list1.getBack() == 30);
    cout << "pushBack, popBack, getBack tests passed!" << endl;

    cout << "Testing pushFront, popFront, getFront..." << endl;
    LinkedList<int> list2;

    list2.pushFront(10);
    assert(list2.getFront() == 10);
    assert(list2.getBack() == 10);
    assert(list2.getSize() == 1);

    list2.pushFront(20);
    assert(list2.getFront() == 20);
    assert(list2.getBack() == 10);
    assert(list2.getSize() == 2);

    list2.popFront();
    assert(list2.getFront() == 10);
    assert(list2.getSize() == 1);

    list2.pushBack(40);
    assert(list2.getFront() == 10);
    assert(list2.getBack() == 40);

    list2.popFront();
    assert(list2.getFront() == 40);
    assert(list2.getSize() == 1);
    cout << "pushFront, popFront, getFront tests passed!" << endl;

    cout << "Testing getItem, setItem..." << endl;
    assert(list1.getItem(0) == 10);
    assert(list1.getItem(1) == 30);

    list1.setItem(1, 35);
    assert(list1.getItem(1) == 35);
    cout << "getItem, setItem tests passed!" << endl;

    cout << "Testing insert, remove..." << endl;
    list1.insert(0, 5);
    assert(list1.getSize() == 3);
    assert(list1.getItem(0) == 5);
    assert(list1.getItem(1) == 10);
    assert(list1.getItem(2) == 35);

    list1.remove(1);
    assert(list1.getSize() == 2);
    assert(list1.getItem(0) == 5);
    assert(list1.getItem(1) == 35);
    cout << "insert, remove tests passed!" << endl;

    cout << "All int tests passed" << endl;

    cout << "\n--- Starting String Tests ---" << endl;

    //Test constructors
    LinkedList<string> s_list1;

    cout << "Testing isEmpty, getSize..." << endl; // Removed getCapacity
    assert(s_list1.isEmpty() == true);
    assert(s_list1.getSize() == 0);

    cout << "Testing pushBack, popBack, getBack..." << endl;
    s_list1.pushBack("hello");
    assert(s_list1.isEmpty() == false);
    assert(s_list1.getSize() == 1);
    assert(s_list1.getBack() == "hello");

    s_list1.pushBack("world");
    assert(s_list1.getSize() == 2);
    assert(s_list1.getBack() == "world");

    s_list1.popBack();
    assert(s_list1.getSize() == 1);
    assert(s_list1.getBack() == "hello");

    s_list1.pushBack("!");
    assert(s_list1.getSize() == 2);
    assert(s_list1.getBack() == "!");
    cout << "pushBack, popBack, getBack tests passed" << endl;

    cout << "Testing pushFront, popFront, getFront..." << endl;
    LinkedList<string> s_list2;

    s_list2.pushFront("ten");
    assert(s_list2.getFront() == "ten");
    assert(s_list2.getBack() == "ten");
    assert(s_list2.getSize() == 1);

    s_list2.pushFront("twenty");
    assert(s_list2.getFront() == "twenty");
    assert(s_list2.getBack() == "ten");
    assert(s_list2.getSize() == 2);

    s_list2.popFront();
    assert(s_list2.getFront() == "ten");
    assert(s_list2.getSize() == 1);

    s_list2.pushBack("forty");
    assert(s_list2.getFront() == "ten");
    assert(s_list2.getBack() == "forty");

    s_list2.popFront();
    assert(s_list2.getFront() == "forty");
    assert(s_list2.getSize() == 1);
    cout << "pushFront, popFront, getFront tests passed" << endl;

    cout << "Testing getItem, setItem..." << endl;
    assert(s_list1.getItem(0) == "hello");
    assert(s_list1.getItem(1) == "!");

    s_list1.setItem(1, "world");
    assert(s_list1.getItem(1) == "world");
    cout << "getItem, setItem tests passed" << endl;

    cout << "Testing insert, remove..." << endl;
    s_list1.insert(0, "Well,");
    assert(s_list1.getSize() == 3);
    assert(s_list1.getItem(0) == "Well,");
    assert(s_list1.getItem(1) == "hello");
    assert(s_list1.getItem(2) == "world");

    s_list1.remove(1);
    assert(s_list1.getSize() == 2);
    assert(s_list1.getItem(0) == "Well,");
    assert(s_list1.getItem(1) == "world");
    cout << "insert, remove tests passed" << endl;

    cout << "All string tests passed" << endl;

    cout << "\n All LinkedList tests passed" << endl;

    return 0;
}