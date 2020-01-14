#pragma once

#include "Node.h"
#include "DuplicateWordSearch.h"

class BinaryTree : public DuplicateWordSearch
{
public:	
	BinaryTree() : root{ nullptr } { number_of_trees++; };

	BinaryTree(const BinaryTree& _copy);

	BinaryTree(const DuplicateWordSearch& _copy) : BinaryTree(dynamic_cast<const BinaryTree&>(_copy)) {};

	virtual ~BinaryTree() { remove(); };

	auto operator=(const BinaryTree& _copy) ->BinaryTree &;

	auto insert_word(const std::string& word) -> bool override;

	auto words_are_inserted() -> void override {};

	auto remove() -> void override;

	auto get_structure_info(const std::string& file) const -> std::string override;

	auto get_number_of_all_words() const -> int override { return this->number_of_all_words; };

	auto get_number_of_different_words() const -> int override { return  (Node::number_of_all_nodes / number_of_trees); };

	virtual auto write_all_words_sorted_alphabetically() const -> std::string override;

	virtual auto get_structure_type() const->std::string override;

	auto copy_using_assignment_operator(const DuplicateWordSearch& _copy) -> DuplicateWordSearch& override 
	{ return operator=(dynamic_cast<const BinaryTree&>(_copy));};

protected:
	Node* root;

	static int number_of_trees;

	virtual auto delete_structure_recursive(Node*& _root) -> void;

	auto find_successor(const Node* node) const -> const Node*;

	auto find_first_node(const Node* _root) const -> const Node*;

	virtual auto copy_tree(const Node* source_root) -> Node*;

	virtual auto insert_word_to_new_binary_tree(const Node* source_node) -> bool;

	virtual auto copy_all_nodes_recursive(const Node* source_root) -> void;
};

