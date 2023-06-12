#pragma once
#include "newVector2.h"
#include "Bullet.h"

class Player
{

public:

	void Initialize();

	void Update(Bullet* bullet);

	void Draw();

	Vector2Int GetPos() { return sentorPos_; }

private:

	Vector2Int pos_;
	Vector2Int sentorPos_;

	int size_;

};
