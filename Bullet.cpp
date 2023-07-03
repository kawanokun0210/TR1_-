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

	gravity = 0;
	distance = 20;
	coolTime_ = 0;

}

void Bullet::ShotGunUpdate() {

	unsigned int currentTime = unsigned int(time(nullptr));
	srand(currentTime);

	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);

	for (int i = 0; i < kBulletNum_; i++) {
		if (keys_[DIK_SPACE] && !preKeys_[DIK_SPACE]) {
			if (bullet_[i].isShot == false) {
				if (coolTime_ <= 0) {
					coolTime_ = 25;
				}
				//初期のポジション
				bullet_[i].pos.x = 640.0f;
				bullet_[i].pos.y = 360.0f;
				bullet_[i].pos.z = -ballelSize;

				//初速(x,yはランダムに、zは空気の圧力で)
				bullet_[i].speed.x = float(rand() % 20 - 10);
				bullet_[i].speed.y = float(rand() % 20 - 10);
				bullet_[i].speed.z = airPower;
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
			bullet_[i].shotCount = 0;
		}
	}

	for (int i = 0; i < kBulletNum_; i++) {
		if (bullet_[i].isShot == true) {

			//isShotがtrueの間は速さを足していく
			bullet_[i].pos.x += bullet_[i].speed.x;
			bullet_[i].pos.y += bullet_[i].speed.y;
			bullet_[i].pos.z += bullet_[i].speed.z;

			//スピードyのみ重力で少しずつ下に行くように
			bullet_[i].speed.y += gravity;

			//摩擦
			float masa = -(bullet_[i].speed.z / 10);
			if (bullet_[i].pos.z < 0) {

				//仮で中心の値を設定
				Vector3 bullelPos = { 640, 360, 0 };
				//ノズル内と弾との当たり判定
				float dis = (bullelPos.x - bullet_[i].pos.x) * (bullelPos.x - bullet_[i].pos.x) + (bullelPos.y - bullet_[i].pos.y) * (bullelPos.y - bullet_[i].pos.y);

				//もしノズル内と弾があたったら
				if (dis >= bullet_[i].size.x + ballelRad) {
					//跳ね返る
					bullet_[i].pos.x *= -1;
					bullet_[i].pos.y *= -1;
					//もしスピードzが1.0fより大きいなら
					if (bullet_[i].speed.z > 1.0f) {
						//少しずつ減少する
						bullet_[i].speed.z -= 0.01f;
					}
					else {
						//そうでなければ1.0fで固定
						bullet_[i].speed.z = 1.0f;
					}
					//摩擦分を反映
					bullet_[i].speed.z += masa;

				}
				for (int j = 0; j < kBulletNum_; j++) {
					//弾同士の当たり判定	
					float disb2b = (bullet_[i].pos.x - bullet_[j].pos.x) * (bullet_[i].pos.x - bullet_[j].pos.x) + (bullet_[i].pos.x - bullet_[j].pos.y) * (bullet_[i].pos.x - bullet_[j].pos.y);
					if (disb2b >= bullet_[i].size.x + bullet_[j].size.x) {
						//もし弾同士であたったら
						//跳ね返る
						bullet_[i].speed.x *= -1;
						bullet_[i].speed.y *= -1;
						//もしスピードzが1.0fより大きいなら
						if (bullet_[i].speed.z > 1.0f) {
							//少しずつ減少する
							bullet_[i].speed.z -= 0.01f;
						}
						else {
							//そうでなければ1.0fで固定
							bullet_[i].speed.z = 1.0f;
						}
						//摩擦分を反映
						bullet_[i].speed.z += masa;
					}
				}
			}
			//もし弾がz20(仮で的の位置)に当たったら
			if (bullet_[i].pos.z > distance) {
				//falseに
				bullet_[i].isShot = false;
			}
		}
		//もしisShotがfalseなら
		if (bullet_[i].isShot == false) {
			//弾痕に代入
			bulletAfter[i].x = bullet_[i].pos.x;
			bulletAfter[i].y = bullet_[i].pos.y;
		}
	}


	ImGui::Begin("Bullet");

	ImGui::Text("shotGun");
	ImGui::Text("RIGHT ARROW CHANGE RIFLE");
	ImGui::SliderFloat("bullelSize", &ballelSize, 1.0f, 100.0f);
	ImGui::SliderFloat("bullelRad", &ballelRad, 30.0f, 100.0f);
	ImGui::SliderFloat("airPower", &airPower, 1.0f, 100.0f);
	ImGui::SliderFloat("gravity", &gravity, 0.00f, 0.50f);
	ImGui::SliderFloat("distance", &distance, 0.00f, 100.0f);

	ImGui::End();
}

void Bullet::RifleUpdate() {
	unsigned int currentTime = unsigned int(time(nullptr));
	srand(currentTime);

	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);

	for (int i = 0; i < kBulletNum_; i++) {
		if (keys_[DIK_SPACE]) {
			if (bullet_[i].isShot == false) {
				if (coolTime_ <= 0) {
					coolTime_ = 25;

					//初期のポジション
					bullet_[i].pos.x = 640.0f;
					bullet_[i].pos.y = 360.0f;
					bullet_[i].pos.z = -ballelSize;

					//初速(x,yはランダムに、zは空気の圧力で)
					bullet_[i].speed.x = float(rand() % 20 - 10);
					bullet_[i].speed.y = float(rand() % 20 - 10);
					bullet_[i].speed.z = airPower;
					bullet_[i].isShot = true;
					bullet_[i].shotCount = 1;
				}
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

	for (int i = 0; i < kBulletNum_; i++) {
		if (bullet_[i].isShot == true) {

			//isShotがtrueの間は速さを足していく
			bullet_[i].pos.x += bullet_[i].speed.x;
			bullet_[i].pos.y += bullet_[i].speed.y;
			bullet_[i].pos.z += bullet_[i].speed.z;

			//スピードyのみ重力で少しずつ下に行くように
			bullet_[i].speed.y += gravity;

			//摩擦
			float masa = -(bullet_[i].speed.z / 10);
			if (bullet_[i].pos.z < 0) {

				//仮で中心の値を設定
				Vector3 bullelPos = { 640, 360, 0 };
				//ノズル内と弾との当たり判定
				float dis = (bullelPos.x - bullet_[i].pos.x) * (bullelPos.x - bullet_[i].pos.x) + (bullelPos.y - bullet_[i].pos.y) * (bullelPos.y - bullet_[i].pos.y);

				//もしノズル内と弾があたったら
				if (dis >= bullet_[i].size.x + ballelRad) {
					//跳ね返る
					bullet_[i].pos.x *= -1;
					bullet_[i].pos.y *= -1;
					//もしスピードzが1.0fより大きいなら
					if (bullet_[i].speed.z > 1.0f) {
						//少しずつ減少する
						bullet_[i].speed.z -= 0.01f;
					}
					else {
						//そうでなければ1.0fで固定
						bullet_[i].speed.z = 1.0f;
					}
					//摩擦分を反映
					bullet_[i].speed.z += masa;

				}
				for (int j = 0; j < kBulletNum_; j++) {
					//弾同士の当たり判定	
					float disb2b = (bullet_[i].pos.x - bullet_[j].pos.x) * (bullet_[i].pos.x - bullet_[j].pos.x) + (bullet_[i].pos.x - bullet_[j].pos.y) * (bullet_[i].pos.x - bullet_[j].pos.y);
					if (disb2b >= bullet_[i].size.x + bullet_[j].size.x) {
						//もし弾同士であたったら
						//跳ね返る
						bullet_[i].speed.x *= -1;
						bullet_[i].speed.y *= -1;
						//もしスピードzが1.0fより大きいなら
						if (bullet_[i].speed.z > 1.0f) {
							//少しずつ減少する
							bullet_[i].speed.z -= 0.01f;
						}
						else {
							//そうでなければ1.0fで固定
							bullet_[i].speed.z = 1.0f;
						}
						//摩擦分を反映
						bullet_[i].speed.z += masa;
					}
				}
			}
			//もし弾がz20(仮で的の位置)に当たったら
			if (bullet_[i].pos.z > distance) {
				//falseに
				bullet_[i].isShot = false;
			}
		}
		//もしisShotがfalseなら
		if (bullet_[i].isShot == false) {
			//弾痕に代入
			bulletAfter[i].x = bullet_[i].pos.x;
			bulletAfter[i].y = bullet_[i].pos.y;
		}
	}


	ImGui::Begin("Bullet");

	ImGui::Text("rifle");
	ImGui::Text("RIGHT ARROW CHANGE PISTOL");
	ImGui::SliderFloat("bullelSize", &ballelSize, 1.0f, 100.0f);
	ImGui::SliderFloat("bullelRad", &ballelRad, 30.0f, 100.0f);
	ImGui::SliderFloat("airPower", &airPower, 1.0f, 100.0f);
	ImGui::SliderFloat("gravity", &gravity, 0.00f, 0.50f);
	ImGui::SliderFloat("distance", &distance, 0.00f, 100.0f);

	ImGui::End();
}

void Bullet::PistolUpdate() {

	unsigned int currentTime = unsigned int(time(nullptr));
	srand(currentTime);

	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);

	if (keys_[DIK_SPACE] && !preKeys_[DIK_SPACE]) {
		if (bullet_[0].isShot == false) {
			if (bullet_[0].shotCount == 0) {
				if (coolTime_ <= 0) {
					coolTime_ = 25;
				}
				//初期のポジション
				bullet_[0].pos.x = 640.0f;
				bullet_[0].pos.y = 360.0f;
				bullet_[0].pos.z = -ballelSize;

				//初速(x,yはランダムに、zは空気の圧力で)
				bullet_[0].speed.x = float(rand() % 20 - 10);
				bullet_[0].speed.y = float(rand() % 20 - 10);
				bullet_[0].speed.z = airPower;
				bullet_[0].isShot = true;
				bullet_[0].shotCount = 1;
				if (bullet_[0].isShot == true) {

				}
			}
		}
	}


	if (coolTime_ >= 0) {
		coolTime_--;
	}


	if (keys_[DIK_RETURN] && preKeys_[DIK_RETURN]) {
		bullet_[0].shotCount = 0;
	}



	if (bullet_[0].isShot == true) {

		//isShotがtrueの間は速さを足していく
		bullet_[0].pos.x += bullet_[0].speed.x;
		bullet_[0].pos.y += bullet_[0].speed.y;
		bullet_[0].pos.z += bullet_[0].speed.z;

		//スピードyのみ重力で少しずつ下に行くように
		bullet_[0].speed.y += gravity;

		//摩擦
		float masa = -(bullet_[0].speed.z / 10);
		if (bullet_[0].pos.z < 0) {

			//仮で中心の値を設定
			Vector3 bullelPos = { 640, 360, 0 };
			//ノズル内と弾との当たり判定
			float dis = (bullelPos.x - bullet_[0].pos.x) * (bullelPos.x - bullet_[0].pos.x) + (bullelPos.y - bullet_[0].pos.y) * (bullelPos.y - bullet_[0].pos.y);

			//もしノズル内と弾があたったら
			if (dis >= bullet_[0].size.x + ballelRad) {
				//跳ね返る
				bullet_[0].pos.x *= -1;
				bullet_[0].pos.y *= -1;
				//もしスピードzが1.0fより大きいなら
				if (bullet_[0].speed.z > 1.0f) {
					//少しずつ減少する
					bullet_[0].speed.z -= 0.01f;
				}
				else {
					//そうでなければ1.0fで固定
					bullet_[0].speed.z = 1.0f;
				}
				//摩擦分を反映
				bullet_[0].speed.z += masa;

			}
			for (int j = 0; j < kBulletNum_; j++) {
				//弾同士の当たり判定	
				float disb2b = (bullet_[0].pos.x - bullet_[0].pos.x) * (bullet_[0].pos.x - bullet_[0].pos.x) + (bullet_[0].pos.x - bullet_[0].pos.y) * (bullet_[0].pos.x - bullet_[0].pos.y);
				if (disb2b >= bullet_[0].size.x + bullet_[0].size.x) {
					//もし弾同士であたったら
					//跳ね返る
					bullet_[0].speed.x *= -1;
					bullet_[0].speed.y *= -1;
					//もしスピードzが1.0fより大きいなら
					if (bullet_[0].speed.z > 1.0f) {
						//少しずつ減少する
						bullet_[0].speed.z -= 0.01f;
					}
					else {
						//そうでなければ1.0fで固定
						bullet_[0].speed.z = 1.0f;
					}
					//摩擦分を反映
					bullet_[0].speed.z += masa;
				}
			}
		}
		//もし弾がz20(仮で的の位置)に当たったら
		if (bullet_[0].pos.z > distance) {
			//falseに
			bullet_[0].isShot = false;
		}
	}
	//もしisShotがfalseなら
	if (bullet_[0].isShot == false) {
		//弾痕に代入
		bulletAfter[0].x = bullet_[0].pos.x;
		bulletAfter[0].y = bullet_[0].pos.y;
	}



	ImGui::Begin("Bullet");

	ImGui::Text("pistol");
	ImGui::Text("RIGHT ARROW CHANGE SHOTGUN");
	ImGui::SliderFloat("bullelSize", &ballelSize, 1.0f, 100.0f);
	ImGui::SliderFloat("bullelRad", &ballelRad, 30.0f, 100.0f);
	ImGui::SliderFloat("airPower", &airPower, 1.0f, 100.0f);
	ImGui::SliderFloat("gravity", &gravity, 0.00f, 0.50f);
	ImGui::SliderFloat("distance", &distance, 0.00f, 100.0f);

	ImGui::End();

}

void Bullet::Draw() {
	for (int i = 0; i < kBulletNum_; i++) {
		if (bullet_[i].isShot == true) {
			//弾の描画
			Novice::DrawEllipse(int(bullet_[i].pos.x), int(bullet_[i].pos.y), int(bullet_[i].size.x), int(bullet_[i].size.y), 0.0f, RED, kFillModeSolid);
		}
		if (bullet_[i].isShot == false) {
			if (bullet_[i].shotCount == 1) {
				//弾痕の描画
				Novice::DrawEllipse(int(bulletAfter[i].x), int(bulletAfter[i].y), 3, 3, 0.0f, RED, kFillModeSolid);
			}
		}
	}
}

void Bullet::PistolDraw() {

	if (bullet_[0].isShot == true) {
		Novice::DrawEllipse(int(bullet_[0].pos.x), int(bullet_[0].pos.y), int(bullet_[0].size.x), int(bullet_[0].size.y), 0.0f, RED, kFillModeSolid);
	}
	if (bullet_[0].isShot == false) {
		if (bullet_[0].shotCount == 1) {
			//弾痕の描画
			Novice::DrawEllipse(int(bulletAfter[0].x), int(bulletAfter[0].y), 3, 3, 0.0f, RED, kFillModeSolid);
		}
	}

}