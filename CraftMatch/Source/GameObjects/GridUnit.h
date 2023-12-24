#include <iostream>
#include "Core/GameObject.h"
class GridUnit : public GameObject
{
public:
    void Init() override;
    GridUnit(Scene& scene) :GameObject("GridObject", scene) {}

            
  
    
};
