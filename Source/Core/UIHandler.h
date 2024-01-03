#pragma once
#include <string>
#include <vector>
#include "../Core.h"
#include "../CoreStructs/Vector.h"

struct UIData
{
public:
	Vector2 position;
	std::string text;
};

class GE_API UIHandler
{
private:
public:
	~UIHandler()
	{
		for (UIData* uiData : uiDatas)
        {
            delete uiData;
        }

        
        uiDatas.clear();
	}
	std::vector<UIData*> uiDatas;
	static std::string uiText;
	static Vector2 Position;

	void AddString(UIData* uiData)
	{
		uiDatas.push_back(uiData);
	}
};
