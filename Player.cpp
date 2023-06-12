#include "Player.h"
#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Player::Initialize() {
	pos_.x = 640;
	pos_.y = 360;
	size_ = 256;
	
	sentorPos_.x = 640;
	sentorPos_.y = 360;

	state = new NoCustomGun();
	state->SetPlayer(this);

	time_t currentTime = time(nullptr);
	srand(unsigned int(currentTime));

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


void NoCustomGun::Update() {

	for (int i = 0; i < 100; i++) {
		rundomX[i] = rand() % 352 - 176;
		rundomY[i] = rand() % 352 - 176;
		bullet_->Update(keys_, preKeys_, player_->GetPos(), &rundomX[i], &rundomY[i]);
	}

	player_->Draw();

	if (preKeys_[DIK_RIGHT] && keys_[DIK_RIGHT] == 0) {	
		player_->ChangeState(new CustomBarrelGun);
	}

}

void CustomBarrelGun::Update() {
	for (int i = 0; i < 100; i++) {
		rundomX[i] = rand() % 192 - 96;
		rundomY[i] = rand() % 192 - 96;
		bullet_->Update(keys_, preKeys_, player_->GetPos(), &rundomX[i], &rundomY[i]);
	}

	player_->SecondDraw();

	if (preKeys_[DIK_RIGHT] && keys_[DIK_RIGHT] == 0) {
		player_->ChangeState(new FullCustomGun);
	}

}

void FullCustomGun::Update() {

	for (int i = 0; i < 100; i++) {
		rundomX[i] = rand() % 96 - 48;
		rundomY[i] = rand() % 96 - 48;
		bullet_->Update(keys_, preKeys_, player_->GetPos(), &rundomX[i], &rundomY[i]);
	}

	player_->ThirdDraw();

	if (preKeys_[DIK_RIGHT] && keys_[DIK_RIGHT] == 0) {
		player_->ChangeState(new NoCustomGun);
	}

}

void Player::Update(Bullet* bullet) {
	state->SetKeys();
	state->SetBullet(bullet);

	state->Update();

}

void Player::Draw() {
	
	
	Novice::DrawEllipse(pos_.x, pos_.y, size_, size_, 0.0f, WHITE, kFillModeWireFrame);
	
	Novice::DrawEllipse(sentorPos_.x, sentorPos_.y, 2, 2, 0.0f, WHITE, kFillModeSolid);

}

void Player::SecondDraw() {

	Novice::DrawEllipse(pos_.x, pos_.y, 128, 128, 0.0f, WHITE, kFillModeWireFrame);

	Novice::DrawEllipse(sentorPos_.x, sentorPos_.y, 2, 2, 0.0f, WHITE, kFillModeSolid);
}

void Player::ThirdDraw() {

	Novice::DrawEllipse(pos_.x, pos_.y, 64, 64, 0.0f, WHITE, kFillModeWireFrame);

	Novice::DrawEllipse(sentorPos_.x, sentorPos_.y, 2, 2, 0.0f, WHITE, kFillModeSolid);
}