#pragma once
#include <iostream>
using namespace std;


class Tree;

class Node
{
	friend Tree;

	Node* parent;

	Node* childRight;
	Node* childMiddleRight;
	Node* childMiddleLeft;
	Node* childLeft;

	int keyLeft;
	int keyMiddle;
	int keyRight;


	bool IsKeyInNode(int key) const;

	Node* NextNode(int key) const;

public:

	Node();

	void SetValues(int key1, int key2, int key3);

	string ToString() const;


};