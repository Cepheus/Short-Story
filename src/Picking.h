#ifndef PICKING_H
#define PICKING_H

#include <Ogre.h>

class Picking
{
public:
    Picking(Ogre::SceneManager* sceneMgr,Ogre::SceneNode *_node1,Ogre::SceneNode *_node2,float _distance);
    ~Picking();

    bool isPicked();

private:
    Ogre::SceneNode *node1;
    Ogre::SceneNode *node2;
    float           distance;
    Ogre::RaySceneQuery* mRayScnQuery; //!< Ray query
};

#endif // PICKING_H
