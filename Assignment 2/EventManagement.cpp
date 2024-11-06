//
// Created by Michael on 30/09/2024.
//

#include "EventManagement.h"
#include "Candidate.h"

Event::Event(std::string type, double impact)
        : type(std::move(type)), impact(impact) {}

void Event::executeEvent(ElectoralDivision &division) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> candidateDist(0, division.getCandidateCount() - 1);
    std::uniform_real_distribution<> stanceChangeDist(-0.2, 0.2);

    // Apply a stance change to a random issue in the division
    int randomCandidateIndex = candidateDist(gen);
    Candidate& candidate = division.getCandidates()[randomCandidateIndex];

    for (int index = 0; index < division.getCandidateCount(); index++) {
        // Change stance strength based on event impact
        for (int stanceIndex=0; stanceIndex < 5; stanceIndex++) {
            std::array<Stance, 5>& stances = division.getStances();
            double newStrength = stances[index].getStrength() + stanceChangeDist(gen) * impact;
            stances[index].setStrength(std::clamp(newStrength,0.0, 1.0));
        }
    }
}

void Event::adjustCandidatePopularity(Candidate &candidate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-0.1, 0.1);

    double change = dist(gen);
    double newPopularity = candidate.getPopularity() + change;
    candidate.setPopularity(std::clamp(newPopularity, 0.0, 1.0));
}

void ElectionDay::triggerEvents(std::vector<ElectoralDivision> &divisions) {
    std::cout << "Election Day: Special events triggered!" << std::endl;

    // Election day might have different types of events
    for (ElectoralDivision& division : divisions) {
        // Perhaps apply special, more impactful events
        Event electionDayEvent("Election-Day", 1.5); // Higher impact on Election Day
        electionDayEvent.executeEvent(division); // Execute a major event in each division
    }
}

void EventDay::adjustLeaderPopularity(Leader& leader) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-0.1, 0.1);

    double popularityChange = dist(gen);
    leader.setPopularity(std::clamp(leader.getPopularity() + popularityChange, 0.0, 1.0));
}

void EventDay::triggerEvents(std::vector<ElectoralDivision> &divisions) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    for(int index=0; index < divisions.size(); ++index) {
        double prob = dist(gen);
        ElectoralDivision& division = divisions[index];
        if(prob <= 0.4) {
            // Trigger candidate popularity event
            adjustCandidatePopularity(division.getCandidates()[index]);
        } else if (prob <= 0.6) {
            // Trigger candidate stance change
            adjustCandidateStances(division.getCandidates()[index]);
        } else if (prob <= 0.8) {
            // Trigger candidate popularity event
            adjustLeaderPopularity(division.getLeader());
        } else {
            // Trigger division stance change
            adjustDivisionStances(division);
        }
    }
}

EventDay::EventDay(std::string m_type, double impact, Event *events, double d) : Event(std::move(m_type),
                                                                                       impact) {}

void EventDay::adjustCandidateStances(Candidate candidate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-0.1, 0.1);

    for (Stance& stance : candidate.getStances()) {
        // This needs to return a non-const reference
        double newStrength = stance.getStrength() + dist(gen);
        stance.setStrength(std::clamp(newStrength, 0.0, 1.0));
    }
}

void EventDay::adjustDivisionStances(ElectoralDivision division) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-0.1, 0.1);  // Random change between -0.1 and 0.1

    // Adjust each stance's strength
    for (Stance& stance : division.getStances()) {
        double newStrength = stance.getStrength() + dist(gen); // Randomly change the strength
        stance.setStrength(std::clamp(newStrength, 0.0, 1.0)); // Ensure strength stays between 0 and 1
    }
}