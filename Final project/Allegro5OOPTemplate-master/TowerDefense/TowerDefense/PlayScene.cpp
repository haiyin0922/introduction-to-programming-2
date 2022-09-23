#include <allegro5/allegro.h>
#include <cmath>
#include <fstream>
#include <functional>
#include <queue>
#include <string>
#include <memory>
#include <string>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "Image.hpp"
#include "Label.hpp"
#include "PlayScene.hpp"
#include "Sprite.hpp"

#include "Drum.hpp"
#include "Drum_small_red.hpp"
#include "Drum_small_blue.hpp"
#include "Drum_big_red.hpp"
#include "Drum_big_blue.hpp"

#include <stdlib.h> 
#include <time.h>  



bool PlayScene::DebugMode = false;
const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 20, PlayScene::MapHeight = 13;
const int PlayScene::BlockSize = 64;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(170, 220);
const std::vector<int> PlayScene::code = { ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN,
									ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT,
									ALLEGRO_KEY_B, ALLEGRO_KEY_A, ALLEGRO_KEYMOD_SHIFT, ALLEGRO_KEY_ENTER };


void PlayScene::Initialize() {
	AudioHelper::PlayAudio("don.wav");

	ticks = 0;
	lives = 0;
	money = 0;
	SpeedMult = 1;
	count = 0;

	good = 0;
	normal = 0;
	bad = 0;

	// Add groups from bottom to top.
	AddNewObject(TileMapGroup = new Group());
	AddNewObject(EnemyGroup = new Group());
	AddNewControlObject(UIGroup = new Group());
	AddNewObject(DrumGroup = new Group());
	AddNewObject(FaceGroup = new Group());

	ReadMap();
	ReadEnemyWave();
	ConstructUI();


	
	// Should support buttons.
	

	if (MapId == 1) AudioHelper::PlayAudio("sakura.wav");
	else if (MapId == 2) AudioHelper::PlayAudio("sky.wav");
	else if (MapId == 3) AudioHelper::PlayAudio("babyshark.wav");
	//AudioHelper::PlayBGM("play.ogg");
}
void PlayScene::Update(float deltaTime) {
	// If we use deltaTime directly, then we might have Bullet-through-paper problem.
	// Reference: Bullet-Through-Paper
	for (int i = 0; i < SpeedMult; i++) {
		IScene::Update(deltaTime);
		// Check if we should create new enemy.

		ticks += deltaTime;


		count = count+1;
		lives = lives + 1;

		int rand_num = rand();

		if (count == 10) {
			DrumGroup->Clear();
		}

		if (lives == 100) {
			DrumGroup->AddNewObject(new Engine::Image("play/face2.png", 115, 40, 85, 100));
		}
		else if (lives == 200) {
			DrumGroup->AddNewObject(new Engine::Image("play/face1.png", 115, 40, 85, 100));
		}
		else if (lives == 300) {
			lives = 0;
			DrumGroup->Clear();
		}



		if (enemyWaveData.empty()) {

			std::string filename1 = std::string("resources/map_id") + ".txt";
			std::ofstream fout1(filename1);
			fout1 << MapId << " ";
			fout1.close();

			std::string filename2 = std::string("resources/scores_map") + std::to_string(MapId) + ".txt";
			// Write enemy file.

			std::ofstream fout2(filename2);
			fout2 << money << " ";
			fout2 << good << " ";
			fout2 << normal << " ";
			fout2 << bad << " ";
			fout2.close();
			Engine::GameEngine::GetInstance().ChangeScene("win");
			continue;
		}

		auto current = enemyWaveData.front();
		
		if (ticks < current.second)
			continue;
		ticks -= current.second;
		enemyWaveData.pop_front();

		Drum* enemy;

		switch (current.first) {
		case 1:
			EnemyGroup->AddNewObject(enemy = new Drum_small_red(1200, 220));
			enemy->Update(ticks);
			break;
		case 2:
			EnemyGroup->AddNewObject(enemy = new Drum_small_blue(1200, 220));
			enemy->Update(ticks);
			break;
		case 3:
			EnemyGroup->AddNewObject(enemy = new Drum_big_red(1200, 220));
			enemy->Update(ticks);
			break;
		case 4:
			EnemyGroup->AddNewObject(enemy = new Drum_big_blue(1200, 220));
			enemy->Update(ticks);
			break;
		default:
			continue;
		}
	}
}


void PlayScene::Draw() const{
	IScene::Draw();
}

void PlayScene::OnMouseDown(int button, int mx, int my) {

}
void PlayScene::OnMouseMove(int mx, int my) {

}
void PlayScene::OnMouseUp(int button, int mx, int my) {

}
void PlayScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);

	if (keyCode == ALLEGRO_KEY_F || keyCode == ALLEGRO_KEY_J) {
		AudioHelper::PlayAudio("don.wav");
		Hit(1);
		if (keyCode == ALLEGRO_KEY_F) changeDrum(1);
		if (keyCode == ALLEGRO_KEY_J) changeDrum(2);
	}
	if (keyCode == ALLEGRO_KEY_D || keyCode == ALLEGRO_KEY_K) {
		AudioHelper::PlayAudio("ka.wav");
		Hit(2);
		if (keyCode == ALLEGRO_KEY_D) changeDrum(3);
		if (keyCode == ALLEGRO_KEY_K) changeDrum(4);
	}

}

void PlayScene::changeDrum(int type) {
	count = 0;
	if (type == 1) {
		DrumGroup->AddNewObject(new Engine::Image("play/F.png", 139, 160, 111, 115));
	}
	else if (type == 2) {
		DrumGroup->AddNewObject(new Engine::Image("play/J.png", 140, 156, 111, 117));
	}
	else if (type == 3) {
		DrumGroup->AddNewObject(new Engine::Image("play/D.png", 138, 155, 113, 121));
	}
	else if (type == 4) {
		DrumGroup->AddNewObject(new Engine::Image("play/K.png", 137, 156, 113, 119));
	}
}

void PlayScene::ReadMap() {

	if (MapId == 1) TileMapGroup->AddNewObject(new Engine::Image("play/sakura.png", 0, 0, 1200, 604));
	else if (MapId == 2) TileMapGroup->AddNewObject(new Engine::Image("play/sky.png", 0, 0, 1200, 604));
	else if (MapId == 3) TileMapGroup->AddNewObject(new Engine::Image("play/babyshark.png", 0, 0, 1200, 604));

}


void PlayScene::Hit(int color){
	
	//auto it = EnemyGroup->GetObjects();
	//Drum* enemy = dynamic_cast<Drum*>(it.front());

	for (auto& it : EnemyGroup->GetObjects()) {
		Drum* enemy = dynamic_cast<Drum*>(it);
		if (enemy->Position.x >= 285 && enemy->Position.x <= 355 && color == enemy->Getcolor()) {
			if (enemy->Position.x >= 310 && enemy->Position.x <= 340) {
				good++;
				EarnMoney(20);
				enemy->Hit(0);
			}
			else {
				normal++;
				enemy->Hit(0);
			}
			return;
		}
	}

}

int PlayScene::GetMoney() const {
	return money;
}
void PlayScene::EarnMoney(int money) {
	this->money += money;
	UIMoney->Text = std::string("score ") + std::to_string(this->money);
}

void PlayScene::ReadEnemyWave() {
	std::string filename = std::string("resources/enemy") + std::to_string(MapId) + ".txt";
	// Read enemy file.
	float type, wait, repeat;
	enemyWaveData.clear();
	std::ifstream fin(filename);
	while (fin >> type && fin >> wait && fin >> repeat) {
		for (int i = 0; i < repeat; i++)
			enemyWaveData.emplace_back(type, wait);
	}
	fin.close();
}

void PlayScene::ConstructUI() {

	// Text
	UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("score ") + std::to_string(money), "pirulen.ttf", 30, 870, 120, 255, 255, 255));

}

void PlayScene::PlusBad() {
	bad++;
}