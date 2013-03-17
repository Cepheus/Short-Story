#include "Picking.h"
#include <iostream>

Picking::Picking(Ogre::SceneManager* sceneMgr)
{
    mRayScnQuery = sceneMgr->createRayQuery(Ogre::Ray(), Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
	mRayScnQuery->setSortByDistance(true);
}

Picking::~Picking()
{
    //dtor
}

bool Picking::isPicked(Ogre::SceneNode *node1,Ogre::SceneNode *node2,float distance)
{
    Ogre::Quaternion quat= node1->getOrientation();
    Ogre::Vector3 normal = quat*Ogre::Vector3(0,0,-1);
    Ogre::Vector3 point = node1->getPosition();
    /*
    std::cout << "Node1 : " <<node1->getName()<<std::endl;
    std::cout << "quat  : " <<quat.w<<" "<<quat.x<<" "<<quat.y<<" "<<quat.z<<std::endl;
    std::cout << "Normal: " << normal.x<<" "<<normal.y<<" "<<normal.z<<std::endl;
    std::cout << "point : " << point.x<<" "<<point.y<<" "<<point.z<<std::endl;
    */

    //Create ray
    Ogre::Ray mouseRay(point, normal);
    mRayScnQuery->setRay(mouseRay);

    //Send ray
    Ogre::RaySceneQueryResult &result = mRayScnQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr;


    //Discover result
    for (itr = result.begin();itr!=result.end();itr++)
    {
        if(itr->movable)
        {
            if(itr->distance<distance)
            {
                //std::cout<< "MovableObject: "<<itr->movable->getName()<<std::endl;
                if(itr->movable->getParentNode() == node2)
                {
                    return true;
                }
            }
        }
    }
    //std::cout<<"endl"<<std::endl<< std::endl;
    return false;
}
