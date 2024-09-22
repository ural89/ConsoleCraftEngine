#include "Pathfinder.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>

PathNode::PathNode(int _x, int _y)
    : x(_x), y(_y), f(0), g(0), h(0)
{
}

bool PathNode::operator>(const PathNode &other) const
{
    return f > other.f;
}

bool PathNode::operator==(const PathNode &other) const
{
    return x == other.x && y == other.y;
}

std::vector<PathNode> Pathfinder::FindPath(const std::vector<std::vector<int>> &graph, const PathNode &start, const PathNode &goal)
{
    const int directionX[] = {-1, 0, 1, 0};
    const int directionY[] = {0, 1, 0, -1};

    std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode>> openList;
    std::vector<std::vector<bool>> closedList(graph.size(), std::vector<bool>(graph[0].size(), false));

    std::vector<std::vector<PathNode>> parent(graph.size(), std::vector<PathNode>(graph[0].size(), PathNode(-1, -1)));

    PathNode startNode = start;
    startNode.g = 0;
    startNode.h = abs(start.x - goal.x) + abs(start.y - goal.y);
    startNode.f = startNode.g + startNode.h;

    openList.push(startNode);

    while (!openList.empty())
    {
        PathNode current = openList.top();
        openList.pop();

        if (current == goal)
        {
            std::vector<PathNode> path;
            while (!(current == start))
            {
                path.push_back(current);
                current = parent[current.x][current.y];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedList[current.x][current.y] = true;

        for (int i = 0; i < 4; ++i)
        {
            int newX = current.x + directionX[i];
            int newY = current.y + directionY[i];

            if (newX >= 0 && newX < graph.size() && newY >= 0 && newY < graph[0].size())
            {
                if (graph[newX][newY] == 0 && !closedList[newX][newY])
                {
                    PathNode neighbor(newX, newY);
                    int newG = current.g + 1;

                    if (newG < neighbor.g || !closedList[newX][newY])
                    {
                        neighbor.g = newG;
                        neighbor.h = abs(newX - goal.x) + abs(newY - goal.y);
                        neighbor.f = neighbor.g + neighbor.h;
                        parent[newX][newY] = current;

                        openList.push(neighbor);
                    }
                }
            }
        }
    }

    return std::vector<PathNode>();
}
