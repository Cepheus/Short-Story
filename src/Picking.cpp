#include "Picking.h"
#include <iostream>

Picking::Picking(Ogre::SceneManager* sceneMgr,Ogre::SceneNode *_node1,Ogre::SceneNode *_node2,float _distance):
    node1(_node1),node2(_node2),distance(_distance)
{
    mRayScnQuery = sceneMgr->createRayQuery(Ogre::Ray(), Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
	mRayScnQuery->setSortByDistance(true);
}

Picking::~Picking()
{
    //dtor
}

bool Picking::isPicked()
{
    Ogre::Quaternion quat= node1->getOrientation();
    Ogre::Vector3 normal = quat*Ogre::Vector3(1,1,1);
    Ogre::Vector3 point = node1->getPosition();
    std::cout << "Node1 : " <<node1->getName()<<std::endl;
    std::cout << "quat  : " <<quat.w<<" "<<quat.x<<" "<<quat.y<<" "<<quat.z<<std::endl;
    std::cout << "Normal: " << normal.x<<" "<<normal.y<<" "<<normal.z<<std::endl;
    std::cout << "point : " << point.x<<" "<<point.y<<" "<<point.z<<std::endl;
    //Create ray
    Ogre::Ray mouseRay(point, normal);
    mRayScnQuery->setRay(mouseRay);

    //Send ray
    Ogre::RaySceneQueryResult &result = mRayScnQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr;

    //Discover result
    for ( itr = result.begin( ); itr != result.end(); itr++ )
    {
        if( itr->movable )
        {
            if(itr->distance>distance)
            {
                std::cout << "MovableObject: " << itr->movable->getName() << std::endl;
                if(itr->movable->getParentNode() == node2)
                {
                    std::cout<<"GGGGGGGGGGGGGGGGGG"<< std::endl;
                    return true;
                }
            }
        }
    }
     std::cout<<std::endl<< std::endl;
    return false;
}
