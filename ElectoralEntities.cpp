#include <random>
#include <array>
#include <numeric>
#include <utility>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "ElectoralEntities.h"

class Candidate;

inline std::string generateRandomName() {
    // Corrected size to match the number of names
    const std::array<std::string, 30> firstNames = {
            "John", "Alice", "Bob", "Eve", "Charlie",
            "David", "Sophia", "Michael", "Olivia", "James",
            "Isabella", "Liam", "Mia", "Noah", "Amelia",
            "Ethan", "Ava", "Alexander", "Harper", "Lucas",
            "Ella", "Benjamin", "Grace", "Henry", "Scarlett",
            "Jacob", "Victoria", "Logan", "Zoe", "Jackson"
    };

    const std::array<std::string, 30> lastNames = {
            "Smith", "Johnson", "Williams", "Jones", "Brown",
            "Davis", "Miller", "Wilson", "Moore", "Taylor",
            "Anderson", "Thomas", "Jackson", "White", "Harris",
            "Martin", "Thompson", "Garcia", "Martinez", "Robinson",
            "Clark", "Rodriguez", "Lewis", "Lee", "Walker",
            "Hall", "Allen", "Young", "King", "Wright"
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> firstNameDist(0, firstNames.size() - 1);
    std::uniform_int_distribution<> lastNameDist(0, lastNames.size() - 1);

    return firstNames[firstNameDist(gen)] + " " + lastNames[lastNameDist(gen)];
}

Stance generateRandomStance(const Issue& issue) {
    // Randomly initialise a stance
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> strengthDist(0.0, 1.0);
    std::uniform_int_distribution<> positionDist(0, 2);   // Assuming 0 for 'Support', 1 for 'Oppose' and 2 for 'Neutral'

    double strength = strengthDist(gen);
    int position = positionDist(gen);

    // Ensure the Stance constructor matches the parameters
    return {issue, strength, static_cast<Stance::Position>(position)}; // Change here if needed
}

ElectoralDivision::ElectoralDivision(double population, std::array<Stance, 5>& stances, const std::array<Issue, 5>& issues)
        : population(population), stances(stances) {
    // Initialize stances with random stances for the given issues
    int index = 0;
    for (const Issue &issue: issues) {
        stances[index] = generateRandomStance(issue);

        index++;
    }

    // Initialize candidates
    for (int i = 0; i < 3; ++i) { // Assume 3 candidates
        std::string candidateName = generateRandomName();

        // Generate random popularity for the candidate
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> popularityDist(0.0, 100.0); // Assuming popularity ranges from 0 to 100

        double candidatePopularity = popularityDist(gen);

        // You will need to have a reference to Leader to pass here
        candidates.emplace_back(candidateName, candidatePopularity, leader, i, stances); // name, popularity, leader, party index
    }
}

void ElectoralDivision::printReport() const {
    std::cout << "=== Electoral Division Report ===" << std::endl;
    std::cout << "Population: " << population << " million" << std::endl;

    std::cout << "\n--- Division Stances ---\n";
    for (const Stance& stance : stances) {
        std::string stancePosition = Stance::stancePositionToString(stance.getPosition());
        std::cout << "Issue: " << stance.getIssue().getName()
                  << ", Position: " << stancePosition
                  << ", Strength: " << stance.getStrength() << std::endl;
    }

    std::cout << "\n--- Candidates ---\n";
    for (const Candidate& candidate : candidates) {
        std::cout << "Candidate: " << candidate.getName()
                  << ", Popularity: " << candidate.getPopularity() << "%" << std::endl;
    }

    std::cout << "===============================\n" << std::endl;
}

Candidate ElectoralDivision::calculateWinner() {
    if (candidates.empty()) throw std::runtime_error("No candidates in the division.");

    Candidate* winningCandidate = &candidates[0];
    double highestScore = -1.0;

    for (Candidate& candidate : candidates) {
        // Compute a stance alignment score based on how well candidate's stances match the division's stances
        double stanceAndPoulationFactor = calculateStanceAndPopulationFactor(candidate);

        double candidatePopularity = candidate.getPopularity();
        double leaderPopularity = leader.getPopularity();

        // Combine the factors to compute the total score
        // Define A, B, C coefficients
        double A = 0.7, B= 0.2, C = 0.1;

        double totalScore = A * stanceAndPoulationFactor + B * candidatePopularity + C * leaderPopularity;

        // Determine if this candidate has the highest score so far
        if (totalScore > highestScore) {
            winningCandidate = &candidate;
            highestScore = totalScore;
        }
    }

    this->leader.setFromCandidate(*winningCandidate); // Update the division's leader
    return *winningCandidate;
}


int ElectoralDivision::getCandidateCount() const {
    return static_cast<int>(candidates.size());
}

std::vector<Candidate>& ElectoralDivision::getCandidates() {
    return candidates;
}


Leader& ElectoralDivision::getLeader() {
    return leader;
}

std::array<Stance, 5>& ElectoralDivision::getStances() {
    return stances;
}

void ElectoralDivision::addCandidate(const Candidate& candidate) {
    candidates.push_back(candidate);
}

// Assuming Candidate has a method to update popularity
void ElectoralDivision::simulateEventDay(const std::array<PoliticalParty, 3>& partyList) {
    std::cout << "\n=== Simulating Event Day ===\n" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> popularityDist(0.05, 0.15);
    // Iterate over each candidate in the division
    for (Candidate& candidate : candidates) {
        // Get the party of the candidate
        int partyIndex = candidate.getPartyIndex();

        // Check if the candidate's party is in the provided party list
        if (partyIndex >= 0 && partyIndex < partyList.size()) {
            const PoliticalParty& party = partyList[partyIndex];

            // Simulate a random popularity increase based on the party's strength or other factors
            double popularityIncrease = party.getPopularity() * popularityDist(gen); // Random increase

            // Update the candidate's popularity
            candidate.updatePopularity(popularityIncrease);
            std::cout << "Candidate " << candidate.getName() << " from party " << party.getName()
                << " increased popularity by " << popularityIncrease << "." << std::endl;
        }
    }
    std::cout << "\n-- Updating Stances ---\n";
    std::uniform_real_distribution<> changeDist(-0.01, 0.01);
    // Optionally, you can perform additional event simulations, like updating stances
    for (Stance& stance : stances) {
        double change = changeDist(gen); // Random change in stance strength
        stance.setStrength(std::clamp(stance.getStrength() + change, 0.0, 1.0));
        std::cout << "Updated stance on issue: " << stance.getIssue().getName()
            << ", new strength: " << stance.getStrength() << std::endl;
    }

    std::cout << "===============================\n" << std::endl;
}

double ElectoralDivision::calculateCosineSimilarity(const Stance &candidateStance, const Stance &divisionStance) {
    // Extract the stance strengths
    double candidateStrength = candidateStance.getStrength();
    double divisionStrength = divisionStance.getStrength();

    // Convert positions to vectors
    // Assuming Support = 1, Neutral = 0, Oppose = -1
    double candidatePosition = (candidateStance.getPosition() == Stance::Position::SUPPORT) ? 1.0 :
                               (candidateStance.getPosition() == Stance::Position::NEUTRAL) ? 0.0 : -1.0;

    double divisionPosition = (divisionStance.getPosition() == Stance::Position::SUPPORT) ? 1.0 :
                              (divisionStance.getPosition() == Stance::Position::NEUTRAL) ? 0.0 : -1.0;

    // Calculate the dot product
    double dotProduct = candidateStrength * divisionStrength * (candidatePosition * divisionPosition);

    // Calculate magnitudes
    double candidateMagnitude = std::sqrt(candidateStrength * candidateStrength + candidatePosition * candidatePosition);
    double divisionMagnitude = std::sqrt(divisionStrength * divisionStrength + divisionPosition * divisionPosition);

    return (candidateMagnitude && divisionMagnitude) ? (dotProduct / (candidateMagnitude * divisionMagnitude)) : 0.0;
}

double ElectoralDivision::calculateStanceAndPopulationFactor(Candidate& candidate) {
    double totalCosineSimilarity = 0.0;

    // Iterate through each stance of teh candidate
    for (int index=0; index < stances.size(); ++index) {
        totalCosineSimilarity += calculateCosineSimilarity(candidate.getStances()[index],
                                                           getStances()[index]);
    }
    double averageCosineSimilarity = totalCosineSimilarity / static_cast<double>(stances.size());
    double populationFactor = (population * 1.0); // Population can be between 0.5 to 1.5 million

    return averageCosineSimilarity * populationFactor;
}




Election::Election(const std::array<PoliticalParty, 3>& partyList, std::vector<ElectoralDivision> divisions) : parties(partyList), divisions(std::move(divisions)) {}

void Election::runSimulation(int campaignDays) {
    std::cout << "Starting Simulation..." << std::endl;
    for (const ElectoralDivision& division: divisions) {
        division.printReport();
    }

    for (int day=0; day < campaignDays; day++) {
        for (EventDay &eventDay: eventDays) {
            eventDay.triggerEvents(divisions);
        }
    }

    std::cout << "Election Day: Results" << std::endl;
}

void Election::computeResults() {
    std::cout << "\n=== Election Results ===" << std::endl;
    std::vector<float> divisionsWon(parties.size(), 0.0f);  // Track divisions won by each party
    std::unordered_map<int, std::vector<Candidate>> partyCandidates;

    // Process each division to determine the winner
    for (ElectoralDivision& division : divisions) {
        Candidate winner = division.calculateWinner();  // Assuming this returns the winning candidate
        int winningPartyIndex = winner.getPartyIndex();

        // Check if the winningPartyIndex is valid
        if (winningPartyIndex >= 0 && winningPartyIndex < parties.size()) {
            // Accumulate scores for the winning party
            divisionsWon[winningPartyIndex]++;
            // Store the winning candidate under the respective party
            partyCandidates[winningPartyIndex].push_back(winner);
        } else {
            std::cerr << "Error: Invalid party index for candidate " << winner.getName() << std::endl;
        }
    }

    // Determine the maximum number of divisions won
    float maxDivisionsWon = *std::max_element(divisionsWon.begin(), divisionsWon.end());
    int partiesWithMaxDivisions = static_cast<int>(std::count(divisionsWon.begin(), divisionsWon.end(), maxDivisionsWon));

    // Check for a hung parliament
    if (partiesWithMaxDivisions > 1) {
        std::cout << "Hung Parliament: No single party won the majority of divisions." << std::endl;
        return;
    }

    // Find the winning party (the one with the most divisions won)
    int winningPartyIndex = static_cast<int>(std::distance(divisionsWon.begin(),
                                                           std::max_element(divisionsWon.begin(), divisionsWon.end())));

    // Print party-wise results
    std::cout << "\n--- Party-wise Results ---\n";
    for (size_t index = 0; index < parties.size(); ++index) {
        std::cout << "Party: " << parties[index].getName() << ", Divisions Won: " << divisionsWon[index] << std::endl;

        // Print each candidate for the party
        if (partyCandidates.find(index) != partyCandidates.end() && !partyCandidates[index].empty()) {
            std::cout << "Candidates:\n";
            for (const Candidate& candidate : partyCandidates[index]) {
                std::cout << "\t- Candidate: " << candidate.getName()
                          << ", Popularity: " << candidate.getPopularity() << "%" << std::endl;
            }
        } else {
            std::cout << "\tNo candidates available for this party." << std::endl;
        }
    }

    // Print the winning party and the leader
    std::cout << "\n--- Election Outcome ---\n";
    std::cout << "Winning party: " << parties[winningPartyIndex].getName() << std::endl;
    std::cout << "New Leader: " << partyCandidates[winningPartyIndex][0].getName() << std::endl;
}
