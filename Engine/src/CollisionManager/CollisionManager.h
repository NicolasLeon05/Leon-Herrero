#pragma once

#include "../entity/Entity2D.h"
#include "../EngineAPI.h"


class CollisionManager
{
private:
	bool IsColliding(Entity2D* entity, Entity2D* other);

public:
	ENGINE_API bool CheckCollision(Entity2D* entity, Entity2D* other);
	ENGINE_API bool CheckCollision(Entity2D* entity, std::vector<Entity2D*>others);

	ENGINE_API float GetCollisionWidthRotated(Entity2D* entity);
	ENGINE_API float GetCollisionHeightRotated(Entity2D* entity);
};