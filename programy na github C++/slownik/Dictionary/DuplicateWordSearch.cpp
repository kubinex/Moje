#include "DuplicateWordSearch.h"
using namespace std;

auto DuplicateWordSearch::operator=(const DuplicateWordSearch& _copy)->DuplicateWordSearch& 
{
	if (&_copy != this)
		number_of_all_words = _copy.number_of_all_words;

	return *this;
}

auto DuplicateWordSearch::change_big_letters_to_lower(string& word) -> string
{
	transform(word.begin(), word.end(), word.begin(), tolower);

	return word;
}

auto DuplicateWordSearch::reject_punctuation_marks_and_unsupported_polish_marks(string& word) -> string
{
	for (int i = 0; i < static_cast<int>(word.size()); i++)
	{		
		if (word.at(i) < 0 || word.at(i) > 255)
		{
			word.erase(i, 1);
			word.insert(i, 1, '~');
		}

		else if (ispunct(word.at(i)))
		{
			word.erase(i, 1); 
			i--;
		}
	}

	return word;
}




