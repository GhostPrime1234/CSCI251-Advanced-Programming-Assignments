#include "header.h"
#include <random>
#include <ctime>
#include <iostream>
#include <climits> // For INT_MAX
#include <iomanip>

using std::string, std::vector;
using std::cout, std::endl;

// Constructor for the Certificate class
Certificate::Certificate(int len) {
    content = make_shared<vector<int>>();  // Initialise content
    const char hex_chars[] = "0123456789ABCDEF";  // Hexadecimal characters
    std::random_device rd;  // Non-deterministic random number generator
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 15);

    // Generate additional words
    for (size_t index = 0; index < len; ++index) {
       char first_char = hex_chars[dis(gen)];
       char second_char = hex_chars[dis(gen)];

       // Convert characters to integer equivalents
       int first_int = hexCharToInt(first_char);
       int second_int = hexCharToInt(second_char);

       // Combine teh two chars into a single integer
       int combined_int = first_int * 16 + second_int;

       // Store the combined integer in the content vector
       content->push_back(combined_int);
    }
}

int Certificate::hexCharToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0'; // '0' to '9'
    else if (c >= 'A' && c <= 'F') return c - 'A' + 10; // 'A' to 'F'
    return 0; // Handle error case, though in this case it should always be valid.
}

// Display the content of the certificate
void Certificate::display(int certificateNumber) const {
    cout << "Certificate " << (certificateNumber + 1) << ": " << endl;
        cout << "----------------------" << endl;

    // Print all hexadecimal values in a single line
     for (const int& value : *content) {
        cout << "0x" << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << value << " ";
    }
    cout << std::dec << endl; // Reset to decimal after printing
}


// Similarity function to compare two certificates
int Certificate::similarity(const Certificate& other) const {
    int similar_count = 0;
    vector<string> words1 = getWords();
    vector<string> words2 = other.getWords();

    for (size_t index = 0; index < words1.size(); ++index) {
        for (size_t j = 0; j < words2.size(); ++j) {
            const string& word1 = words1[index];
            const string& word2 = words2[j];
            if (!word1.empty() && !word2.empty() && word1[0] == word2[0]) {
                ++similar_count;  // Increment the counter
                break;  // Move to the next word1 once a match is found
            }
        }
    }
    return similar_count;
}

vector<string> Certificate::getWords() const {
    vector<string> words;

    for (int value : *content) {
        // Convert each integer to a two-digit hexadecimal string
        int first_char = (value >> 4) & 0xF;  // Higher nibble
        int second_char = value & 0xF;        // Lower nibble

        // Convert to hex characters
        char first_hex = (first_char < 10) ? '0' + first_char : 'A' + (first_char - 10);
        char second_hex = (second_char < 10) ? '0' + second_char : 'A' + (second_char - 10);

        // Create a string with the two characters
        string word = { first_hex, second_hex }; // Now using char variables

        words.push_back(word);
    }

    return words;
}



const string Certificate::getContent() const {
    string str;
    
    for (int value : *content) {
        // Extract the two hexadecimal digits from each integer
        char first_char = (value >> 4) & 0xF;  // Get the higher nibble
        char second_char = value & 0xF;        // Get the lower nibble

        // Convert to hex characters
        first_char = (first_char < 10) ? '0' + first_char : 'A' + (first_char - 10);
        second_char = (second_char < 10) ? '0' + second_char : 'A' + (second_char - 10);

        // Append both characters to the string
        str += first_char;
        str += second_char;
    }

    return str;
}

