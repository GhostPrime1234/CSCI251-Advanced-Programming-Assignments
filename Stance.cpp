#include "Stance.h"
#include "Issue.h" // Make sure you have this include

// Constructor with parameters
Stance::Stance(Issue issue, double strength, Position position)
    : issue(std::move(issue)), strength(strength), position(position) {}

// Default Constructor
Stance::Stance()
    : issue(Issue("default", 0)), // Create a default Issue here
    strength(0.0),
    position(NEUTRAL) {}


// Getters
Stance::Position Stance::getPosition() const {
    return position;
}

const Issue& Stance::getIssue() const {
    return issue;
}

double Stance::getStrength() const {
    return strength;
}

void Stance::setStrength(double strength) {
    this->strength = strength;
}

std::string Stance::stancePositionToString(Stance::Position position) {
    switch (position) {
        case Stance::SUPPORT:
            return "Support";
        case Stance::OPPOSE:
            return "Oppose";
        case Stance::NEUTRAL:
            return "Neutral";
        default:
            return "Unknown";
    }
}


