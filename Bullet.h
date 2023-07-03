#pragma once
#include "newVector2.h"

struct BULLET
{
	Vector3 pos;
	Vector3 size;
	bool isShot;
	int shotCount;
	Vector3 speed;
};

class Bullet
{

public:

	void Initialize();

	void Update();

	void Draw();

private:

	float ballelSize = 100;
	float ballelRad = 30;

	static const int kBulletNum_ = 50;
	float airPower = 1;

	BULLET bullet_[kBulletNum_];

	Vector3 bulletAfter[kBulletNum_]{};

	int coolTime_;

	float gravity;

	float distance;

	char keys_[256];
	char preKeys_[256];
};

