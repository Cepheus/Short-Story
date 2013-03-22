#include "AnimationsAuto.h"

AnimationsAuto::AnimationsAuto (ShortStory *shortStory)
{
	mShortStory = shortStory;
	mPersonnageTomberAnimationState = 0;
	mPersonnage = mShortStory->getSceneManager()->getEntity("Personnage");
	// mRobot = mShortStory->getSceneManager()->getEntity("Personnage");

	//mRobotActiveBoust = false;
	//mPersonnageActiveBoust = false;

	mCamera = mShortStory->getCamera();
	setFlag = 0;
	x = 140.0;
	y = 960.0;
	z = -600.0;
	height = 850.0;
	lengh = 350;
	jumpLengh = 100;
	jumpHeight = 49;
	g = 98;
	distanceTemp = 4;
	y = height;

}
AnimationsAuto::~AnimationsAuto ()
{
}

/******** PERSONNAGE *******/

void AnimationsAuto::walkPersonnage (const FrameEvent &evt)
{
	mPersonnage->getAnimationState("Walk")->setEnabled(true);
	mPersonnage->getAnimationState("Walk")->addTime(evt.timeSinceLastFrame);
}

void AnimationsAuto::stealthPersonnage (const FrameEvent &evt)
{
	mPersonnage->getAnimationState("Stealth")->setEnabled(true);
	mPersonnage->getAnimationState("Stealth")->addTime(evt.timeSinceLastFrame);
}

void AnimationsAuto::idle1Personnage (const FrameEvent &evt)
{
	mPersonnage->getAnimationState("Idle1")->setEnabled(true);
	mPersonnage->getAnimationState("Idle1")->addTime(evt.timeSinceLastFrame);
}

void AnimationsAuto::idle2Personnage (const FrameEvent &evt)
{
	mPersonnage->getAnimationState("Idle2")->setEnabled(true);
	mPersonnage->getAnimationState("Idle2")->addTime(evt.timeSinceLastFrame);
}

void AnimationsAuto::idle3Personnage (const FrameEvent &evt)
{
	mPersonnage->getAnimationState("Idle3")->setEnabled(true);
	mPersonnage->getAnimationState("Idle3")->addTime(evt.timeSinceLastFrame);
}

void AnimationsAuto::kickPersonnage (const FrameEvent &evt)
{
	mPersonnage->getAnimationState("Kick")->setEnabled(true);
	mPersonnage->getAnimationState("Kick")->addTime(evt.timeSinceLastFrame);
}

void AnimationsAuto::sideKickPersonnage (const FrameEvent &evt)
{
	mPersonnage->getAnimationState("SideKick")->setEnabled(true);
	mPersonnage->getAnimationState("SideKick")->addTime(evt.timeSinceLastFrame);
}

void AnimationsAuto::death2Personnage (const FrameEvent &evt)
{
	mPersonnage->getAnimationState("Death2")->setEnabled(true);
	mPersonnage->getAnimationState("Death2")->addTime(evt.timeSinceLastFrame);

}

void AnimationsAuto::tomberPersonnage ()
{
	//mCamera->getParentNode();
	//Entity* mPersonnage = mShortStory->getSceneManager()->getEntity("Personnage");

	SceneNode * personnageNode = mPersonnage->getParentSceneNode();
	//personnageNode->setPosition(Vector3(-800,0,500));
	//personnageNode->translate(Vector3(-100,0,500));
	//personnageNode->resetToInitialState();
	//personnageNode->setPosition(-100, 0, 500);
	Ogre::Animation *personnageAnimation = mShortStory->getSceneManager()->createAnimation("PersonnageTomberAnimation",
	        20); //30 secondes d'annimation
	personnageAnimation->setRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);
	personnageAnimation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	//personnageNode->setPosition(Ogre::Vector3(x, y, z));
	//personnageNode->yaw( Degree( -90 ));
	//piste n°0
	//personnageNode->setInitialState();
	//personnageNode->setPosition(Ogre::Vector3(x, y, z));
	Ogre::NodeAnimationTrack *track = personnageAnimation->createNodeTrack(0, personnageNode);
	track->createNodeKeyFrame(0);

	//personnageNode->rotate(Ogre::Quaternion(Ogre::Degree(-25), Ogre::Vector3::UNIT_Y));
	//personnageNode->setInitialState();
	//x=x-100;
	//y=y;
	//z=z+500;
	//1ere clef
	Ogre::TransformKeyFrame *key = track->createNodeKeyFrame(1);
	key->setTranslate(Ogre::Vector3(x, y, z));

	//2ere clef
	key = track->createNodeKeyFrame(6);
	key->setTranslate(Ogre::Vector3(x - lengh, y, z));
	//3ere clef
	key = track->createNodeKeyFrame(8);
	key->setTranslate(Ogre::Vector3(x - lengh, y, z));
	//4ere clef
	key = track->createNodeKeyFrame(8.8);
	key->setTranslate(Ogre::Vector3(x - lengh - jumpLengh / 2.0 + distanceTemp, y + jumpHeight - distanceTemp, z));
	//5ere clef
	key = track->createNodeKeyFrame(9);
	key->setTranslate(Ogre::Vector3(x - lengh - jumpLengh / 2.0, y + jumpHeight, z));
	//6ere clef
	key = track->createNodeKeyFrame(9.2);
	key->setTranslate(Ogre::Vector3(x - lengh - jumpLengh / 2.0 - distanceTemp, y + jumpHeight - distanceTemp, z));
	//7ere clef
	key = track->createNodeKeyFrame(10);
	key->setTranslate(Ogre::Vector3(x - lengh - jumpLengh, y, z));

	int time = 2;
	for (time = 2; time <= 4; time++)
	{
		// 6+i ere clef
		key = track->createNodeKeyFrame(9 + time);
		if (y - g / 2 * (time * time) > 0)
		{
			key->setTranslate(Ogre::Vector3(x - lengh - jumpLengh, y - g / 2 * (time * time), z));
		}
		else
		{
			key->setTranslate(Ogre::Vector3(x - lengh - jumpLengh, 0, z));
		}

		if (time <= 3)
		{
			key->setRotation(Ogre::Quaternion(Ogre::Degree(90 / 2 * (time - 1)), Ogre::Vector3::UNIT_Z));
		}
		else
		{
			key->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Z));
		}
	}
	//11ere clef
	key = track->createNodeKeyFrame(14.165);
	key->setTranslate(Ogre::Vector3(x - lengh - jumpLengh, 0, z));
	key->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Z));

	//12ere clef
	key = track->createNodeKeyFrame(15);
	key->setTranslate(Ogre::Vector3(x - lengh - jumpLengh, 0, z));
	key->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Z));

	//13ere clef
	key = track->createNodeKeyFrame(20);
	key->setTranslate(Ogre::Vector3(x - lengh - jumpLengh, 0, z));
	key->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Z));

	mPersonnageTomberAnimationState = mShortStory->getSceneManager()->createAnimationState("PersonnageTomberAnimation");
	mPersonnageTomberAnimationState->setTimePosition(0);
	mPersonnageTomberAnimationState->setLoop(false);
	mPersonnageTomberAnimationState->setEnabled(false);

}

void AnimationsAuto::animationFin (const FrameEvent &evt)
{

	mPersonnageTomberAnimationState->setEnabled(true);
	if (!mPersonnageTomberAnimationState->hasEnded())
	{

		mPersonnageTomberAnimationState->addTime(evt.timeSinceLastFrame);
	}

	mAnimStateCamera->setEnabled(true);
	if (!mAnimStateCamera->hasEnded())
	{
		mAnimStateCamera->addTime(evt.timeSinceLastFrame);
	}
}
void AnimationsAuto::replay ()
{
	setPosition();
	mPersonnageTomberAnimationState->setTimePosition(0);
	mAnimStateCamera->setTimePosition(0);
}

void AnimationsAuto::setPosition ()
{
	// on place le perso
	Node *persNode = mPersonnage->getParentNode();
	persNode->setPosition(x, y, z);
	// on place la camera
	SceneNode* camNode = mCamera->getParentSceneNode();
	camNode->setPosition(Vector3::ZERO);
	mCamera->setPosition(Vector3(x - 2000, y, z - 1000));    //-600,0,-1400

	//mCamera->lookAt(Ogre::Vector3(x,y,z));
	mCamera->setAutoTracking(true, mPersonnage->getParentSceneNode());
	//mRobot->getParentSceneNode()->setInitialState();
	//SceneNode * personnageNode = mPersonnage->getParentSceneNode();
	//personnageNode->translate(Vector3(x,y,z));
	//personnageNode->yaw(Degree(90));
}

void AnimationsAuto::tomberRegarderCamera ()
{
	using namespace Ogre;

	SceneNode* camNode = mCamera->getParentSceneNode();

	Animation* animCamera = mShortStory->getSceneManager()->createAnimation("TomberCameraTrack", 40);
	animCamera->setInterpolationMode(Animation::IM_LINEAR);

	NodeAnimationTrack* track = animCamera->createNodeTrack(0, camNode);

	TransformKeyFrame* key = track->createNodeKeyFrame(0);

	key = track->createNodeKeyFrame(10);
	key->setTranslate(Vector3(-800, 200, 500));

	key = track->createNodeKeyFrame(20);
	key->setTranslate(Vector3(-850, 400, 1400));

	key = track->createNodeKeyFrame(30);
	key->setTranslate(Vector3(-1200, 1000, 2200));

	key = track->createNodeKeyFrame(40);
	key->setTranslate(Vector3(-1200, 1000, 2200));

	mAnimStateCamera = mShortStory->getSceneManager()->createAnimationState("TomberCameraTrack");
	mAnimStateCamera->setTimePosition(0);
	mAnimStateCamera->setEnabled(false);
	mAnimStateCamera->setLoop(false);
	//
}

void AnimationsAuto::setAnimation ()
{
	if (setFlag == 0)
	{
		setPosition();
		tomberRegarderCamera();
		tomberPersonnage();
		setFlag = 1;
	}

}
