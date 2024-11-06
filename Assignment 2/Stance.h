//
// Created by Michael on 30/09/2024.
//

#ifndef ASSIGNMENT2_STANCE_H
#define ASSIGNMENT2_STANCE_H

#include "Issue.h"

class Stance {
private:
    Issue issue;       // The issue related to the stance
    double strength;   // Strength of the stance (range can be 0.0 to 1.0)

public:
    enum Position { SUPPORT, OPPOSE, NEUTRAL } position; // Current position on the issue

    Stance(); // Default constructor
    Stance(Issue, double, Position);
    [[nodiscard]] Position getPosition() const;
    [[nodiscard]] const Issue& getIssue() const;
    void setStrength(double);
    [[nodiscard]] double getStrength() const;
    //double calculateSimilarity(const Stance&) const;
    static std::string stancePositionToString(Stance::Position position);
};


#endif //ASSIGNMENT2_STANCE_H
