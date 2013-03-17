#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "Scene.h"
#include "ShortStory.h"

#include <Ogre.h>
using namespace Ogre;

class Animations
{
public:
    Animations(ShortStory * shortStory);
    ~Animations();

    /** track du robot*/
    enum RobotStats
    {
        TRACK0, TRACK1
    };

//private:
    ShortStory *mShortStory;
    Scene *mScene;
    Entity * mRobot;
    Entity* mPersonnage;

    Ogre::AnimationState *mRobotTree2DoorAnimationState;
    Ogre::AnimationState *mRobotJump24thState;
    bool mRobotActiveBoust;

    //animations du robot
    void setRobotTrack(int track);
    bool displayRobot(RobotStats track, const FrameEvent &evt);
    void robotAnimation_Jump24thParticules();

    void setRobotAnimations();
    void robotAnimation_Tree2Door();
    void robotAnimation_Jump24th();
    void walkRobot(const FrameEvent &evt);
    void idleRobot (const FrameEvent &evt);
    void shootRobot (const FrameEvent &evt);
    void slumpRobot (const FrameEvent &evt);

    //animations du personnage;
    void death2Personnage (const FrameEvent &evt);
    void sideKickPersonnage (const FrameEvent &evt);
    void kickPersonnage (const FrameEvent &evt);
    void idle3Personnage (const FrameEvent &evt);
    void idle2Personnage (const FrameEvent &evt);
    void idle1Personnage (const FrameEvent &evt);
    void stealthPersonnage (const FrameEvent &evt);
    void walkPersonnage (const FrameEvent &evt);
    void setPersonnageAnimation();
};

#endif // ANIMATIONS_H
