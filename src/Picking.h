#ifndef PICKING_H
#define PICKING_H

#include <Ogre.h>

class Picking
{
public:
    Picking(Ogre::SceneManager* sceneMgr);
    ~Picking();

    bool isPicked(Ogre::SceneNode *node1,Ogre::SceneNode *node2,float distance);

private:
    Ogre::RaySceneQuery* mRayScnQuery; //!< Ray query
};

#endif // PICKING_H
