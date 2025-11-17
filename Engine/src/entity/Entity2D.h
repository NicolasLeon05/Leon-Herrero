#pragma once

#include "Entity.h"
#include "../material/Material.h"

class Entity2D : public Entity
{
protected:
	Material material;

public:
	Entity2D();
	~Entity2D();

	Material& GetMaterial();
	void SetMaterial();

	float GetCollisionWidth();
	float GetCollisionHeight();

	virtual void Draw();
};