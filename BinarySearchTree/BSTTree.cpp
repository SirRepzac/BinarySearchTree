#include "BSTTree.h"
#include <queue>
#include <sstream>
#include <stack>

using namespace std;

BSTTree::BSTTree()
{
	head = nullptr;
	c = 0.75f;
}

BSTNode* BSTTree::Find(int key)
{
	return FindAlgo(key, head);
}

BSTNode* BSTTree::FindAlgo(int key, BSTNode* currentNode)
{
	if (currentNode == nullptr)
		return nullptr;

	if (key == currentNode->key)
		return currentNode;

	return FindAlgo(key, currentNode->GetNextNode(key));
}

void BSTTree::Insert(int key)
{

	if (!head)
	{
		head = new BSTNode(key);
		return;
	}

	BSTNode* current = head;
	BSTNode* parent = nullptr;

	while (current)
	{
		parent = current;

		if (key == current->key)
		{
			return; // Key already exists, bounce
		}
		else if (key < current->key)
		{
			current = current->leftChild;
		}
		else
		{
			current = current->rightChild;
		}
	}

	BSTNode* newNode = new BSTNode(key);

	// Insert at the correct position
	newNode->parent = parent;
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
		UpdateNodeAmount(parent);

		// Check if rebalancing is needed
		if (CheckIfRebalanceIsNeeded(parent))
		{
			RebalanceAt(parent);
		}
		parent = parent->parent;
	}

}

double BSTTree::GetBalanceFactor(BSTNode* node)
{
	if (!node) return 0.0; // Null nodes are balanced

	int leftSize = node->leftChild ? node->leftChild->nodeAmount : 0;
	int rightSize = node->rightChild ? node->rightChild->nodeAmount : 0;
	int totalSize = node->nodeAmount; // Includes the node itself

	if (totalSize <= 1) return 0.0; // A single node is always balanced

	double leftRatio = static_cast<double>(leftSize) / totalSize;
	double rightRatio = static_cast<double>(rightSize) / totalSize;

	if (leftRatio > rightRatio)
	{
		return -leftRatio;
	}
	else
	{
		return rightRatio;
	}
}

bool BSTTree::CheckIfRebalanceIsNeeded(BSTNode* node)
{
	if (!node) return false;
	return abs(GetBalanceFactor(node)) > c;
}

void BSTTree::DeleteTree()
{
	vector<BSTNode*> nodes;

	InOrderTraversal(head, nodes);

	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes[i];
	}

	head = nullptr;
}

void BSTTree::InOrderTraversal(BSTNode* node, vector<BSTNode*>& nodes)
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

BSTNode* BSTTree::RotateRight(BSTNode* node)
{
	BSTNode* newRoot = node->leftChild;
	node->leftChild = newRoot->rightChild;

	if (newRoot->rightChild)
	{
		newRoot->rightChild->parent = node;
	}

	newRoot->rightChild = node;
	newRoot->parent = node->parent;
	node->parent = newRoot;

	// Fix parent's child reference
	if (newRoot->parent)
	{
		if (newRoot->parent->leftChild == node)
		{
			newRoot->parent->leftChild = newRoot;
		}
		else
		{
			newRoot->parent->rightChild = newRoot;
		}
	}

	// Update nodeAmount
	UpdateNodeAmount(node);
	UpdateNodeAmount(newRoot);

	return newRoot;
}

BSTNode* BSTTree::RotateLeft(BSTNode* node)
{
	BSTNode* newRoot = node->rightChild;
	node->rightChild = newRoot->leftChild;

	if (newRoot->leftChild)
	{
		newRoot->leftChild->parent = node;
	}

	newRoot->leftChild = node;
	newRoot->parent = node->parent;
	node->parent = newRoot;

	// Fix parent's child reference
	if (newRoot->parent)
	{
		if (newRoot->parent->leftChild == node)
		{
			newRoot->parent->leftChild = newRoot;
		}
		else
		{
			newRoot->parent->rightChild = newRoot;
		}
	}

	// Update nodeAmount
	UpdateNodeAmount(node);
	UpdateNodeAmount(newRoot);

	return newRoot;
}

void BSTTree::UpdateNodeAmount(BSTNode* node)
{
	if (!node) return;
	node->nodeAmount = 1; // Count itself
	if (node->leftChild)
	{
		node->nodeAmount += node->leftChild->nodeAmount;
	}
	if (node->rightChild)
	{
		node->nodeAmount += node->rightChild->nodeAmount;
	}
}

void BSTTree::RebalanceAt(BSTNode* node)
{
	if (!node) return;

	float balanceFactor = GetBalanceFactor(node);

	// LL Case (Right Rotation)
	if (balanceFactor < 0 && GetBalanceFactor(node->leftChild) <= 0)
	{
		node = RotateRight(node);
	}
	// RR Case (Left Rotation)
	else if (balanceFactor > 0 && GetBalanceFactor(node->rightChild) >= 0)
	{
		node = RotateLeft(node);
	}
	// LR Case (Left-Right Rotation)
	else if (balanceFactor < 0 && GetBalanceFactor(node->leftChild) > 0)
	{
		node->leftChild = RotateLeft(node->leftChild);
		node = RotateRight(node);
	}
	// RL Case (Right-Left Rotation)
	else if (balanceFactor > 0 && GetBalanceFactor(node->rightChild) < 0)
	{
		node->rightChild = RotateRight(node->rightChild);
		node = RotateLeft(node);
	}

	// If the node was root, update head
	if (!node->parent)
	{
		head = node;
	}
}

void BSTTree::Delete(int key)
{
	BSTNode* nodeWithKey = Find(key);

	if (nodeWithKey == nullptr)
	{
		return;
	}

	Delete(nodeWithKey);

	if (CheckIfRebalanceIsNeeded(head))
	{
		RebalanceAt(head);
	}
}

void BSTTree::Delete(BSTNode* node)
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


