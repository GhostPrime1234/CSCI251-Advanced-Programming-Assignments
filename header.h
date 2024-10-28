// header.h
#include <string>
#include <vector>
#include <climits> // For INT_MAX
#include <random>
#include <iostream>
#include <memory>
#include <unordered_set>

using std::cout, std::endl;
using std::string, std::vector, std::pair;
using std::shared_ptr, std::make_shared;

// Certificate class definition
class Certificate {
public:
    Certificate(int);  // Constructor with length of words
    int hexCharToInt(char);
    void display(int) const;  // Display certificate content
    int similarity(const Certificate&) const;  // Similarity function
    vector<string> getWords() const;  // Function to get words as vector
    const string getContent() const;

private:
    shared_ptr<vector<int>> content;  // Private content to store entire document  
};

// Template class definition for DocumentHandler
template <class T>
class DocumentHandler {
private:
    shared_ptr<vector<shared_ptr<T>>> documents;  // Pointer to shared pointers of documents

    // Random number generator and distribution
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

public:
    DocumentHandler();
    void addDocument(shared_ptr<T>);  // Add a document to the collection
    std::shared_ptr<T> getDocument(int index);
    void display() const;  // Display all documents
    int minSimilarity() const;  // Find minimum similarity between documents
    void digitStatistics() const;  // Compute digit frequency statistics
};

// DocumentHandler Constructor initializes the random generator and distribution
template <typename T>
DocumentHandler<T>::DocumentHandler() : gen(std::random_device{}()), dis(0, 9), documents(make_shared<vector<shared_ptr<T>>>()) {}

// Add a document to the document handler
template <typename T>
void DocumentHandler<T>::addDocument(shared_ptr<T> doc) {
    documents->push_back(doc);  // Correct use of push_back
}

// Display the contents of all documents in the document handler
template <typename T>
void DocumentHandler<T>::display() const {
    cout << "Certificates:" << endl;
    cout << "======================" << endl;
    int count = 1;
    for (const shared_ptr<T>& doc : *documents) {
        if (doc) {
            doc->display((count -1));
            count++;
        } else {
            cout << "Document " << count << " is null.\n";
        }
    }
    cout << endl;
   
}

// Corrected getDocument method with nullptr check
template <typename T>
std::shared_ptr<T> DocumentHandler<T>::getDocument(int index) {
    if (index >= 0 && index < documents->size()) {
        return (*documents)[index];  // Dereference shared_ptr to access the vector
    }
    return nullptr;
}

// Update the minSimilarity method to improve clarity
template <typename T>
int DocumentHandler<T>::minSimilarity() const {
    if (documents->size() < 2) {
        cout << "Not enough documents to compare." << endl;
        return -1;
    }

    int min_sim = std::numeric_limits<int>::max();
    int cert1 = -1, cert2 = -1;

    for (size_t i = 0; i < documents->size(); ++i) {
        for (size_t j = i + 1; j < documents->size(); ++j) {
            int sim = (*documents)[i]->similarity(*(*documents)[j]); // Use -> to access methods of shared_ptr
            if (sim < min_sim) {
                min_sim = sim;
                cert1 = i + 1;  // Store 1-based index
                cert2 = j + 1;  // Store 1-based index
            }
        }
    }

    cout << "Min similarity: " << min_sim 
         << ", between certificates " << cert1 << " and " << cert2 << endl << endl;   
    return min_sim;
}

// Digit frequency statistics
template <typename T>
void DocumentHandler<T>::digitStatistics() const {
    // Array to store frequency of hexadecimal digits (0-9 and A-F)
    int digitFrequency[16] = {};

    // Iterate through all documents
    for (const shared_ptr<T>& doc : *documents) {  // Use shared_ptr to access documents
        vector<string> words = doc->getWords();  // Use -> to call member function

        // Count the frequency of each digit in the words
        for (const string& word : words) {
            for (char c : word) {
                int index = (c >= '0' && c <= '9') ? c - '0' : c - 'A' + 10;
                if (index >= 0 && index < 16) { // Ensure index is valid
                    digitFrequency[index]++;
                }
            }
        }
    }

    // Variables to hold the minimum and maximum frequency
    int minFreq = INT_MAX, maxFreq = 0;
    vector<pair<char, int>> minDigits, maxDigits;

    // Traverse the frequency array to determine min and max frequencies
    for (int i = 0; i < 16; ++i) {
        if (digitFrequency[i] < minFreq && digitFrequency[i] > 0) {  // Ignore if frequency is 0
            minFreq = digitFrequency[i];
            minDigits.clear();
            minDigits.push_back({(i < 10) ? '0' + i : 'A' + i - 10, digitFrequency[i]});
        } else if (digitFrequency[i] == minFreq && digitFrequency[i] > 0) {
            minDigits.push_back({(i < 10) ? '0' + i : 'A' + i - 10, digitFrequency[i]});
        }

        if (digitFrequency[i] > maxFreq) {
            maxFreq = digitFrequency[i];
            maxDigits.clear();
            maxDigits.push_back({(i < 10) ? '0' + i : 'A' + i - 10, digitFrequency[i]});
        } else if (digitFrequency[i] == maxFreq) {
            maxDigits.push_back({(i < 10) ? '0' + i : 'A' + i - 10, digitFrequency[i]});
        }
    }

    // Display results
    cout << "Least frequent digits with count:" << endl;
    for (const pair<char, int>& p : minDigits) {
        cout << p.first << ": " << p.second << endl;
    }

    cout << "Most frequent digits with count:" << endl;
    for (const pair<char, int>& p : maxDigits) {
        cout << p.first << ": " << p.second << endl;
    }
}
