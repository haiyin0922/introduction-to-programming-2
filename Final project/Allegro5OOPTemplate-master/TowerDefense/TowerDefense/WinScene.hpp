#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include "IScene.hpp"


class WinScene final : public Engine::IScene {
private:
	int MapId;
	float ticks;
	int scores , good , normal , bad;
	int highest_score;
public:
	explicit WinScene() = default;
	void Initialize() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);

	void ReadScores();
	void ReadHighestScore();
	void WriteHighestScore();
};

#endif // WINSCENE_HPP
