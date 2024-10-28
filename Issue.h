//
// Created by Michael on 30/09/2024.
//

#ifndef ASSIGNMENT2_ISSUE_H
#define ASSIGNMENT2_ISSUE_H

#include <string>

class Issue {
private:
    std::string name;
    double significance; // Range (0, 1]
public:
    Issue(std::string name, double significance);
    double getSignificance() const;     // Range (0, 1]
    std::string getName() const;
    void setSignificance(double newSignificance);
};


#endif //ASSIGNMENT2_ISSUE_H
