#include <Ogre.h>
#include "ShortStory.h"
#include "InputListener.h"
#include "Scene.h"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain (HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
	// Application générale
	ShortStory shst;
	// Gère les inputs
	InputListener *il = 0;
	// Contient la scène principale
	Scene *scene = 0;

	try
	{
		if (shst.Initialize()) // le lancement est OK
		{
			// création de la scène
			scene = new Scene(&shst);
			scene->createScene();

			// ajout des inputs
			il = new InputListener(scene, shst.getSceneManager(), shst.getWindow(), shst.getCamera());
			shst.getRoot()->addFrameListener(il);

			// On lance la boucle de rendu, affichage du bouzin
			shst.start();

			delete scene;
			delete il;
		}
	}
	catch (Ogre::Exception& e)
	{
		delete il;
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!",
		        MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		fprintf(stderr, "An exception has occurred: %s\n",
				e.getFullDescription().c_str());
#endif
	}

	return 0;
}
