#include "BinaryTreeCString.h"
using namespace std;

int BinaryTreeCString::number_of_trees;

auto BinaryTreeCString::operator=(const BinaryTreeCString& _copy) -> BinaryTreeCString &
{
	if (&_copy != this)
	{
		remove();

		DuplicateWordSearch::operator=(_copy);

		root = copy_tree(_copy.root);
	}

	return *this;
}

auto BinaryTreeCString::remove() -> void
{
	delete_structure_recursive(this->root);

	number_of_trees--;
}

auto BinaryTreeCString::delete_structure_recursive(Node* _root) -> void
{
	if (_root)
	{
		delete_structure_recursive(_root->left);
		delete_structure_recursive(_root->right);

		delete _root;
		_root = nullptr;
	}
}

auto BinaryTreeCString::find_first_node(const Node* _root) const -> const Node*
{
	auto tmp = _root;

	while (tmp && tmp->left)
		tmp = tmp->left;

	return tmp;
}

auto BinaryTreeCString::find_successor(const Node* node) const -> const Node*
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

auto BinaryTreeCString::insert_word(const string& word) -> bool
{
	++number_of_all_words;

	bool left{}, right{};

	if (!root)
		root = new Node{ word.c_str() };

	else
	{
		auto tmp = root;

		while (true)
		{
			if (tmp->right && tmp->word_c_str[0] < word.c_str()[0])
				tmp = tmp->right;

			else if (tmp->left && tmp->word_c_str[0] > word.c_str()[0])
				tmp = tmp->left;

			else if (tmp->word_c_str[0] == word.c_str()[0])
			{
				for (int index = 0;; index++)
				{
					//jeœli doszliœmy z indeksem na koniec obu s³ow i ka¿da kolejna litera w nich jest identyczna
					//oznacza to, ¿e w strukturze ju¿ istnieje dane s³owo, znaleziono identyczne wzglêdem aktualnego	
					if ((index == strlen(word.c_str()) - 1) && (index == strlen(tmp->word_c_str) - 1) &&
						(tmp->word_c_str[index] == word.c_str()[index]))
					{
						tmp->number_of_occurrences_of_the_word++;

						return false;
					}	

					//jeœli nowe s³owo jest krótsze od tego w aktualnie analizowanym wêŸle lub któraœ kolejna literka jest ni¿ej w nowym s³owie
					//ni¿ w s³owie znajduj¹cym siê w analizowanym wêŸle, to wtedy nowe s³owo powinno byæ wczeœniej chronologicznie od tego wêz³a
					//dlatego te¿ idziemy w lewo w wêŸle 
					else if (tmp->word_c_str[index] > word.c_str()[index] || (tmp->word_c_str[index] == word.c_str()[index] &&
						index == strlen(word.c_str()) - 1 && index != strlen(tmp->word_c_str) - 1))
					{
						if (tmp->left)
							tmp = tmp->left;

						else
							left = true;

						break;
					}

					else if (index == strlen(tmp->word_c_str) - 1 || tmp->word_c_str[index] < word.c_str()[index])
					{
						if (tmp->right)
							tmp = tmp->right;

						else
							right = true;

						break;
					}
				}
			}

			else
				break;

			if (left || right)
				break;
		}

		if (right || tmp->word_c_str[0] < word.c_str()[0])
		{
			tmp->right = new Node{ word.c_str() };
			tmp->right->parent = tmp;
		}
		else
		{
			tmp->left = new Node{ word.c_str() };
			tmp->left->parent = tmp;
		}
	}

	return true;
}

auto BinaryTreeCString::insert_word_to_new_binary_tree(const Node* source_node, Node*& new_root) const -> bool
{

	bool left{}, right{};

	if (!new_root)
		new_root = new Node{ source_node };

	else
	{
		auto tmp = new_root;

		while (true)
		{
			if (tmp->right && tmp->word_c_str[0] < source_node->word_c_str[0])
				tmp = tmp->right;

			else if (tmp->left && tmp->word_c_str[0] > source_node->word_c_str[0])
				tmp = tmp->left;

			else if (tmp->word_c_str[0] == source_node->word_c_str[0])
			{
				for (int index = 0;; index++)
				{
					//jeœli doszliœmy z indeksem na koniec obu s³ow i ka¿da kolejna litera w nich jest identyczna
					//oznacza to, ¿e w strukturze ju¿ istnieje dane s³owo, znaleziono identyczne wzglêdem aktualnego	
					if ((index == strlen(source_node->word_c_str) - 1) && (index == strlen(tmp->word_c_str) - 1) &&
						(tmp->word_c_str[index] == source_node->word_c_str[index]))
					{
						tmp->number_of_occurrences_of_the_word++;

						return false;
					}

					//jeœli nowe s³owo jest krótsze od tego w aktualnie analizowanym wêŸle lub któraœ kolejna literka jest ni¿ej w nowym s³owie
					//ni¿ w s³owie znajduj¹cym siê w analizowanym wêŸle, to wtedy nowe s³owo powinno byæ wczeœniej chronologicznie od tego wêz³a
					//dlatego te¿ idziemy w lewo w wêŸle 
					else if (tmp->word_c_str[index] > source_node->word_c_str[index] || 
						(tmp->word_c_str[index] == source_node->word_c_str[index] &&
						index == strlen(source_node->word_c_str) - 1 && index != strlen(tmp->word_c_str) - 1))
					{
						if (tmp->left)
							tmp = tmp->left;

						else
							left = true;

						break;
					}

					else if (index == strlen(tmp->word_c_str) - 1 || 
						tmp->word_c_str[index] < source_node->word_c_str[index])
					{
						if (tmp->right)
							tmp = tmp->right;

						else
							right = true;

						break;
					}
				}
			}

			else
				break;

			if (left || right)
				break;
		}

		if (right || tmp->word_c_str[0] < source_node->word_c_str[0])
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

auto BinaryTreeCString::copy_all_nodes_recursive(const Node* source_root, Node*& _root) const -> void
{
	if (source_root)
	{
		insert_word_to_new_binary_tree(source_root, _root);

		copy_all_nodes_recursive(source_root->left, _root);
		copy_all_nodes_recursive(source_root->right, _root);
	}
}

auto BinaryTreeCString::copy_tree(const Node* source_root) const -> Node*
{
	if (!source_root)
		return nullptr;

	else
		number_of_trees++;

	Node* new_root = nullptr;

	copy_all_nodes_recursive(source_root, new_root);

	return new_root;
}

auto BinaryTreeCString::write_all_words_sorted_alphabetically() const -> string 
{
	string returned_str;
	string word, number_of_occurences;

	auto tmp = find_first_node(this->root);

	while (tmp)
	{
		returned_str += '|';
		word = tmp->word_c_str;
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

auto BinaryTreeCString::get_structure_type() const -> string
{
	return "drzewo binarne zbudowane z wezlow przechowujacych slowa w zmiennej typu CString (char*)";
}

auto BinaryTreeCString::get_structure_info(const string& file) const -> string 
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
