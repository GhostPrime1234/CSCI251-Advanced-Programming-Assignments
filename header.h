#ifndef ASSIGNMENT1_HEADER_H
#define ASSIGNMENT1_HEADER_H

#include <string>

struct Worker;
struct Task;

struct Task {
    int m_taskId;
    std::string m_description;
    int m_uncertainty;
    int m_difficulty;
    int m_priorityLabel;
    int m_workers[20];
    int m_numWorker;

    static void readTasks(const char* filename, Task tasks[], int &numTasks);
    static void assignTasks(const Task tasks[], int numTasks, const Worker workers[], int numWorkers, const char* outputFileName);
};

struct Worker {
    int workerId;
    std::string name;
    int variability;
    int ability;
    int experienceLabel;

    static void readWorkers(const char* filename, Worker workers[], int &numWorkers);
    void writeWorkerInfo(std::ofstream &outputFile) const;
    static int calculatePerformance(const Worker& worker, const Task& task);
};

#endif //ASSIGNMENT1_HEADER_H
