#include <map>
#include <vector>
#include <iostream>
#include <string>

class Time {
public:
    Time(unsigned day, std::string timeStr, unsigned duration) :
        _day(day), _timeStr(timeStr), _duration(duration)
    {
        unsigned hours = std::stoi(timeStr.substr(0, 2));
        unsigned minutes = std::stoi(timeStr.substr(3, 4));
        _start = hours * 60 + minutes;

        _absolute_start = _day * 24 * 60 + _start;
        _absolute_end = _absolute_start + _duration;
    }

    unsigned getDay() const {
        return _day;
    }
    std::string getTimeStamp() const {
        return _timeStr + " " + std::to_string(_duration);
    }

    bool operator<(const Time& b) const {
        return _absolute_end <= b._absolute_start;
    }
    bool operator>(const Time& b) const {
        return _absolute_start <= b._absolute_end;
    }
    bool operator==(const Time& b) const {
        return !(*this > b) && !(*this < b);
    }

private:
    unsigned _day;
    unsigned _start;
    unsigned _duration;

    unsigned _absolute_start;
    unsigned _absolute_end;

    std::string _timeStr;
};


class Person {
public:
    using Meeting = std::pair<Time, std::vector<std::string>>;
    using MembersVector = std::vector<std::string>;

public:
    bool isBusy(const Time& time) const {
        bool is_busy = false;
        auto it = _meetings.find(time);
        if (it != _meetings.end()) {
            is_busy = true;
        }
        return is_busy;
    }

    void appoint(const Time& time, const MembersVector& members) {
        if (!isBusy(time))
            _meetings[time] = members;
    }

    std::vector<Meeting> getMeetings(unsigned day) const {
        std::vector<Meeting> meetings_that_day;
        for (auto meeting : _meetings) {
            if (meeting.first.getDay() == day)
                meetings_that_day.push_back(meeting);
        }
        return meetings_that_day;
    }

private:
    std::map<Time, MembersVector> _meetings;
};

void meetingManager() 
{
    unsigned input_length;
    std::cin >> input_length;
    std::string output = "";

    std::map<std::string, Person> people;

    for (unsigned i = 0; i < input_length; ++i) {
        std::string command;
        std::cin >> command;

        if (command == "APPOINT") {
            unsigned day;
            std::string timeStr;
            unsigned duration;
            std::cin >> day >> timeStr >> duration;
            Time time(day, timeStr, duration);

            unsigned people_count;
            std::cin >> people_count;
            std::vector<std::string> members;
            std::vector<std::string> fails;
            for (unsigned j = 0; j < people_count; ++j) {
                std::string member;
                std::cin >> member;
                
                auto search = people.find(member);
                if (search != people.end())
                    if (search->second.isBusy(time))
                        fails.push_back(member);

                members.push_back(member);
            }

            if (fails.empty()) {
                output += "OK \n";
                for (auto member : members)
                    people[member].appoint(time, members);
            }
            else {
                output += "FAIL \n";
                for (auto member : fails) {
                    output += member + " ";
                }
                output += "\n";
            }

        }
        else if (command == "PRINT") {
            unsigned day;
            std::string member;
            std::cin >> day >> member;

            std::vector<Person::Meeting> meetings;
            auto search = people.find(member);
            if (search != people.end()) 
                meetings = search->second.getMeetings(day);

            for (auto meeting : meetings) {
                output += meeting.first.getTimeStamp();
                for (auto person : meeting.second) {
                    output += " ";
                    output += person;
                }
                output += "\n";
            }
        }
    }

    std::cout << output;
}


int main() 
{
    meetingManager();
    return 0;
}
