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
	bool isActive = true;
	Vector2 position;
	std::string text;
};
struct UIPanel
{
public:
	void AddString(Vector2 position, std::string text)
	{
		auto uiData = std::make_shared<UIData>();
		uiData->position = position;
		uiData->text = text;
		uiDatas.push_back(uiData);
		lastTexts.push_back(text);
	}
	void ChangeText(int uiDataIndex, std::string text)
	{
		uiDatas[uiDataIndex]->text = text;
		if (lastTexts[uiDataIndex] != text)
			RefreshPanel();
		lastTexts[uiDataIndex] = text;
	}
	void SetActive(bool isActive)
	{
		this->isActive = isActive;
		if (!isActive)
			hasClearedFlag = false;
	}
	void RefreshPanel()
	{
		hasClearedFlag = false;
	}
	bool hasClearedFlag = false;
	bool isActive = true;
	std::vector<std::shared_ptr<UIData>> uiDatas;
	std::vector<std::string> lastTexts;
};
/// <summary>
/// to disable and clear a panel use SetActive(false)
/// </summary>
class GE_API UIHandler
{
private:
public:
	UIHandler()
	{
	}
	~UIHandler()
	{

		uiDatas.clear();
	}
	std::vector<std::shared_ptr<UIData>> uiDatas;
	std::vector<std::shared_ptr<UIPanel>> uiPanels;
	static std::string uiText;
	static Vector2 Position;

	void AddPanel(std::shared_ptr<UIPanel> uiPanel)
	{
		uiPanels.push_back(uiPanel);
	}
	void RemovePanel(std::shared_ptr<UIPanel> uiPanel)
	{
		auto it = std::find(uiPanels.begin(), uiPanels.end(), uiPanel);
		if (it != uiPanels.end())
		{
			uiPanels.erase(it);
		}

#ifdef __GNUC__
		system("clear");
#else
		system("cls");
#endif
	}
	void AddString(std::shared_ptr<UIData> uiData)
	{
		uiDatas.push_back(uiData);
	}
	void RemoveString(std::shared_ptr<UIData> uiData)
	{

		// uiData->text = ""; TODO: make this and flag
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
