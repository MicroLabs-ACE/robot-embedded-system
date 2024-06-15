#include "Graph.hpp"
#include <cmath> // for abs
#include <iostream>
#include <sstream> // for std::stringstream
MapGraph::MapGraph(int length, int width) : length(length), width(width) {
    generateGraph();
}

void MapGraph::generateGraph() {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            std::pair<int, int> directions[] = {
                {0, -1}, {1, -1}, {1, 0}, {1, 1},
                {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}
            };
            std::string directionNames[] = {
                "north", "northEast", "east", "southEast",
                "south", "southWest", "west", "northWest"
            };

            for (int k = 0; k < 8; ++k) {
                int x = i + directions[k].first;
                int y = j + directions[k].second;

                bool horizontalCondition = x >= 0 && x < length;
                bool verticalCondition = y >= 0 && y < width;

                if (horizontalCondition && verticalCondition) {
                    std::stringstream ssSrc, ssDst;
                    ssSrc << i << "-" << j;
                    ssDst << x << "-" << y;

                    std::string src = ssSrc.str();
                    std::string dst = ssDst.str();

                    int weight = 5;
                    if (directionNames[k] == "north" || directionNames[k] == "south")
                        weight = 3;
                    else if (directionNames[k] == "west" || directionNames[k] == "east")
                        weight = 4;

                    addEdge(src, dst, weight);
                }
            }
        }
    }
}

// Check if a node exists
bool MapGraph::doesNodeExist(const std::string& node) const {
    return graph.find(node) != graph.end();
}

// Add an edge between src and dst with a given weight
void MapGraph::addEdge(const std::string& src, const std::string& dst, int weight) {
    if (!doesNodeExist(src)) {
        graph[src] = {{dst, weight}};
    } else {
        graph[src][dst] = weight;
    }

    if (!doesNodeExist(dst)) {
        graph[dst] = {};
    }
}

// Get the distance between src and dst
int MapGraph::getDistance(const std::string& src, const std::string& dst) const {
    if (graph.find(src) != graph.end() && graph.at(src).find(dst) != graph.at(src).end()) {
        return graph.at(src).at(dst);
    }
    return -1; // Return -1 if no path exists
}

// Get the direction from src to dst
int MapGraph::getDirection(const std::string& src, const std::string& dst) const {
    int x0, y0, x1, y1;
    sscanf(src.c_str(), "%d-%d", &x0, &y0);
    sscanf(dst.c_str(), "%d-%d", &x1, &y1);

    int dx = x1 - x0;
    int dy = y1 - y0;

    if (dx == 0 && dy == 1) return 0;
    if (dx == 1 && dy == 1) return 45;
    if (dx == 1 && dy == 0) return 90;
    if (dx == 1 && dy == -1) return 135;
    if (dx == 0 && dy == -1) return 180;
    if (dx == -1 && dy == -1) return 225;
    if (dx == -1 && dy == 0) return 270;
    if (dx == -1 && dy == 1) return 315;

    return -1; // If not a valid direction
}
