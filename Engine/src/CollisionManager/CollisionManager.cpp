#include "CollisionManager.h"

bool  CollisionManager::IsColliding(Entity2D* entity, Entity2D* other)
{
	return (entity->GetX() + entity->GetCollisionWidth()/2 >= other->GetX() - other->GetCollisionWidth()/2	&&
		entity->GetX() - entity->GetCollisionWidth() / 2 <= other->GetX() + other->GetCollisionWidth() / 2 &&
		entity->GetY() + entity->GetCollisionHeight() / 2 >= other->GetX() - other->GetCollisionHeight() / 2 &&
		entity->GetY() - entity->GetCollisionHeight() / 2 <= other->GetX() + other->GetCollisionHeight() / 2);
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
	
