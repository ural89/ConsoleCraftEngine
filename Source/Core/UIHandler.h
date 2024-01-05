#pragma once
#include <string>
#include <vector>
#include "../Core.h"
#include "../CoreStructs/Vector.h"
#include <memory>
#include <algorithm>
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

		uiDatas.clear();
	}
	std::vector<std::shared_ptr<UIData>> uiDatas;
	static std::string uiText;
	static Vector2 Position;

	void AddString(std::shared_ptr<UIData> uiData)
	{
		uiDatas.push_back(uiData);
	}
	void RemoveString(std::shared_ptr<UIData> uiData)
	{
		auto it = std::find(uiDatas.begin(), uiDatas.end(), uiData);
		if (it != uiDatas.end())
		{
			uiDatas.erase(it);
		}
	}
};
