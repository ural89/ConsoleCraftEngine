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
    for (auto &row : m_Map) // reset map 
    {
        std::fill(row.begin(), row.end(), 0);
    }

    auto gameObjects = m_Scene.GetGameObjects();
    for (auto &gameObject : gameObjects)
    {
        if (gameObject->isNavIgnore)
        {
            continue;
        }
        const Vector2 pos = gameObject->transform.Position;
        int height = gameObject->GetHeight();
        int width = gameObject->GetWidth();
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                int mapX = pos.X + j;
                int mapY = pos.Y + i;

                if (mapX >= 0 && mapX < m_Map.size() && mapY >= 0 && mapY < m_Map[0].size())
                {
                    m_Map[mapX][mapY] = 1; 
                }
            }
        }
    }
    if(m_Map[goal.x][goal.y])
    {
        return std::vector<PathNode>();
    }

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
