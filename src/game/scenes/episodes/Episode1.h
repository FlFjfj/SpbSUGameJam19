//
// Created by hedonistant on 30.03.19.
//

#ifndef GAME_EPISODE1_H
#define GAME_EPISODE1_H


#include <memory>
#include <game/GlobalContext.h>
#include <iostream>
/*
 Player can
    help friend0 to collect scrap metal (HelpToCollect)
    refuse to help (RefuseToHelp)
    hand friend0 to cops and lose him

    if player helps he can
        CollectBar (and other stuff) and lose friend1 (CollectBar) but make more money
        Collect other stuff and keep friend1

 */
enum class Stages {
    Intro,
    SelectCase,
    HelpToCollect,
    RefuseToHelp,
    HandToCops,
    CollectBar,
    Ending
};

class  Episode1 : public Scene {
public:
    void init() override ;
    void enter() override ;
    void update() override ;
    void draw(float complete) override ;
    void onMouseButton(int button, int action, int mods) override;
    void onKey(int key, int scancode, int action, int mods) override;

private:
    float timeFromStart;
    int numPieces;
    bool barCollected;
    Stages stage;
    int buttonPos;
    void changeStage(Stages stage1);

};



std::unique_ptr<Scene> createEpisode1();


#endif //GAME_EPISODE1_H
