//
// Created by Michael on 30/09/2024.
//

#ifndef ASSIGNMENT2_PEOPLE_H
#define ASSIGNMENT2_PEOPLE_H

#include <string>
#include <vector>
#include <array>

#include "Stance.h"

class ElectoralDivision;

class People {
protected:
    double popularity; // Range (0, 1]
public:
    People(double popularity);
};




#endif //ASSIGNMENT2_PEOPLE_H
