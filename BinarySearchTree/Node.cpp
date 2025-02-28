#include "Node.h"

Node::Node()
{
	keyAmount = 0;

	parent = nullptr;

	for (int i = 0; i < (maxKeyAmount + 1); i++)
	{
		children[i] = nullptr;
	}

	for (int i = 0; i < maxKeyAmount; i++)
	{
		keys[i] = 0;
	}
}

bool Node::IsKeyInNode(int key) const
{
	for (int i = 0; i < keyAmount; i++)
	{
		if (key == keys[i] && key != 0)
		{
			return true;
		}
	}

	return false;
}

Node* Node::NextNode(int key) const
{
	for (int i = 0; i < keyAmount; i++)
	{
		if (key < keys[i])
		{
			return children[i];
		}
		else
			return children[keyAmount];
	}

}

int Node::NodeNeedsKey()
{
	for (int i = 0; i < maxKeyAmount; i++)
	{
		if (keys[i] == 0)
			return i;
	}

	return -1;
}

void Node::AddNewKey(int key, int position)
{
	keys[position] = key;
}

void Node::SortKeys()
{
	std::sort(keys, keys + keyAmount);
}

int Node::GetMiddleKey(int* keys)
{
	return keys[(maxKeyAmount + 1) / 2];
}

int* Node::GetExtendedKeysSorted(int key)
{
	int allKeys[maxKeyAmount + 1];
	for (int i = 0; i < maxKeyAmount; i++)
	{
		allKeys[i] = keys[i];
	}

	allKeys[maxKeyAmount] = key;

	std::sort(allKeys, allKeys + (maxKeyAmount + 1));
	return allKeys;
}

bool Node::IsLeaf()
{
	if (this == nullptr)
		return true;

	for (int i = 0; i < maxKeyAmount + 1; i++)
	{
		if (children[i] != nullptr)
		{
			return false;
		}
	}

	return true;
}

void Node::SetValues(int* keys)
{
	for (int i = 0; i < maxKeyAmount; i++)
	{
		this->keys[i] = keys[i];
	}
}

string Node::ToString() const
{
	string str = "[";
	for (int i = 0; i < maxKeyAmount; i++)
	{
		str += to_string(keys[i]) + ", ";
	}

	str.pop_back();
	str.pop_back();

	str += "]";
	return str;
}

