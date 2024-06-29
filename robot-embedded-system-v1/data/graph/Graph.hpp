#ifndef MAPGRAPH_H
#define MAPGRAPH_H

#include <unordered_map>
#include <string>
#include <utility>

class MapGraph {
public:
    MapGraph(int length, int width);
    void setDimensions(int length, int width);
    bool doesNodeExist(const std::string& node) const;
    void addEdge(const std::string& src, const std::string& dst, int weight);
    int getDistance(const std::string& src, const std::string& dst) const;
    int getDirection(const std::string& src, const std::string& dst) const;

private:
    int length;
    int width;
    void generateGraph();
    std::unordered_map<std::string, std::unordered_map<std::string, int>> graph;
};

#endif
