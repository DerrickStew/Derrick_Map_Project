#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <utility>
#include <sstream>
#include "ScheduleItem.h"

class Schedule 
{
private:
    map<string, ScheduleItem> scheduleMap;

    // Precondition: None
   // Postcondition: Prints column headers
    void printHeader() const {
        cout << left << setw(8) << "Subject" << setw(10) << "Catalog" << setw(10) << "Section" << setw(12) << "Component" << setw(10) << "Session"
            << setw(6) << "Units" << setw(10) << "TotEnrl" << setw(10) << "CapEnrl" << setw(20) << "Instructor" << endl;
    }

public:
    // Precondition: File is open and in correct format (CSV) with column headers
    // Postcondition: Initializes scheduleMap with data from the file
    void initSchedule(ifstream& file) {
        string line;
        getline(file, line); // Discard the first line (header)

        // Read each line of the file and create ScheduleItem objects
        while (getline(file, line)) {
            stringstream ss(line);
            string subject, catalog, section, component, session, instructor;
            int units, totEnrl, capEnrl;

            getline(ss, subject, ',');
            getline(ss, catalog, ',');
            getline(ss, section, ',');
            getline(ss, component, ',');
            getline(ss, session, ',');
            ss >> units;
            ss.ignore(1, ',');
            ss >> totEnrl;
            ss.ignore(1, ',');
            ss >> capEnrl;
            ss.ignore(1, ',');
            getline(ss, instructor, ',');

            // Create a ScheduleItem object and add it to the map
            ScheduleItem item(subject, catalog, section, component, session, units, totEnrl, capEnrl, instructor);
            addEntry(item);
        }
    }

    // Precondition: None
    // Postcondition: Adds the given ScheduleItem to scheduleMap with a unique key
    void addEntry(const ScheduleItem& item) {
        string key = item.getSubject() + "_" + item.getCatalog() + "_" + item.getSection();
        scheduleMap[key] = item;
    }

    // Precondition: None
    // Postcondition: Prints column headers followed by all ScheduleItem objects in scheduleMap
    void print() const {
        printHeader();
        for (const auto& entry : scheduleMap) {
            entry.second.print();
        }
    }

    // Precondition: None
    // Postcondition: Prints column headers followed by ScheduleItem objects with matching subject
    void findSubject(const string& targetSubject) const {
        printHeader();
        for (const auto& entry : scheduleMap) {
            if (entry.second.getSubject() == targetSubject) {
                entry.second.print();
            }
        }
    }

    // Precondition: None
    // Postcondition: Prints column headers followed by ScheduleItem objects with matching subject and catalog
    void findSubjectCatalog(const string& targetSubject, const string& targetCatalog) const {
        printHeader();
        for (const auto& entry : scheduleMap) {
            if (entry.second.getSubject() == targetSubject && entry.second.getCatalog() == targetCatalog) {
                entry.second.print();
            }
        }
    }

    // Precondition: None
    // Postcondition: Prints column headers followed by ScheduleItem objects with matching instructor
    void findInstructor(const string& targetInstructor) const {
        printHeader();
        for (const auto& entry : scheduleMap) {
            if (entry.second.getInstructor() == targetInstructor) {
                entry.second.print();
            }
        }
    }
};