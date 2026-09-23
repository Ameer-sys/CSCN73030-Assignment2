#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Stores the information for a single student.
struct STUDENT_DATA
{
    string firstName;
    string lastName;
};

int main()
{
    vector<STUDENT_DATA> students;

    // Open the student data file.
    ifstream inputFile("StudentData.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open StudentData.txt" << endl;
        return 1;
    }

    string line;

    // Read each student from the file.
    while (getline(inputFile, line))
    {
        size_t commaPosition = line.find(',');

        if (commaPosition != string::npos)
        {
            STUDENT_DATA student;

            student.firstName = line.substr(0, commaPosition);
            student.lastName = line.substr(commaPosition + 1);

            students.push_back(student);
        }
    }

    inputFile.close();

    return 0;
}