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
	
	
	//Novice::DrawEllipse(pos_.x, pos_.y, size_, size_, 0.0f, WHITE, kFillModeWireFrame);
	
//	Novice::DrawEllipse(sentorPos_.x, sentorPos_.y, 2, 2, 0.0f, WHITE, kFillModeSolid);
	bullet_->Draw();

}
