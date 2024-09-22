#pragma once

#include <vector>
#include <map>
#include "../../CoreStructs/Vector.h"
struct PathNode //TODO: constructor with position
{
public:
    PathNode *Connection;
    float G;
    float H;
    float GetF() const
    {
        return G + H;
    }

    std::vector<PathNode> Neighbours;
    Vector2 Position;
    bool operator==(const PathNode& other)
    {
        return other.Position == Position;
    }
    
    bool operator!=(const PathNode& other)
    {
        return other.Position != Position;
    }
};

class Pathfinding
{

public:
    Pathfinding(class Scene &scene);
    std::vector<PathNode> GetPath(PathNode startNode, PathNode targetNode);

private:
    Scene &m_Scene;
    std::map<Vector2, PathNode> m_Grid;
};