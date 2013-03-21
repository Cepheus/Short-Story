#include "Animations.h"

Animations::Animations(ShortStory *shortStory)
{
    mShortStory = shortStory;
    mPersonnage = mShortStory->getSceneManager()->getEntity("Personnage");
}
Animations::~Animations(){}

/******** PERSONNAGE *******/
void Animations::setPersonnageAnimation(){

    AnimationState *mAnimState;
    AnimationStateSet *set = mPersonnage->getAllAnimationStates();
    AnimationStateIterator it = set->getAnimationStateIterator();

    //load animation
    while (it.hasMoreElements())
    {
        mAnimState = it.getNext();
        mAnimState->setEnabled(false);
    }
}

void Animations::walkPersonnage (const FrameEvent &evt)
{
    mPersonnage->getAnimationState("Walk")->setEnabled(true);
    mPersonnage->getAnimationState("Walk")->addTime(evt.timeSinceLastFrame);
}

void Animations::stealthPersonnage (const FrameEvent &evt)
{
    mPersonnage->getAnimationState("Stealth")->setEnabled(true);
    mPersonnage->getAnimationState("Stealth")->addTime(evt.timeSinceLastFrame);
}

void Animations::idle1Personnage (const FrameEvent &evt)
{
    mPersonnage->getAnimationState("Idle1")->setEnabled(true);
    mPersonnage->getAnimationState("Idle1")->addTime(evt.timeSinceLastFrame);
}

void Animations::idle2Personnage (const FrameEvent &evt)
{
    mPersonnage->getAnimationState("Idle2")->setEnabled(true);
    mPersonnage->getAnimationState("Idle2")->addTime(evt.timeSinceLastFrame);
}

void Animations::idle3Personnage (const FrameEvent &evt)
{
    mPersonnage->getAnimationState("Idle3")->setEnabled(true);
    mPersonnage->getAnimationState("Idle3")->addTime(evt.timeSinceLastFrame);
}

void Animations::kickPersonnage (const FrameEvent &evt)
{
    mPersonnage->getAnimationState("Kick")->setEnabled(true);
    mPersonnage->getAnimationState("Kick")->addTime(evt.timeSinceLastFrame);
}

void Animations::sideKickPersonnage (const FrameEvent &evt)
{
    mPersonnage->getAnimationState("SideKick")->setEnabled(true);
    mPersonnage->getAnimationState("SideKick")->addTime(evt.timeSinceLastFrame);
}

void Animations::death1Personnage (const FrameEvent &evt)
{
    mPersonnage->getAnimationState("Death2")->setEnabled(true);
    mPersonnage->getAnimationState("Death2")->addTime(evt.timeSinceLastFrame);
}

void Animations::death2Personnage (const FrameEvent &evt)
{
    mPersonnage->getAnimationState("Death2")->setEnabled(true);
    mPersonnage->getAnimationState("Death2")->addTime(evt.timeSinceLastFrame);
}


/** Chat **/

void Animations::walkCat (const FrameEvent &evt){
    Entity* chat = mShortStory->getSceneManager()->getEntity("Chat");
    chat->getAnimationState("marche")->setEnabled(true);
    chat->getAnimationState("marche")->addTime(evt.timeSinceLastFrame);
}

void Animations::waitCat (const FrameEvent  &evt){
    Entity* chat = mShortStory->getSceneManager()->getEntity("Chat");
    chat->getAnimationState("attend")->setEnabled(true);
    chat->getAnimationState("attend")->addTime(evt.timeSinceLastFrame);
}

void Animations::sitCat (const FrameEvent & evt){
    Entity* chat = mShortStory->getSceneManager()->getEntity("Chat");
    chat->getAnimationState("assoir")->setEnabled(true);
    chat->getAnimationState("assoir")->addTime(evt.timeSinceLastFrame);
}

void Animations::getupCat(const FrameEvent & evt){
    Entity* chat = mShortStory->getSceneManager()->getEntity("Chat");
    chat->getAnimationState("debout")->setEnabled(true);
    chat->getAnimationState("debout")->addTime(evt.timeSinceLastFrame);

}
