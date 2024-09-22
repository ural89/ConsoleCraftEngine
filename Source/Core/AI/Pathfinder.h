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
    std::vector<PathNode> FindPath(const std::vector<std::vector<int>> &graph, const PathNode &start, const PathNode &goal);
};
