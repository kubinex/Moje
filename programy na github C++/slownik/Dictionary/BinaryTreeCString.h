#pragma once

#include "BinaryTree.h"

class BinaryTreeCString final : public BinaryTree
{
public:
	BinaryTreeCString() = default;

	BinaryTreeCString(const BinaryTreeCString& _copy);

	BinaryTreeCString(const DuplicateWordSearch& _copy) : BinaryTreeCString(dynamic_cast<const BinaryTreeCString&>(_copy)) {};

	~BinaryTreeCString() = default;

	auto operator=(const BinaryTreeCString& _copy)->BinaryTreeCString &;

	auto insert_word(const std::string& word) -> bool override;

	auto get_structure_type() const -> std::string override;

	auto copy_using_assignment_operator(const DuplicateWordSearch& _copy) -> DuplicateWordSearch& override 
	{ return operator=(dynamic_cast<const BinaryTreeCString&>(_copy));};

private:
	auto insert_word_to_new_binary_tree(const Node* source_node) -> bool override;

	auto write_all_words_sorted_alphabetically() const -> std::string override;

	auto copy_tree(const Node* source_root) -> Node* override;

	auto copy_all_nodes_recursive(const Node* source_root) -> void override;
};


