cmake_minimum_required(VERSION 3.28.1)
project(Assignment2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Assignment2
        src/main.cpp
        src/PoliticalParty.cpp
        src/ElectoralEntities.cpp
        src/Candidate.cpp
        src/EventManagement.cpp
        src/Issue.cpp
        src/Leader.cpp
        src/People.cpp
        src/Stance.cpp
)
