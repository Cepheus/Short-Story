#include "Animations.h"

Animations::Animations(ShortStory *shortStory)
{
    mShortStory = shortStory;
    mPersonnage = mShortStory->getSceneManager()->getEntity("Personnage");
    mRobot = mShortStory->getSceneManager()->getEntity("Robot");

    mRobotCurantTrack = 0;

    setRobotAnimations();
}
Animations::~Animations(){}

/******** ROBOT *******/

bool Animations::displayRobot(RobotStats track, const FrameEvent &evt){
    switch (track) {
    case Animations::TRACK0 :
        mRobotTree2DoorAnimationState->setEnabled(true);
        if(!mRobotTree2DoorAnimationState->hasEnded()){
            walkRobot(evt);
            return false;
        }
        else{
            idleRobot(evt);
            return false;
        }
        break;
    default:
        idleRobot(evt);
        break;
    }
}

void Animations::robotAnimation_Tree2Door(){
    Node * robotNode = mRobot->getParentNode();
    //declaration de l'animation
    Ogre::Animation *robotAnimation = mShortStory->getSceneManager()->createAnimation("RobotTree2DoorAnimation", 30); //30 secondes d'annimation

    //mode d'intermolation Translation et rotation
    robotAnimation->setRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);
    robotAnimation->setInterpolationMode(Ogre::Animation::IM_SPLINE);

    //piste n°0
    Ogre::NodeAnimationTrack *track = robotAnimation->createNodeTrack(0, robotNode);
    track->createNodeKeyFrame(0);
    Ogre::Vector3 departTrack0 = mShortStory->getSceneManager()->getSceneNode("TreeNode")->getPosition();
    departTrack0[1] = 0;
    robotNode->setPosition(departTrack0);
    robotNode->rotate(Ogre::Quaternion(Ogre::Degree(-25), Ogre::Vector3::UNIT_Y));
    robotNode->setInitialState();

    //1ere clef
    Ogre::TransformKeyFrame *key1 = track->createNodeKeyFrame(10);
    key1->setRotation(Ogre::Quaternion(Ogre::Degree(-10), Ogre::Vector3::UNIT_Y));
    key1->setTranslate(Ogre::Vector3(500, 0, 400));

    //2ere clef
    Ogre::TransformKeyFrame *key2 = track->createNodeKeyFrame(20);
    key2->setRotation(Ogre::Quaternion(Ogre::Degree(10), Ogre::Vector3::UNIT_Y));
    key2->setTranslate(Ogre::Vector3(1000, 0, 700));

    //2ere clef
    Ogre::TransformKeyFrame *key3 = track->createNodeKeyFrame(30);
    key3->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y));
    key3->setTranslate(Ogre::Vector3(1200, 0, 600));

    mRobotTree2DoorAnimationState = mShortStory->getSceneManager()->createAnimationState("RobotTree2DoorAnimation");
    mRobotTree2DoorAnimationState->setTimePosition(0);
    mRobotTree2DoorAnimationState->setLoop(false);
    mRobotTree2DoorAnimationState->setEnabled(false);
}

void Animations::setRobotAnimations(){
    robotAnimation_Tree2Door();
}

void Animations::walkRobot (const FrameEvent &evt)
{

    mRobotTree2DoorAnimationState->addTime(evt.timeSinceLastFrame);

    mRobot->getAnimationState("Walk")->setEnabled(true);
    mRobot->getAnimationState("Walk")->addTime(evt.timeSinceLastFrame);
}

void Animations::idleRobot (const FrameEvent &evt)
{
    mRobot->getAnimationState("Idle")->setEnabled(true);
    mRobot->getAnimationState("Idle")->addTime(evt.timeSinceLastFrame);
}

void Animations::shootRobot (const FrameEvent &evt)
{
    mRobot->getAnimationState("Shoot")->setEnabled(true);
    mRobot->getAnimationState("Shoot")->addTime(evt.timeSinceLastFrame);
}

void Animations::slumpRobot (const FrameEvent &evt)
{
    mRobot->getAnimationState("Slump")->setEnabled(true);
    mRobot->getAnimationState("Slump")->addTime(evt.timeSinceLastFrame);
}


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
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    mPersonnage->getAnimationState("Stealth")->setEnabled(true);
    mPersonnage->getAnimationState("Stealth")->addTime(evt.timeSinceLastFrame);
}

void Animations::idle1Personnage (const FrameEvent &evt)
{
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    mPersonnage->getAnimationState("Idle1")->setEnabled(true);
    mPersonnage->getAnimationState("Idle1")->addTime(evt.timeSinceLastFrame);
}

void Animations::idle2Personnage (const FrameEvent &evt)
{
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    mPersonnage->getAnimationState("Idle2")->setEnabled(true);
    mPersonnage->getAnimationState("Idle2")->addTime(evt.timeSinceLastFrame);
}

void Animations::idle3Personnage (const FrameEvent &evt)
{
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    mPersonnage->getAnimationState("Idle3")->setEnabled(true);
    mPersonnage->getAnimationState("Idle3")->addTime(evt.timeSinceLastFrame);
}

void Animations::kickPersonnage (const FrameEvent &evt)
{
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    mPersonnage->getAnimationState("Kick")->setEnabled(true);
    mPersonnage->getAnimationState("Kick")->addTime(evt.timeSinceLastFrame);
}

void Animations::sideKickPersonnage (const FrameEvent &evt)
{
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    mPersonnage->getAnimationState("SideKick")->setEnabled(true);
    mPersonnage->getAnimationState("SideKick")->addTime(evt.timeSinceLastFrame);
}

void Animations::death2Personnage (const FrameEvent &evt)
{
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    mPersonnage->getAnimationState("Death2")->setEnabled(true);
    mPersonnage->getAnimationState("Death2")->addTime(evt.timeSinceLastFrame);

}
