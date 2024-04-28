#pragma once
#include "../../../GameObject.h"
#include "../../../../Core.h"
class GE_API Cursor : public GameObject
{
public:
    Cursor(class Scene &scene);
    ~Cursor(){}

    void Init() override;
private:

};