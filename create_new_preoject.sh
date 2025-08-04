
#!/usr/bin/env bash

# === Config ===
PROJECT_NAME="YourFirstGame2"
ENGINE_PATH=".."  # Adjust if needed
FIRST_SCENE="FirstScene"

# === Create project folder ===
mkdir -p "$PROJECT_NAME/Source/Scenes"
mkdir -p "$PROJECT_NAME/Source/GameObjects"
mkdir -p "$PROJECT_NAME/build"

# === Write CMakeLists.txt ===
cat > "$PROJECT_NAME/CMakeLists.txt" <<EOF
cmake_minimum_required(VERSION 3.12)
project(${PROJECT_NAME})

# Source files
file(GLOB_RECURSE ENGINE_SOURCES
    ${ENGINE_PATH}/Source/*.cpp
)

# Header files
file(GLOB_RECURSE ENGINE_HEADERS
    ${ENGINE_PATH}/Source/*.h
)

add_library(ConsoleCraftEngine SHARED \${ENGINE_SOURCES} )

file(GLOB_RECURSE GAME_SOURCES Source/*.cpp)
file(GLOB_RECURSE GAME_HEADERS Source/*.h)

# Executable
link_directories(\${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${PROJECT_NAME} \${GAME_SOURCES} \${GAME_HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    \${CMAKE_CURRENT_SOURCE_DIR}/Source 
    \${CMAKE_CURRENT_SOURCE_DIR}/${ENGINE_PATH}/Source
    \${CMAKE_CURRENT_SOURCE_DIR}/${ENGINE_PATH}/Source/Core
)

# Link with ConsoleCraftEngine library
target_link_libraries(${PROJECT_NAME} PUBLIC ConsoleCraftEngine ncurses)
EOF

# === Write YourFirstGameEntry.cpp ===
cat > "$PROJECT_NAME/Source/${PROJECT_NAME}Entry.cpp" <<EOF
#include "Scenes/${FIRST_SCENE}.h"
#include "Core/EntryPoint.h"
#include <vector>

class ${PROJECT_NAME}
{
public:
    ~${PROJECT_NAME}()
    {
    };

    Engine engine;

    void StartGame()
    {
        engine.scenes.push_back(new $FIRST_SCENE());
        engine.StartGame();
    }

    void Clean()
    {
        engine.Clean();
    }
};

int main()
{
    ${PROJECT_NAME} *game = new ${PROJECT_NAME}();
    game->StartGame();
    game->Clean();
    delete game;
    system("pause");
    return 0;
}
EOF

# === Write YourScene.h ===
cat > "$PROJECT_NAME/Source/Scenes/$FIRST_SCENE.h" <<EOF
#pragma once
#include "Core/Scene.h"

class $FIRST_SCENE : public Scene
{
public:
    void Init() override;
    void Update(float deltaTime) override;

private:
    void OnInput(int input);

};
EOF

# === Write YourScene.cpp ===
cat > "$PROJECT_NAME/Source/Scenes/$FIRST_SCENE.cpp" <<EOF
#include "${FIRST_SCENE}.h"

#include "GameObjects/YourGameObject.h"

void FirstScene::Init()
{
    AddGameObject(new YourGameObject(*this), Vector2(5,5));
    // TODO: Initialize your scene
}

void FirstScene::Update(float deltaTime)
{
    // TODO: Update logic for scene
}

EOF

#create Source/GameObjects
#YourGameObject.h and YourGameObject.cpp
# === Write YourGameObject.h ===
cat > "$PROJECT_NAME/Source/GameObjects/YourGameObject.h" <<EOF
#pragma once
#include "GameObject.h"

class YourGameObject : public GameObject {
public:
  YourGameObject(class Scene &scene) : GameObject("YourGameObject", scene) {}
  void Init() override;
  void OnInput(int input);
  void Update(float deltaTime) override;
};
EOF

# === Write YourGameObject.cpp ===
cat > "$PROJECT_NAME/Source/GameObjects/YourGameObject.cpp" <<EOF

#include "YourGameObject.h"
#include "Input.h"

void YourGameObject::Init() {
    symbol = '8';
    sprite = {
        {1, 1},
        {1, 1},
    };
    auto inputEvent = BIND_EVENT_FN(YourGameObject::OnInput);
    Input::AddListener(inputEvent);
}

void YourGameObject::OnInput(int input)
{
	if (std::tolower(input) == 'd')
	{
	    transform.MovePosition(1, 0);
	}
	if (std::tolower(input) == 'a')
	{
		transform.MovePosition(-1, 0);
	}
	if (std::tolower(input) == 'w')
	{
		transform.MovePosition(0, -1);
	}
	if (std::tolower(input) == 's')
	{
		transform.MovePosition(0, 1);
	}
}

void YourGameObject::Update(float deltaTime) 
{

}
EOF
cat > "$PROJECT_NAME/build/build.sh" <<EOF
cmake .. && make && ./${PROJECT_NAME}
EOF

echo "✅ Project ${PROJECT_NAME} structure created!"
