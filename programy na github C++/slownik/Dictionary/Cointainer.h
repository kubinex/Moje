#pragma once
#include <map>
#include <vector>

#include "DuplicateWordSearch.h"

class Cointainer : public DuplicateWordSearch
{
public:
	Cointainer() : words_sorted_alphabetically{}, words_sorted_by_number_of_occurences{ }
	{ number_of_cointainers += 2; };

	Cointainer(const Cointainer& _copy) : words_sorted_alphabetically{_copy.words_sorted_alphabetically}, 
		words_sorted_by_number_of_occurences{_copy.words_sorted_by_number_of_occurences}, DuplicateWordSearch(_copy) 
	{number_of_cointainers += 2; };

	Cointainer(const DuplicateWordSearch& _copy) : Cointainer(dynamic_cast<const Cointainer&>(_copy)) {};

	~Cointainer() { remove(); };

	auto operator=(const Cointainer& _copy) -> Cointainer &;

	auto insert_word(const std::string& word) -> bool override;

	auto words_are_inserted() -> void override { initialize_words_sorted_by_number_of_occurences(); };
	
	auto remove() -> void override;

	auto write_all_words_sorted_alphabetically() const -> std::string override;

	auto write_all_words_sorted_by_number_of_occurences() const -> std::string;

	auto get_structure_type() const -> std::string override;

	auto get_structure_info(const std::string& file) const -> std::string override;

	auto get_number_of_all_words() const -> int override { return this->number_of_all_words; };

	auto get_number_of_different_words() const -> int override { return static_cast<int>(this->words_sorted_alphabetically.size()); };

	auto copy_using_assignment_operator(const DuplicateWordSearch& _copy) -> DuplicateWordSearch & override 
	{ return operator=(dynamic_cast<const Cointainer&>(_copy)); };

private:

	static int number_of_cointainers;

	std::map<std::string, int> words_sorted_alphabetically{};

	std::multimap<int, std::string> words_sorted_by_number_of_occurences{};

	auto initialize_words_sorted_by_number_of_occurences() -> void;
};

