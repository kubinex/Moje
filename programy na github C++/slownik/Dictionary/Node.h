#pragma once

#include <string>

struct Node
{
	static int number_of_all_nodes;

	std::string word;

	char* word_c_str{};

	int number_of_occurrences_of_the_word{};

	Node* left, * right, * parent;

	Node(const std::string& _word) : word{ _word }, number_of_occurrences_of_the_word{ 1 }, word_c_str{ nullptr },
		left{ nullptr }, right{ nullptr }, parent{ nullptr } {++number_of_all_nodes; };

	Node(const char* _word);

	Node(const Node* _copy);

	~Node()
	{
		delete word_c_str;
		word_c_str = nullptr;

		--number_of_all_nodes;
	}
};