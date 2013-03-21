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


    /** track du robot*/
    enum RobotStats
    {
        TRACK0, TRACK1
    };

//private:
    ShortStory *mShortStory;
    Scene *mScene;
    Entity * mChat;
    Entity* mPersonnage;
	Camera* mCamera;



	Ogre::AnimationState *mPersonnageTomberAnimationState;
	Ogre::AnimationState *mPersonnageWalkAnimationState;
	Ogre::AnimationState *mAnimStateCamera;

    bool mChatActiveBoust;
	bool mPersonnageActiveBoust;

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
	void tomberChat();

	void tomberRegarderCamera();

	void setAnimation();
	void animationFin(const FrameEvent &evt);
	void replay();
};

#endif // ANIMATIONSAUTO_H
