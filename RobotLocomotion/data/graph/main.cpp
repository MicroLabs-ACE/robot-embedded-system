// main.cpp
#include "Graph.hpp"
#include <iostream>

int main() {
    MapGraph graph(3, 3);

    // Print the distance between some nodes
    std::cout << "Distance between 0-0 and 1-0: " << graph.getDistance("0-0", "1-0") << std::endl;
    std::cout << "Distance between 0-0 and 0-1: " << graph.getDistance("0-0", "0-1") << std::endl;

    // Print the direction between some nodes
    std::cout << "Direction from 0-0 to 1-0: " << graph.getDirection("0-0", "1-0") << std::endl;
    std::cout << "Direction from 0-0 to 0-1: " << graph.getDirection("0-0", "0-1") << std::endl;

    return 0;
}
