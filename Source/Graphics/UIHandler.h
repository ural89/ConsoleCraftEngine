#pragma once

#include "Math/Vector2.h"

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
		//uiData->text = ""; TODO: make this and flag
		auto it = std::find(uiDatas.begin(), uiDatas.end(), uiData);
		if (it != uiDatas.end())
		{
			uiDatas.erase(it);
		}
		
#ifdef __GNUC__
		system("clear");
#else
		system("cls");
#endif
	}
};
