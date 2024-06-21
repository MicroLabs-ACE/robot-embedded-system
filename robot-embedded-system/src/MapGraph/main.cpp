#include "MapGraph.hpp"
#include <iostream>

void testDistance(MapGraph &graph, const std::string &src, const std::string &dst)
{
    int distance = graph.getDistance(src, dst);
    std::cout << "Distance between " << src << " and " << dst << ": ";
    if (distance != -1)
    {
        std::cout << distance << std::endl;
    }
    else
    {
        std::cout << "No path exists" << std::endl;
    }
}

void testDirection(MapGraph &graph, const std::string &src, const std::string &dst)
{
    int direction = graph.getDirection(src, dst);
    std::cout << "Direction from " << src << " to " << dst << ": ";
    if (direction != -1)
    {
        std::cout << direction << " degrees" << std::endl;
    }
    else
    {
        std::cout << "Invalid direction" << std::endl;
    }
}

void testGraphConstructionAndTraversal()
{
    MapGraph graph(3, 3);

    // Print the generated graph or its part
    std::cout << "Generated Graph:" << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::string node = std::to_string(i) + "-" + std::to_string(j);
            if (graph.doesNodeExist(node))
            {
                std::cout << "Node " << node << " is connected to:";
                // For demonstration purposes, we simulate adjacency here
                std::cout << " (0-0, weight 3) (0-1, weight 4) (0-2, weight 5)"; // Adjust as per your graph structure
                std::cout << std::endl;
            }
        }
    }

    std::cout << std::endl;

    // Test distance between nodes
    testDistance(graph, "0-0", "1-0");
    testDistance(graph, "0-0", "0-1");
    testDistance(graph, "0-0", "2-2");
    testDistance(graph, "2-2", "1-1");

    std::cout << std::endl;

    // Test direction between nodes
    testDirection(graph, "0-0", "1-0");
    testDirection(graph, "0-0", "0-1");
    testDirection(graph, "1-1", "2-2");
    testDirection(graph, "2-2", "0-0");
}

int main()
{
    testGraphConstructionAndTraversal();
    return 0;
}
