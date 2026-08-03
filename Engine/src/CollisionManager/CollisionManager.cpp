#include "CollisionManager.h"

bool CollisionManager::IsColliding(Entity2D* entity, Entity2D* other)
{
	float width1 = GetCollisionWidthRotated(entity) / 2.0f;
	float height1 = GetCollisionHeightRotated(entity) / 2.0f;

	float width2 = GetCollisionWidthRotated(other) / 2.0f;
	float height2 = GetCollisionHeightRotated(other) / 2.0f;

	return (
		entity->GetX() + width1 >= other->GetX() - width2 &&
		entity->GetX() - width1 <= other->GetX() + width2 &&
		entity->GetY() + height1 >= other->GetY() - height2 &&
		entity->GetY() - height1 <= other->GetY() + height2
		);
}

float CollisionManager::GetCollisionWidthRotated(Entity2D* entity)
{
	float width = entity->GetScale().x;
	float height = entity->GetScale().y;

	float theta = glm::radians(entity->GetRotation().z);

	return fabs(width * cos(theta)) + fabs(height * sin(theta));
}

float CollisionManager::GetCollisionHeightRotated(Entity2D* entity)
{
	float width = entity->GetScale().x;
	float height = entity->GetScale().y;

	float theta = glm::radians(entity->GetRotation().z);

	return fabs(width * sin(theta)) + fabs(height * cos(theta));
}

bool CollisionManager::CheckCollision(Entity2D* movingEntity, Entity2D* obstacle)
{
	if (IsColliding(movingEntity, obstacle))
	{
		movingEntity->RestorePreviousPosition();
		obstacle->RestorePreviousPosition();
		return true;
	}
	return false;
}

bool CollisionManager::CheckCollision(Entity2D* movingEntity, std::vector<Entity2D*> obstacles)
{
	bool collided = false;
	for (int i = 0; i < obstacles.size(); i++)
	{
		if (IsColliding(movingEntity, obstacles[i]))
		{
			movingEntity->RestorePreviousPosition();
			obstacles[i]->RestorePreviousPosition();
			collided = true;
		}
	}

	return collided;
}

void CollisionManager::ResolveCollisionPush(Entity2D* entityToPush, Entity2D* pushingEntity, float margin)
{
	float halfWidthEntity = GetCollisionWidthRotated(entityToPush) * 0.5f;
	float halfHeightEntity = GetCollisionHeightRotated(entityToPush) * 0.5f;

	float halfWidthOther = GetCollisionWidthRotated(pushingEntity) * 0.5f;
	float halfHeightOther = GetCollisionHeightRotated(pushingEntity) * 0.5f;

	glm::vec3 entityPos = entityToPush->GetPosition();
	glm::vec3 otherPos = pushingEntity->GetPosition();

	float deltaX = entityPos.x - otherPos.x;
	float deltaY = entityPos.y - otherPos.y;

	float penetrationX = (halfWidthEntity + halfWidthOther) - fabs(deltaX);
	float penetrationY = (halfHeightEntity + halfHeightOther) - fabs(deltaY);

	if (penetrationX <= 0.0f || penetrationY <= 0.0f)
		return;

	glm::vec3 resolvedPosition = entityPos;

	if (penetrationX < penetrationY)
	{
		if (deltaX > 0.0f)
			resolvedPosition.x += penetrationX + margin;
		else
			resolvedPosition.x -= penetrationX + margin;
	}
	else
	{
		if (deltaY > 0.0f)
			resolvedPosition.y += penetrationY + margin;
		else
			resolvedPosition.y -= penetrationY + margin;
	}

	entityToPush->SetResolvedPosition(resolvedPosition.x, resolvedPosition.y, resolvedPosition.z);
}

