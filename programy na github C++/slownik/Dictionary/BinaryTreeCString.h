#pragma once

#include "Node.h"
#include "DuplicateWordSearch.h"

class BinaryTreeCString : public DuplicateWordSearch
{
public:
	BinaryTreeCString() : root{ nullptr } { number_of_trees++; };

	BinaryTreeCString(const BinaryTreeCString& _copy) : root{ copy_tree(_copy.root) }, 
		DuplicateWordSearch(_copy) {};

	~BinaryTreeCString() { remove(); };

	auto operator=(const BinaryTreeCString& _copy)->BinaryTreeCString &;

	auto insert_word(const std::string& word) -> bool override;

	auto words_are_inserted() -> void override {};

	auto remove() -> void override;

	auto write_all_words_sorted_alphabetically() const -> std::string override;

	auto get_structure_type() const -> std::string override;

	auto get_structure_info(const std::string& file) const -> std::string override;

	auto get_number_of_all_words() const -> int override { return this->number_of_all_words; };

	auto get_number_of_different_words() const -> int override { return  (Node::number_of_all_nodes / number_of_trees); };

	auto create_new_structure() const -> DuplicateWordSearch* override { return new BinaryTreeCString; };

	auto copy_structure() const -> DuplicateWordSearch* override { return new BinaryTreeCString{ *this }; };

	auto copy_using_assignment_operator(const DuplicateWordSearch& _copy) -> DuplicateWordSearch &
		override {return operator=(dynamic_cast<const BinaryTreeCString&>(_copy));};

private:
	Node* root;

	static int number_of_trees;

	auto delete_structure_recursive(Node* _root) -> void;

	auto find_successor(const Node* node) const -> const Node*;

	auto find_first_node(const Node* _root) const -> const Node*;

	auto copy_tree(const Node* source_root) const -> Node*;

	auto insert_word_to_new_binary_tree(const Node * source_root, Node*& new_root) const -> bool;

	auto copy_all_nodes_recursive(const Node* source_root, Node*& _root) const -> void;
};


