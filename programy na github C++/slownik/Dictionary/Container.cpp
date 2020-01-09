#include "Cointainer.h"
using namespace std;

int Cointainer::number_of_cointainers;

auto Cointainer::operator=(const Cointainer& _copy) -> Cointainer &
{
	if (&_copy != this)
	{
		remove();

		DuplicateWordSearch::operator=(_copy);

		words_sorted_alphabetically = _copy.words_sorted_alphabetically;

		words_sorted_by_number_of_occurences = _copy.words_sorted_by_number_of_occurences;
		
		number_of_cointainers += 2;
	}

	return *this;
}

auto Cointainer::initialize_words_sorted_by_number_of_occurences() -> void 
{
	string word;

	int number_of_occurrences;

	for (/*pair<string, int>*/ auto element : words_sorted_alphabetically)
	{
		// Accessing KEY from element
		word = element.first;
		// Accessing VALUE from element.
		number_of_occurrences = element.second;

		words_sorted_by_number_of_occurences.insert(pair <int, string>(number_of_occurrences, word));
	}
}

auto Cointainer::insert_word(const string& word) -> bool
{
	++number_of_all_words;

	if (words_sorted_alphabetically[word]++)
		return false;

	return true;
}

auto Cointainer::remove() -> void
{
	words_sorted_alphabetically.clear();
	words_sorted_by_number_of_occurences.clear();

	number_of_cointainers -= 2;
}

auto Cointainer::write_all_words_sorted_by_number_of_occurences() const -> string 
{
	string returned_str;
	string word, number_of_occurences;

	if (!words_sorted_by_number_of_occurences.empty())
	{
		multimap<int, string>::const_iterator iter = --words_sorted_by_number_of_occurences.end();

		do
		{
			returned_str += '|';
			word = iter->second;
			returned_str += word;
			returned_str.insert(returned_str.size(), 46 - word.size(), '_');
			returned_str += '|';
			number_of_occurences = to_string(iter->first);
			returned_str += number_of_occurences;
			returned_str.insert(returned_str.size(), 39 - number_of_occurences.size(), '_');
			returned_str += "|\n";
		} while ((iter--) != words_sorted_by_number_of_occurences.begin());
	}

	return returned_str;
}

auto Cointainer::write_all_words_sorted_alphabetically() const -> string 
{
	string returned_str;
	string word, number_of_occurences;

	for (/*pair<string, int>*/ auto element : words_sorted_alphabetically)
	{
		returned_str += '|';
		word = element.first;
		returned_str += word;
		returned_str.insert(returned_str.size(), 46 - word.size(), '_');
		returned_str += '|';
		number_of_occurences = to_string(element.second);
		returned_str += number_of_occurences;
		returned_str.insert(returned_str.size(), 39 - number_of_occurences.size(), '_');
		returned_str += "|\n";
	}

	return returned_str;
}

auto Cointainer::get_structure_type() const -> string
{
	return "kontener map z biblioteki STL ";
}

auto Cointainer::get_structure_info(const string& file) const -> string
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
		returned_str += "oraz ilosc wystapien danego slowa w tym pliku.\n";
		returned_str += "(Pod poni¿sza tabela jest jeszcze wykaz slow posortowany wg ";
		returned_str += "ilosci wystapien danego slowa we wczytanym tekscie):\n ";
		returned_str.insert(returned_str.size(), 86, '_');
		returned_str += " \n|";
		returned_str += "slowa, ktore znajduja sie we wczytanym tekscie|";
		returned_str += "liczba wystapien danego slowa w tekscie|\n|";
		returned_str.insert(returned_str.size(), 46, '_');
		returned_str += "|";
		returned_str.insert(returned_str.size(), 39, '_');
		returned_str += "|\n";
		returned_str += write_all_words_sorted_alphabetically();
		returned_str += "\n\nPonizej znajduje sie wykaz slow uzytych w wczytanym tekscie\n";
		returned_str += "posortowany wedlug iloscy wystapien danego slowa w tekscie:\n\n";
		returned_str += " ";
		returned_str.insert(returned_str.size(), 86, '_');
		returned_str += " \n|";
		returned_str += "slowa, ktore znajduja sie we wczytanym tekscie|";
		returned_str += "liczba wystapien danego slowa w tekscie|\n|";
		returned_str.insert(returned_str.size(), 46, '_');
		returned_str += "|";
		returned_str.insert(returned_str.size(), 39, '_');
		returned_str += "|\n";
		returned_str += write_all_words_sorted_by_number_of_occurences();	
	}

	else
		returned_str += ", dlatego slownik nie zostal wygenerowany!\n";

	return returned_str;
}

