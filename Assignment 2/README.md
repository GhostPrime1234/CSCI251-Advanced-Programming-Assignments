## Description
The project simulates an election process where multiple political parties, electoral divisions, and candidates compete. The simulation involves issues with varying stances, and each candidate's popularity is influence by their stance on key issues.

## Class Overview
1.  `Candidate`
+ Represents a political candidate in the election 
+ Each candidate has a name, popularity and a stance on several issues.
+ Methods:
  + `getPopularity()`, `getName()`, `getPartyIndex()` to retrieve candidate details.
  + `updatePopularity(double change)` adjusts candidates popularity based on events.
2. `ElectoralDivision`
 + Represents an electoral division with a specific population.
 + Contains a list of stances on issues and candidates.
 + Methods:
   + `calculateWinner()`: Determines the winning candidate of the division based on popularity.
   + `simulateEventDay()`: Simulates campaign days when candidates gain or lose popularity
   + `getCandidate()`, `getLeader()`, `getStances()` retrieves division's internal data
3. `PoliticalParty`:
+ Represents a political party with a leader and party-wide popularity.
+ Methods:
  + `getPopularity()`, `getName()`: Returns the popularity and name of the party.     
4. `Stance`:
+ Represents a candidate's position on a specific issue.
+ Methods:
  + `getIssue()`, `getPosition()`, `getStrength()`: Retrieves stance details.
  + `setStrength(double strength)`: Modifies the strength of a stance
5. `Issue`:
+ Represents a national issue that candidates take stances on.
+ Methods:
  + `getName()`: Returns the name of the issue.
6. `Leader`:
+ Represents a party leader.
+ Contains methods to set or get the leader's details
7. `Election`:
+ Handles the entire election process, including campaign days and final results.
+ Methods:
  + `runSimulation(int campaignDays)`: Runs the election simulation for a specified number of campaign days.
  + `computeResults()`: Computes the election results based on the popularity of candidates and their parties.
  + `addParty(PoliticalParty party)`: Adds a party to the election process.
8. `EventDay`:
+ Represents events that occur on campaign days, affecting candidate popularity

## Project Structure
The project consists of teh following source files:
- Candidate.cpp
- ElectoralEntities.cpp
- EventManagement.cpp
- Issue.cpp
- Leader.cpp
- main.cpp
- People.cpp
- PoliticalParty.cpp
- Stance.cpp


## How to Run the Program
1. Ensure that the following files are in the same directory. 
   - Candidate.cpp
   - ElectoralEntities.cpp
   - EventManagement.cpp
   - Issue.cpp
   - Leader.cpp
   - main.cpp
   - People.cpp
   - PoliticalParty.cpp
   - Stance.cpp
2. **Compile the Program**
+ Open a terminal in the project directory and run the following commands to compile the program:
```bash
g++ -c main.cpp -std=c++17
g++ -c Candidate.cpp -std=c++17
g++ -c ElectoralEntities.cpp -std=c++17
g++ -c EventManagement.cpp -std=c++17
g++ -c Issue.cpp -std=c++17
g++ -c Leader.cpp -std=c++17
g++ -c People.cpp -std=c++17
g++ -c PoliticalParty.cpp -std=c++17
g++ -c Stance.cpp -std=c++17
```
3. **Link the Object Files**:
+ After compiling the individual files, link them together with the following command:
```bash
g++ main.o Candidate.o ElectoralEntities.o EventManagement.o Issue.o Leader.o People.o PoliticalParty.o Stance.o -o APE -std=c++17
```
4. **Run the Program**:
Once the code is compiled successfully, you can run the program from the terminal as follows:
```bash
./APE n m
```
Where:
+ `n` is the number of electoral divisions in the nation. It must be an integer in the range of **1 to 10** (inclusive).
+ `m` is the number of campaign days before the election. It must be an integer in teh range of **1 to 30** (inclusive).