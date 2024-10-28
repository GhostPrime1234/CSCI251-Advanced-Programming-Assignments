#ifndef POLITICAL_ENTITIES_H
#define POLITICAL_ENTITIES_H

#include "Leader.h"
#include "Candidate.h"
#include <string>
#include <vector>

class Leader;


class PoliticalParty {
public:
    // Constructor
    PoliticalParty(std::string name, Leader leader, double popularityFactor);

    // Move constructor declaration
    PoliticalParty(PoliticalParty&& other) noexcept;

    void addCandidate(const Candidate& candidate);
    void setName(std::string);
    std::string getName() const;
    [[nodiscard]]  Leader& getLeader();
    double getPopularity() const;  // Getter for the popularity
    void setPopularity(double);    // Setter to update the popularity
    void adjustPopularity(double); // Method to adjust popularity based on an event
    void printReport() const;
private:
    std::string name;
    Leader leader;
    double popularityFactor;
    std::vector<Candidate> candidates; // List of candidates
};

#endif // POLITICAL_ENTITIES_H
