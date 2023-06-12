#include "Bullet.h"
#include <Novice.h>

void Bullet::Initialize() {
	for (int i = 0; i < kBulletNum_; i++) {
		bullet_[i].pos.x = -100;
		bullet_[i].pos.y = -100;
		bullet_[i].size.x = 8;
		bullet_[i].size.y = 8;
		bullet_[i].isShot = false;
		bullet_[i].shotCount = 0;
	}
	
	coolTime_ = 0;

}

void Bullet::Update(char* keys, char* preKeys,Vector2Int pos, int rundomPosX[], int rundomPosY[]) {

	for (int i = 0; i < kBulletNum_; i++) {
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			if (bullet_[i].isShot == false) {
				if (coolTime_ <= 0) {
					coolTime_ = 25;
				}
				bullet_[i].pos.x = pos.x + rundomPosX[i];
				bullet_[i].pos.y = pos.y + rundomPosY[i];
				bullet_[i].isShot = true;
				bullet_[i].shotCount = 1;
				if (bullet_[i].isShot == true) {
					break;
				}
			}
		}
	}

	if (coolTime_ >= 0) {
		coolTime_--;
	}

	for (int i = 0; i < kBulletNum_; i++) {
		if (keys[DIK_RETURN] && preKeys[DIK_RETURN]) {
			bullet_[i].isShot = false;
		}
	}

}

void Bullet::Draw() {
	for (int i = 0; i < kBulletNum_; i++) {
		if (bullet_[i].isShot == true) {
			Novice::DrawEllipse(bullet_[i].pos.x, bullet_[i].pos.y, bullet_[i].size.x, bullet_[i].size.y, 0.0f, RED, kFillModeSolid);
		}
	}
}