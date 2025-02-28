#include "Tree.h"

Tree::Tree()
{
	head = nullptr;
}

void Tree::Insert(Node* newNode)
{
	int key = 0;

	for (int i = 0; i < newNode->keyAmount; i++)
	{
		if (newNode->keys[i] != 0)
		{
			key = newNode->keys[i];
			break;
		}
	}

	if (key == 0)
	{
		cout << "Err: No value in node" << endl;
		return;
	}

	InsertMethod(key, head);
}

void Tree::Insert(int key)
{
	if (key == 0)
	{
		cout << "Err: Key cannot be zero" << endl;
		return;
	}

	InsertMethod(key, head);
}

void Tree::InsertMethod(int key, Node* from)
{
	if (from->IsKeyInNode(key))
	{
		cout << "Err: Key already in tree" << endl;
		return;
	}

	Node* nextNode = from->NextNode(key);
	// If a child node exists at the correct position -> go there
	if (nextNode != nullptr)
	{
		InsertMethod(key, nextNode);
	}

	int positionToAddKey = from->NodeNeedsKey();
	// If there was no child node, but the current node isnt full
	if (positionToAddKey != -1)
	{
		from->AddNewKey(key, positionToAddKey);
		cout << "Key was added to an existing node! Node: " + from->ToString() << endl;
		return;
	}

	//If there was no child node and the current node is full
	tuple<int, Node*> stuff = from->SplitNodeInMiddle(key);
	int newKey = get<0>(stuff);
	Node* splitNodes = get<1>(stuff);

	from->parent->Restructure(newKey, splitNodes);

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


