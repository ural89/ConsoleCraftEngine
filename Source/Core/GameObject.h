#pragma once
#include "../Core.h"
#include "../CoreStructs/Transform.h"
#include "Component/Component.h"
#include <vector>
#define MAX_SPRITE_DIM 8
#define MAX_SPRITE_SIZE (MAX_SPRITE_DIM * MAX_SPRITE_DIM)
class GE_API GameObject
{

  public:
	GameObject(std::string &&name, class Scene &scene) : name(name), scene(scene)
	{
    
	};
	void SetSprite(const std::vector<std::vector<int>> &spriteData)
	{
		if (spriteData.empty())
			return;

		int inputHeight = spriteData.size();
		int inputWidth = 0;
		for (const auto &row : spriteData)
			if (row.size() > inputWidth)
				inputWidth = row.size();

		if (inputWidth > MAX_SPRITE_DIM || inputHeight > MAX_SPRITE_DIM)
		{
			std::cerr << "Error: Sprite is too big for the 8x8 buffer!" << std::endl;
			return;
		}

		this->width = inputWidth;
		this->height = inputHeight;

		for (int y = 0; y < inputHeight; y++)
		{
			for (int x = 0; x < spriteData[y].size(); x++)
			{
				int index = (y * this->width) + x;
				newSprite[index] = spriteData[y][x];
			}
		}
	}
	virtual ~GameObject()
	{
		for (auto &component : components)
		{
			delete component;
		}
		components.clear();
		sprite.clear();
	}

	Transform transform = Transform();

	std::string name = "Gameobject";
	std::vector<std::vector<int>> sprite = {{1, 1}, {1, 1}};
	int newSprite[8 * 8];

	virtual int GetWidth() const
	{
		return width;
	}
	virtual int GetHeight() const
	{
		return height;
	}
	void Destroy()
	{
		isDestroyedFlag = true;
		transform.HasOwnerDestroyed = true;
	}
	void AddComponent(Component *component)
	{
		components.push_back(component);
		component->Init();
	}
	template <typename T>
	T *AddComponent()
	{
		auto component = new T(*this);
		AddComponent(component);
		return component;
	}
	void SetRenderable(bool isRenderable)
	{
		this->isRenderable = isRenderable;
		if (!isRenderable)
		{
			forceClearFromScreen = true;
		}
	}

	template <typename T>
	T *GetComponent()
	{
		for (auto &component : components)
		{

			if (typeid(*component) == typeid(T))
			{
				return dynamic_cast<T *>(component);
			}
		}
		return nullptr;
	}

  public:
	virtual void Init() {};
	virtual void Update(float deltaTime) {};
	virtual void OnCollided(GameObject &other) {};
	virtual void OnCollisionExit(GameObject &other) {};
	virtual void OnCollidedBorder(int border) {};
	void InitComponents()
	{
		for (auto &component : components)
		{
			component->Init();
		}
	}
	void UpdateComponents(float deltaTime)
	{
		for (auto &component : components)
		{
			component->Update(deltaTime);
		}
	}

  public:
	std::string symbol = "*";
	int overrideColor = -1;
	int width;
	int height;

	bool isDestroyedFlag = false;
	bool hasClearedFromScreen = false;
	bool forceClearFromScreen = false;
	bool isRenderable = true;
	bool hasCollider = true;
	bool canFindable = true;
	bool isNavIgnore = false;
	Scene &GetCurrentScene()
	{
		return scene;
	}
	bool operator!=(const GameObject &other) const
	{
		return this != &other;
	}

  protected:
	std::vector<Component *> components;
	Scene &scene;
#ifdef __GNUC__
	int GREEN = 2;
	int RED = 1;
	int YELLOW = 3;
#else
	int GREEN = 2;
	int RED = 4;
	int YELLOW = 1;
#endif
};
