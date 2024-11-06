//
// Created by Michael on 30/09/2024.
//

#ifndef ASSIGNMENT2_EVENTMANAGEMENT_H
#define ASSIGNMENT2_EVENTMANAGEMENT_H

#include "ElectoralEntities.h"
#include <random>
#include <iostream>
#include <algorithm>

class Candidate;
class Leader;
class ElectoralDivision;

class Event {
private:
    std::string type; // Type of the event
    double impact;    // Impact on popularity or stances
public:
    Event(std::string, double);
    static void adjustCandidatePopularity(Candidate&);
    void executeEvent(ElectoralDivision&) const; // Modify division based on event
};

class EventDay: protected Event {
private:
    std::vector<Event> events; // List of events for the day
public:
    explicit EventDay(std::string, double, Event*, double);
    virtual ~EventDay() = default;

    virtual void triggerEvents(std::vector<ElectoralDivision>&); // Trigger events for all divisions

    static void adjustCandidateStances(Candidate candidate);
    static void adjustLeaderPopularity(Leader&);

    static void adjustDivisionStances(ElectoralDivision);
};

class ElectionDay final : public EventDay {
public:
    ElectionDay() : EventDay(std::string(), 0, nullptr, 0) {}

    void triggerEvents(std::vector<ElectoralDivision>&) override;
};


#endif //ASSIGNMENT2_EVENTMANAGEMENT_H
