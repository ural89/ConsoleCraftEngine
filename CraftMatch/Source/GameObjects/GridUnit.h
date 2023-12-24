#include <iostream>
#include "Core/GameObject.h"
class GridUnit : public GameObject
{
public:
    GridUnit(Scene& scene) :GameObject("GridObject", scene) {}
    void Init() override;

    void OnCreatingLine();
    void OnSelected();
    void OnUnselected();
};
