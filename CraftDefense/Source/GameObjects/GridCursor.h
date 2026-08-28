#pragma once
#include "Core/GameObject.h"

class GridCursor : public GameObject
{
public:
    GridCursor(class Scene &s);

    void Init() override;
    void MoveTo(int c, int r);
    void Recolor(bool canPlant, bool hasSun);

    int Col() const { return col; }
    int Row() const { return row; }

private:
    int col = 0;
    int row = 0;
};
