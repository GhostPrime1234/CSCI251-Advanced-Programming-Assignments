# Certificate Management system
## Table of Contents
- [Features](#features)
- [File Structure](#file-structure)
- [Usage](#usage)
- [Classes](#classes)
- [Functions](#functions)
- [Compilation](#compilation)
## Features
+ Generates a specified number of random hexadecimal certificates.
+ Displays all generated certificates.
+ Computes and displays the minimum similarity between certificates
+ Analyses and displays the frequency of hexadecimal digits used in the certificates.
## File Structure

+ header.cpp
+ header.h
+ main.cpp

## Descriptions
+ **main.cpp:** The entry point of the application, handling user input and managing the creation and display of certificates.
+ **header.cpp:** Implementation of the `Certificate` class, including their methods and functionality.
+ **header.h:** Header file defining the `Certificate` and `DocumentHandler` classes, their methods, and necessary includes. It also implements the `DocumentHandler` class.
## Usage
+ To compile and run the program, follow these steps
1. Compile the program using a C++ compiler (C++17 standard):
```bash
g++ main.cpp header.cpp -o main -std=c++17
```
2. Run the program with the required arguments:
```bash
./main <num> <len>
```
+ `<num>`: Number of certificates to generate.
+ `<len>`: Length of each certificate (in terms of hexadecimal pairs).
**Example:**
```bash
./main 5 4
```
This command generates 5 certificates, each consisting of 4 pairs of hexadecimal digits.
## Classes
### `Certificate`
+ **Methods**:
    + **Constructor**: Initialses a certificate of a specified length with random hexadecimal content.
        + **Parameters**:
            + `int len`: The length of the certificate in terms of hexadecimal pairs.
            + `const std::string& match_char`: A character used for matching the first character of the previous certificate (if applicable).
    + **Destructor**: Outputs a message when the certificate is destroyed.
    + **Methods**:
        + `void display() const`: Displays the content of the certificate.
        + `int similarity(const Certificate&) const`: Computes the similarity score between two certificates.
            + **Parameters**:
                + `const Certificate& other**: The other certificate to compare against.
            + **Returns**: An integer representing the similarity score, with lower values indicating higher similarity.
        + `std::vector<std::string> getWords() const`: extracts words from the certificate's content.
            + **Returns**: A vector of strings, each representing a word in the certificate.
### `DocumentHandler<T>`
+ **Methods**:
    + **Constructor:** Initialises a new instance of the `Documenthandler`, setting up the random number generator and the distribution for random digit generation.
    + `std::shared_ptr<T> getDocument(int index)`: Retrieves a document from the colleciton by its index
        + **Parameters**:
            + `int index`: The index of the document to retrieve. It should be a non-negative integer within the range of the existing documents.
        + **Returns**: A shared pointer to the requested document if the index is valid; otherwise, returns `nullptr`.
    + `void addDocument(std::shared_ptr<T> doc)`: Adds a document (certificate) to the collection.
        + **Parameters**:
            `std::shared_ptr<T> doc`: A shared pointer to the document (certificate) to be added.
    + `void display() const`: Displays all documents in the collection.
    + `int minSimilarity() const`: Computes the minimum similarity score between all pairs of documents in the collection.
        + **Returns**: An integer representing the minimum similarity score found; returns `-1` if there are not enough documents to compare.
    + `void digitStatistics() const`: Analyses and displays the frequency of hexadecimal digits used across all documents.

## Functions

### Main Functions
+ **`int main(int argc, char* argv[])`**: Handles command-line arguments, creates certificates, displays them and calls analysis functions.

## Compilation
Ensure you have a C++ compiler that support C++17 or later. Use the following command to compile the code:
```bash
g++ main.cpp header.cpp -o main -std=c++17
```

