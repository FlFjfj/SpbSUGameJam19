//
// Created by hedonistant on 30.03.19.
//

#include "Episode1.h"

void Episode1::init() {

}

void Episode1::enter()  {
    numPieces = 0;
    timeFromStart = 0;
    barCollected = false;
    buttonPos=0;
}

void  Episode1::update() {
    std::cout<<buttonPos<<std::endl;
    timeFromStart += GlobalContext::TICK_DELTA;
    switch (stage) {
        case Stages::Intro: {
            if (timeFromStart > 5){
                stage = Stages::SelectCase;
            }

            break;
        }

        case Stages::SelectCase: {

            break;
        }

        case Stages::HelpToCollect: {
            if (numPieces>=10) {
                GlobalContext::cash+=(numPieces-1)*2 + barCollected ? 100 : 0;
                stage = Stages::Ending;
            }

            break;
        }

        case Stages::RefuseToHelp: {
            //some visual content
            if (timeFromStart > 5) {
                stage = Stages::Ending;
            }

            break;
        }

        case Stages::HandToCops: {
            //some visual content

            GlobalContext::broAvialable[0]=0;
            stage = Stages::Ending;

            break;
        }

        case Stages::CollectBar: {
            if (timeFromStart>5) {
                GlobalContext::broAvialable[1] = 0;
                stage = Stages::HelpToCollect;
            }

            break;
        }

        case Stages::Ending: {

            if (numPieces>=10) {
                GlobalContext::cash+=(numPieces-1)*2 + barCollected ? 100 : 0;
                stage = Stages::Ending;
            }

            break;
        }
    }
}

void Episode1::draw(float complete) {

}

void Episode1::onMouseButton(int button, int action, int mods) {
    if (stage==Stages::HelpToCollect){

    }
}

void Episode1::onKey(int key, int scancode, int action, int mods) {
    if (stage==Stages::SelectCase){
        switch (key){
            case GLFW_KEY_UP: {
                if (action == GLFW_RELEASE){
                    buttonPos-=1;
                    buttonPos = buttonPos<0? 2 : buttonPos;
                }

                break;
            }

            case GLFW_KEY_DOWN: {
                if (action == GLFW_RELEASE){
                    buttonPos+=1;
                    buttonPos = buttonPos>2? 0 : buttonPos;
                }

                break;
            }
        }
    }
}

void Episode1::changeStage(Stages stage1) {
    stage = stage1;
    timeFromStart = 0;
    std::cout<<"Stage: " << (int)stage << std::endl;
}

std::unique_ptr<Scene> createEpisode1() {
    return std::make_unique<Episode1>();
}