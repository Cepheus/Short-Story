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

//private:
    ShortStory *mShortStory;
    Scene *mScene;
    Entity* mPersonnage;

    //animations du personnage;
    //void personnageAnimation_Death();
    void death1Personnage (const FrameEvent &evt);
    void death2Personnage (const FrameEvent &evt);
    void sideKickPersonnage (const FrameEvent &evt);
    void kickPersonnage (const FrameEvent &evt);
    void idle3Personnage (const FrameEvent &evt);
    void idle2Personnage (const FrameEvent &evt);
    void idle1Personnage (const FrameEvent &evt);
    void stealthPersonnage (const FrameEvent &evt);
    void walkPersonnage (const FrameEvent &evt);
    void setPersonnageAnimation();

	//animations du chat
    void walkCat(const FrameEvent &evt);
    void waitCat (const FrameEvent &evt);
    void sitCat (const FrameEvent & evt);
    void getupCat(const FrameEvent & evt);
};

#endif // ANIMATIONS_H
