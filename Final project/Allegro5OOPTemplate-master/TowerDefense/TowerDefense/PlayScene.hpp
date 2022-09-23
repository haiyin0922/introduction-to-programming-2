#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <list>
#include <utility>
#include <vector>

#include "IScene.hpp"
#include "Point.hpp"

class Turret;
namespace Engine {
	class Group;
	class Image;
	class Label;
}  // namespace Engine

class PlayScene final : public Engine::IScene {
private:
	enum TileType {
		TILE_DIRT,
		TILE_FLOOR,
		TILE_OCCUPIED,
	};
protected:
	int lives;
	int money;
	int SpeedMult;
	int count;
	int good;
	int normal;
	int bad;
public:
	static bool DebugMode;
	static const std::vector<Engine::Point> directions;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const Engine::Point SpawnGridPoint;
	static const Engine::Point EndGridPoint;
	static const std::vector<int> code;
	int MapId;
	float ticks;
	// Map tiles.

	Group* TileMapGroup;
	Group* EnemyGroup;
	Group* DrumGroup;
	Group* FaceGroup;


	explicit PlayScene() = default;
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	
	void changeDrum(int type);
	void ReadMap();
	void Hit(int color);
	int GetMoney() const;
	void EarnMoney(int money);
	void PlusBad();

	std::list<std::pair<int, float>> enemyWaveData;
	void ReadEnemyWave();

	void ConstructUI();
	Group* UIGroup;
	Engine::Label* UIMoney;


};
#endif // PLAYSCENE_HPP
