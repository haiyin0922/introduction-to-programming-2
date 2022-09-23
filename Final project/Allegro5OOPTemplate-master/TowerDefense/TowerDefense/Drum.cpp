#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>

#include "AudioHelper.hpp"
#include "Drum.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"

PlayScene* Drum::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Drum::OnExplode() {
}
Drum::Drum(std::string img, float x, float y, float radius, float speed, int color, int money) :
	Engine::Sprite(img, x, y), speed(speed), color(color), money(money) {
	CollisionRadius = radius;
}
void Drum::Hit(float damage) {

	speed = 1;
	hit_x = Position.x;

}
void Drum::UpdatePath(const std::vector<std::vector<int>>& mapDistance) {
	
}
void Drum::Update(float deltaTime) {

	if (speed == 1) {
		float x = (870 - hit_x)/ 100;
		Engine::Point sub(5*x , -5);
		Position = Position + sub;
		if (Position.x >= 870) {
			getPlayScene()->EarnMoney(money);
			getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		}
	}
	else {
		Engine::Point sub(13, 0);
		Position = Position - sub;

		if (Position.x <= getPlayScene()->EndGridPoint.x) {
			getPlayScene()-> PlusBad();
			getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		}
	}

	Sprite::Update(deltaTime);
}
void Drum::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}

int Drum::Getcolor() {
	return color;
}