#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Drum : public Engine::Sprite {
protected:
	std::vector<Engine::Point> path;
	float speed;
	int color;
	int money;
	float hit_x;
	PlayScene* getPlayScene();
	virtual void OnExplode();
public:
	Drum(std::string img, float x, float y, float radius, float speed, int color, int money);
	void Hit(float damage);
	void UpdatePath(const std::vector<std::vector<int>>& mapDistance);
	void Update(float deltaTime) override;
	void Draw() const override;
	int Getcolor();
};
#endif // ENEMY_HPP