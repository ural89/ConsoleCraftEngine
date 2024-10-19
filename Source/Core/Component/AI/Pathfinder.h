#pragma once

#include <vector>
#include <queue>
#include <cmath>

struct PathNode
{
    int x, y;
    int f, g, h;

    PathNode(int r, int c);

    bool operator>(const PathNode &other) const;
    bool operator==(const PathNode &other) const;
};
class Pathfinder
{
public:
    ~Pathfinder()
    {
        m_Map.clear();
    }
    Pathfinder(const class Scene &scene);
    std::vector<PathNode> FindPath(const PathNode &start, const PathNode &goal);

private:
    const Scene &m_Scene;
    std::vector<std::vector<int>> m_Map;
    int m_FinderGameObjectWidth = 4;
    int m_FinderGameObjectHeight = 4;

};
