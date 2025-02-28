#include "Node.h"

Node::Node()
{
	parent = nullptr;

	for (int i = 0; i < keyAmount + 1; i++)
	{
		children[i] = nullptr;
	}

	for (int i = 0; i < keyAmount; i++)
	{
		keys[i] = 0;
	}
}

bool Node::IsKeyInNode(int key) const
{
	for (int i = 0; i < keyAmount; i++)
	{
		if (key == keys[i])
		{
			return true;
		}
	}

	return false;
}

Node* Node::NextNode(int key) const
{
	if (key < keyLeft)
	{
		return childLeft;
	}
	else if (key < keyRight)
	{
		return childMiddle;
	}
	else
		return childRight;
}

int Node::NodeNeedsKey()
{
	for (int i = 0; i < keyAmount; i++)
	{
		if (keys[i] == 0)
			return i;
	}

	return -1;
}

void Node::AddNewKey(int key, int position)
{
	keys[position] = key;
	SortKeys();
}

void Node::SortKeys()
{
    int nonZeroKeys[keyAmount];
    int zeroKeys[keyAmount];
    int nonZeroCount = 0;
    int zeroCount = 0;

    // Separate non-zero keys and zero keys
    for (int i = 0; i < keyAmount; i++) {
        if (keys[i] == 0) {
            zeroKeys[zeroCount++] = keys[i];
        } else {
            nonZeroKeys[nonZeroCount++] = keys[i];
        }
    }

    // Sort non-zero keys
    std::sort(nonZeroKeys, nonZeroKeys + nonZeroCount);

    // Merge non-zero keys and zero keys
    int midIndex = nonZeroCount / 2;

    for (int i = 0; i < midIndex; i++) {
        keys[i] = nonZeroKeys[i];
    }
    for (int i = 0; i < zeroCount; i++) {
        keys[midIndex + i] = zeroKeys[i];
    }
    for (int i = midIndex; i < nonZeroCount; i++) {
        keys[zeroCount + i] = nonZeroKeys[i];
    }
}

int Node::GetMiddleKey(int* keys)
{
	return keys[(keyAmount + 1) / 2];
}

int* Node::GetExtendedKeysSorted(int key)
{
	int allKeys[keyAmount + 1];
	for (int i = 0; i < keyAmount; i++)
	{
		allKeys[i] = keys[i];
	}

	allKeys[keyAmount] = key;

	std::sort(allKeys, allKeys + (keyAmount + 1));
	return allKeys;
}

tuple<int, Node*> Node::SplitNodeInMiddle(int key)
{

	int* allKeysOrdered = GetExtendedKeysSorted(key);
	Node nodes[2];

	int middleKey = GetMiddleKey(allKeysOrdered);
	int leftKeys[(keyAmount + 1) / 2];
	int rightKeys[(keyAmount + 1) / 2];



	Node leftNode = Node();
	Node rightNode = Node();

	for (int i = 0; i < middleKey; i++)
	{
		leftKeys[i] = allKeysOrdered[i];
		rightKeys[i] = allKeysOrdered[(middleKey + 1) + i];
	}

	leftNode.SetValues(leftKeys);
	rightNode.SetValues(rightKeys);

	nodes[0] = leftNode;
	nodes[1] = rightNode;

	return tuple<int, Node*>(middleKey, nodes);
}

void Node::Restructure(int key, Node* nodes)
{
	int positionToAddKey = NodeNeedsKey();

	// current node isnt full
	if (positionToAddKey != -1)
	{
		AddNewKey(key, positionToAddKey);

		for (int i = 0; i < keyAmount; i++)
		{
			if (key == keys[i])
			{
				children[i] = &nodes[0];
				children[i + 1] = &nodes[1];
			}

		}
		cout << "Key was moved to an existing node! Node: " + ToString() << endl;
		return;
	}

	int* sorted = GetExtendedKeysSorted(key);

	for (int i = 0; i < keyAmount + 1; i++)
	{
		if (key == sorted[i])
		{
			// placed to the left of middle in the new node
			if (i < (keyAmount + 1) / 2)
			{
				children[i] = &nodes[0];
			}
			// placed to the right in the new node
			else if (i > (keyAmount + 1) / 2)
			{
				children[i + 1] = &nodes[1];
			}
			// placed in the middle in the new node
			else
			{

			}
		}

	}

	if (parent != nullptr)
	{
		parent->Restructure()
	}

}

void Node::SetValues(int* keys)
{
	for (int i = 0; i < keyAmount; i++)
	{
		this->keys[i] = keys[i];
	}
}

string Node::ToString() const
{
	string str = "[";
	for (int i = 0; i < keyAmount; i++)
	{
		str += to_string(keys[i]) + ", ";
	}

	str.pop_back();
	str.pop_back();

	str += "]";
	return str;
}

