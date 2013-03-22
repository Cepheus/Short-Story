#ifndef ANIMATIONSAUTO_H
#define ANIMATIONSAUTO_H

#include "Scene.h"
#include "ShortStory.h"

#include <Ogre.h>
using namespace Ogre;

class AnimationsAuto
{

public:
    AnimationsAuto(ShortStory * shortStory);
    ~AnimationsAuto();

	float x;
	float y;
	float z;
	float height;
	float lengh;
	float jumpLengh;
	float jumpHeight;
	float g;
	float distanceTemp;

	int setFlag;



//private:
    ShortStory *mShortStory;
    Scene *mScene;
    //Entity * mRobot;
    Entity* mPersonnage;
	Camera* mCamera;



	Ogre::AnimationState *mPersonnageTomberAnimationState;
	Ogre::AnimationState *mPersonnageWalkAnimationState;
	Ogre::AnimationState *mAnimStateCamera;

    //bool mRobotActiveBoust;
	bool mPersonnageActiveBoust;

    //animations du robot
    void setRobotTrack(int track);
    //bool displayRobot(RobotStats track, const FrameEvent &evt);
    void robotAnimation_Jump24thParticules();

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



	void tomberPersonnage();
	void tomberRobot();

	void tomberRegarderCamera();

	void setAnimation();
	void setPosition();
	void animationFin(const FrameEvent &evt);
	void replay();
};

#endif // ANIMATIONSAUTO_H
