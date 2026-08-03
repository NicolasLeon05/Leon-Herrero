#pragma once

#include "../entity/Entity2D.h"
#include "../EngineAPI.h"


class CollisionManager
{
public:
	ENGINE_API bool CheckCollision(Entity2D* entity, Entity2D* other);
	ENGINE_API bool CheckCollision(Entity2D* entity, std::vector<Entity2D*>others);
	ENGINE_API bool IsColliding(Entity2D* entity, Entity2D* other);

	ENGINE_API void ResolveCollisionPush(Entity2D* entity, Entity2D* other, float margin = 0.0f);

	ENGINE_API float GetCollisionWidthRotated(Entity2D* entity);
	ENGINE_API float GetCollisionHeightRotated(Entity2D* entity);
};