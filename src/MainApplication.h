/*
Filename:    MainApplication.h
*/
#ifndef __MainApplication_h_
#define __MainApplication_h_

#include "BaseApplication.h"

class MainApplication : public BaseApplication
{
public:
    MainApplication(void);
    virtual ~MainApplication(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __MainApplication_h_
