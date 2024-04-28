#pragma once
class BuildHandler
{
public:
    BuildHandler(const class BuildingMenu& buldingMenu, class Scene& scene, class PlayerVault* playerVault);
    ~BuildHandler()
    {

    }
    void Build(struct Vector2 position);
private:
	class PlayerVault* playerVault;
	const BuildingMenu& buildingMenu;
	Scene& scene;
};