//
// Created by Michael on 15/08/2024.
//
#include "header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <ctime>
#include <iomanip>

using std::cout, std::cin, std::cerr, std::endl, std::string;
using std::ifstream, std::ofstream;

// Function to read tasks from a file
void Task::readTasks(const char *filename, Task *tasks, int &numTasks) {
    ifstream inFile(filename); // Open the file

    // Check if the file was opened successfully
    if (!inFile) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    // Initialise task count
    numTasks = 0;
    string line;
    string part;

    // Read the file line by line
    while (std::getline(inFile, line)) {
        // Check if the maximum number of tasks is reached
        if (numTasks >= 20) {
            cerr << "Error: Maximum number of Tasks reached (20)." << endl;
            break;
        }
        Task &task = tasks[numTasks];

        // Create a stringstream to parse the line
        std::stringstream ss(line);

        // Extract and validate taskId
        if (std::getline(ss, part, ',')) {
            try {
                task.m_taskId = std::stoi(part);
            } catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid taskId in line: " << line << " (part: " << part << ")" << endl;
                continue;
            }
        } else {
            cerr << "Error: Invalid taskId in line: " << line << endl;
            continue;
        }

        // Extract description
        if (std::getline(ss, part, ';')) {
            task.m_description = part;
        } else {
            cerr << "Error: Invalid description in line: " << line << endl;
            continue;
        }

        // Extract and validate uncertainty
        if (std::getline(ss, part, '$')) {
            try {
                task.m_uncertainty = std::stoi(part);
            } catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid uncertainty in line: " << line << " (part: " << part << ")" << endl;
                continue;
            }
        } else {
            cerr << "Error: Invalid uncertainty in line: " << line << endl;
            continue;
        }

        // Extract and validate difficulty
        if (std::getline(ss, part, '%')) {
            try {
                task.m_difficulty = std::stoi(part);
            } catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid difficulty in line: " << line << " (part: " << part << ")" << endl;
                continue;
            }
        } else {
            cerr << "Error: Invalid difficulty in line: " << line << endl;
            continue;
        }

        // Extract and validate priorityLabel
        if (std::getline(ss, part, '&')) {
            try {
                task.m_priorityLabel = std::stoi(part);
            } catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid priorityLabel in line: " << line << " (part: " << part << ")" << endl;
                continue;
            }
        } else {
            cerr << "Error: Invalid priorityLabel in line: " << line << endl;
            continue;
        }

        // Extract workers associated with the task
        string workersString;
        if (std::getline(ss, workersString)) {
            std::stringstream workersStream(workersString);
            string workerIdStr;

            // Initialise worker count
            task.m_numWorker = 0;
            while (std::getline(workersStream, workerIdStr, ',')) {
                // Check for and remove "Workers:" prefix
                if (workerIdStr.find("workers:") != std::string::npos) {
                    workerIdStr.erase(0, 8); // Remove "workers:" prefix
                }
                try {
                    int workerId = std::stoi(workerIdStr);

                    // Add worker ID to the task if within the limit
                    if (task.m_numWorker < 20) {
                        task.m_workers[task.m_numWorker++] = workerId;
                    } else {
                        cerr << "Error: Too many workers in line: " << line << endl;
                        break;
                    }
                } catch (const std::invalid_argument& e) {
                    cerr << "Error: Invalid worker ID in line: " << line << " (part: " << workerIdStr << ")" << endl;
                }
            }
        } else {
            cerr << "Error: Invalid workers in line: " << line << endl;
            continue;
        }

        numTasks++; // Increment the task count
    }
}

// Function to assign tasks to workers and write the results to output file
void Task::assignTasks(const Task *tasks, int numTasks, const Worker *workers, int numWorkers, const char *outputFileName) {
    std::ofstream outputFile(outputFileName); // Open the output file

    // Check if the output file was opened successfully
    if (!outputFile) {
        cerr << "Error: Could not open output file " << outputFileName << endl;
        return;
    }
    // Write out worker information
    outputFile << std::left << std::setw(15) << "Worker ID"
                << std::setw(13) << "Name"
                << std::setw(15) << "Variability"
                << std::setw(10) << "Ability"
                << std::setw(15) << "Experience Label" << std::endl;


    // Write each worker's information to the output file
    for (int i = 0; i < numWorkers; i++) {
        workers[i].writeWorkerInfo(outputFile);
    }

    // Process each task
    for (int i = 0; i < numTasks; i++) {
        const Task &task = tasks[i];

        outputFile << endl;
        for (int j = 0; j < 35; j++)
            outputFile << "==";

        outputFile << endl;
        bool taskAssigned = false;

        // Write task details
        outputFile << "Processing Task ID: " << task.m_taskId << endl;
        outputFile << "Description\t: " << task.m_description << endl;
        outputFile << "Uncertainty\t: " << task.m_uncertainty << endl;
        outputFile << "Difficulty\t: " << task.m_difficulty << endl;
        outputFile << "Priority\t: " << task.m_priorityLabel << endl;
        outputFile << "Workers\t\t: ";

        for (int j = 0; j < task.m_numWorker; j++) {

            outputFile << task.m_workers[j];
            if (j < task.m_numWorker - 1) outputFile << ", ";
        }
        outputFile << endl;

        // Attempt to assign the task to workers
        for (int j = 0; j < task.m_numWorker; j++) {
            outputFile << "\t---------------------------------------------" << endl;
            int workerId = task.m_workers[j];
            if (workerId >= 0 && workerId < numWorkers) {
                const Worker &worker = workers[workerId];
                outputFile << "\tTrial (" << j + 1 << "/" << task.m_numWorker << "), "
                           << (worker.experienceLabel == 1 ? "Senior worker" : "Ordinary Worker")
                           << " : " << worker.workerId << endl;
                outputFile << "\t---------------------------------------------" << endl;

                double averagePerformance = Worker::calculatePerformance(worker, task);

                outputFile << "\tThe average performance is: " << averagePerformance << endl;

                // Check if the worker's performance is sufficient to complete the task
                if (averagePerformance > 50) {
                    outputFile << "\tAssignment of Task " << task.m_taskId << " to worker " << workerId << " succeeds." << endl;
                    taskAssigned = true;
                    break;
                }
                outputFile << "\tAssignment of Task " << task.m_taskId << " to worker " << workerId << " fails." << endl;
            } else {
                outputFile << "\tInvalid worker ID: " << workerId << endl;
            }
        }

        // If no worker could complete the task
        if (!taskAssigned) {
            outputFile << "\tNo worker was able to complete Task " << task.m_taskId << endl;
        }

    }

    outputFile.close(); // Close the output file
}

// Function to read workers from a file
void Worker::readWorkers(const char *filename, Worker *workers, int &numWorkers) {
    ifstream inFile(filename); // Open the file

    // Check if the file was opened successfully
    if (!inFile) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    numWorkers = 0;// Initialise worker count
    string line; // Initialise space in memory to store the line
    string part; // Initialise space in memory to store the

    // Read the file line by line
    while (std::getline(inFile, line)) {
        // Check if the maximum numbers is reached
        if (numWorkers >= 20) {
            cerr << "Error: Maximum number of workers reached (20)." << endl;
            break;
        }

        Worker &worker = workers[numWorkers];
        std::stringstream ss(line); // Create a stringstream object to parse the line

        // Extract and validate workerId
        if (std::getline(ss, part, ',')) {
            try {
                worker.workerId = std::stoi(part);
            } catch (const std::invalid_argument&) {
                cerr << "Error: Invalid workerId in line: " << line << " (part: " << part << ")" << endl;
                continue;
            }
        } else {
            cerr << "Error: Invalid workerId in line: " << line << endl;
            continue;
        }

        // Extract name
        if (std::getline(ss, part, '%')) {
            worker.name = part;
        } else {
            cerr << "Error: Invalid name in line: " << line << endl;
            continue;
        }

        // Extract and validate variability
        if (std::getline(ss, part, '$')) {
            try {
                worker.variability = std::stoi(part);
            } catch (const std::invalid_argument&) {
                cerr << "Error: Invalid variability in line: " << line << " (part: " << part << ")" << endl;
                continue;
            }
        } else {
            cerr << "Error: Invalid variability in line: " << line << endl;
            continue;
        }

        // Extract and validate ability
        if (std::getline(ss, part, ';')) {
            try {
                worker.ability = std::stoi(part);
            } catch (const std::invalid_argument&) {
                cerr << "Error: Invalid ability in line: " << line << " (part: " << part << ")" << endl;
                continue;
            }
        } else {
            cerr << "Error: Invalid ability in line: " << line << endl;
            continue;
        }

        // Extract and validate experienceLabel
        if (std::getline(ss, part)) {
            try {
                worker.experienceLabel = std::stoi(part);
            } catch (const std::invalid_argument&) {
                cerr << "Error: Invalid experienceLabel in line: " << line << " (part: " << part << ")" << endl;
                continue;
            }
        } else {
            cerr << "Error: Invalid experienceLabel in line: " << line << endl;
            continue;
        }

        numWorkers++; // Increment worker count
    }
}

// Function to calculate performance based on worker and task attributes
int Worker::calculatePerformance(const Worker &worker, const Task &task) {
    const int mean = worker.ability - task.m_difficulty;
    const int stdev = task.m_uncertainty + worker.variability;

    std::random_device rd;
    std::default_random_engine engine(rd()); // randomness engine
    std::normal_distribution<> distribution(mean, stdev); // Normal distribution for performance

    int numTrials = (task.m_priorityLabel == 1) ? 10 : 5;

    double sum = 0;

    for(int index=0; index < numTrials; index++)
    {
        sum += distribution(engine);
    }

    double averagePerformance = sum / numTrials;
    if (worker.experienceLabel == 1) {
        averagePerformance += 6;
    }

    return static_cast<int>(averagePerformance);
}

// Function to write worker information to an output file
void Worker::writeWorkerInfo(std::ofstream &outputFile) const {
    const string experienceStr = (experienceLabel == 1) ? "Senior" : "Ordinary";
    outputFile << std::left << std::setw(15) << workerId
            << std::setw(13) << name
            << std::setw(15) << variability
            << std::setw(10) << ability
            << std::setw(5) << experienceStr << std::endl;
}
