Short-Story
===========

Projet RV

GROS COMMIT

- refait l'architecture du programme (ya des commentaires, rien de compliqué à comprendre)
	- ShortStory : classe principale qui initialise l'appli et contient la boucle de rendu
	- Scene : classe permettant de créer la scène
	- InputListener : classe gérant les inputs (notamment claiver / souris)
	- OgreRay : classe expériementale pour la gestion de collisions

- j'ai volontairement commit les fichiers cfg car grosse MàJ : tout supprimé, gain de temps énorme au lancement !
	- configurés pour une exécution se lançant dans le dossier  (et pas /bin/Debug ou Release). Si vous avez pas ça, faut changer les chemins
	- plugins_d.cfg lancé quand variable _DEBUG set (ajoutez le define dans la config DEBUG)

