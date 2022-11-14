# Description du projet

Le jeu modifié est space invaders.

Les modifications que je souhaite apporter sont :
- Augmenter le bestiaire d'ennemi (des ennemis différents possédant des paternes propres à chacuns)
- Créer des bonus améliorant le vaisseau
- Créer un système de point de vie pour le vaisseau et les ennemis

# Comment compiler le projet sous Linux

Depuis le dossier MiniProjet exécuter la commande :

```
clang -o space_invaders space_invaders.c -Wall -std=c11 /home/bot/Raylib.git/src/libraylib.a -lm -lGL -lX11 -ldl -lpthread -lrt
```

# Comment exécuter

Depuis le dossier MiniProjet exécuter la commande :

```
./space_invaders
```

# Comment utiliser le projet

## Règle

Le but est de finir toutes les vagues d'ennemis en tuant tous les ennemis de chaque vague.

Chaque vague d'ennemi contient un type d'ennemi spécifique excepté la vague finale.

Chaque ennemi ont une chance (20%) d'être golden.
Les ennemis golden laisse tombé un bonus ramassable par le vaisseau joueur.
Lorsqu'un bonus est ramassé par le joueur, il gagne, selon la couleur, un des bonus suivant :
- Bonus violet : augmentation de la cadence de tir
- Bonus vert : augmentation de la vitesse du vaisseau joueur
- Bonus marron : augmentation de la largeur des lasers tirés par le vaisseau joueur
- Bonus bleu : Obtention d'un bouclier blockant une collision au vaisseau joueur (non cumulable)

## Commandes

Utiliser les flèches directionnelles du clavier afin de bouger le vaisseau joueur.

Utiliser la barre d'espace afin de tirer sur les ennemis.

Utiliser la touche "P" comme "pause" pour mettre le jeux en pause.

Utiliser la touche entrée pour rédémarrer le jeux une fois perdu.

Utiliser la touche echap pour fermer le jeux.

Utiliser la touche "C" comme "cheat" pour gagner des vies.

Utiliser la touche "K" comme "kill" pour tuer tous les ennemis restant de la vague actuelle.

# URL vidéo de démo

# Quelques détails sur votre implémentation

Tout le code modifié est contenu dans le fichier space_invaders.c

Les 5 premières fonctions InitGame(void), UpdateGame, DrawGame, UnloadGame et UpdateDrawFrame sont des fonctions du jeux classiques raylib. Certaines de ces fonctions ont été modifié mais la structure général du code de ces fonctions a été gardée.

Toutes les autres fonctions implémenter ensuite sont entièrement créer de 0. Ces fonctions peuvent être classées en 2 catégories, celles qui gèrent les ennemis et celles qui gèrent les bonus.

# Extensions / améliorations possibles

- Rajouter plus de type d'ennemis
- Rajouter plus de type de bonus
- Ajouter une animation sur certains ennemis
- Ajouter un mode "2 joueurs"