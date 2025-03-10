#include "BTreeNode.h"
#include "BTreeTree.h"

BTreeNode::BTreeNode()
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

bool BTreeNode::IsKeyInNode(int key) const
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

void BTreeNode::RemoveKey(int key)
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

void BTreeNode::ClearChildren()
{
	for (int i = 0; i < maxKeyAmount + 1; i++)
	{
		children[i] = nullptr;
	}
}

void BTreeNode::ClearKeys()
{
	for (int i = 0; i < maxKeyAmount; i++)
	{
		keys[i] = 0;
	}
}

void BTreeNode::SetKeyAmount()
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

void BTreeNode::RemoveChild(BTreeNode* child)
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

void BTreeNode::AddKey(int key)
{
	if (keyAmount >= maxKeyAmount)
	{
		tuple<int, tuple<BTreeNode*, BTreeNode*>> items = Split(key);
		int midKey = items._Myfirst._Val;
		tuple<BTreeNode*, BTreeNode*> splitResults = items._Get_rest()._Myfirst._Val;
		BTreeNode* leftSibling = splitResults._Myfirst._Val;
		BTreeNode* rightSibling = splitResults._Get_rest()._Myfirst._Val;




		// if this was head
		if (parent == nullptr)
		{
			BTreeNode* newRoot = new BTreeNode();
			newRoot->keys[0] = midKey;
			newRoot->keyAmount = 1;
			newRoot->children[0] = leftSibling;
			newRoot->children[1] = rightSibling;
			leftSibling->parent = newRoot;
			rightSibling->parent = newRoot;
			this->parent = newRoot;
			for (int i = 0; i < maxKeyAmount + 1; i++)
			{
				if (children[i] != nullptr)
				{
					if (i < maxKeyAmount / 2)
					{
						children[i]->parent = leftSibling;
					}
					else
					{
						children[i]->parent = rightSibling;
					}
				}
			}
		}
		else
		{
			parent->AddKey(midKey);
			// Parent just split
			if (parent->keyAmount == 1)
			{
				// If the current parent is incorrect, find the correct parent
				if (parent->keys[0] != midKey)
				{
					BTreeNode* realParent = parent;

					for (int i = 0; i < maxKeyAmount + 1; i++)
					{
						if (parent->parent->children[i] != nullptr)
						{

							if (parent->parent->children[i]->keys[0] == midKey)
							{
								realParent = parent->parent->children[i];
							}
						}
					}

					realParent->children[0] = leftSibling;
					realParent->children[1] = rightSibling;
					leftSibling->parent = realParent;
					rightSibling->parent = realParent;
				}
				else
				{

					parent->children[0] = leftSibling;
					parent->children[1] = rightSibling;
					leftSibling->parent = parent;
					rightSibling->parent = parent;
				}
			}
			// Parent now has 3 children
			else
			{
				parent->children[parent->GetChildLocation(this)] = nullptr;
				parent->children[parent->GetChildLocation(nullptr)] = leftSibling;
				parent->children[parent->GetChildLocation(nullptr)] = rightSibling;

				leftSibling->parent = parent;
				rightSibling->parent = parent;

				parent->SortChildren();
			}
		}
		cout << "Split to: " + leftSibling->ToString() + rightSibling->ToString() + " with parent " + leftSibling->parent->ToString() + " (using key " + to_string(key) + ")" << endl;
	}
	else
	{
		cout << to_string(key) + " inserted against " + ToString();
		int keyPos = NodeNeedsKey();
		keys[keyPos] = key;
		keyAmount++;
		SortKeys();
		SortChildren();
		cout << " creating " + ToString() << endl;

	}


}

tuple<int, tuple<BTreeNode*, BTreeNode*>> BTreeNode::Split(int key)
{

	cout << to_string(key) + ToString() + "->";

	const int maxKeys = maxKeyAmount + 1;
	int midIndex = (maxKeys) / 2;

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

	BTreeNode* leftSibling = new BTreeNode();
	BTreeNode* rightSibling = new BTreeNode();

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

	// add children (both get the middle child)
	for (int i = 0; i <= midIndex; i++)
	{
		leftSibling->children[i] = children[i];
	}
	for (int i = 0; i <= maxKeyAmount - midIndex; i++)
	{
		rightSibling->children[i] = children[i + midIndex];
	}

	leftSibling->SetKeyAmount();
	leftSibling->SortKeys();

	rightSibling->SetKeyAmount();
	rightSibling->SortKeys();

	// set children's parents as these with the middle child ending up as a child to rightSibling
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
	
	return tuple<int, tuple<BTreeNode*, BTreeNode*>>(midKey, tuple<BTreeNode*, BTreeNode*>(leftSibling, rightSibling));

}

BTreeNode* BTreeNode::GetSibling()
{
	for (int i = 0; i < maxKeyAmount; i++)
	{
		if (parent->children[i] != this && parent->children[i] != nullptr)
		{
			return parent->children[i];
		}
	}
}

int BTreeNode::GetKeyPos(int key)
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

int BTreeNode::GetChildLocation(BTreeNode* child)
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

BTreeNode* BTreeNode::NextNode(int key) const
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

int BTreeNode::NodeNeedsKey()
{
	for (int i = 0; i < maxKeyAmount; i++)
	{
		if (keys[i] == 0)
			return i;
	}

	return -1;
}

BTreeNode* BTreeNode::GetEmptyChild()
{
	for (int i = 0; i < maxKeyAmount + 1; i++)
	{
		if (children[i] == nullptr)
		{
			return children[i];
		}
	}
}

void BTreeNode::SortKeys()
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

void BTreeNode::SortChildren()
{
	BTreeNode* nodes[maxKeyAmount + 1];

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

bool BTreeNode::HasMaxChildren()
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

int BTreeNode::GetMiddleKey(int* keys)
{
	return keys[(maxKeyAmount + 1) / 2];
}

bool BTreeNode::IsLeaf()
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

void BTreeNode::SetValues(int* keys)
{
	for (int i = 0; i < maxKeyAmount; i++)
	{
		this->keys[i] = keys[i];
	}
}

string BTreeNode::ToString() const
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

