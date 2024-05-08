// Derrick_Map_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Schedule.h"

// Function to calculate hash index for a given key
size_t calculateHashIndex(const std::string& key) {
    return key.length();
}

int main()
{
    size_t tableSize = 20;
    Schedule schedule(tableSize);
    ifstream file("STEM - Summer 2022 Schedule of Classes as of 05-02-22(1).csv");

    if (file.is_open()) 
    {
        schedule.initSchedule(file);
        file.close();
    }
    else 
    {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    int choice;
    string subject, catalog, instructor;

    // Menu loop
    do {
        cout << "Menu:" << endl;
        cout << "1. Print schedule" << endl;
        cout << "2. Find records by subject" << endl;
        cout << "3. Find records by subject and catalog" << endl;
        cout << "4. Find records by instructor" << endl;
        cout << "5. Display table statistics" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            schedule.print();
            break;
        case 2:
            cout << "Enter subject: ";
            cin >> subject;
            schedule.findSubject(subject);
            break;
        case 3:
            cout << "Enter subject: ";
            cin >> subject;
            cout << "Enter catalog: ";
            cin >> catalog;
            schedule.findSubjectCatalog(subject, catalog);
            break;
        case 4:
            cout << "Enter instructor's last name: ";
            cin >> instructor;
            schedule.findInstructor(instructor);
            break;
        case 5:
            schedule.statistics();
        case 6:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    } while (choice != 6);

    return 0;
}