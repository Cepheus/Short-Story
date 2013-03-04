#include <Ogre.h>
#include "ShortStory.h"
#include "InputListener.h"
#include "Scene.h"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
    // Application g�n�rale
    ShortStory shst;
    // G�re les inputs
    InputListener *il = 0;
    // Contient la sc�ne principale
    Scene *scene = 0;

    try
    {
        if (shst.Initialize()) // le lancement est OK
        {
            // ajout des inputs
            il = new InputListener(shst.getSceneManager(), shst.getWindow(), shst.getCamera());
            shst.getRoot()->addFrameListener(il);

            // cr�ation de la sc�ne
            scene = new Scene(shst.getSceneManager());
            scene->createScene();

            // On lance la boucle de rendu, affichage du bouzin
            shst.start();

            delete scene;
            delete il;
        }
    }
    catch(Ogre::Exception& e)
    {
        delete il;
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        fprintf(stderr, "An exception has occurred: %s\n",
            e.getFullDescription().c_str());
#endif
    }

    return 0;
}
