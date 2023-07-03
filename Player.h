#pragma once
#include "newVector2.h"
#include "Bullet.h"

class Player;

enum class Phase {
	ShotGun,
	Rifle,
	Pistol
};

class PlayerState {

protected:

	Player* player_ = nullptr;
	Bullet* bullet_ = nullptr;
	char keys_[256];
	char preKeys_[256];

public:

	virtual void SetPlayer(Player* player) { player_ = player; }
	virtual void Update() {};
	void SetKeys();
	void SetBullet(Bullet* bullet) { bullet_ = bullet; }

};

class ShotGun :public PlayerState {

public:

	void Update() override;

};

class Rifle :public PlayerState {

public:

	void Update() override;

};

class Pistol :public PlayerState {

public:

	void Update() override;

};

class Player
{

public:

	~Player() { delete state; }

	void Initialize();

	void Update(Bullet* bullet_);

	void Draw();

	void ChangeState(PlayerState* newPlayerState);

	Vector2Int GetPos() { return sentorPos_; }

private:

	Vector2Int pos_;

	Vector2Int sentorPos_;

	int size_;

	Bullet* bullet_ = nullptr;

	Phase phase_ = Phase::ShotGun;

	PlayerState* state;

};
