#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

projects=("AIGame" "CraftCity" "CraftMatch" "CraftPhysicsTest" "CraftRogue" "CraftShooterGame")

for project in "${projects[@]}"; do
    echo "Building $project..."
    if [ -d "$project" ]; then
        (
            cd "$project"
            mkdir -p build
            cd build
            cmake -G Ninja ..
            ninja
        )
    else
        echo "Directory $project not found, skipping."
    fi
done
