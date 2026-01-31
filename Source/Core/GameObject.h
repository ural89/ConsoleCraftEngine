#pragma once
#include "../Core.h"
#include "../CoreStructs/Transform.h"
#include "Component/Component.h"
#include <vector>

class GE_API GameObject
{

  public:
	GameObject(std::string &&name, class Scene &scene) : name(name), scene(scene)
	{
		width = 2;
		height = 2;
		newSprite = new int[2 * 2]{1, 1, 1, 1};
	};
	void SetSprite(std::vector<std::vector<int>> sprite)
	{
		int spriteWidth = sprite.size();
		int spriteHeight = 0;

		int maxHeight = 0;
		for (int i = 0; i < spriteWidth; i++)
		{
			int currentLineSize = sprite[i].size();
			if (maxHeight < currentLineSize)
			{
				maxHeight = currentLineSize;
			}
		}
		height = maxHeight;
		width = spriteWidth;

		if (newSprite != nullptr)
		{
			delete[] newSprite;
		}
		newSprite = new int[width * height];

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int index = (y * width) + x;
				if (x < sprite[y].size())
				{
					newSprite[index] = sprite[y][x];
				}
				else
				{
					newSprite[index] = 0;
				}
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
		delete newSprite;
	}

	Transform transform = Transform();

	std::string name = "Gameobject";
	std::vector<std::vector<int>> sprite = {{1, 1}, {1, 1}};
	int *newSprite = nullptr;

	virtual int GetWidth() const
	{
		return sprite[0].size();
	}
	virtual int GetHeight() const
	{
		return sprite.size();
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
