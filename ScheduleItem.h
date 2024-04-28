#pragma once

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class ScheduleItem {
private:
    string subject;
    string catalog;
    string section;
    string component;
    string session;
    int units;
    int totEnrl;
    int capEnrl;
    string instructor;

public:
    // Constructor with default parameters
    ScheduleItem(string subj = "", string cat = "", string sect = "", string comp = "", string sess = "", int u = 0, int tot = 0, int cap = 0, string instr = "") :
        subject(subj), catalog(cat), section(sect), component(comp), session(sess), units(u), totEnrl(tot), capEnrl(cap), instructor(instr) {}

    // Getter functions for private member variables
    string getSubject() const { return subject; }
    string getCatalog() const { return catalog; }
    string getSection() const { return section; }
    string getComponent() const { return component; }
    string getSession() const { return session; }
    int getUnits() const { return units; }
    int getTotEnrl() const { return totEnrl; }
    int getCapEnrl() const { return capEnrl; }
    string getInstructor() const { return instructor; }

    // Overloaded comparison operators for comparing ScheduleItem objects
    bool operator==(const ScheduleItem& other) const {
        return (subject == other.subject && catalog == other.catalog && section == other.section);
    }

    bool operator!=(const ScheduleItem& other) const {
        return !(*this == other);
    }

    bool operator>=(const ScheduleItem& other) const {
        return (subject >= other.subject && catalog >= other.catalog && section >= other.section);
    }

    // Function to print the ScheduleItem object
    void print() const {
        cout << left << setw(8) << subject << setw(10) << catalog << setw(10) << section << setw(12) << component << setw(10) << session
            << setw(6) << units << setw(10) << totEnrl << setw(10) << capEnrl << setw(20) << instructor << endl;
    }
};
