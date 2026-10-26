#include <iostream>
#include <string>
#include <cassert>
#include "ArrayList.hpp"

using namespace std;

int main()
{
    cout << "Starting int tests:" << endl;

    //Test constructors
    ArrayList<int> list1;
    ArrayList<int> list2(5); 

    cout << "Testing isEmpty, getSize, getCapacity..." << endl;
    assert(list1.isEmpty() == true);
    assert(list1.getSize() == 0);
    assert(list1.getCapacity() == 10);
    assert(list2.getCapacity() == 5);

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
    ArrayList<int> list3;

    list3.pushFront(10);
    assert(list3.getFront() == 10);
    assert(list3.getBack() == 10);
    assert(list3.getSize() == 1);

    list3.pushFront(20);
    assert(list3.getFront() == 20);
    assert(list3.getBack() == 10);
    assert(list3.getSize() == 2);

    list3.popFront();
    assert(list3.getFront() == 10);
    assert(list3.getSize() == 1);

    list3.pushBack(40);
    assert(list3.getFront() == 10);
    assert(list3.getBack() == 40);

    list3.popFront();
    assert(list3.getFront() == 40);
    assert(list3.getSize() == 1);
    cout << "pushFront, popFront, getFront tests passed!" << endl;

    cout << "Testing getItem, setItem..." << endl;
    assert(list1.getItem(0) == 10);
    assert(list1.getItem(1) == 30);

    list1.setItem(1, 35);
    assert(list1.getItem(1) == 35);
    cout << "getItem, setItem tests passed!" << endl;

    // list1 is currently [10, 35], size 2
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

    cout << "Testing resize..." << endl;
    ArrayList<int> list4(2);
    assert(list4.getCapacity() == 2);
    list4.pushBack(1);
    list4.pushBack(2);
    assert(list4.getCapacity() == 2);

    list4.pushBack(3);
    assert(list4.getSize() == 3);
    assert(list4.getCapacity() == 4);
    assert(list4.getItem(2) == 3);
    cout << "resize tests passed!" << endl;

    cout << "All int tests passed" << endl;

    cout << "\n--- Starting String Tests ---" << endl;

    //Test constructors
    ArrayList<string> s_list1;
    ArrayList<string> s_list2(5);

    cout << "Testing isEmpty, getSize, getCapacity..." << endl;
    assert(s_list1.isEmpty() == true);
    assert(s_list1.getSize() == 0);
    assert(s_list1.getCapacity() == 10);
    assert(s_list2.getCapacity() == 5);

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
    ArrayList<string> s_list3;

    s_list3.pushFront("ten");
    assert(s_list3.getFront() == "ten");
    assert(s_list3.getBack() == "ten");
    assert(s_list3.getSize() == 1);

    s_list3.pushFront("twenty");
    assert(s_list3.getFront() == "twenty");
    assert(s_list3.getBack() == "ten");
    assert(s_list3.getSize() == 2);

    s_list3.popFront();
    assert(s_list3.getFront() == "ten");
    assert(s_list3.getSize() == 1);

    s_list3.pushBack("forty");
    assert(s_list3.getFront() == "ten");
    assert(s_list3.getBack() == "forty");

    s_list3.popFront();
    assert(s_list3.getFront() == "forty");
    assert(s_list3.getSize() == 1);
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

    cout << "Testing resize..." << endl;
    ArrayList<string> s_list4(2);
    assert(s_list4.getCapacity() == 2);
    s_list4.pushBack("a");
    s_list4.pushBack("b");
    assert(s_list4.getCapacity() == 2);

    s_list4.pushBack("c"); 
    assert(s_list4.getSize() == 3);
    assert(s_list4.getCapacity() == 4); 
    assert(s_list4.getItem(2) == "c");
    cout << "resize tests passed" << endl;

    cout << "All string tests passed" << endl;

    cout << "\n ALL ARRAYLIST TESTS PASSED" << endl;

    return 0;
}