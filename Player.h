#pragma once
#include "newVector2.h"
#include "Bullet.h"

class Player;

enum class Phase {
	NoCustom,
	CustomBarrel,
	FullCustom,
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

class NoCustomGun : public PlayerState {

public:

	int rundomX[100] = { 0 };
	int rundomY[100] = { 0 };

	void Update() override;

};

class CustomBarrelGun : public PlayerState {

public:

	int rundomX[100] = { 0 };
	int rundomY[100] = { 0 };

	void Update() override;

};

class FullCustomGun : public PlayerState {

public:

	int rundomX[100] = { 0 };
	int rundomY[100] = { 0 };

	void Update() override;

};

class Player
{

public:

	~Player() { delete state; }

	void Initialize();

	void Update(Bullet* bullet);

	void Draw();

	void SecondDraw();

	void ThirdDraw();

	void ChangeState(PlayerState* newPlayerState);

	Vector2Int GetPos() { return sentorPos_; }

private:

	Vector2Int pos_;
	Vector2Int sentorPos_;

	int size_;

	Phase phase_ = Phase::NoCustom;

	PlayerState* state;

};
