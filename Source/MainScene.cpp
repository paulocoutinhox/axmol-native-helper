#include "MainScene.h"
#include "common/PlatformHelperConfig.hpp"
#include "ui/UIButton.h"

using namespace ax;
using namespace ax::ui;

// on "init" you need to initialize your instance
bool MainScene::init() {
    // super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    float padding = 40.0f;
    float currentY = safeOrigin.y + safeArea.size.height;

    // title label
    auto titleLabel = Label::createWithTTF("Native Helper", "fonts/Marker Felt.ttf", 50);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, currentY - titleLabel->getContentSize().height / 2));
    addChild(titleLabel);

    currentY -= titleLabel->getContentSize().height + (padding * 2);

    // customer id
    auto btCustomerId = Button::create();
    btCustomerId->setTitleText("> Get Customer Id");
    btCustomerId->setTitleFontName("fonts/Marker Felt.ttf");
    btCustomerId->setTitleFontSize(38);
    btCustomerId->setPosition(Vec2(origin.x + visibleSize.width / 2, currentY - btCustomerId->getContentSize().height / 2));
    btCustomerId->addClickEventListener([&](Object *sender) {
        infoLabel->setString("Loading...");

        PlatformHelper::shared()->performAction("get-customer-id", "", [this](std::string result) {
            ax::Director::getInstance()->getScheduler()->runOnAxmolThread([=, this]() {
                infoLabel->setString("Response:\n\n" + result);
            });
        });
    });
    addChild(btCustomerId);

    currentY -= btCustomerId->getContentSize().height + padding;

    // task long
    auto btExecuteTaskLong = Button::create();
    btExecuteTaskLong->setTitleText("> Execute Task Long");
    btExecuteTaskLong->setTitleFontName("fonts/Marker Felt.ttf");
    btExecuteTaskLong->setTitleFontSize(38);
    btExecuteTaskLong->setPosition(Vec2(origin.x + visibleSize.width / 2, currentY - btExecuteTaskLong->getContentSize().height / 2));
    btExecuteTaskLong->addClickEventListener([&](Object *sender) {
        infoLabel->setString("Loading...");

        PlatformHelper::shared()->performAction("start-task-long", "", [this](std::string result) {
            ax::Director::getInstance()->getScheduler()->runOnAxmolThread([=, this]() {
                infoLabel->setString("Response:\n\n" + result);
            });
        });
    });
    addChild(btExecuteTaskLong);

    currentY -= btCustomerId->getContentSize().height + padding;

    // alert
    auto btShowAlert = Button::create();
    btShowAlert->setTitleText("> Show Alert");
    btShowAlert->setTitleFontName("fonts/Marker Felt.ttf");
    btShowAlert->setTitleFontSize(38);
    btShowAlert->setPosition(Vec2(origin.x + visibleSize.width / 2, currentY - btShowAlert->getContentSize().height / 2));
    btShowAlert->addClickEventListener([&](Object *sender) {
        infoLabel->setString("Loading...");

        std::string jsonString = R"({"message": "My alert message from JSON"})";

        PlatformHelper::shared()->performAction("show-alert", jsonString, [this](std::string result) {
            ax::Director::getInstance()->getScheduler()->runOnAxmolThread([=, this]() {
                infoLabel->setString("Response:\n\n" + result);
            });
        });
    });
    addChild(btShowAlert);

    currentY -= btShowAlert->getContentSize().height + padding;

    // chain action
    auto btChainAction = Button::create();
    btChainAction->setTitleText("> Chain Action");
    btChainAction->setTitleFontName("fonts/Marker Felt.ttf");
    btChainAction->setTitleFontSize(38);
    btChainAction->setPosition(Vec2(origin.x + visibleSize.width / 2, currentY - btChainAction->getContentSize().height / 2));
    btChainAction->addClickEventListener([&](Object *sender) {
        infoLabel->setString("Loading...");

        std::string jsonString = R"({"step1": true})";

        PlatformHelper::shared()->performAction("chain-step1", jsonString, [this](std::string result) {
            ax::Director::getInstance()->getScheduler()->runOnAxmolThread([=, this]() {
                infoLabel->setString("Response Chain Step 1:\n\n" + result);

                infoLabel->setString("Loading step 2...");

                std::string jsonString = R"({"step2": true})";

                PlatformHelper::shared()->performAction("chain-step2", jsonString, [this](std::string result) {
                    ax::Director::getInstance()->getScheduler()->runOnAxmolThread([=, this]() {
                        infoLabel->setString("Response Chain Step 2:\n\n" + result);
                    });
                });
            });
        });
    });
    addChild(btChainAction);

    currentY -= btChainAction->getContentSize().height + (padding * 2);

    // info label
    infoLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 28);
    infoLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, currentY - infoLabel->getContentSize().height / 2));
    infoLabel->setMaxLineWidth(visibleSize.width - 2 * padding);
    infoLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    infoLabel->setAnchorPoint(Vec2(0.5, 1.0));
    infoLabel->setString("Press Button Above");
    addChild(infoLabel);

    // schedule update
    scheduleUpdate();

    return true;
}

void MainScene::update(float delta) {
    switch (_gameState) {
    case GameState::init: {
        _gameState = GameState::update;
        break;
    }

    case GameState::update: {
        // custom code
        break;
    }
    }
}
