#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

class Date {
public:
    Date() {
        time_t t = time(nullptr);
        date = *localtime(&t);
    }

    void GetDate(istream& stream) {
        stream >> get_time(&date, "%Y/%m/%d");
    }

    int Year() const {
        return 1900 + date.tm_year;
    }

    int Month() const {
        return 1 + date.tm_mon;
    }

    int Day() const {
        return date.tm_mday;
    }

private:
    tm date;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.Month() != rhs.Month())return lhs.Month() < rhs.Month();
    else return lhs.Day() < rhs.Day();
}

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.Month() == rhs.Month() && lhs.Day() == rhs.Day();
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setfill('0');
    stream << setw(2) << date.Month() << '/' << setw(2) << date.Day();
}

int main() {
    Date cur_date;
    map<Date, vector<string>> birthday_of_friends;
    string name;
    Date birth;
    while (cin >> name && name != "end") {
        birth.GetDate(cin);
        birthday_of_friends[birth].push_back(name);
    }
    auto it = birthday_of_friends.lower_bound(cur_date);
    if (it == birthday_of_friends.end())return 0;
    if (it->first == cur_date) {
        cout << "Reminder today is the birthday of:\n";
    }
    for (const auto& n: it->second) {
        cout << n << ' ' << it->first << '\n';
    }
    return 0;
}
