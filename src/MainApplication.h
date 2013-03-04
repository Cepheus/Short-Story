/*
Filename:    MainApplication.h
*/
#ifndef __MainApplication_h_
#define __MainApplication_h_

#include "BaseApplication.h"
#include "OgreRay.h"

class MainApplication : public BaseApplication
{
public:
    MainApplication(void);
    virtual ~MainApplication(void);

protected:
    virtual void createScene(void);

private:
    void createTerrain(void);
    Ogre::Terrain *mTerrain;
    Ogre::TerrainGlobalOptions *mGlobals;
};

#endif // #ifndef __MainApplication_h_
