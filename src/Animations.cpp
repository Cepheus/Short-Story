#include "Animations.h"

Animations::Animations(ShortStory *shortStory)
{
    mShortStory = shortStory;
    mPersonnage = mShortStory->getSceneManager()->getEntity("Personnage");
    mRobot = mShortStory->getSceneManager()->getEntity("Robot");

    mRobotActiveBoust = false;

    setRobotAnimations();
}
Animations::~Animations(){}

/******** ROBOT *******/

bool Animations::displayRobot(RobotStats track, const FrameEvent &evt){
    switch (track) {
    case Animations::TRACK0 :
        mRobotTree2DoorAnimationState->setEnabled(true);
        if(!mRobotTree2DoorAnimationState->hasEnded()){
            mRobotTree2DoorAnimationState->addTime(evt.timeSinceLastFrame);
            walkRobot(evt);
            return true;
        }
        else{
            idleRobot(evt);
            return false;
        }
        break;
    case Animations::TRACK1 :
        mRobotJump24thState->setEnabled(true);
        if(!mRobotJump24thState->hasEnded()){
            if(mRobotActiveBoust == false){
                robotAnimation_Jump24thParticules();
                mRobotActiveBoust = true;
            }
            mRobotJump24thState->addTime(evt.timeSinceLastFrame);
            slumpRobot(evt);
            return true;
        }
        else{
            robotAnimation_Jump24thParticules();
            idleRobot(evt);
            mRobotJump24thState->setEnabled(false);
            return false;
        }
        break;
    case Animations::TRACK2 :

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

    //2eme clef
    Ogre::TransformKeyFrame *key3 = track->createNodeKeyFrame(30);
    key3->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y));
    key3->setTranslate(Ogre::Vector3(1200, 0, 600));

    mRobotTree2DoorAnimationState = mShortStory->getSceneManager()->createAnimationState("RobotTree2DoorAnimation");
    mRobotTree2DoorAnimationState->setTimePosition(0);
    mRobotTree2DoorAnimationState->setLoop(false);
    mRobotTree2DoorAnimationState->setEnabled(false);
}

void Animations::robotAnimation_Jump24thParticules(){
    if(!mRobotActiveBoust){
        mShortStory->getSceneManager()->getParticleSystem("fire1Robot")->setVisible(true);
        mShortStory->getSceneManager()->getParticleSystem("fire2Robot")->setVisible(true);
    }
    else
    {
        mShortStory->getSceneManager()->getParticleSystem("fire1Robot")->setVisible(false);
        mShortStory->getSceneManager()->getParticleSystem("fire1Robot")->setVisible(false);
    }
}

void Animations::robotAnimation_Jump24th(){
    SceneNode * robotNode = mShortStory->getSceneManager()->getSceneNode("RobotNode");
    //declaration de l'animation
    Ogre::Animation *robotAnimation = mShortStory->getSceneManager()->createAnimation("RobotJump24thAnimation", 10); //30 secondes d'annimation

    //mode d'intermolation Translation et rotation
    robotAnimation->setRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);
    robotAnimation->setInterpolationMode(Ogre::Animation::IM_SPLINE);

    //piste n°0
    Ogre::NodeAnimationTrack *track = robotAnimation->createNodeTrack(0, robotNode);
    track->createNodeKeyFrame(0);
    robotNode->setInitialState();

    //1ere clef
    Ogre::TransformKeyFrame *key1 = track->createNodeKeyFrame(7);
    key1->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));
    key1->setTranslate(Ogre::Vector3(0, 900, -150));

    //2eme clef
    Ogre::TransformKeyFrame *key2 = track->createNodeKeyFrame(10);
    key2->setRotation(Ogre::Quaternion(Ogre::Degree(10), Ogre::Vector3::UNIT_Y));
    key2->setTranslate(Ogre::Vector3(0, 700, -300));

    mRobotJump24thState = mShortStory->getSceneManager()->createAnimationState("RobotJump24thAnimation");
    mRobotJump24thState->setTimePosition(0);
    mRobotJump24thState->setLoop(false);
    mRobotJump24thState->setEnabled(false);
}

//void Animations::personnageAnimation_Death(){
//    Ogre::TransformKeyFrame *key;
//    SceneNode * robotNode = mShortStory->getSceneManager()->getSceneNode("RobotNode");
//    //declaration de l'animation
//    Ogre::Animation *robotAnimation = mShortStory->getSceneManager()->createAnimation("RobotDeathAnimation", 11); //30 secondes d'annimation

//    //mode d'intermolation Translation et rotation
//    robotAnimation->setRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);
//    robotAnimation->setInterpolationMode(Ogre::Animation::IM_SPLINE);

//    //piste n°0
//    Ogre::NodeAnimationTrack *track = robotAnimation->createNodeTrack(0, robotNode);
//    track->createNodeKeyFrame(0);
//    robotNode->setInitialState();


//    key = track->createNodeKeyFrame(0.01);
//    key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));
//    key->setTranslate(Ogre::Vector3(100, 150, -200));

//    //1ere clef piste 0
//    key = track->createNodeKeyFrame(5);
//    key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));
//    key->setTranslate(Ogre::Vector3(100, 150, -200));

//    //2eme clef piste 0
//    key = track->createNodeKeyFrame(10);
//    key->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y));
//    key->setTranslate(Ogre::Vector3(50, 150, -300));

//    //3eme clef piste 0
//    key = track->createNodeKeyFrame(10);
//    key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));
//    key->setTranslate(Ogre::Vector3(0, 150, -400));

//    mRobotDeathState = mShortStory->getSceneManager()->createAnimationState("RobotDeathAnimation");
//    mRobotDeathState->setTimePosition(0);
//    mRobotDeathState->setLoop(false);
//    mRobotDeathState->setEnabled(false);
//}

void Animations::setRobotAnimations(){

    //iterateurs d'animation
    AnimationState *mAnimState;
    AnimationStateSet *set = mRobot->getAllAnimationStates();
    AnimationStateIterator it = set->getAnimationStateIterator();

    //load animation
    while (it.hasMoreElements())
    {
        mAnimState = it.getNext();
        mAnimState->setEnabled(false);
    }

    SceneNode * robotNode = mShortStory->getSceneManager()->getSceneNode("RobotNode");

    ParticleSystem * fire1 = mShortStory->getSceneManager()->createParticleSystem("fire1Robot", "Smoke");
    ParticleSystem * fire2 = mShortStory->getSceneManager()->createParticleSystem("fire2Robot", "Smoke");

    mRobot->attachObjectToBone("Joint8", fire1);
    mRobot->attachObjectToBone("Joint4", fire2);

    fire1->setVisible(false);
    fire2->setVisible(false);

    robotAnimation_Tree2Door();
    robotAnimation_Jump24th();
}

void Animations::walkRobot (const FrameEvent &evt)
{
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
