# RespawnIRC

JVIrc-like pour respawn.

Pour plus d'infos, le site : http://lepigeon888.github.io/RespawnIRC/

## Compilation

### Windows

Pour Windows le plus simple reste de télécharger la dernière version de Qt (http://www.qt.io/download-open-source/) contenant Qt Creator, les libs Qt et un compilateur, de se rendre dans le dossier `respawnIrc` et d'ouvrir le .pro avec Qt Creator puis de cliquer sur `compiler`. Un nouveau dossier devrait être créé à la racine du projet (là où se trouve le dossier `ressources` et `theme`) et à l'intérieur de celui-ci se trouve un dossier `debug` ou `release` (selon comment vous avez compilé) contenant le .exe.

### Linux

Pour Linux, il vous suffit d'installer les paquets `qt5-default qtmultimedia5-dev libqt5webkit5-dev`. Ensuite, vous n'avez plus qu'à vous rendre dans le dossier `respawnIrc` qui contient le .pro et exécuter ces commandes :

    qmake
    make

Un fichier `respawnIrc` devrait être créé dans le répertoire courant.