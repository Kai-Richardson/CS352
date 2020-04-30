#include "hw5.hpp"

#include <fstream>
#include <iostream>
#include <string>

/// Runs parseRecord on each line of the file, printing the results
void parseAllRecords(std::istream& in, std::ostream& out) {
    std::string line;
    while ( std::getline(in, line) ) {
        try {
            out << parseRecord(line) << std::endl;
        } catch (const WrongFieldCount& e) {
            out << "Wrong number of fields: " << e.num_fields << std::endl;
        } catch (const InvalidCourseNum& e) {
            out << "Invalid course number: " << e.course_num << std::endl;
        } catch (const NegativeCourseNum& e) {
            out << "Not a positive integer for course number: " << e.course_num << std::endl;
        } catch (const InvalidNumCredits& e) {
            out << "Invalid number of credits: " << e.num_credits << std::endl;
        } catch (const InvalidGrade& e) {
            out << "Invalid grade: " << e.grade << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    switch(argc) {
        case 1: {
            parseAllRecords(std::cin, std::cout);
            break;
        }
        case 2: {
            std::ifstream in{argv[1]};
            parseAllRecords(in, std::cout);
            break;
        }
        case 3: {
            std::ifstream in{argv[1]};
            std::ofstream out{argv[2]};
            parseAllRecords(in, out);
            break;
        }
        default: {
            std::cout << "usage: " << argv[0] << " [infile [outfile]]" << std::endl;
            break;
        }
    }
}