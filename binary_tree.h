#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  
#include <stack>
#include <queue>
#include <array>
#include <algorithm>
#include <filesystem>


class binary_tree {
private:
	struct treeNode {
		treeNode* parent;
		treeNode* left;
		treeNode* right;
		int val;

		treeNode(int elem) :
			val{ elem },
			parent{ nullptr },
			right{ nullptr },
			left{ nullptr }{}

		treeNode(treeNode* par, int elem) :
			val{ elem },
			parent{ par },
			right{ nullptr },
			left{ nullptr }{}

	};

	void insert_recr(treeNode* root, int value);
	bool find_element_recr(treeNode* root, int value);
	int height(treeNode* root);

	template<typename lambda_type>
	void pre_order_recr(treeNode* root, lambda_type lambda);

	template<typename lambda_type>
	void in_order(treeNode* root, lambda_type lambda);

	template<typename lambda_type>
	void post_order(treeNode* root, lambda_type lambda);

	template<typename lambda_type>
	void bfs_order(treeNode* root, lambda_type lambda);

	treeNode* get_treeNode(int val);
	treeNode* next(treeNode* node);
	treeNode* head;
public:

	template<typename lambda_type>
	void pre_order_recr( lambda_type lambda);

	template<typename lambda_type>
	void pre_order(lambda_type lambda);

	template<typename lambda_type>
	void in_order(lambda_type lambda);

	template<typename lambda_type>
	void post_order(lambda_type lambda);

	template<typename lambda_type>
	void bfs_order(lambda_type lambda);

	bool is_empty();
	binary_tree() :head{ nullptr } {}
	void insert(int value);
	void insert_recr(int value);
	void delete_node(int del_val);
	bool find_element(int value);
	bool find_element_recr(int value);
	int height();
	void delete_tree();
	void write_to_file(std::filesystem::path filePath);
	void read_fr_file(std::filesystem::path filePath);


};

inline bool binary_tree::is_empty()
{
	if (head == nullptr) return true;
	return false;
}

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
		else if (curr->val > value) {
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

void binary_tree::insert_recr(int value) {
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
			root->right = new treeNode(root, value);
	}
	else {
		if (root->left != nullptr)
			insert_recr(root->left, value);
		else
			root->left = new treeNode(root, value);
	}


}

void binary_tree::delete_node(int del_val)
{
	auto d_node = this->get_treeNode(del_val);
	if(d_node==nullptr)
		throw std::exception("элемента нет");

	auto parent = d_node->parent;
	if (d_node->right == nullptr && d_node->left == nullptr) {
		if (parent != nullptr) {
			if (parent->left == d_node)
				parent->left = nullptr;

			else
				parent->right = nullptr;
		}
		delete(d_node);
		if (parent == nullptr)
			head = nullptr;

	}
	else if (d_node->right == nullptr || d_node->left == nullptr) {
		if (parent != nullptr) {
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
			if (d_node->left) {
				head = d_node->left;
				d_node->left->parent=nullptr;
			}
			else {
				head = d_node->right;
				d_node->right->parent = nullptr;
			}
			delete(d_node);
			
		}


	}
	else {
		auto next_node = this->next(d_node);
		d_node->val = next_node->val;
		if (next_node->parent->right == next_node)
			next_node->parent->right = next_node->left;
		else {
			next_node->parent->left = next_node->left;

		}
		if (next_node->right != nullptr)
			next_node->right->parent = next_node->parent;
		delete(next_node);

	}

}

binary_tree::treeNode* binary_tree::get_treeNode(int f_val)
{
	treeNode* curr = head;
	while (curr) {
		if (curr->val < f_val)
			curr = curr->right;
		else if (curr->val > f_val)
			curr = curr->left;
		else
			return curr;
	}
	return nullptr;
}

binary_tree::treeNode* binary_tree::next(treeNode* node) {

	if (node->left != nullptr) {

		auto min_node = node->left;
		while (min_node->right) {
			//if (min_node->left == nullptr)
			//	return min_node;
			min_node = min_node->right;
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

bool binary_tree::find_element(int f_val)
{
	treeNode* curr = head;
	while (curr) {
		if (curr->val < f_val)
			curr = curr->right;
		else if (curr->val > f_val)
			curr = curr->left;
		else
			return true;
	}
	return false;
}

bool binary_tree::find_element_recr(int value)
{
	if (is_empty())
		throw std::exception("дерево пустое");
	else
		return	this->find_element_recr(head, std::move(value));
}

bool binary_tree::find_element_recr(treeNode* root, int value)
{
	if (root == nullptr)
		return false;
	else if (root->val > value)
		find_element_recr(root->left, value);
	else if (root->val < value)
		find_element_recr(root->right, value);
	else
		return true;
}

int binary_tree::height(treeNode* root) {
	int height_max{};
	if (root != nullptr) {
		int l_height = height(root->left);
		int r_height = height(root->right);
		height_max = std::max(l_height, r_height) + 1;
		return height_max;
	}
	else
		return height_max;
}

int binary_tree::height()
{
	if (is_empty())
		return 0;
	else
		return this->height(head);

}

template<typename lambda_type>
void binary_tree::pre_order_recr(treeNode* root, lambda_type lambda) {
	if (root == nullptr)
		return;
	lambda(root->val);
	pre_order_recr(root->left, lambda);
	pre_order_recr(root->right, lambda);

}

template<typename lambda_type>
void binary_tree::pre_order(lambda_type lambda)
{
	if (is_empty())
		throw std::exception("дерево пустое");

	std::stack<binary_tree::treeNode*> stack_node;
	stack_node.push(head);
	while (!stack_node.empty()) {
		auto curr = stack_node.top();
		stack_node.pop();
		lambda(curr->val);
		if (curr->right != nullptr)
			stack_node.push(curr->right);
		if (curr->left != nullptr)
			stack_node.push(curr->left);
	}
}

template<typename lambda_type>
void binary_tree::in_order(treeNode* root, lambda_type lambda) {
	if (root == nullptr)
		return;
	in_order(root->left, lambda);
	lambda(root->val);
	in_order(root->right, lambda);
}

template<typename lambda_type>
inline void binary_tree::post_order(treeNode* root, lambda_type lambda) {
	if (root == nullptr)
		return;
	post_order(root->left, lambda);
	post_order(root->right, lambda);
	lambda(root->val);

}

template<typename lambda_type>
void binary_tree::bfs_order(treeNode* root, lambda_type lambda) {
	if (is_empty())
		throw std::exception("дерево пустое");

	std::queue<treeNode*> queue_node;
	queue_node.push(head);
	while (!queue_node.empty()) {
		auto curr = queue_node.front();
		queue_node.pop();
		lambda(curr->val);
		if (curr->left != nullptr)
			queue_node.push(curr->left);
		if (curr->right != nullptr)
			queue_node.push(curr->right);
	}


}

template<typename lambda_type>
void binary_tree::pre_order_recr(lambda_type lambda)
{
	if (is_empty())
		throw std::exception("дерево пустое");
	pre_order_recr(head, lambda);
}

template<typename lambda_type>
void binary_tree::in_order(lambda_type lambda)
{
	if (is_empty())
		throw std::exception("дерево пустое");
	in_order(head, lambda);
}

template<typename lambda_type>
void binary_tree::post_order(lambda_type lambda)
{
	if (is_empty())
		throw std::exception("дерево пустое");
	post_order(head, lambda);
}

template<typename lambda_type>
void binary_tree::bfs_order(lambda_type lambda)
{
	if (is_empty())
		throw std::exception("дерево пустое");
	bfs_order(head, lambda);
}


void binary_tree::delete_tree()
{
	if (!this->is_empty()) {
		std::queue<treeNode*> queue_node;
		queue_node.push(head);
		while (!queue_node.empty()) {
			auto curr = queue_node.front();
			queue_node.pop();
			if (curr->left != nullptr)
				queue_node.push(curr->left);
			if (curr->right != nullptr)
				queue_node.push(curr->right);
			delete(curr);
		}
		head = nullptr;
	}
}



void binary_tree::write_to_file(std::filesystem::path filePath){
	std::wofstream writeFile(filePath, std::ios::trunc);
	static std::vector< std::vector<int>> save_tree{ std::vector<int>{} };
	static int i = 0;
	auto save_lambd = [&](auto&& val) {
		save_tree[i].push_back(val);
	};
	auto increment = [&]() {
		++i;
		save_tree.push_back(std::vector<int>{});
	};
	pre_order(save_lambd);
	increment();
	pre_order_recr(save_lambd);
	increment();
	in_order(save_lambd);
	increment();
	post_order(save_lambd);
	increment();
	bfs_order(save_lambd);

	for (auto&& curr_row : save_tree) {
		for (auto&& curr_colmn : curr_row) {
			writeFile << curr_colmn << " ";
		}
		writeFile << std::endl;
	}

	writeFile.close();
}

void binary_tree::read_fr_file(std::filesystem::path filePath)
{
	using namespace std;

	ifstream file(filePath, ios::in);
	if (file.good())
	{
		string str;
		getline(file, str);
		
			istringstream ss(str);
			int num;
			while (ss >> num)
			{
				this->insert(num);
			}
		
	}
}

