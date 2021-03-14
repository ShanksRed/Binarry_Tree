#pragma once

#include<iostream>


class binary_tree {
private:
	struct treeNode {
		treeNode* parent;
		treeNode* left;
		treeNode* right;
		int val;

		treeNode(int elem):
			val{elem},
			parent{nullptr},
			right{ nullptr },
			left{ nullptr }{}

		treeNode(treeNode*par, int elem) :
			val{ elem },
			parent{ par },
			right{ nullptr },
			left{ nullptr }{}

	};
	
	void insert_recr(treeNode* root, int value);
	treeNode* next(treeNode* node);
public:
	treeNode* head;
	binary_tree():head{nullptr} {}
	void insert(int value);
	void insert_recr(int value);
	void delete_node(treeNode* d_node);


};

void binary_tree::insert(int value) {
	auto new_node = new treeNode(value);
	if (head == nullptr) {
		head = new_node;
		return;
	}
	auto curr = this->head;
	while (curr != nullptr) {
		if (curr->val < value) {
			if (curr->right != nullptr)
				curr = curr->right;
			else {
				curr->right = new_node;
				new_node->parent = curr;
				break;
			}	
		}
		else if(curr->val > value) {
			if (curr->left != nullptr)
				curr = curr->left;
			else {
				curr->left = new_node;
				new_node->parent = curr;
				break;
			}
		}
	}
}

inline void binary_tree::insert_recr(int value){
	if (head == nullptr)
		head = new treeNode(value);
	else
		this->insert_recr(head, value);
	

}

void binary_tree::insert_recr(treeNode* root, int value)
{
	if (root->val < value) {
		if (root->right != nullptr)
			insert_recr(root->right, value);
		else
			root->right = new treeNode(root,value);
	}
	else {
		if (root->left != nullptr)
			insert_recr(root->left, value);
		else
			root->left = new treeNode(root,value);
	}

	
}


inline void binary_tree::delete_node(treeNode* d_node)
{
	auto parent = d_node->parent;
	if (d_node->right == nullptr && d_node->left == nullptr) {
		if (parent->left == d_node) 
			parent->left = nullptr;
		
		else 
			parent->right = nullptr;
		delete(d_node);
		
	}
	else if (d_node->right == nullptr || d_node->left == nullptr) {
		if (d_node->right != nullptr) {
			if (parent->left == d_node)
				parent->left = d_node->right;
			else
				parent->right = d_node->right;
			d_node->right->parent = parent;
		}
		else {
			if (parent->right == d_node)
				parent->right = d_node->left;
			else
				parent->left = d_node->left;
			d_node->left->parent = parent;
		}
		delete(d_node);
	}
	else {
		auto next_node = this->next(d_node);
		d_node->val = next_node->val;
		if (next_node->parent->right == next_node)
			next_node->parent->right = next_node->right;
		else {
			next_node->parent->left = next_node->right;
		}
		if (next_node->right != nullptr)
			next_node->right->parent = next_node->parent;
		delete(next_node);

	}

}

binary_tree::treeNode* binary_tree::next(treeNode* node){
	/*auto next_n = node->right;
	while (next_n->left) 
		next_n = next_n->left;
	return next_n;*/


	/*while (node->left)
		node = node->left;
	return node;*/
	

	/*while (node->left)
		node = node->left;
	return node;*/


	if (node->right != nullptr) {
		/*while (node->right->left)
			node = node->right->left;
		return node;*/

		auto min_node = node->right;
		while (min_node->left) {
			if (min_node->left == nullptr)
				return min_node;
			min_node = min_node->left;
		}
		return min_node;

	}
	else {
		auto parent = node->parent;
		while (parent != nullptr && parent->right == node) {
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
	
}
