#include "BSTTreeUnbalanced.h"
#include <stack>

BSTTreeUnbalanced::BSTTreeUnbalanced()
{
	head = nullptr;
}

BSTNode* BSTTreeUnbalanced::Find(int key)
{
	return FindAlgo(key, head);
}

BSTNode* BSTTreeUnbalanced::FindAlgo(int key, BSTNode* currentNode)
{
	if (currentNode == nullptr)
		return nullptr;

	if (key == currentNode->key)
		return currentNode;

	return FindAlgo(key, currentNode->GetNextNode(key));
}

void BSTTreeUnbalanced::Insert(int key)
{
	if (head == nullptr)
	{
		head = new BSTNode(key);
		return;
	}

	BSTNode* currentNode = head;
	BSTNode* parent = nullptr;

	// Iterative traversal to find insertion point
	while (currentNode)
	{
		parent = currentNode;
		if (key == currentNode->key)
		{
			return; // Key already exists, no duplicates allowed
		}
		else if (key < currentNode->key)
		{
			currentNode = currentNode->leftChild;
		}
		else
		{
			currentNode = currentNode->rightChild;
		}
	}

	// Create new node
	BSTNode* newNode = new BSTNode(key);
	newNode->parent = parent;

	// Attach to correct side
	if (key < parent->key)
	{
		parent->leftChild = newNode;
	}
	else
	{
		parent->rightChild = newNode;
	}

	// Update nodeAmount upwards
	while (parent)
	{
		parent->nodeAmount++;
		parent = parent->parent;
	}
}

void BSTTreeUnbalanced::DeleteTree()
{
	vector<BSTNode*> nodes;

	InOrderTraversal(head, nodes);

	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes[i];
	}

	head = nullptr;
}

void BSTTreeUnbalanced::InOrderTraversal(BSTNode* node, vector<BSTNode*>& nodes)
{
	stack<BSTNode*> stack;
	BSTNode* current = head;

	// Traverse the tree
	while (current != nullptr || !stack.empty())
	{
		// Reach the leftmost node of the current node
		while (current != nullptr)
		{
			stack.push(current);
			current = current->leftChild;
		}

		// Pop the node from the stack and add it to the result
		current = stack.top();
		stack.pop();
		nodes.push_back(current);

		// Now, visit the right child
		current = current->rightChild;
	}
}


// NOT IMPORTANT BELOW

void BSTTreeUnbalanced::Delete(int key)
{
	BSTNode* nodeWithKey = Find(key);

	if (nodeWithKey == nullptr)
	{
		return;
	}

	Delete(nodeWithKey);
}

void BSTTreeUnbalanced::Delete(BSTNode* node)
{
	// The node being deleted has no children
	if (node->IsLeaf())
	{
		if (node == head)
		{
			head = nullptr;
		}
		else
		{
			node->parent->DeleteChild(node);
		}

		BSTNode* parentNode = node->parent;
		while (parentNode->parent != nullptr)
		{
			parentNode->nodeAmount--;
			parentNode = parentNode->parent;
		}
		// Remove from nodeAmount for head
		parentNode->nodeAmount--;

		delete node;
		return;
	}

	// The node being deleted has 1 child, relocate the child to the deleted values position
	else if (node->ChildAmount() == 1)
	{
		BSTNode* child = (node->leftChild != nullptr) ? node->leftChild : node->rightChild;

		if (node == head)
		{
			head = child;
			child->parent = nullptr;
		}
		else
		{
			child->parent = node->parent;
			if (node->parent->leftChild == node)
				node->parent->leftChild = child;
			else
				node->parent->rightChild = child;
		}

		BSTNode* parentNode = node->parent;
		while (parentNode->parent != nullptr)
		{
			parentNode->nodeAmount--;
			parentNode = parentNode->parent;
		}
		// Remove from nodeAmount for head
		parentNode->nodeAmount--;

		delete node;
		return;
	}
	// The node being deleted has 2 children
	else
	{
		// Swap value with the smallest node in the right subtree
		BSTNode* smallestInRightSubtree = node->rightChild->GetSmallest();
		node->key = smallestInRightSubtree->key;
		Delete(smallestInRightSubtree);
	}
}