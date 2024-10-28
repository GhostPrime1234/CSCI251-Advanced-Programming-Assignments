//
// Created by Michael on 30/09/2024.
//

#include "Candidate.h" // Correctly include the Candidate header file
#include "ElectoralEntities.h" // Include if used

Candidate::Candidate(const std::string &name, double popularity, Leader &leader, int partyIndex, std::array<Stance, 5> candidateStances)
        : People(popularity), name(name), popularity(popularity), leader(leader), partyIndex(partyIndex), stances(candidateStances) {
}

void Candidate::printStances() const {
    std::cout << "Candidate: " << name << ", Popularity: " << popularity << "%" << std::endl;
    std::cout << "Stances on Issues: " << std::endl;

    for (const Stance& stance : stances) {
        std::string stanceStr;
        switch(stance.getPosition()) {
            case Stance::SUPPORT:
                stanceStr = "Support";
                break;
            case Stance::OPPOSE:
                stanceStr = "Oppose";
                break;
            case Stance::NEUTRAL:
                stanceStr = "Neutral";
                break;
        }
        std::cout << " - " << stance.getIssue().getName() << ": " << stanceStr << " (Support Level: " << stance.getStrength() * 100 << "%)" << std::endl;
    }
    std::cout << std::endl;
}

std::string Candidate::getName() const {
    return this->name;
}

std::array<Stance, 5> Candidate::getStances() {
    return this->stances;
}

double Candidate::getPopularity() const {
    return this->popularity;
}

void Candidate::setPopularity(double newPopularity) {
    this->popularity = newPopularity;
}

int Candidate::getPartyIndex() const {
    return this->partyIndex;
}
void Candidate::updateStance(Stance &stance, int index) {
    this->stances[index] = stance;
}
void Candidate::updatePopularity(double change) {
    this->popularity += change;
    if (this->popularity < 0.0)
        this->popularity = 0.0;  // Ensure no negative popularity
    if (this->popularity > 100.0)
        this->popularity = 100.0; // Cap at 100 if needed
}