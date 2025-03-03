#include "Node.h"
#include "Tree.h"

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

void Node::RemoveKey(int key)
{
	for (int i = 0; i < keyAmount; i++)
	{
		if (key == keys[i])
		{
			keys[i] = 0;
			keyAmount--;
		}
	}
}

void Node::ClearChildren()
{
	for (int i = 0; i < maxKeyAmount + 1; i++)
	{
		children[i] = nullptr;
	}
}

void Node::ClearKeys()
{
	for (int i = 0; i < maxKeyAmount; i++)
	{
		keys[i] = 0;
	}
}

void Node::SetKeyAmount()
{
	keyAmount = 0;
	for (int i = 0; i < maxKeyAmount; i++)
	{
		if (keys[i] != 0)
		{
			keyAmount++;
		}
	}
}

void Node::RemoveChild(Node* child)
{
	for (size_t i = 0; i < maxKeyAmount + 1; i++)
	{
		if (children[i] == child)
		{
			children[i] == nullptr;
			return;
		}
	}
}

void Node::AddKeyAndChild(int key, Node* newChild, Node* oldChild)
{
	int keyPos = NodeNeedsKey();

	if (keyAmount >= maxKeyAmount)
	{
		Split(key);
		Node* newThis = parent->children[parent->GetChildLocation(NextNode(key))];

		ClearChildren();
		children[0] = newChild;
		children[1] = oldChild;
		SortChildren();
	}
	else
	{
		AddNewKey(key, keyPos);
		keyAmount++;
		SortKeys();
		SortChildren();

		Node* newChildPosition = NextNode(newChild->keys[0]);
		children[GetChildLocation(newChildPosition)] = newChild;

	}
}

Node* Node::GetLeftSibling()
{
	int thisChildLocation = parent->GetChildLocation(this);
	return parent->children[thisChildLocation - 1];
}

void Node::Split(int key)
{

	cout << to_string(key) + ToString() + "->";

	const int maxKeys = maxKeyAmount + 1;
	int midIndex = (maxKeys) / 2;

	Node* leftSibling = new Node();
	Node* rightSibling = new Node();

	// New Array with all existing keys + this new key
	int keys[maxKeyAmount + 1];
	for (int i = 0; i < keyAmount; i++)
	{
		keys[i] = this->keys[i];
	}
	keys[maxKeyAmount] = key;
	std::sort(keys, keys + maxKeys);

	// Find the middle key
	int midKey = keys[midIndex];

	// Populate leftSibling keys
	for (int i = 0; i < midIndex; i++)
	{
		leftSibling->keys[i] = keys[i];
	}

	// Populate rightSibling keys
	for (int i = maxKeyAmount; i > midIndex; i--)
	{
		rightSibling->keys[i - 1] = keys[i];
	}


	for (int i = 0; i <= midIndex; i++)
	{
		leftSibling->children[i] = children[i];
	}

	for (int i = 0; i < keyAmount - midIndex; i++)
	{
		rightSibling->children[i] = children[i + midIndex];
	}

	leftSibling->SetKeyAmount();
	leftSibling->SortKeys();

	rightSibling->SetKeyAmount();
	rightSibling->SortKeys();

	for (int i = 0; i < leftSibling->keyAmount + 1; i++)
	{
		if (children[i] != nullptr)
		{
			children[i]->parent = leftSibling;
		}
	}

	for (int i = 0; i < rightSibling->keyAmount + 1; i++)
	{
		if (children[i] != nullptr)
		{
			children[i]->parent = rightSibling;
		}
	}

	cout << leftSibling->ToString() + to_string(midKey) + rightSibling->ToString() << endl;

	// if this was head
	if (parent == nullptr)
	{
		Node* newRoot = new Node();
		newRoot->keys[0] = midKey;
		newRoot->keyAmount = 1;
		newRoot->children[0] = leftSibling;
		newRoot->children[1] = rightSibling;
		leftSibling->parent = newRoot;
		rightSibling->parent = newRoot;
		this->parent = newRoot;
		newRoot->SortChildren();
	}
	// if parent does not have max children
	else if (!parent->HasMaxChildren())
	{
		leftSibling->parent = parent;
		rightSibling->parent = parent;

		parent->AddKeyAndChild(midKey, leftSibling, rightSibling);
	}
	// if this is the right childnode
	else if (parent->GetChildLocation(NextNode(key)) > midIndex)
	{
		parent->children[parent->GetChildLocation(this)] = rightSibling;
		AddKeyAndChild(midKey, leftSibling, rightSibling);
	}
	// if this is the left childnode
	else if (parent->GetChildLocation(NextNode(key)) < midIndex)
	{
		parent->children[parent->GetChildLocation(this)] = leftSibling;
		AddKeyAndChild(midKey, rightSibling, leftSibling);
	}
	// if this is the middle childnode
	else
	{
		parent->Split(midKey);

		parent->children[0] = rightSibling;
		rightSibling->parent = parent;

		Node* parentLeftSibling = parent->GetLeftSibling();
		parentLeftSibling->children[1] = leftSibling;
		leftSibling->parent = parentLeftSibling;
	}
	std::cout << "Split to: " + leftSibling->ToString() + rightSibling->ToString() + " with parent " + leftSibling->parent->ToString() << endl;
}

int Node::GetKeyPos(int key)
{
	for (int i = 0; i < keyAmount; i++)
	{
		if (key == keys[i])
		{
			return i;
		}
	}

	return -1;
}

int Node::GetChildLocation(Node* child)
{
	for (int i = 0; i < keyAmount + 1; i++)
	{
		if (children[i] == child)
		{
			return i;
		}
	}

	return -1;
}

Node* Node::NextNode(int key) const
{
	for (int i = 0; i < keyAmount; i++)
	{
		if (key < keys[i])
		{
			return children[i];
		}
	}
	return children[keyAmount];
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
	for (int i = 0; i < maxKeyAmount; i++)
	{
		if (keys[i] == 0)
		{
			for (int j = i; j < maxKeyAmount; j++)
			{
				if (j + 1 == maxKeyAmount)
				{
					keys[j] = 0;
				}
				else
				{
					keys[j] = keys[j + 1];

				}
			}
		}
	}

	std::sort(keys, keys + keyAmount);

	if (!IsLeaf())
	{
		SortChildren();
	}
}

void Node::SortChildren()
{
	Node* nodes[maxKeyAmount + 1];

	for (int i = 0; i <= maxKeyAmount; i++)
	{
		nodes[i] = nullptr;
	}

	for (int i = 0; i <= keyAmount; i++)
	{
		if (children[i] != nullptr)
		{
			nodes[GetChildLocation(NextNode(children[i]->keys[0]))] = children[i];
		}
	}

	for (int i = 0; i <= maxKeyAmount; i++)
	{
		if (i <= keyAmount && nodes[i] != nullptr)
		{
			children[i] = nodes[i];
		}
		else
		{
			children[i] = nullptr;
		}
	}
}

bool Node::HasMaxChildren()
{
	for (int i = 0; i < maxKeyAmount + 1; i++)
	{
		if (children[i] == nullptr)
		{
			return false;
		}
	}

	return true;
}

int Node::GetMiddleKey(int* keys)
{
	return keys[(maxKeyAmount + 1) / 2];
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
	for (int i = 0; i < keyAmount; i++)
	{
		if (keys[i] != 0)
			str += to_string(keys[i]) + ", ";
	}
	if (str != "[")
	{
		str.pop_back();
		str.pop_back();
	}

	str += "]";
	return str;
}

