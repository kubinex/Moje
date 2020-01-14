#include "BinaryTree.h"
using namespace std;

int BinaryTree::number_of_trees;

BinaryTree::BinaryTree(const BinaryTree& _copy)
{
	DuplicateWordSearch::operator=(_copy);

	copy_tree(_copy.root);

	number_of_trees++;
};

auto BinaryTree::operator=(const BinaryTree& _copy) -> BinaryTree&
{
	if (&_copy != this)
	{
		remove();

		DuplicateWordSearch::operator=(_copy);

		copy_tree(_copy.root);

		number_of_trees++;
	}

	return *this;
}

auto BinaryTree::remove() -> void
{
	delete_structure_recursive(this->root);

	number_of_trees--;
}

auto BinaryTree::delete_structure_recursive(Node*& _root) -> void
{
	if (_root)
	{
		delete_structure_recursive(_root->left);
		delete_structure_recursive(_root->right);

		delete _root;
		_root = nullptr;
	}
}

auto BinaryTree::find_first_node(const Node* _root) const -> const Node*
{	
	auto tmp = _root;

	while (tmp && tmp->left)
		tmp = tmp->left;

	return tmp;
}

auto BinaryTree::find_successor(const Node* node) const -> const Node* 
{
	if (!node)
		return nullptr;
	
	if (node->right)
	{
		//wtedy szukamy najmiejszego potomka w prawo
		node = node->right;

		while (node && node->left)
			node = node->left;

		return node;
	}

	else
	{
		//wtedy nastêpnikiem jest wêze³ bêd¹cy najni¿szym przodkiem wêz³a odniesienia
		auto tmp = node->parent;

		while (tmp && tmp->left != node)
		{
			node = tmp;
			tmp = tmp->parent;			
		}

		return tmp;
	}
}

auto BinaryTree::insert_word(const string& word) -> bool
{
	++number_of_all_words;

	if (!root)
		root = new Node{ word };
	
	else
	{
		auto tmp = root;
		
		while (true)
		{
			if (tmp->right && tmp->word < word)
				tmp = tmp->right;

			else if (tmp->left && tmp->word > word)
				tmp = tmp->left;

			else if (tmp->word == word)
			{
				tmp->number_of_occurrences_of_the_word++;

				return false;
			}

			else
				break;	
		}

		if (tmp->word < word)
		{
			tmp->right = new Node{ word };
			tmp->right->parent = tmp;
		}	

		else
		{
			tmp->left = new Node{ word };
			tmp->left->parent = tmp;
		}		
	}

	return true;
}

auto BinaryTree::insert_word_to_new_binary_tree(const Node* source_node) -> bool
{
	if (!root)
		root = new Node{ source_node };

	else
	{
		auto tmp = root;

		while (true)
		{
			if (tmp->right && tmp->word < source_node->word)
				tmp = tmp->right;

			else if (tmp->left && tmp->word > source_node->word)
				tmp = tmp->left;

			else if (tmp->word == source_node->word)
				return false;

			else
				break;
		}

		if (tmp->word < source_node->word)
		{
			tmp->right = new Node{ source_node };
			tmp->right->parent = tmp;
		}

		else
		{
			tmp->left = new Node{ source_node };
			tmp->left->parent = tmp;
		}
	}

	return true;
}

auto BinaryTree::copy_all_nodes_recursive(const Node *source_root) -> void
{
	if (source_root)
	{
		insert_word_to_new_binary_tree(source_root);

		copy_all_nodes_recursive(source_root->left);
		copy_all_nodes_recursive(source_root->right);
	}
}

auto BinaryTree::copy_tree(const Node* source_root) -> Node*
{
	if (!source_root)
		return nullptr;

	copy_all_nodes_recursive(source_root);

	return root;
}

auto BinaryTree::write_all_words_sorted_alphabetically() const -> string
{
	string returned_str;
	string word, number_of_occurences;

	auto tmp = find_first_node(this->root);

	while (tmp)
	{
		returned_str += '|';
		word = tmp->word;
		returned_str += word;
		returned_str.insert(returned_str.size(), 46 - word.size(), '_');
		returned_str += '|';
		number_of_occurences = to_string(tmp->number_of_occurrences_of_the_word);
		returned_str += number_of_occurences;
		returned_str.insert(returned_str.size(), 39 - number_of_occurences.size(), '_');
		returned_str += "|\n";

		tmp = find_successor(tmp);
	}

	return returned_str;
}

auto BinaryTree::get_structure_type() const -> string
{
	return "drzewo binarne zbudowane z wezlow przechowujacych slowa w zmiennej typu (klasie) std::String";
}

auto BinaryTree::get_structure_info(const string& file) const -> string 
{
	string returned_str;

	returned_str += "Wybrano ";
	returned_str += get_structure_type();
	returned_str += "\njako strukture do przechowywania danych.\n\nW pliku ";
	returned_str += file;

	if (!get_number_of_all_words())
		returned_str += " nie";

	returned_str += " znaleziono ";

	if (!get_number_of_all_words())
		returned_str += "zadnych";

	else
		returned_str += to_string(get_number_of_all_words());

	returned_str += " slow";

	if (get_number_of_all_words())
	{
		returned_str += ", w tym ";
		returned_str += to_string(get_number_of_different_words());
		returned_str += " roznych slow.\n\nPonizej znajduje sie wykaz slow";
		returned_str += " uzytych w wczytanym tekscie posortowany alfabetycznie\n";
		returned_str += "oraz ilosc wystapien danego slowa w tym pliku:\n\n";
		returned_str += " ";
		returned_str.insert(returned_str.size(), 86, '_');
		returned_str += " \n|";
		returned_str += "slowa, ktore znajduja sie we wczytanym tekscie|";
		returned_str += "liczba wystapien danego slowa w tekscie|\n|";
		returned_str.insert(returned_str.size(), 46, '_');
		returned_str += "|";
		returned_str.insert(returned_str.size(), 39, '_');
		returned_str += "|\n";
		returned_str += write_all_words_sorted_alphabetically();
	}

	else
		returned_str += ", dlatego slownik nie zostal wygenerowany!\n";

	return returned_str;
}
