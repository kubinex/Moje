#define _CRTDBG_MAP_ALLOC
#include <iostream>

#include "ProgramService.h"

using std::cout;
using std::endl;

int value_returned_by_program;

/*Program wczytuje i zlicza s³owa z pliku tekstowego w jêzyku angielskim (bez polskich liter) np. ksi¹¿kê. 
Program ma zaimplementowane trzy algorytmy wyszukiwania powtarzaj¹cych siê s³ów - 
pierwszy i drugi wykorzystuje drzewo binarne, ostatni wykorzystuje klasê Map z biblioteki Stl.
Ma koniec dzia³ania program tworzy raport w pliku tekstowym*/
int main(int argc, char* argv[])
{
	{
		ProgramService program, p2;

		try
		{
			cout << "Uwaga! Program nie obsluguje polskich (ani zadnych spoza kodowania ASCII) znakow!" << endl << endl;
			//zrobic tak, zeby tutaj uzywac tylko konstruktorow i operatorow!
			//wyjatek 	catch (ProgramService::UnproperArgumentsException) przeniesc do miejsca, 
			//gdzie sie tworzy program, zeby tam uzytkownik mogl recznie wprowadzic argumenty poprzez konsole
			program.load_arguments_and_initialize_structure(argc, argv);

			program.load_words_from_file_into_program();		

			ProgramService program2 = program, p;

			p = program;

			program2.write_report();

			cout << "Program zakonczyl dzialanie i wygenerowal raport. \nProgram napisal Jakub Lagodka " << endl << endl;
		}
		catch (ProgramService::UnproperArgumentsException)
		{
			cout << "Podano niepoprawne parametry! \nUZYCIE: -i <INPUT FILE> -o <OUTPUT FILE>"
				"-a <";

			for (std::pair<std::string, std::string> element : program.get_list_of_key_words())
			{
				cout << element.first << ", ";
			}

			cout << ">" << endl;			

			value_returned_by_program = 1;
		}
		catch (ProgramService::ShowHelpException)
		{
			cout << "Podano niepoprawne parametry!\nPomoc: Program wczytuje i zlicza slowa z pliku tekstowego w jezyku angielskim\n"
				"wprowadz argumenty w nastepujacej kolejnosci:\n -i <INPUT FILE> -o <OUTPUT FILE> -a"
				"-a <";

			for (std::pair<std::string, std::string> element : program.get_list_of_key_words())
			{
				cout << element.first << ", ";
			}

			cout << ">" << endl;

			value_returned_by_program = 2;
		}
		catch (ProgramService::WriteToFileException)
		{
			cout << "Nie udalo sie zapisac pliku wyjsciowego!";

			value_returned_by_program = 3;
		}
		catch (ProgramService::OpenFileException)
		{
			cout << "Nie udalo sie otworzyc pliku wejsciowego!" << endl;

			value_returned_by_program = 4;
		}
		catch (DateTime::NoLocalTimePointException)
		{
			cout << "W programie nastapilo wywolanie funkcji wypisujacej czas dzialania programu "
				<< "bez poprawnie utworzonego uprzednio punktu czasu!"
				<< "\nTaki punkt mozna utworzyc np. poprzez wywolanie funkcji auto set_time_point_local_first() -> void;"
				<< endl;

			value_returned_by_program = 5;
		}
		catch (...)
		{
			cout << "Wystapil niezydentyfikowany b³¹d podczas dzia³ania programu (wyjatek) i nastapilo zatrzymanie dzialania programu! " 
				<< endl;

			value_returned_by_program = 6;
		}
	}

#ifdef _WIN32
		_CrtDumpMemoryLeaks();

#endif
		return value_returned_by_program;
}
