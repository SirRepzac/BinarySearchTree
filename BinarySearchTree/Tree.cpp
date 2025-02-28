#include "Tree.h"

Tree::Tree()
{
	head = nullptr;
}

void Tree::Insert(Node* newNode)
{
}

Node* Tree::Find(int key)
{
	return FindMethod(key, head);
}

Node* Tree::FindMethod(int key, Node* from)
{
	if (from == nullptr)
		return nullptr;

	if (from->IsKeyInNode(key))
		return from;

	Node* nextNode = from->NextNode(key);

	FindMethod(key, nextNode);
}
