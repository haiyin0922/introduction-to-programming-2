#include <functional>
#include <string>
#include <fstream>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "WinScene.hpp"

void WinScene::Initialize() {
	AudioHelper::PlayAudio("opening.wav");

	Engine::ImageButton* enter;
	ReadScores();
	ReadHighestScore();

	if (scores > highest_score) {
		highest_score = scores;
		WriteHighestScore();
	}

	enter = new Engine::ImageButton("win/end.png", "win/end.png", 0, 0, 1200, 604);
	enter->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(enter);
	AddNewObject(new Engine::Label(std::to_string(scores), "pirulen.ttf", 30, 664, 174, 255, 255, 255, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label(std::to_string(good), "pirulen.ttf", 25, 925, 142, 0, 0, 0, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label(std::to_string(normal), "pirulen.ttf", 25, 925, 175, 0, 0, 0, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label(std::to_string(bad), "pirulen.ttf", 25, 925, 208, 0, 0, 0, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label("HIGHEST SCORE", "pirulen.ttf", 40, 600, 430, 0, 0, 0, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label(std::to_string(highest_score), "pirulen.ttf", 40, 600, 490, 0, 0, 0, 255, 0.5, 0.5));

}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	/*if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		AudioHelper::PlayBGM("happy.ogg");
	}*/
}
void WinScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("start");
}

void WinScene::ReadScores() {

	std::string filename1 = std::string("resources/map_id") + ".txt";
	std::ifstream fin1(filename1);
	fin1 >> MapId;
	fin1.close();

	std::string filename2 = std::string("resources/scores_map") + std::to_string(MapId) + ".txt";
	// Read enemy file.

	std::ifstream fin2(filename2);
	fin2 >> scores;
	fin2 >> good;
	fin2 >> normal;
	fin2 >> bad;
	
	fin2.close();
}

void WinScene::ReadHighestScore() {

	std::string filename1 = std::string("resources/map_id") + ".txt";
	std::ifstream fin1(filename1);
	fin1 >> MapId;
	fin1.close();

	std::string filename2 = std::string("resources/highest_score_map") + std::to_string(MapId) + ".txt";
	// Read enemy file.

	std::ifstream fin2(filename2);
	fin2 >> highest_score;

	fin2.close();

}

void WinScene::WriteHighestScore() {

	std::string filename1 = std::string("resources/map_id") + ".txt";
	std::ifstream fin1(filename1);
	fin1 >> MapId;
	fin1.close();

	std::string filename2 = std::string("resources/highest_score_map") + std::to_string(MapId) + ".txt";
	// Write enemy file.

	std::ofstream fout2(filename2);
	fout2 << highest_score << " ";
	fout2.close();
}