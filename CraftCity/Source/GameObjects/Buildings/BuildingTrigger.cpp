#include "BuildingTrigger.h"
#include "Road.h"
void BuildingTrigger::OnCollided(GameObject &other)
{
	if (other.name == "Road" && other != owner)
	{
		if (auto otherRoad = dynamic_cast<Road *>(&other))
		{
			if (otherRoad->HasConnectedToMain)
			{

				if (auto ownerRoad = static_cast<Road *>(&owner))
				{
					mainConnectionRoad = otherRoad;
					ownerRoad->HasConnectedToMain = true;
				}
				HasRoad = true;
			}
		}
	}

	// TODO: add for electricity and water
}

void BuildingTrigger::OnCollisionExit(GameObject &other)
{
	if (other.name == "Road" && other != owner)
	{
			std::cout << other.name << '\n';
			if (auto otherRoad = static_cast<Road *>(&other))
			{
				if (mainConnectionRoad == otherRoad)
				{

					if (auto ownerRoad = static_cast<Road *>(&owner))
					{
						ownerRoad->HasConnectedToMain = false;
					}
					HasRoad = false;
				}
			}
	}
}
