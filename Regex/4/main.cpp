#include <iostream>
#include <regex>


class Date_research {
private:
    std::regex pattern_date;
    std::regex pattern_time;

public:
    Date_research() {
        std::regex _pattern_date(R"(\b([\d]{1,4})[\.](([0]?[\d])|([1][012]))[\.](([3][01])|([12][\d])|([0]?[\d]))\b)");
        pattern_date = _pattern_date;
        std::regex _pattern_time(R"((\b(([2][0123])|([1][\d])|([0]?[\d]))[\:]([012345][\d])[\:]([012345][\d])\b))");
        pattern_time = _pattern_time;
    }

    void get_date_from_text(const std::string& str) {
        std::sregex_iterator begin(str.cbegin(), str.cend(), pattern_date);
        std::sregex_iterator end;

        std::cout << "Date: " << std::endl;
        std::for_each(begin, end, [](const std::smatch & m) {
            std::cout << m[0] << std::endl;
        });
    }

    void get_time_from_text(const std::string& str) {
        std::sregex_iterator begin(str.cbegin(), str.cend(), pattern_time);
        std::sregex_iterator end;

        std::cout << "Time: " << std::endl;
        std::for_each(begin, end, [](const std::smatch & m) {
            std::cout << m[0] << std::endl;
        });
    }
};

int main() {
    std::string data = "YYYY.MM.DD   HH:MM:SS\n"
                       "\n"
                       "1423.12.30\t31:23:23\n"
                       "1423.12.04\t12:12:12\n"
                       "2345.00.23\t24:59:34 \n"
                       "1234.12.23  23:24:23\n"
                       "1243.4.23\t00:34:34\n"
                       "1234.04.23  09:34:34\n"
                       "1433.12.23\t00:00:00\n"
                       "0000.23.32\t25:61:61";
    Date_research dateResearch;
    dateResearch.get_date_from_text(data);
    std::cout << std::endl;
    dateResearch.get_time_from_text(data);
    return 0;
}