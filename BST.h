#pragma once

#ifndef BST_H
#define BST_H

#include <string>
#include <iostream> 
#include <sstream> 

typedef std::string ItemType; 

struct WordNode {
	ItemType m_data; 
	WordNode* m_left; 
	WordNode* m_right; 
	int m_count; 
};

class WordTree {
private: 
	WordNode* root;

	//by choice, helpers will be inlined 
	WordNode* copyHelper(WordNode* toCopy) const; 
	unsigned int distinctWordsHelper(WordNode* node) const; 
	unsigned int totalWordsHelper(WordNode* node) const; 
	void printHelper(std::ostream& out, WordNode* node) const; 
	WordNode* destruct(WordNode* node) {
		if (node == nullptr) return nullptr; 
		if (node->m_left) return destruct(node->m_left); 
		else if (node->m_right) return destruct(node->m_right); 
		else {
			delete node; 
			node = nullptr; 
			return node; 
		}
	}

public:
	// default constructor 
	WordTree(); 

	// copy constructor 
	WordTree(const WordTree& rhs); 

	//assignment operator 
	const WordTree& operator=(const WordTree& rhs);

	// Inserts v into the WordTree 
	void add(ItemType v); 

	// Returns the number of distinct words / nodes 
	int distinctWords() const; 

	// Returns the total number of words inserted, including duplicate
	// values 
	int totalWords() const; 

	// Prints the LinkedList
	friend std::ostream& operator<<(std::ostream &out, const WordTree& rhs); 

	// Destroys all the dynamically allocated memory
	// in the tree 
	~WordTree(); 
};

inline WordNode* WordTree::copyHelper(WordNode* toCopy) const {
	if (toCopy == nullptr) {
		return nullptr; 
	}

	WordNode* newNode = new WordNode; 
	newNode->m_data = toCopy->m_data;
	newNode->m_count = toCopy->m_count; 
	newNode->m_left = copyHelper(toCopy->m_left);
	newNode->m_right = copyHelper(toCopy->m_right); 
	
	return newNode; 
}

inline unsigned int WordTree::distinctWordsHelper(WordNode* node) const {
	unsigned int count = 1; 
	if (node->m_left) {
		count += distinctWordsHelper(node->m_left); 
	}
	if (node->m_right) {
		count += distinctWordsHelper(node->m_right); 
	}
	return count; 
}

inline unsigned int WordTree::totalWordsHelper(WordNode* node) const {
	unsigned int count = node->m_count; 
	if (node->m_left) {
		count += totalWordsHelper(node->m_left); 
	}
	if (node->m_right) {
		count += totalWordsHelper(node->m_right); 
	}
	return count; 
}

inline void WordTree::printHelper(std::ostream& out, WordNode* node) const {
	if (node == nullptr) return;

	printHelper(out, node->m_left); 
	out << node->m_data << " " << node->m_count << std::endl;
	printHelper(out, node->m_right);
}
#endif 