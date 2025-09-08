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

	void Draw() override;
	void virtual SetVertices(float posX, float posY, float posZ);
};