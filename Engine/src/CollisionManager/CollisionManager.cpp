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

bool CollisionManager::CheckCollision(Entity2D* entity, Entity2D* other)
{
	if (IsColliding(entity, other))
	{
		entity->SetPosition(entity->GetPrevPosition());
		return true;
	}
	return false;
}

bool CollisionManager::CheckCollision(Entity2D* entity, std::vector<Entity2D*> others)
{
	bool collided = false;
	for (int i = 0; i < others.size(); i++)
	{
		if (IsColliding(entity, others[i]))
		{
			entity->SetPosition(entity->GetPrevPosition());
			collided = true;
		}
	}

	return collided;
}

void CollisionManager::ResolveCollisionPush(Entity2D* entity, Entity2D* other, float margin)
{
    float halfWidthEntity = GetCollisionWidthRotated(entity) * 0.5f;
    float halfHeightEntity = GetCollisionHeightRotated(entity) * 0.5f;

    float halfWidthOther = GetCollisionWidthRotated(other) * 0.5f;
    float halfHeightOther = GetCollisionHeightRotated(other) * 0.5f;

    glm::vec3 entityPos = entity->GetPosition();
    glm::vec3 otherPos = other->GetPosition();

    float deltaX = entityPos.x - otherPos.x;
    float deltaY = entityPos.y - otherPos.y;

    float penetrationX = (halfWidthEntity + halfWidthOther) - fabs(deltaX);
    float penetrationY = (halfHeightEntity + halfHeightOther) - fabs(deltaY);

    if (penetrationX <= 0 || penetrationY <= 0)
        return;

    if (penetrationX < penetrationY)
    {
        if (deltaX > 0)
            entity->SetX(entityPos.x + penetrationX + margin);
        else
            entity->SetX(entityPos.x - penetrationX - margin);
    }
    else
    {
        if (deltaY > 0)
            entity->SetY(entityPos.y + penetrationY + margin);
        else
            entity->SetY(entityPos.y - penetrationY - margin);
    }
}

