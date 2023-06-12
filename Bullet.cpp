#include "Bullet.h"
#include <Novice.h>
#include <stdlib.h>
#include <time.h>

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

void Bullet::Update() {
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);

	for (int i = 0; i < kBulletNum_; i++) {
		if (bullet_[i].isShot == false) {
			bullet_[i].pos.z = -60;
		}
	}
	for (int i = 0; i < kBulletNum_; i++) {
		if (keys_[DIK_SPACE] && preKeys_[DIK_SPACE] == 0) {
			if (bullet_[i].isShot == false) {
				if (coolTime_ <= 0) {
					coolTime_ = 25;
				}
				bullet_[i].pos.x = 640.0f;
				bullet_[i].pos.y = 360.0f;
				bullet_[i].speed.x = float(rand() % 2 - 1);
				bullet_[i].speed.y = float(rand() % 2 - 1);
				bullet_[i].speed.z = airPower;

				//bullet_[i].pos.x = pos.x + float(rundomPosX[i]);
				//bullet_[i].pos.y = pos.y + float(rundomPosY[i]);
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
		if (keys_[DIK_RETURN] && preKeys_[DIK_RETURN]) {
			bullet_[i].isShot = false;
		}
	}


	unsigned int currentTime = unsigned int(time(nullptr));
	srand(currentTime);
	

	for (int i = 0; i < kBulletNum_; i++) {
		if (bullet_[i].isShot == true) {

			bullet_[i].pos.x += bullet_[i].speed.x;
			bullet_[i].pos.y += bullet_[i].speed.y;
			bullet_[i].pos.z += bullet_[i].speed.z;

			if(bullet_[i].pos.z < 0) {

				Vector3 bullelPos = { 640, 360, 0 };
				float dis = (bullelPos.x - bullet_[i].pos.x) * (bullelPos.x - bullet_[i].pos.x) + (bullelPos.y - bullet_[i].pos.y) * (bullelPos.y - bullet_[i].pos.y);

				if (dis >= bullet_[i].size.x + 32) {
					bullet_[i].pos.x *= -1;
					bullet_[i].pos.y *= -1;
				}
			}

			if (bullet_[i].pos.z > 10) {
				bulletAfter[i].x = bullet_[i].pos.x;
  				bulletAfter[i].y = bullet_[i].pos.y;
				bullet_[i].isShot = false;
			}

		}
	}




}

void Bullet::Draw() {
	for (int i = 0; i < kBulletNum_; i++) {
		if (bullet_[i].isShot == true) {
			Novice::DrawEllipse(int(bullet_[i].pos.x), int(bullet_[i].pos.y), int(bullet_[i].size.x), int(bullet_[i].size.y), 0.0f, RED, kFillModeSolid);
		}
		Novice::DrawEllipse(int(bulletAfter[i].x), int(bulletAfter[i].y), 8, 8, 0.0f, RED, kFillModeSolid);

	}
}