#pragma once

#include "axmol.h"

class MainScene : public ax::Scene {
    enum class GameState {
        init = 0,
        update,
    };

public:
    bool init() override;
    void update(float delta) override;

private:
    GameState _gameState = GameState::init;
    ax::Label *infoLabel;
};
