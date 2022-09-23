#ifndef STARTSCENE_HPP
#define STARTSCENE_HPP
#include "IScene.hpp"

class StartScene final : public Engine::IScene {
public:
	explicit StartScene() = default;
	void Initialize() override;
	void BackOnClick(int stage);
	void OnKeyDown(int keyCode);
};

#endif // STARTSCENE_HPP
#pragma once
