#include "CollisionManager.h"

bool CollisionManager::IsColliding(Entity2D* entity, Entity2D* other)
{
	float width1 = CollisionWidthRotated(entity) / 2.0f;
	float height1 = CollisionHeightRotated(entity) / 2.0f;

	float width2 = CollisionWidthRotated(other) / 2.0f;
	float height2 = CollisionHeightRotated(other) / 2.0f;

	return (
		entity->GetX() + width1 >= other->GetX() - width2 &&
		entity->GetX() - width1 <= other->GetX() + width2 &&
		entity->GetY() + height1 >= other->GetY() - height2 &&
		entity->GetY() - height1 <= other->GetY() + height2
		);
}

float CollisionManager::CollisionWidthRotated(Entity2D* entity)
{
	float width = entity->GetScale().x;
	float height = entity->GetScale().y;

	float theta = glm::radians(entity->GetRotation().z);

	return fabs(width * cos(theta)) + fabs(height * sin(theta));
}

float CollisionManager::CollisionHeightRotated(Entity2D* entity)
{
	float width = entity->GetScale().x;
	float height = entity->GetScale().y;

	float theta = glm::radians(entity->GetRotation().z);

	return fabs(width * sin(theta)) + fabs(height * cos(theta));
}

void CollisionManager::CheckCollision(Entity2D* entity, Entity2D* other)
{
	if (IsColliding(entity, other))
	{
		entity->SetPosition(entity->GetPrevPosition());
	}
}

void CollisionManager::CheckCollision(Entity2D* entity, std::vector<Entity2D*> others)
{
	for (int i = 0; i < others.size(); i++)
	{
		if (IsColliding(entity, others[i]))
		{
			entity->SetPosition(entity->GetPrevPosition());
		}
	}
}

