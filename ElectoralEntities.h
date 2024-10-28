#ifndef ELECTORAL_ENTITIES_H
#define ELECTORAL_ENTITIES_H

#include <array>
#include <vector>
#include "Stance.h"
#include "PoliticalParty.h"  // Add this include to resolve PoliticalParty
#include "EventManagement.h"

#include <string>
#include <array>
#include <vector>
#include <stdexcept>


class Leader;
class Candidate;
class EventDay;
class PoliticalParty;

class ElectoralDivision {
private:
    double population; // Population in millions
    std::array<Stance, 5> stances; // Stances on issues
    std::vector<Candidate> candidates; // Candidates in this division
    Leader leader; // Assuming Leader has a valid definition

public:
    ElectoralDivision(double, std::array<Stance, 5>&, const std::array<Issue, 5>&);
    void updateStances();
    Candidate calculateWinner(); // Returns the winning candidate
    [[nodiscard]] double getPopulation() const;
    [[nodiscard]] int getCandidateCount() const;
    Leader& getLeader(); // Return Leader reference
    std::vector<Candidate>& getCandidates(); // Return const reference
    std::array<Stance, 5>& getStances();
    void addCandidate(const Candidate&);
    void simulateEventDay(const std::array<PoliticalParty, 3>&);
    void printReport() const;
    static double calculateCosineSimilarity(const Stance&, const Stance&);

    double calculateStanceAndPopulationFactor(Candidate &candidate);
};

class Election {
private:
    const std::array<PoliticalParty, 3>& parties; // Fixed-size array for 3 political parties
    int currentPartyCount = 0;  // Tracks the number of parties added
    std::vector<ElectoralDivision> divisions; // List of electoral divisions
    std::vector<EventDay> eventDays; // List of event days

public:
    explicit Election(const std::array<PoliticalParty, 3>& parties, std::vector<ElectoralDivision> divisions);
    void runSimulation(int);
    bool addParty(const PoliticalParty&);
    void computeResults();
};

#endif // ELECTORAL_ENTITIES_H
