#include "ProgramService.h" 
using namespace std;

auto ProgramService::operator=(const ProgramService& _copy) -> ProgramService &
{
	if (&_copy != this)
	{
		remove();

		list_of_arguments = _copy.list_of_arguments;

		list_of_key_words = _copy.list_of_key_words;		

		time = _copy.time;

		if (_copy.get_structure())
		{
			initialize_structure();

			structure->copy_using_assignment_operator(*_copy.structure);
		}
	}

	return *this;
}

auto ProgramService::remove() -> void
{
	delete structure;
	structure = nullptr;

	if (input.is_open())
		input.close();

	if (output.is_open())
		output.close();
}

auto ProgramService::initialize_list_of_key_words() -> void
{
	list_of_key_words["cointainer"] = "cointainer";
	list_of_key_words["map"] = "cointainer";
	list_of_key_words["Cointainer"] = "cointainer";
	list_of_key_words["Map"] = "cointainer";

	list_of_key_words["tree"] = "binary_tree";
	list_of_key_words["binary_tree"] = "binary_tree";
	list_of_key_words["Tree"] = "binary_tree";
	list_of_key_words["Binary_tree"] = "binary_tree";

	list_of_key_words["tree_cstr"] = "binary_tree_cstring";
	list_of_key_words["tree_cstring"] = "binary_tree_cstring";
	list_of_key_words["binary_tree_cstr"] = "binary_tree_cstring";
	list_of_key_words["binary_tree_cstring"] = "binary_tree_cstring";
	list_of_key_words["Tree_cstr"] = "binary_tree_cstring";
	list_of_key_words["Tree_cstring"] = "binary_tree_cstring";
	list_of_key_words["Binary_tree_cstr"] = "binary_tree_cstring";
	list_of_key_words["Binary_tree_cstring"] = "binary_tree_cstring";
}

auto ProgramService::initialize_structure() -> void
{
	map<string, string>::const_iterator it;

	it = list_of_key_words.find(list_of_arguments.at("-a"));

	if (it->second == "cointainer")
		structure = new Cointainer;

	else if (it->second == "binary_tree")
		structure = new BinaryTree;

	else
		structure = new BinaryTreeCString;
}

auto ProgramService::copy_structure(const ProgramService& _copy) -> DuplicateWordSearch*
{
	if (!_copy.get_list_of_arguments().empty())
	{
		map<string, string>::const_iterator it;

		it = list_of_key_words.find(list_of_arguments.at("-a"));

		if (it->second == "cointainer")
			structure = new Cointainer{ *_copy.get_structure() };

		else if (it->second == "binary_tree")
			structure = new BinaryTree{ *_copy.get_structure() };

		else
			structure = new BinaryTreeCString{ *_copy.get_structure() };

		return structure;
	}

	else
		return nullptr;
}

auto ProgramService::load_arguments_and_initialize_structure(int argc, char* argv[]) -> void
{
	string argument;

	bool is_input{}, is_output{}, is_structure{};

	initialize_list_of_key_words();

	if (argc == 1)
		throw ShowHelpException();

	else if (argc == 2)
	{
		for (int i = 1; i < argc; ++i)
		{
			argument = argv[i];

			if (argument == "-h")
				throw ShowHelpException();

			else if (i == argc - 1)
				throw UnproperArgumentsException();
		}
	}

	else if (argc != 7)
		throw UnproperArgumentsException();

	for (int i = 1; i < argc; ++i)
	{
		if (argument == "-i")
		{
			list_of_arguments["-i"] = argv[i];
			is_input = true;
		}

		else if (argument == "-o")
		{
			list_of_arguments["-o"] = argv[i];
			is_output = true;
		}

		else if (argument == "-a")
		{
			is_structure = true;

			argument = argv[i];

			map<string, string>::iterator it;

			it = list_of_key_words.find(argument);

			if (it != list_of_key_words.end())
				list_of_arguments["-a"] = argv[i];

			else
				throw UnproperArgumentsException();
		}

		argument = argv[i];
	}

	if (!is_input || !is_output || !is_structure)
		throw UnproperArgumentsException();

	initialize_structure();
}

auto ProgramService::open_input_and_output_file_if_not_opened() -> void
{	
	if(input.is_open())
		input.close();

	input.open(list_of_arguments.at("-i"), ios::in);

	if (!input.good())
		//jesli wejscie nieprawidlowe - rzucamy wyjatek
		throw OpenFileException();
	
	if (output.is_open())
		output.close();

	output.open(list_of_arguments.at("-o"), ios::out);

	if (!output.good())
		throw WriteToFileException();
}

auto ProgramService::load_words_from_file_into_program() -> void
{
	open_input_and_output_file_if_not_opened();

	string word;
		
	while (!input.eof())
	{
		input >> word;

		if (!input.fail())
		{
			word = structure->reject_punctuation_marks_and_unsupported_polish_marks(word);
			word = structure->change_big_letters_to_lower(word);

			if (!word.empty())
				structure->insert_word(word);							
		}						
	}

	structure->words_are_inserted();
}

auto ProgramService::write_report() -> void
{	
	if (!list_of_arguments.empty())
	{
		open_input_and_output_file_if_not_opened();

		output << "Raport dotyczacy programu:" << endl << endl
			<< "Program dzialal w nastepujacym przedziale czasowym:\n"
			<< time.get_date_time_info_about_difference_beetween_initialization_and_current_time()
			<< endl << endl << structure->get_structure_info(get_list_of_arguments().at("-i"))
			<< endl << "Program napisal Jakub Lagodka.";
	}
	//trzeba zrobic tez raport jesli bylo puste!
}
