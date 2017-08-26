#include "BST.h" 
#include <algorithm>
using namespace std;

WordTree::WordTree() : root(nullptr) {}

WordTree::WordTree(const WordTree& rhs) {
	if (rhs.root == nullptr) {
		this->root = nullptr;
	}

	else root = copyHelper(rhs.root); 
}

const WordTree& WordTree::operator=(const WordTree& rhs) {
	if (this != &rhs) {
		WordTree temp = rhs; 
		swap(root, temp.root); 
	}

	return *this; 
}

void WordTree::add(ItemType v) {
	// Base Case: adding to empty tree 
	if (root == nullptr) {
		root = new WordNode; 
		root->m_count = 1; 
		root->m_data = v; 
		root->m_left = nullptr; 
		root->m_right = nullptr; 
		return; 
	}

	WordNode* node = root; 
	while (true) {
		// Case: v < current
		if (v < node->m_data) {
			//left exists
			if (node->m_left) {
				node = node->m_left; 
				continue; 
			}

			//left does not yet exist
			else {
				node->m_left = new WordNode; 
				node->m_left->m_data = v; 
				node->m_left->m_count = 1; 
				node->m_left->m_left = nullptr; 
				node->m_left->m_right = nullptr; 
				break; 
			}
		}

		// Case: v == current
		else if (v == node->m_data) {
			node->m_count += 1; 
			break;
		}

		// Case: v > current 
		else {
			//right exists
			if (node->m_right) {
				node = node->m_right; 
				continue; 
			}

			//right does not yet exist
			else {
				node->m_right = new WordNode; 
				node->m_right->m_data = v; 
				node->m_right->m_count = 1; 
				node->m_right->m_left = nullptr; 
				node->m_right->m_right = nullptr; 
				break;
			}
		}
	}
}

int WordTree::distinctWords() const {
	unsigned int count = 0; 
	if (root != nullptr) {
		count = distinctWordsHelper(root);
	}
	return count; 
}

int WordTree::totalWords() const {
	unsigned int count = 0; 
	if (root != nullptr) {
		count = totalWordsHelper(root); 
	}
	return count; 
}

ostream& operator<<(ostream &out, const WordTree& rhs) {
	if (rhs.root != nullptr) {
		rhs.printHelper(out, rhs.root);
	}
	return out; 
}

WordTree::~WordTree() {
	WordNode* node = root; 
	if (node != nullptr) {
		destruct(root); 
	}
}