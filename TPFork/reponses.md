# Réponses aux questions du TP Fork

Binôme:

- Nadia Lahya
- Kylian Mehdi

Groupe TP : TP1H

# Exercice 1.1

## Question a :

PID parent = 44832; PPID enfant = 44832. Le fork fait sur le processus parent s'est bien executé. Le PPID représente le processus père.

## Question b :

PPID parent = 37592;

    systemd(1)───systemd(36647)───gnome-terminal-(37473)───bash(37592)───pstree(49997) Le nom du parent est bash.

## Question c :

    Cette ligne va être affichée deux fois
    Parent :  PID = 55139 - PPID = 37592
    Cette ligne va être affichée deux fois
    Enfant : PID = 55140 - PPID = 55139
    Enfant : PID = 55140 - PPID = 55139
    mehdiky@iutv-a105-08:~/TPSemèstre3/C/os_mehdi_lahya/TPFork (main)
    $ Enfant : PID = 55140 - PPID = 36647
    Enfant : PID = 55140 - PPID = 36647

Ensuite :

    pstree -ps 55140 |grep 36647
            |-systemd(36647)-+-(sd-pam)(36665)

Nous pouvons donc voir qu'après la mort du parent le PPID de l'enfant a changé pour 36647 donc il a été adopté par 'systemd'.

# Exercice 2, Variables Globales :

## Question a :

Non il n'y a pas d'interferance la variable globale. Chaque processus crée son propre contexte après le Fork(). Lors de l'incrémentation chacun incrément sa propre variable globale.

Avec initialisation de la variable globale à 434.

    ./forkGlobales
    Parent 434
    Enfant 434

# Exercice 3, Fichier Partagé :

## Question a :

Il y a un mélange d'affichage car on a crée le fichier "sharedFile" avant le fork, ainsi le processus parent crée le fichier.

Une fois l'enfant crée il accède au même fichier (qui a été stocké en mémoire) et écrit dans le fichier. Ainsi, on voit que l'OS donnant la main à chaque processus pour un temps donné, donne lieu à un mélange, comme ci-dessous:

    ./forkShared

    Je suis l'enfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaant !![64437:106]
    Je suis le peeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeere !![64436:112]
    Je suis l'enfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaant !![64437:107]
    Je suis le peeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeere !![64436:113]
    Je suis l'enfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaant !![64437:108]
    Je suis le peeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeere !![64436:114]

# Exercice 4, Fichier Partagé et synchronisation :

## Question a :

Non, il n'y a plus de mélanges. Le processus parent attend que le processus enfant se termine avant de commencer ses propres affichages.

## Question b :

Oui, les affichages des deux processus apparaissent dans le fichier. Le processus enfant ouvre le fichier en mode "w" ce qui écrase tout contenu existant. Ensuite, le processus parent ouvre le fichier en mode "a" après que l'enfant a terminé d'écrire.

# Question Bonus

L'affichage n'apparaît jamais car execlp donne la main à un autre processus ici "ps" et par conséquent se n'est plus l'enfant qui à la main.