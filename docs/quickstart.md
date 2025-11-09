# ConsoleCraftEngine – Quick Start Guide

## Installing

Clone the repository and enter the engine folder:

```bash
git clone https://github.com/ural89/ConsoleCraftEngine
cd ConsoleCraftEngine
```
## Create Your First Project

Run the project creation script:

```bash
./create_new_project.sh
```

When prompted, enter your project name.
Project names must **not contain spaces**.

Build and run your project:

``` bash
cd YourProject/build`
`./build.sh
```

You will see an **example scene** with an example game object.
Use **W A S D** keys to move the object around.

---

## Adding a Component to Your GameObject

Let’s add a **ParticleSource** component to the example game object.

### 1. Modify `ExampleGameObject.h`

Add a `ParticleSource` pointer in the private section:

``` cpp
class ExampleGameObject : public GameObject {
public:
    void Init() override;
    void OnInput(int input);
    void Update(float deltaTime) override;
private:
    class ParticleSource *particleSource;
};
```
### 2. Modify `ExampleGameObject.cpp`

Include the particle source header **after** `#include "Input.h"`:
``` cpp
#include "ExampleGameObject.h"
#include "Input.h"
#include "Core/ParticleSystem/ParticleSource.h"
```
Create and add **ParticleSource** component to example gameobject
``` cpp
void ExampleGameObject::Init() {
    symbol = '8';
    sprite = {
        {1, 1},
        {1, 1},
    };
    auto inputEvent = BIND_EVENT_FN(ExampleGameObject::OnInput);
    Input::AddListener(inputEvent);

	//add particle source here
    particleSource = AddComponent<ParticleSource>();
}

```
Then update the `OnInput` method to emit particles when pressing Space:
``` cpp
void ExampleGameObject::OnInput(int input) {
    if (input == SPACEBAR) {
		int particleCount = 4;
        particleSource->EmitParticle(particleCount,
         FIRETYPEPARTICLE);
    }

    // existing input handling...
    if (std::tolower(input) == 'd') transform.MovePosition(1, 0);
    if (std::tolower(input) == 'a') transform.MovePosition(-1, 0);
    if (std::tolower(input) == 'w') transform.MovePosition(0, -1);
    if (std::tolower(input) == 's') transform.MovePosition(0, 1);
}
```
### 3. Rebuild & Run

Go back to the build folder and run your project again:
```bash
cd YourProject/build
./build.sh
```


Now, when you press Spacebar, particles will spawn around your game object!

## Check Wiki for more detailed info
[Wiki](https://github.com/ural89/ConsoleCraftEngine/wiki)
