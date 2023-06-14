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

}

void Player::Update() {

	bullet_->Update();

}

void Player::Draw() {

	bullet_->Draw();

}
