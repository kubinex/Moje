#include "DateTime.h"
using namespace std;

DateTime::DateTime(const DateTime& _copy) : date_local_second {_copy.date_local_second},
date_local_current {_copy.date_local_current}, time_at_initialization {_copy.time_at_initialization},
time_local_first {_copy.time_local_first}, time_local_second {_copy.time_local_second},
time_local_current{_copy.time_local_current}
{
	set_time_point_at_initialization();
}

auto DateTime::operator=(const DateTime& _copy) -> DateTime &
{
	if (&_copy != this)
	{
		date_local_first = _copy.date_local_first ;

		date_local_second = _copy.date_local_second ;

		date_local_current = _copy.date_local_current ;

		time_local_first = _copy.time_local_first ;

		time_local_second = _copy.time_local_second ;

		time_local_current = _copy.time_local_current ;

		set_time_point_at_initialization();
	}

	return *this;
}

auto DateTime::hours(const chrono::system_clock::time_point& before, const chrono::system_clock::time_point& after) const -> int
{
	int difference = static_cast<int>(chrono::duration_cast<chrono::hours>(after - before).count());

	if (difference < 0)
		throw NoLocalTimePointException();

	return difference;
}

auto DateTime::minutes(const chrono::system_clock::time_point& before, const chrono::system_clock::time_point& after) const -> int 
{
	int difference = static_cast<int>(chrono::duration_cast<chrono::minutes>(after - before).count());

	if (difference < 0)
		throw NoLocalTimePointException();

	return static_cast<int>(chrono::duration_cast<chrono::minutes>(after - before).count());
}

auto DateTime::seconds(const chrono::system_clock::time_point& before, const chrono::system_clock::time_point& after) const -> int 
{
	int difference = static_cast<int>(chrono::duration_cast<chrono::seconds>(after - before).count());

	if (difference < 0)
		throw NoLocalTimePointException();

	return difference;
}

auto DateTime::milliseconds(const chrono::system_clock::time_point& before, const chrono::system_clock::time_point& after) const -> int 
{
	int difference = write_only_three_least_significant_digits(
		static_cast<int>(chrono::duration_cast<chrono::milliseconds>(after - before).count()));

	if (difference < 0)
		throw NoLocalTimePointException();

	return difference;
}

auto DateTime::microseconds(const chrono::system_clock::time_point& before, const chrono::system_clock::time_point& after) const -> int
{
	int difference = write_only_three_least_significant_digits(
		static_cast<int>(chrono::duration_cast<chrono::microseconds>(after - before).count()));

	if (difference < 0)
		throw NoLocalTimePointException();

	return difference;
}

auto DateTime::write_only_three_least_significant_digits(int number) const -> int
{
	int returned_number{};

	int multiplicator = 1;

	while (multiplicator < 1000)
	{
		returned_number += multiplicator * (number % 10);

		multiplicator *= 10;

		number /= 10;
	}

	return returned_number;
}

auto DateTime::set_time_point_at_initialization() -> void
{
	GetLocalTime(&date_at_initialization);

	time_at_initialization = chrono::system_clock::now();
}

auto DateTime::set_time_point_local_first() -> void
{
	GetLocalTime(&date_local_first);

	time_local_first = chrono::system_clock::now();
}

auto DateTime::set_time_point_local_second() -> void
{
	GetLocalTime(&date_local_second);

	time_local_second = chrono::system_clock::now();
}

auto  DateTime::set_time_point_current() -> void
{
	GetLocalTime(&date_local_current);

	time_local_current = chrono::system_clock::now();
}

auto DateTime::get_date_time_info_about_difference_beetween_initialization_and_current_time() -> string
{
	string returned_str;

	set_time_point_current();

	returned_str += "od ";
	returned_str += get_date_as_string(get_date_at_initialization());
	returned_str += "\ndo ";
	returned_str += get_date_as_string(get_date_local_current());
	returned_str += "\nProgram dzialal przez ";
	returned_str += to_string(hours(get_time_at_initialization(), get_time_local_current())) + " godzin, ";
	returned_str += to_string(minutes(get_time_at_initialization(), get_time_local_current())) + " minut, ";
	returned_str += to_string(seconds(get_time_at_initialization(), get_time_local_current())) + " sekund, ";
	returned_str += to_string(milliseconds(get_time_at_initialization(), get_time_local_current())) + " milisekund, ";
	returned_str += to_string(microseconds(get_time_at_initialization(), get_time_local_current())) + " mikrosekund.";

	return returned_str;
}

auto DateTime::get_date_as_string(const SYSTEMTIME& date) const -> string 
{
	string returned_str;

	returned_str += to_string(date.wDay);
	returned_str += ".";
	returned_str += to_string(date.wMonth);
	returned_str += ".";
	returned_str += to_string(date.wYear);
	returned_str += +" o godzinie ";
	returned_str += to_string(date.wHour);
	returned_str += ":";
	returned_str += to_string(date.wMinute);
	returned_str += ":";
	returned_str += to_string(date.wSecond);
	returned_str += ":";
	returned_str += to_string(date.wMilliseconds);
	returned_str += ".";

	return returned_str;
}