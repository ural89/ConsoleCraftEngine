#include "Pathfinding.h"
#include "../Scene.h"
#include <algorithm>
Pathfinding::Pathfinding(Scene &scene) : m_Scene(scene)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            PathNode _node;
            auto pos = Vector2(i, j);
            _node.Position = pos;
            m_Grid[pos] = _node;
        }
    }
    std::vector<Vector2> directions = {Vector2(0, 1), Vector2(-1, 0), Vector2(0, -1), Vector2(1, 0),
                                       Vector2(1, 1), Vector2(1, -1), Vector2(-1, -1), Vector2(-1, 1)};
    for (auto& keyValue : m_Grid)
    {
        for (auto &direction : directions)
            if (m_Grid.count(keyValue.first + direction))
            {
                keyValue.second.Neighbours.push_back(m_Grid[keyValue.first + direction]);
            }
    }
}

// f(n) = g(n) + h(n) //f total, g travalled, h to travel
// first look f cost, if equal then h cost
// one grid costs 1 and diagonal costs 1.4

std::vector<PathNode> Pathfinding::GetPath(PathNode startNode, PathNode targetNode)
{
    std::vector<PathNode> toSearchNodes = std::vector<PathNode>{startNode};
    std::vector<PathNode> processedNodes;
    while (!toSearchNodes.empty())
    {
        auto &currentNode = toSearchNodes[0];
        for (auto &toSearchNode : toSearchNodes)
        {
            if (toSearchNode.GetF() <= currentNode.GetF() && toSearchNode.H < currentNode.H)
            {
                currentNode = toSearchNode;
            }
        }
        processedNodes.push_back(currentNode);
        toSearchNodes.erase(std::remove(toSearchNodes.begin(), toSearchNodes.end(), currentNode), toSearchNodes.end());

        if (currentNode == targetNode)
        {
            auto currentPathTile = targetNode;
            std::vector<PathNode> path;
            int count = 100;
            while (currentPathTile != startNode)
            {
                path.push_back(currentPathTile);
                currentPathTile = *currentPathTile.Connection;
                count--;
                if (count < 0)
                    std::cerr << "Error pathfinding\n";
            }

            return path;
        }
        for (auto &neighbour : currentNode.Neighbours)
        {
            if (!std::count(processedNodes.begin(), processedNodes.end(), neighbour))
            {
                bool isInSearch = std::count(toSearchNodes.begin(), toSearchNodes.end(), neighbour);
                float costToNeighbour = currentNode.G + Vector2::Distance(neighbour.Position, currentNode.Position);

                if (isInSearch || costToNeighbour < neighbour.G) // TODO: also is walkable
                {
                    neighbour.G = costToNeighbour;
                    neighbour.Connection = &currentNode;

                    if (isInSearch)
                    {
                        neighbour.H = Vector2::Distance(neighbour.Position, targetNode.Position);
                        toSearchNodes.push_back(neighbour);
                    }
                }
            }
        }
    }
    return processedNodes; // TODO: fix
}
