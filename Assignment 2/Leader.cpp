//
// Created by Michael on 30/09/2024.
//
// Leader class implementation
#include "Leader.h"
#include "Candidate.h"

// Constructor Implementation
Leader::Leader(std::string name, double popularity)
        : People(popularity), name(std::move(name)) { }

// default constructor of Leader
Leader::Leader() : People(0.0), name("Unamed Leader") {} // Default values for name and popularity

double Leader::getPopularity() const {
    return this->popularity;  // Return the popularity
}

void Leader::setPopularity(double popularity) {
    this->popularity = popularity;  // Set the popularity
}

std::string Leader::getName() const {
    return this->name;  // Return the name
}

void Leader::setFromCandidate(const Candidate &candidate) {
    this->name = candidate.getName();
    this->popularity = candidate.getPopularity();
}
