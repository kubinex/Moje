#pragma once
#include <chrono>
#include <Windows.h>
#include <string>

class DateTime
{
public:
	class NoLocalTimePointException {};

	DateTime() { set_time_point_at_initialization(); };

	DateTime(const DateTime&);

	auto operator=(const DateTime& _copy) -> DateTime &;

	auto get_date_at_initialization() const -> SYSTEMTIME { return date_at_initialization; };

	auto get_date_local_first() const -> SYSTEMTIME { return date_local_first; };

	auto get_date_local_second() const -> SYSTEMTIME { return date_local_second; };

	auto get_date_local_current() const -> SYSTEMTIME { return date_local_current; };

	auto get_time_at_initialization() const -> std::chrono::system_clock::time_point { return time_at_initialization; };

	auto get_time_local_first() const -> std::chrono::system_clock::time_point { return time_local_first; };

	auto get_time_local_second() const -> std::chrono::system_clock::time_point { return time_local_second; };

	auto get_time_local_current() const -> std::chrono::system_clock::time_point { return time_local_current; };

	auto set_time_point_at_initialization() -> void;

	auto set_time_point_local_first() -> void;

	auto set_time_point_local_second() -> void;

	auto set_time_point_current() -> void;

	auto hours(const std::chrono::system_clock::time_point& before, const std::chrono::system_clock::time_point& after) const -> int;

	auto minutes(const std::chrono::system_clock::time_point& before, const std::chrono::system_clock::time_point& after) const -> int;

	auto seconds(const std::chrono::system_clock::time_point& before, const std::chrono::system_clock::time_point& after) const -> int;

	auto milliseconds(const std::chrono::system_clock::time_point& before, const std::chrono::system_clock::time_point& after) const -> int;

	auto microseconds(const std::chrono::system_clock::time_point& before, const std::chrono::system_clock::time_point& after) const -> int;

	auto get_date_time_info_about_difference_beetween_initialization_and_current_time() -> std::string;

	auto get_date_as_string(const SYSTEMTIME& date) const -> std::string;

private:
	SYSTEMTIME date_at_initialization{};

	SYSTEMTIME date_local_first{};

	SYSTEMTIME date_local_second{};

	SYSTEMTIME date_local_current{};

	std::chrono::system_clock::time_point time_at_initialization{};

	std::chrono::system_clock::time_point time_local_first{};

	std::chrono::system_clock::time_point time_local_second{};

	std::chrono::system_clock::time_point time_local_current{};

	auto write_only_three_least_significant_digits(int number) const -> int;
};