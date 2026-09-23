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

#ifdef PRE_RELEASE
    // Email information is only available in the pre-release version.
    string email;
#endif
};

int main()
{
    vector<STUDENT_DATA> students;

#ifdef PRE_RELEASE
    // Pre-release builds use the expanded student data file
    // containing first name, last name, and email address.
    cout << "Running PRE-RELEASE version" << endl;
    ifstream inputFile("StudentData_Emails.txt");
#else
    // Standard builds use the original student data file.
    cout << "Running STANDARD version" << endl;
    ifstream inputFile("StudentData.txt");
#endif

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open student data file." << endl;
        return 1;
    }

    string line;

    // Read each student record from the selected input file.
    while (getline(inputFile, line))
    {
        STUDENT_DATA student;

        size_t firstComma = line.find(',');

        if (firstComma == string::npos)
        {
            continue;
        }

        student.firstName = line.substr(0, firstComma);

#ifdef PRE_RELEASE
        // Pre-release data contains:
        // FirstName,LastName,Email
        size_t secondComma = line.find(',', firstComma + 1);

        if (secondComma == string::npos)
        {
            continue;
        }

        student.lastName =
            line.substr(firstComma + 1, secondComma - firstComma - 1);

        student.email = line.substr(secondComma + 1);
#else
        // Standard data contains:
        // FirstName,LastName
        student.lastName = line.substr(firstComma + 1);
#endif

        students.push_back(student);
    }

    inputFile.close();

#ifdef _DEBUG
    // Debug-only functionality verifies that the student
    // information was loaded correctly.
    cout << endl;
    cout << "DEBUG MODE - Student Data" << endl;
    cout << "-------------------------" << endl;

    for (const STUDENT_DATA& student : students)
    {
        cout << student.firstName << " "
            << student.lastName;

#ifdef PRE_RELEASE
        cout << " - " << student.email;
#endif

        cout << endl;
    }
#endif

    return 0;
}