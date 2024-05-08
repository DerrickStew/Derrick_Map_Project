#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <utility>
#include <sstream>
#include "ScheduleItem.h"
#include "HashTable.h"

class Schedule 
{
private:
    HashTable<string, ScheduleItem> scheduleMap; // Instance variable changed to HashTable
    function<size_t(const string& )> hashFunction; // Stores user-defined hash function


    // Precondition: None
   // Postcondition: Prints column headers
    void printHeader() const {
        cout << left << setw(8) << "Subject" << setw(10) << "Catalog" << setw(10) << "Section" << setw(12) << "Component" << setw(10) << "Session"
            << setw(6) << "Units" << setw(10) << "TotEnrl" << setw(10) << "CapEnrl" << setw(20) << "Instructor" << endl;
    }

public:
    // Constructor with table size argument
        Schedule(size_t tableSize) : scheduleMap(tableSize) {}

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
        scheduleMap.insert(key, item);
    }

    // Precondition: None
    // Postcondition: Prints column headers followed by all ScheduleItem objects in scheduleMap
    void print() const {
        printHeader();
        for (auto it = scheduleMap.begin(); it != scheduleMap.end(); ++it) {
            it->second.print();
        }

    }

    // Precondition: None
    // Postcondition: Prints column headers followed by ScheduleItem objects with matching subject
    void findSubject(const string& targetSubject) const {
        printHeader();
        for (auto it = scheduleMap.begin(); it != scheduleMap.end(); ++it) {
            if (it->second.getSubject() == targetSubject)
                it->second.print();
        }
    }

    // Precondition: None
    // Postcondition: Prints column headers followed by ScheduleItem objects with matching subject and catalog
    void findSubjectCatalog(const string& targetSubject, const string& targetCatalog) const {
        printHeader();
        for (auto it = scheduleMap.begin(); it != scheduleMap.end(); ++it) {
            if (it->second.getSubject() == targetSubject && it->second.getCatalog() == targetCatalog)
                it->second.print();
        }
    }

    // Precondition: None
    // Postcondition: Prints column headers followed by ScheduleItem objects with matching instructor
    void findInstructor(const string& targetInstructor) const {
        printHeader();
        for (auto it = scheduleMap.begin(); it != scheduleMap.end(); ++it) {
            if (it->second.getInstructor() == targetInstructor)
                it->second.print();
        }
    }

    // Precondition – Receives a pointer to a user-defined hash function
    // Postcondition – Sets the hash function in HashTable.h to the user-defined function
    void setHashFunction(std::function<size_t(const std::string&)> hashFunc) {
        scheduleMap.setHashFunction(hashFunc);
    }

    // Postcondition – Displays the size of the hash table,
    // the number of buckets in the hash table
    // the load factor of the hash table,
    // the number of collisions,
    // and the length of the longest chain
    void statistics() {
        std::cout << "Hash Table Statistics:\n";
        std::cout << "Size of the hash table: " << scheduleMap.getSize() << std::endl;
        std::cout << "Number of buckets in the hash table: " << scheduleMap.getBuckets() << std::endl;
        std::cout << "Load factor of the hash table: " << scheduleMap.getLoadFactor() << std::endl;
        std::cout << "Number of collisions: " << scheduleMap.countCollisions() << std::endl;
        std::cout << "Length of the longest chain: " << scheduleMap.maxBucketSize() << std::endl;
    }
};