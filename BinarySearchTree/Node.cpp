#include "Node.h"

Node::Node()
{
	parent = nullptr;

	childLeft = nullptr;
	childMiddleLeft = nullptr;
	childMiddleRight = nullptr;
	childRight = nullptr;

	keyLeft = 0;
	keyMiddle = 0;
	keyRight = 0;
}

bool Node::IsKeyInNode(int key) const
{
	if (keyLeft == key)
		return true;
	else if (keyMiddle == key)
		return true;
	else if (keyRight == key)
		return true;
	else
		return false;
}

Node* Node::NextNode(int key) const
{
	if (key < keyLeft)
	{
		return childLeft;
	}
	else if (key < keyMiddle)
	{
		return childMiddleLeft;
	}
	else if (key < keyRight)
	{
		return childMiddleRight;
	}
	else
		return childRight;
}

void Node::SetValues(int key1, int key2, int key3)
{
	keyLeft = key1;
	keyMiddle = key2;
	keyRight = key3;
}

string Node::ToString() const
{
	return "[", keyLeft, ", ", keyMiddle, ", ", keyRight, "]";
}

