#include <iostream>
#include "header.h"

using std::cout, std::cerr, std::endl;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Please output the Tasks, Workers and the Output files. " << endl;
        exit(1);
    }
    const int MAX_WORKERS = 11;
    Worker workers[MAX_WORKERS];
    int numWorkers = 0;

    const int MAX_TASKS = 10;
    Task tasks[MAX_TASKS];
    int numTasks = 0;

    Worker::readWorkers(argv[2], workers, numWorkers);

    // Read tasks from teh file
    Task::readTasks(argv[1], tasks, numTasks);

    Task::assignTasks(tasks, numTasks, workers, numWorkers, argv[3]);

    return 0;
}
