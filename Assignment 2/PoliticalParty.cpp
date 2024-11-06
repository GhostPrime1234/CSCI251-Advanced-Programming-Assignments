//
// Created by michael on 20/09/2024.
//

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <utility>
#include "PoliticalParty.h"
#include "Candidate.h"
#include "Leader.h"

class People;
class Leader;
class Candidate;
class PoliticalParty;



PoliticalParty::PoliticalParty(std::string name, Leader leader, double popularityFactor)
	: name(std::move(name)), leader(std::move(leader)) , popularityFactor(popularityFactor){}

// Move constructor for PoliticalParty
PoliticalParty::PoliticalParty(PoliticalParty&& other) noexcept
    : name(std::move(other.name)),
    leader(std::move(other.leader)),
    popularityFactor(other.popularityFactor),
    candidates(std::move(other.candidates)) {}


std::string PoliticalParty::getName() const {
    return this->name;
}

void PoliticalParty::addCandidate(const Candidate &candidate) {
	candidates.push_back(candidate);
}

Leader& PoliticalParty::getLeader() {
	return leader;
}

void PoliticalParty::printReport() const {
    std::cout << "Party: " << name << std::endl;
    std::cout << "Leader: " << leader.getName() << " with popularity: " << leader.getPopularity() << std::endl;
    std::cout << "Candidates: " << std::endl;
    for (const auto& candidate : candidates) {
        std::cout << " - " << candidate.getName() << " with popularity: " << candidate.getPopularity() << std::endl;
    }
}

double PoliticalParty::getPopularity() const
{
    return popularityFactor;
}