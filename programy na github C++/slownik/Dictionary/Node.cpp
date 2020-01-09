#include "Node.h"
using namespace std;

int Node::number_of_all_nodes;

Node::Node(const char* _word) : word{}, number_of_occurrences_of_the_word{ 1 },
	left{ nullptr }, right{ nullptr }, parent{ nullptr }
{
	word_c_str = new char[strlen(_word) + 1];

	for (unsigned int index = 0; index <= strlen(_word); index++)
	{
		word_c_str[index] = _word[index];
	}

	++number_of_all_nodes;
}

Node::Node(const Node* _copy) : left{ nullptr }, right{ nullptr }, parent{ nullptr }
{
	if (_copy)
	{
		if (_copy->word_c_str)
		{
			word_c_str = new char[strlen(_copy->word_c_str) + 1];

			for (unsigned int index = 0; index <= strlen(_copy->word_c_str); index++)
			{
				word_c_str[index] = _copy->word_c_str[index];
			}
		}

		else if (!_copy->word.empty())
		{
			word = _copy->word;

			word_c_str = nullptr;
		}

		number_of_occurrences_of_the_word = _copy->number_of_occurrences_of_the_word;

		++number_of_all_nodes;
	}
}