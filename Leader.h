#ifndef ASSIGNMENT2_LEADER_H
#define ASSIGNMENT2_LEADER_H

#include <string>
#include "People.h"

// Forward declaration of Candidate
class Candidate;

class Leader : public People {
public:
    Leader(std::string name, double popularity);
    Leader();
    [[nodiscard]] double getPopularity() const;
    void setPopularity(double popularity);
    [[nodiscard]] std::string getName() const;
    void setFromCandidate(const Candidate& candidate); // Use the forward declaration here
private:
    std::string name;
};

#endif // ASSIGNMENT2_LEADER_H
