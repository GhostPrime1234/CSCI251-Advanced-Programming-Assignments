//
// Created by Michael on 30/09/2024.
//

#include "Issue.h"
double Issue::getSignificance() const {
    return significance;
}

Issue::Issue(std::string name, double significance) : name(std::move(name)), significance(significance){}

std::string Issue::getName() const {
    return name;
}