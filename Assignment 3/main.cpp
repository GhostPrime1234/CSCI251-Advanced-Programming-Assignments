#include "header.h"
#include <iostream>
#include <ctime>
#include <memory> // For std::make_shared

using std::make_shared;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./main num len\n";
        return 1;
    }

    int num = std::atoi(argv[1]);
    int len = std::atoi(argv[2]);

    DocumentHandler<Certificate> handler;

    std::string match_char; // Variable to store a character for matching

    // Generate certificates and add them to the handler
    for (int index = 0; index < num; ++index) {
        // Create a new certificate and directly use make_shared, passing the match character
        std::shared_ptr<Certificate> cert = make_shared<Certificate>(len);
        handler.addDocument(cert);
      }

    // Display all certificates
    handler.display();

    // Call the minSimilarity and digitStatistics functions
    handler.minSimilarity();
    handler.digitStatistics();

    return 0;
}