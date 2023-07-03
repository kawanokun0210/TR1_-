#include "Player.h"
#include <Novice.h>

void Player::Initialize() {
	pos_.x = 640;
	pos_.y = 360;
	size_ = 256;
	
	sentorPos_.x = 640;
	sentorPos_.y = 360;

	bullet_ =new Bullet();
	bullet_->Initialize();

	state = new ShotGun();
	state->SetPlayer(this);

}

void Player::ChangeState(PlayerState* newPlayerState) {
	delete state;

	state = newPlayerState;
	state->SetPlayer(this);

}

void PlayerState::SetKeys() {
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
}

void ShotGun::Update() {
	bullet_->ShotGunUpdate();

	if (preKeys_[DIK_RIGHT] && keys_[DIK_RIGHT] == 0) {
		player_->ChangeState(new Rifle);
	}
}

void Rifle::Update() {
	bullet_->RifleUpdate();

	if (preKeys_[DIK_RIGHT] && keys_[DIK_RIGHT] == 0) {
		player_->ChangeState(new Pistol);
	}
}

void Pistol::Update() {
	bullet_->PistolUpdate();

	if (preKeys_[DIK_RIGHT] && keys_[DIK_RIGHT] == 0) {
		player_->ChangeState(new ShotGun);
	}
}

void Player::Update(Bullet* bullet) {

	//bullet_->ShotGunUpdate();
	state->SetBullet(bullet);
	state->SetKeys();

	state->Update();

}

void Player::Draw() {

	bullet_->Draw();

}
