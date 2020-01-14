#pragma once

#include <algorithm>
#include <string>

class DuplicateWordSearch
{
public:	
	DuplicateWordSearch() = default;

	DuplicateWordSearch(const DuplicateWordSearch&) = default;

	virtual ~DuplicateWordSearch() = default;

	virtual auto insert_word(const std::string& word) -> bool = 0; //funkcje skladowe czysto wirtualne

	virtual auto words_are_inserted() -> void = 0;

	virtual auto remove() -> void = 0;

	virtual auto write_all_words_sorted_alphabetically() const -> std::string  = 0;

	virtual auto get_structure_info(const std::string& file) const -> std::string = 0;

	virtual auto get_structure_type() const -> std::string = 0;

	virtual auto get_number_of_all_words() const -> int = 0;

	virtual auto get_number_of_different_words() const -> int = 0;

	virtual auto operator=(const DuplicateWordSearch& _copy) -> DuplicateWordSearch&;

	virtual auto copy_using_assignment_operator(const DuplicateWordSearch&  _copy) -> DuplicateWordSearch & = 0;

	auto change_big_letters_to_lower(std::string& word) -> std::string;

	auto reject_punctuation_marks_and_unsupported_polish_marks(std::string& word) -> std::string;

protected:
	int number_of_all_words{};
};

