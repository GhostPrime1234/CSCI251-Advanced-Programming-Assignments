#include <iostream>
#include <vector>
#include <cstdlib> // For randomization
#include <ctime>   // For std::time
#include "People.h"
#include "PoliticalParty.h"
#include "ElectoralEntities.h"
#include "Stance.h"

inline std::string generateRandomName() {
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

class ElectoralDivision;
class Stance;
int main(int argc, char* argv[]) {
    // Ensure correct usage
    if (argc != 3) {
        std::cerr << "Usage: ./APE <number_of_divisions> <number_of_campaign_days>" << std::endl;
        return 1;
    }

    // Initialise numDivisions and numCampaignDays in global scope
    int numDivisions = 0;
    int numCampaignDays = 0;
    try {
        // Parse command-line arguments
        numDivisions = std::atoi(argv[1]);
        numCampaignDays = std::atoi(argv[2]);

        // Validate inputs
        if (numDivisions < 1 || numDivisions > 10) {
            std::cerr << "Error: Number of divisions should be between 1 to 10" << std::endl;
            return 1;
        }
        if (numCampaignDays < 1 || numCampaignDays > 30) {
            std::cerr << "Error: Number of campaign days should be between 1 to 30." << std::endl;
            return 1;
        }
    } catch (const std::invalid_argument& error) {
        std::cout << "Error: Invalid argument. Please enter integer values for both divisions and campaign days." << std::endl;
    } catch (const std::out_of_range& error) {
        std::cerr << "Error Input value out of range." << std::endl;
        return 1;
    }


    // Initialise the political parties
    Leader progressiveLeader("Jacob Harris", 0.78);
    Leader unityLeader("Olivia Clarke", 0.72);
    Leader allianceLeader("Liam Murphy", 0.66);

    std::array<PoliticalParty, 3> parties = {
            PoliticalParty("Verdelorian Progressives", progressiveLeader, 0.75),
            PoliticalParty("National Unity Party", unityLeader, 0.65),
            PoliticalParty("People's Alliance", allianceLeader, 0.70)
    };

    // Create the five stances for the electoral divisions
    std::array<const char*, 5> issues = {"Global Warming", "Healthcare Reform", "Education Access", "Infrastructure Development", "Rights of Pets"};

    // Create issues with significance values (0.5 - 1.0)
    std::array<Issue, 5> issueObjects = {
            Issue(issues[0], 0.9),
            Issue(issues[1], 0.8),
            Issue(issues[2], 0.8),
            Issue(issues[3], 0.7),
            Issue(issues[4], 0.6)
    };

    // Create default stances based on these issues
    std::array<Stance, 5> defaultStances = {
            Stance(issueObjects[0], 0.7, Stance::SUPPORT),
            Stance(issueObjects[1], 0.5, Stance::OPPOSE),
            Stance(issueObjects[2], 0.6, Stance::NEUTRAL),
            Stance(issueObjects[3], 0.8, Stance::SUPPORT),
            Stance(issueObjects[4], 0.4, Stance::OPPOSE)
    };

    // Initialise electoral divisions with random popularity and default stances
    std::vector<ElectoralDivision> divisions;

    // Create a random number generator
    std::random_device rd; // Seed
    std::mt19937 gen(rd());  // Mersenne Twister generator;
    std::uniform_real_distribution<> dist(5.0, 10.0);  // Define a uniform distribution between 5.0 and 10.0
    for (int index = 0; index < numDivisions; ++index) {
        double population = dist(gen); // Population between 5.0 and 10.0 million
        divisions.emplace_back(population, defaultStances, issueObjects);
    }

    // Create candidates and add them to parties and divisions
    for (int partyIndex = 0; partyIndex < parties.size(); ++partyIndex) {
        PoliticalParty& party = parties[partyIndex];
        Leader& leader = party.getLeader();
        std::uniform_real_distribution<> popDist(0.0, 100.0);
        double popularity = popDist(gen);

        // Random stance generator for SUPPORT, OPPOSE, NEUTRAL
        std::uniform_int_distribution<> stanceTypeDist(0, 2);
        std::uniform_real_distribution<> supportLevelDist(0.0, 1.0);

        for (int i = 0; i < numDivisions; ++i) { // Assuming each party has a certain number of candidates
            // Generate a candidate with a random name, popularity, leader, party index, and stances
            std::array<Stance, 5> candidateStances;
            for (size_t stanceIndex = 0; stanceIndex < candidateStances.size(); ++stanceIndex) {
                double supportLevel = supportLevelDist(gen); // Random support level
                Stance::Position position = static_cast<Stance::Position>(stanceTypeDist(gen));
                candidateStances[stanceIndex] = Stance(issueObjects[stanceIndex], supportLevel, position);
            }

            // Create a unique candidate with a unique popularity
            Candidate candidate(generateRandomName(), popularity, leader, partyIndex, candidateStances);

            // Add candidate to party
            party.addCandidate(candidate); // This should store the candidate correctly in the party

            // Debug output
            std::cout << "Created Candidate: " << candidate.getName()
                      << ", Party: " << party.getName() << ", Party Index: " << partyIndex << std::endl;

            // Randomly assign candidate to divisions
            for (ElectoralDivision& division : divisions) {
                division.addCandidate(candidate); // Add candidate to division
            }

            // Print candidate details and stances
            candidate.printStances();
        }
    }

    // Before campaign starts, output party and nation report
    std::cout << "=== Initial Party Report ===" << std::endl;
    for (const PoliticalParty& party : parties) {
        party.printReport();  // Output party details
    }

    std::cout << "=== Initial Nation Report ===" << std::endl;
    for (const ElectoralDivision& division : divisions) {
        division.printReport();  // Output division details
    }

    // Simulate campaign event days
    for (int day = 1; day <= numCampaignDays; ++day) {
        std::cout << "=== Campaign Day " << day << " ===" << std::endl;
        for (ElectoralDivision& division : divisions) {
            division.simulateEventDay(parties);  // Each division runs its event day logic
        }

        // Output daily reports
        std::cout << "=== Party Report after Day " << day << " ===" << std::endl;
        for (const PoliticalParty& party : parties) {
            party.printReport();
        }

        std::cout << "=== Nation Report after Day " << day << " ===" << std::endl;
        for (const ElectoralDivision& division : divisions) {
            division.printReport();
        }
    }

    // Election day process
    std::cout << "=== Election Day ===" << std::endl;

    Election election(parties, divisions);  // Election object handles scoring and determining the winner
    election.runSimulation(numDivisions);
    election.computeResults();  // Output national summary and winner announcement

    return 0;
}
