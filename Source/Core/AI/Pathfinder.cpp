#include "Pathfinder.h"
#include "../Scene.h"
#include "../GameObject.h"
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

Pathfinder::Pathfinder(const Scene &scene) : m_Scene(scene),
                                             m_Map(50, std::vector<int>(50, 0))
{
    int size = scene.GetGameObjects().size();
    std::cout << size << '\n';
}

std::vector<PathNode> Pathfinder::FindPath(const PathNode &start, const PathNode &goal)
{
    // auto gameObjects = m_Scene.GetGameObjects();
    // for (auto &gameObject : gameObjects)
    // {
    //     const Vector2 pos = gameObject->transform.Position;

    //     if (pos.X >= 0 && pos.X < map.size() && pos.Y >= 0 && pos.Y < map[0].size())
    //     {
    //         map[pos.X][pos.Y] = 1;
    //     }
    // }

    const int directionX[] = {-1, 0, 1, 0};
    const int directionY[] = {0, 1, 0, -1};

    std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode>> openList;
    std::vector<std::vector<bool>> closedList(m_Map.size(), std::vector<bool>(m_Map[0].size(), false));

    std::vector<std::vector<PathNode>> parent(m_Map.size(), std::vector<PathNode>(m_Map[0].size(), PathNode(-1, -1)));

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
            for (int j = 0; j < 4; ++j)
            {
                int newX = current.x + directionX[i];
                int newY = current.y + directionY[j];

                if (newX >= 0 && newX < m_Map.size() && newY >= 0 && newY < m_Map[0].size())
                {
                    if (m_Map[newX][newY] == 0 && !closedList[newX][newY])
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
