#pragma once
#include <fstream>

#include "DuplicateWordSearch.h"
#include "BinaryTree.h"
#include "BinaryTreeCString.h"
#include "Cointainer.h"
#include "DateTime.h"

class ProgramService
{
public:
	class ShowHelpException {};
	class UnproperArgumentsException {};
	class OpenFileException {};
	class WriteToFileException {};

	// Konstruktor bezparametrowy
	ProgramService() = default;

	ProgramService(const ProgramService&);
	//destruktor
	~ProgramService() { remove(); };

	auto operator=(const ProgramService& _copy)->ProgramService &;

	auto load_arguments_and_initialize_structure(int argc, char* argv[]) -> void;

	auto open_input_and_output_file_if_not_opened() -> void;

	auto get_list_of_arguments() const -> std::map<std::string, std::string> { return list_of_arguments; };

	auto get_list_of_key_words() const -> std::map<std::string, std::string> { return list_of_key_words; };

	auto write_report() -> void ;

	auto load_words_from_file_into_program() -> void;

	auto remove() -> void;

private:
	auto initialize_list_of_key_words() -> void;

	auto initialize_structure() -> void;

	DuplicateWordSearch* structure{};

	DateTime time{};

	std::ifstream input;

	std::ofstream output; //tworzymy plik do zapisu

	std::map<std::string, std::string> list_of_arguments{};

	std::map<std::string, std::string> list_of_key_words{};

	/*auto copy_using_operator(const ProgramService& _copy)->void;*/
};
	

