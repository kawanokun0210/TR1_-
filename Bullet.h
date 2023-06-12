#pragma once
#include "newVector2.h"

struct BULLET
{
	Vector2Int pos;
	Vector2Int size;
	bool isShot;
	int shotCount;
};

class Bullet
{

public:

	void Initialize();

	void Update(char* keys, char* preKeys,Vector2Int pos, int rundomPosX[], int rundomPosY[]);

	void Draw();

private:

	static const int kBulletNum_ = 100;

	BULLET bullet_[kBulletNum_];

	int coolTime_;

};

