#include "Bullet.h"
#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include "imgui.h"

void Bullet::Initialize() {
	for (int i = 0; i < kBulletNum_; i++) {
		bullet_[i].pos.x = -100;
		bullet_[i].pos.y = -100;
		bullet_[i].size.x = 2;
		bullet_[i].size.y = 2;
		bullet_[i].isShot = false;
		bullet_[i].shotCount = 0;
	}
	
	coolTime_ = 0;

}

void Bullet::Update() {
	ImGui::Begin("Bullet");
	ImGui::SliderFloat("bullelSize", &ballelSize, 1.0f, 1000.0f);
	ImGui::SliderFloat("bullelRad", &ballelRad, 8.0f, 1000.0f);
	ImGui::SliderFloat("airPower", &airPower, 1.0f, 100.0f);

	ImGui::End();

	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);

	for (int i = 0; i < kBulletNum_; i++) {
		if (bullet_[i].isShot == false) {
			bullet_[i].pos.z = -ballelSize;
		}
	}
	for (int i = 0; i < kBulletNum_; i++) {
		if (keys_[DIK_SPACE] && !preKeys_[DIK_SPACE]) {
			if (bullet_[i].isShot == false) {
				if (coolTime_ <= 0) {
					coolTime_ = 25;
				}
				bullet_[i].pos.x = 640.0f;
				bullet_[i].pos.y = 360.0f;
				bullet_[i].speed.x = float(rand() % 20 - 10);
				bullet_[i].speed.y = float(rand() % 20 - 10);
				bullet_[i].speed.z = airPower;

				//bullet_[i].pos.x = pos.x + float(rundomPosX[i]);
				//bullet_[i].pos.y = pos.y + float(rundomPosY[i]);
				bullet_[i].isShot = true;
				bullet_[i].shotCount = 1;
				if (bullet_[i].isShot == true) {
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

				if (dis >= bullet_[i].size.x + ballelRad) {
					bullet_[i].pos.x *= -1;
					bullet_[i].pos.y *= -1;
					if (airPower > 1.0f) {
						airPower -= 0.1f;
					}
					else {
						airPower = 1.0f;
					}
				}
			}

			if (bullet_[i].pos.z > 20) {
				bullet_[i].isShot = false;
			}

		}

		if (bullet_[i].isShot == false) {
			bulletAfter[i].x = bullet_[i].pos.x;
			bulletAfter[i].y = bullet_[i].pos.y;
		}
 	}




}

void Bullet::Draw() {
	for (int i = 0; i < kBulletNum_; i++) {
		if (bullet_[i].isShot == true) {
			Novice::DrawEllipse(int(bullet_[i].pos.x), int(bullet_[i].pos.y), int(bullet_[i].size.x), int(bullet_[i].size.y), 0.0f, RED, kFillModeSolid);
		}
		if (bullet_[i].isShot == false) {

			Novice::DrawEllipse(int(bulletAfter[i].x), int(bulletAfter[i].y), 3, 3, 0.0f, RED, kFillModeSolid);
		}
	}
}