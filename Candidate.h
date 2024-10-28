#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
#include <array>
#include "People.h" // Ensure this is included if Candidate inherits from People
#include "Leader.h" // If you are using Leader here


class Candidate : public People {
public:
    Candidate(const std::string &name, double popularity, Leader &leader, int partyIndex, std::array<Stance, 5> candidateStances);

    double calculateScore(const ElectoralDivision& division) const;
    void updateStance(Stance& stance, int index);
    void printStances() const;
    static std::string getLeader(Candidate& candidate);
    std::string getName() const;
    std::array<Stance, 5> getStances();
    double getPopularity() const;
    void updatePopularity(double);
    void setPopularity(double newPopularity);
    int getPartyIndex() const;
    std::string getKeyIssue() const;

private:
    std::string name;
    double popularity;
    Leader& leader;
    int partyIndex;
    std::array<Stance, 5> stances; // Ensure you have this member variable
};

#endif // CANDIDATE_H
