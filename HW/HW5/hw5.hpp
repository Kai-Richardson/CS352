#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include <bits/stdc++.h>

using namespace std;

/***
 *  CS 352 HW 5 By Kai Richardson
 *
 *  Question 2:
 *      New error: NegativeCourseNum
 *          Requires each course number to be a positive integer
 *
 *     ██ ▄█▀ ▄▄▄       ██▓    ██▀███   ██▓ ▄████▄   ██░ ██  ▄▄▄       ██▀███  ▓█████▄   ██████  ▒█████   ███▄    █
 *     ██▄█▒ ▒████▄    ▓██▒   ▓██ ▒ ██▒▓██▒▒██▀ ▀█  ▓██░ ██▒▒████▄    ▓██ ▒ ██▒▒██▀ ██▌▒██    ▒ ▒██▒  ██▒ ██ ▀█   █
 *    ▓███▄░ ▒██  ▀█▄  ▒██▒   ▓██ ░▄█ ▒▒██▒▒▓█    ▄ ▒██▀▀██░▒██  ▀█▄  ▓██ ░▄█ ▒░██   █▌░ ▓██▄   ▒██░  ██▒▓██  ▀█ ██▒
 *    ▓██ █▄ ░██▄▄▄▄██ ░██░   ▒██▀▀█▄  ░██░▒▓▓▄ ▄██▒░▓█ ░██ ░██▄▄▄▄██ ▒██▀▀█▄  ░▓█▄   ▌  ▒   ██▒▒██   ██░▓██▒  ▐▌██▒
 *    ▒██▒ █▄ ▓█   ▓██▒░██░   ░██▓ ▒██▒░██░▒ ▓███▀ ░░▓█▒░██▓ ▓█   ▓██▒░██▓ ▒██▒░▒████▓ ▒██████▒▒░ ████▓▒░▒██░   ▓██░
 *    ▒ ▒▒ ▓▒ ▒▒   ▓▒█░░▓     ░ ▒▓ ░▒▓░░▓  ░ ░▒ ▒  ░ ▒ ░░▒░▒ ▒▒   ▓▒█░░ ▒▓ ░▒▓░ ▒▒▓  ▒ ▒ ▒▓▒ ▒ ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒
 *    ░ ░▒ ▒░  ▒   ▒▒ ░ ▒ ░     ░▒ ░ ▒░ ▒ ░  ░  ▒    ▒ ░▒░ ░  ▒   ▒▒ ░  ░▒ ░ ▒░ ░ ▒  ▒ ░ ░▒  ░ ░  ░ ▒ ▒░ ░ ░░   ░ ▒░
 *    ░ ░░ ░   ░   ▒    ▒ ░     ░░   ░  ▒ ░░         ░  ░░ ░  ░   ▒     ░░   ░  ░ ░  ░ ░  ░  ░  ░ ░ ░ ▒     ░   ░ ░
 *    ░  ░         ░  ░ ░        ░      ░  ░ ░       ░  ░  ░      ░  ░   ░        ░          ░      ░ ░           ░
 */


/// A record representing a student's course performance
struct ClassRecord
{
    string subject;      ///< Subject code
    int course_num;      ///< Course number
    string section;      ///< Section letter
    int num_credits;     ///< Number of course credits
    string student_name; ///< Student's name
    double grade;        ///< Grade in course
};

/// Print a ClassRecord
ostream &operator<<(ostream &out, const ClassRecord &r)
{
    return out << "[" << r.subject << " " << r.course_num << " " << r.section << " "
               << r.num_credits << " " << r.student_name << " " << r.grade << "]";
}

/// Base class for parsing errors
class ParseError
{
public:
    /// Ensure subclasses are properly destroyed
    virtual ~ParseError() = default;
};

/// An error representing the wrong number of fields
struct WrongFieldCount : public ParseError
{
    int num_fields; // the number of fields present

    WrongFieldCount(int n) : num_fields(n) {}
};

/// An error representing a negative course number
struct NegativeCourseNum : public ParseError
{
    int course_num; // the course number that was negative

    NegativeCourseNum(int n) : course_num(n) {}
};

/// An error representing an invalid course number
struct InvalidCourseNum : public ParseError
{
    string course_num; // the course number that could not be parsed

    InvalidCourseNum(const string &n) : course_num(n) {}
};

/// An error representing an invalid number of credits
struct InvalidNumCredits : public ParseError
{
    string num_credits; // the number of credits that could not be parsed

    InvalidNumCredits(const string &n) : num_credits(n) {}
};

/// An error representing an invalid grade
struct InvalidGrade : public ParseError
{
    string grade; // the grade that could not be parsed

    InvalidGrade(const string &g) : grade(g) {}
};

/// Converts a letter grade to the appropriate GPA
/// A = 4.0, B = 3.0, C = 2.0, D = 1.0, F = 0.0
/// All except F can be followed with + or - for +/- 0.3
/// Return the grade on success, throws InvalidGrade on failure
double letterToGpa(const string &sgrade)
{
    int grade = 0;
    string str = sgrade;
    str.append(" "); //To let the below substrings always exist
    if (str.substr(1, 2) == "+")
    {
        grade += 0.3;
    }
    else if (str.substr(1, 2) == "-")
    {
        grade += 0.3;
    }
    switch (str[0]) //Switch over first char
    {
    case 'A':
        return grade += 4;
    case 'B':
        return grade += 3;
    case 'C':
        return grade += 2;
    case 'D':
        return grade += 1;
    case 'F':
        return 0;

    default: //doesn't match pattern
        throw InvalidGrade(sgrade);
        break;
    }
}

//Converts a course number to an int, throws InvalidCourseNum if not an integer
int parseCourseNum(const std::string &s)
{
    std::size_t pos;
    int result = std::stoi(s, &pos);
    if (pos != s.size())
        throw InvalidCourseNum(s);
    return result;
}

//Converts a credit string to an int, throws InvalidNumCredits if not an integer
int parseCredits(const std::string &s)
{
    std::size_t pos;
    int result = std::stoi(s, &pos);
    if (pos != s.size())
        throw InvalidNumCredits(s);
    return result;
}

//Returns the number of space-delineated words in a string
int count_words(string str) {
    int word_count = 0;
    stringstream ss(str);
    string word;
    while( ss >> word ) ++word_count;
    return word_count;
}

/// Convert an input string in the following format to a ClassRecord:
///   Subject CourseNum Section NumCredits FirstName LastName GradeLetter
///
/// The fields are subject to the following constraints:
///   * CourseNum and NumCredits are integer values
///   * GradeLetter is a valid grade according to the following grammar:
///       [A-D]('+'|'-')? | 'F'
///   * There are exactly seven whitespace-separated fields
///
/// Returns the ClassRecord on successful match, throws an appropriate ParseError
/// on failure.
ClassRecord parseRecord(const string &line)
{

    //create holder obj for input
    string str = line;

    //utilize stringstream and holder string
    stringstream ss(str);
    string word;

    //Check for 7 space-seperated fields
    if (count_words(str) != 7) {
        throw WrongFieldCount(count_words(str));
    }

    int numCycles = 0; //Track which number we're on

    //Struct input holder vars
    string OUT_subject = "error";
    int OUT_course_num = -1;
    string OUT_section = "error";
    int OUT_num_credits = -1;
    string OUT_student_name = "error";
    double OUT_grade = -1.0;

    while (ss >> word)
    {
        switch (numCycles)
        {
        case 0:
            OUT_subject = word;
            break;
        case 1:
        {
            try
            {
                int courseInt = stoi(word);
                if (courseInt < 0)
                    throw NegativeCourseNum(courseInt);
                OUT_course_num = courseInt;
            }
            catch(const InvalidNumCredits e)
            {
                throw InvalidNumCredits(word);
            }
            break;
        }
        case 2:
            OUT_section = word;
            break;
        case 3:
            try
            {
                OUT_num_credits = stoi(word);
            }
            catch(const InvalidCourseNum e)
            {
                throw InvalidCourseNum(word);
            }
            break;
        case 4:
            OUT_student_name = word;
            break;
        case 5:
            OUT_student_name.insert(0, ",");
            OUT_student_name.insert(0, word);
            break;
        case 6:
            try
            {
                OUT_grade = letterToGpa(word);
            }
            catch(const InvalidGrade e)
            {
                throw InvalidGrade(word);
            }
            break;
        }

        numCycles++;
    }

    return ClassRecord{
        OUT_subject,
        OUT_course_num,
        OUT_section,
        OUT_num_credits,
        OUT_student_name,
        OUT_grade,
    };
}