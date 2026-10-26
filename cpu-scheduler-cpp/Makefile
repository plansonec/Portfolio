# Makefile for C++ CPU Process Scheduler & Custom Data Structures Suite
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGETS = schedulesim ArrayList_TEST LinkedList_TEST BSTMultimap_TEST RoundRobin_TEST CompletelyFair_TEST

all: $(TARGETS)

schedulesim: schedulesim.cpp Simulate.cpp Scheduler.cpp Process.cpp ArrayList.hpp ArrayList.tpp LinkedList.hpp LinkedList.tpp BSTMultimap.hpp BSTMultimap.tpp
	$(CXX) $(CXXFLAGS) schedulesim.cpp Simulate.cpp Scheduler.cpp Process.cpp -o schedulesim

ArrayList_TEST: ArrayList_TEST.cpp ArrayList.hpp ArrayList.tpp List.hpp
	$(CXX) $(CXXFLAGS) ArrayList_TEST.cpp -o ArrayList_TEST

LinkedList_TEST: LinkedList_TEST.cpp LinkedList.hpp LinkedList.tpp LinkedListNode.hpp LinkedListNode.tpp List.hpp
	$(CXX) $(CXXFLAGS) LinkedList_TEST.cpp -o LinkedList_TEST

BSTMultimap_TEST: BSTMultimap_TEST.cpp BSTMultimap.hpp BSTMultimap.tpp BSTNode.hpp BSTNode.tpp BSTForwardIterator.hpp BSTForwardIterator.tpp
	$(CXX) $(CXXFLAGS) BSTMultimap_TEST.cpp -o BSTMultimap_TEST

RoundRobin_TEST: RoundRobin_TEST.cpp Scheduler.cpp Process.cpp ArrayList.hpp LinkedList.hpp
	$(CXX) $(CXXFLAGS) RoundRobin_TEST.cpp Scheduler.cpp Process.cpp -o RoundRobin_TEST

CompletelyFair_TEST: CompletelyFair_TEST.cpp Scheduler.cpp Process.cpp BSTMultimap.hpp
	$(CXX) $(CXXFLAGS) CompletelyFair_TEST.cpp Scheduler.cpp Process.cpp -o CompletelyFair_TEST

test: $(TARGETS)
	./ArrayList_TEST
	./LinkedList_TEST
	./BSTMultimap_TEST
	./RoundRobin_TEST
	./CompletelyFair_TEST

benchmark: schedulesim
	./schedulesim 10 10 100000
	./schedulesim 100 100 100000

clean:
	rm -f $(TARGETS) *.o

.PHONY: all test benchmark clean
