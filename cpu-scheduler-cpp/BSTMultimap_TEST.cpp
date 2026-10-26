#include <iostream>
#include <string>
#include <cassert>
#include "BSTMultimap.hpp"

using namespace std;

int main()
{
    cout << "Starting BSTMultimap Tests" << endl;

    BSTMultimap<int, string> tree;

    cout << "Testing empty tree..." << endl;
    assert(tree.isEmpty() == true);
    assert(tree.getSize() == 0);
    cout << "Empty tree tests passed." << endl;

    cout << "Testing insert (root)..." << endl;
    tree.insert(50, "Root");
    assert(tree.isEmpty() == false);
    assert(tree.getSize() == 1);
    cout << "Root insertion passed." << endl;

    cout << "Testing insert (children)..." << endl;
    tree.insert(30, "Left Child");
    assert(tree.getSize() == 2);

    tree.insert(70, "Right Child");
    assert(tree.getSize() == 3);
    cout << "Child insertion passed." << endl;

    cout << "Testing insert (grandchildren)..." << endl;
    tree.insert(20, "Left-Left");
    tree.insert(40, "Left-Right");
    tree.insert(60, "Right-Left");
    tree.insert(80, "Right-Right");
    assert(tree.getSize() == 7);
    cout << "Grandchild insertion passed." << endl;

    cout << "Testing insert (duplicates)..." << endl;
    tree.insert(50, "Root Duplicate");
    assert(tree.getSize() == 8);    
    tree.insert(30, "Left Duplicate");
    assert(tree.getSize() == 9);
    cout << "Duplicate insertion passed." << endl;

    cout << "\n ALL BASIC BST TESTS PASSED" << endl;

    cout << "Testing contains..." << endl;
    assert(tree.contains(50) == true);
    assert(tree.contains(30) == true);
    assert(tree.contains(80) == true);
    assert(tree.contains(999) == false); // Key doesn't exist
    cout << "Contains passed." << endl;

    cout << "Testing clear..." << endl;
    tree.clear();
    assert(tree.getSize() == 0);
    assert(tree.isEmpty() == true);
    assert(tree.contains(50) == false);
    cout << "Clear passed." << endl;

    tree.clear();
    cout << "Clear on empty tree passed." << endl;

    cout << "\n*** ALL SEARCH & DESTROY TESTS PASSED ***" << endl;

    cout << "Testing getMin and Iterator..." << endl;

    tree.clear();
    tree.insert(50, "50");
    tree.insert(30, "30");
    tree.insert(70, "70");
    tree.insert(20, "20");
    tree.insert(40, "40");
    tree.insert(60, "60");
    tree.insert(80, "80");

    BSTForwardIterator<int, string> it = tree.getMin();
    assert(it.getKey() == 20);
    assert(it.isPastEnd() == false);

    int expected[] = {20, 30, 40, 50, 60, 70, 80};    
    for (int i = 0; i < 7; i++)
    {
        assert(it.getKey() == expected[i]);
        assert(it.isPastEnd() == false);

        it.next();
    }

    assert(it.isPastEnd() == true);

    cout << "Iterator passed." << endl;

    cout << "\n ALL ITERATOR TESTS PASSED " << endl;

    cout << "Testing getMax..." << endl;
    BSTForwardIterator<int, string> maxIt = tree.getMax();
    assert(maxIt.getKey() == 80);
    cout << "getMax passed." << endl;

    cout << "Testing findFirst/findLast..." << endl;    
    tree.insert(50, "50_First");
    tree.insert(50, "50_Last");     
    tree.clear();
    tree.insert(20, "A");
    tree.insert(20, "B");
    tree.insert(20, "C");

    BSTForwardIterator<int, string> first = tree.findFirst(20);
    BSTForwardIterator<int, string> last = tree.findLast(20);

    assert(first.getValue() == "A");
    assert(last.getValue() == "C");    
    BSTForwardIterator<int, string> missing = tree.findFirst(999);
    assert(missing.isPastEnd() == true);

    cout << "findFirst/findLast passed." << endl;

    cout << "\n ALL TASK 13 TESTS PASSED" << endl;

    cout << "Testing remove..." << endl;
    tree.clear();
    tree.insert(50, "Root");
    tree.insert(20, "Left");
    tree.insert(70, "Right");
    tree.insert(30, "Left-Right (Leaf)");
    tree.insert(60, "Right-Left (Leaf)");
    tree.insert(80, "Right-Right (Leaf)");

    BSTForwardIterator<int, string> it30 = tree.findFirst(30);
    BSTForwardIterator<int, string> next = tree.remove(it30); // Should return 50
    assert(tree.contains(30) == false);
    assert(next.getKey() == 50);
    assert(tree.getSize() == 5);
    cout << "Remove leaf passed." << endl;

    tree.insert(25, "Child of 20");
    BSTForwardIterator<int, string> it20 = tree.findFirst(20);
    next = tree.remove(it20); // Should return 25
    assert(tree.contains(20) == false);
    assert(tree.contains(25) == true);
    assert(next.getKey() == 25);
    cout << "Remove 1-child node passed." << endl;

    BSTForwardIterator<int, string> it50 = tree.findFirst(50);
    next = tree.remove(it50); // Successor is 60 (min of right subtree)
    assert(tree.contains(50) == false);
    assert(next.getKey() == 60);

    BSTForwardIterator<int, string> minIt = tree.getMin();
    assert(minIt.getKey() == 25);
    minIt.next();
    assert(minIt.getKey() == 60); // 25 -> 60
    minIt.next();
    assert(minIt.getKey() == 70); // 60 -> 70

    cout << "Remove 2-child node passed." << endl;

    cout << "\n ALL TASK 14 TESTS PASSED" << endl;

    return 0;
}