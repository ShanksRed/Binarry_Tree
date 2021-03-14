#include <iostream>
#include "binary_tree.h"

int main() {
	binary_tree tree;

	tree.insert_recr(5);
	tree.insert_recr(6);
	tree.insert_recr(4);
	tree.delete_node(tree.head);

}