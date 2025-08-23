
#!/usr/bin/env bash

read -p "Enter project name: " PROJECT_NAME
if [[ "$PROJECT_NAME" =~ \  ]]; then
    echo "Error: Project name cannot contain spaces."
    exit 1
fi
PROJECT_NAME=${PROJECT_NAME:-YourFirstGame}  # fallback if empty

# === Config ===
# PROJECT_NAME="YourFirstGame"
ENGINE_PATH=".."  # Adjust if needed
ENTRY_SCENE="EntryScene"

# === Create project folder ===
mkdir -p "$PROJECT_NAME/Source/Scenes"
mkdir -p "$PROJECT_NAME/Source/GameObjects"
mkdir -p "$PROJECT_NAME/build"

# === Write CMakeLists.txt ===
cat > "$PROJECT_NAME/CMakeLists.txt" <<EOF
cmake_minimum_required(VERSION 3.12)
project(${PROJECT_NAME})
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

# === Write YourGameEntry.cpp ===
cat > "$PROJECT_NAME/Source/${PROJECT_NAME}Entry.cpp" <<EOF
#include "Scenes/${ENTRY_SCENE}.h"
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
        engine.scenes.push_back(new $ENTRY_SCENE());
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
cat > "$PROJECT_NAME/Source/Scenes/$ENTRY_SCENE.h" <<EOF
#pragma once
#include "Core/Scene.h"

class $ENTRY_SCENE : public Scene
{
public:
    void Init() override;
    void Update(float deltaTime) override;

private:
    void OnInput(int input);

};
EOF

# === Write YourScene.cpp ===
cat > "$PROJECT_NAME/Source/Scenes/$ENTRY_SCENE.cpp" <<EOF
#include "${ENTRY_SCENE}.h"

#include "GameObjects/ExampleGameObject.h"

void ${ENTRY_SCENE}::Init()
{
    AddGameObject(new ExampleGameObject(*this), Vector2(5,5));
    // TODO: Initialize your scene
}

void ${ENTRY_SCENE}::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    // TODO: Update logic for scene
}

EOF

#create Source/GameObjects
#ExampleGameObject.h and ExampleGameObject.cpp
# === Write ExampleGameObject.h ===
cat > "$PROJECT_NAME/Source/GameObjects/ExampleGameObject.h" <<EOF
#pragma once
#include "GameObject.h"

class ExampleGameObject : public GameObject {
public:
  ExampleGameObject(class Scene &scene) : GameObject("ExampleGameObject", scene) {}
  void Init() override;
  void OnInput(int input);
  void Update(float deltaTime) override;
};
EOF

# === Write ExampleGameObject.cpp ===
cat > "$PROJECT_NAME/Source/GameObjects/ExampleGameObject.cpp" <<EOF

#include "ExampleGameObject.h"
#include "Input.h"

void ExampleGameObject::Init() {
    symbol = '8';
    sprite = {
        {1, 1},
        {1, 1},
    };
    auto inputEvent = BIND_EVENT_FN(ExampleGameObject::OnInput);
    Input::AddListener(inputEvent);
}

void ExampleGameObject::OnInput(int input)
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

void ExampleGameObject::Update(float deltaTime) 
{

}
EOF
cat > "$PROJECT_NAME/build/build.sh" <<EOF
cmake .. && make && ./${PROJECT_NAME}
EOF
chmod +x "$PROJECT_NAME/build/build.sh"

echo "Project ${PROJECT_NAME} structure created!"
