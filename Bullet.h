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

	static const int kBulletNum_ = 100;
	const float airPower = 10;
	Vector3 firstVec{ 0, 0, airPower };

	BULLET bullet_[kBulletNum_];

	Vector3 bulletAfter[kBulletNum_]{};

	int coolTime_;

	char keys_[256];
	char preKeys_[256];
};

