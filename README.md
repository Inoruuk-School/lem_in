# lem_in #

L'objectif de ce projet est de créer un gestionnaire de fourmilière.


Usage :
```
./lem_in [< mon_fichier.txt] [mon_fichier.txt]
```
Résumé du sujet :

On va s’intéresser plus particulièrement à sa partie calculs. Son fonctionnement ? Simple ! On monte une fourmilière avec tout son lot de tunnels et de salles, on met des fourmis d’un côté et on regarde comment elles trouvent la sortie.
Comment on monte une fourmilière ? On a besoin de tubes et de boîtes. On relie les boîtes entre elles par plus ou moins de tubes. Un tube relie deux boîtes entre elles et pas plus.
Une boîte peut être reliée à une infinité d’autres boîtes par autant de tubes qu’il en faudra. Ensuite on enterre le tout (où vous voudrez) pour que les fourmis ne puissent pas tricher en regardant avant de commencer.
Comme ici, on est pas trop bricolage à coup de boîtes, scotch et bouts de ficelle, on va en faire une version high-tech.
Le but du projet sera donc de faire un simulateur de "Hex".

* L'objectif de ce projet est de faire progresser N fourmis du début à la fin de la fourmilière en parcourant N salle
* Les contraintes de ce projet sont les suivantes : 
  * il faut trouver le.s chemin.s le.s plus court.s
  * il ne doit pas y avoir deux fourmis dans la même salle au même moment
  * il ne doit pas y avoir d'embouteillage
  * Deux salle ne doivent pas avoir les même coordonnées
* Le format du texte donné au programme est:
```
  nombre_de_fourmis
  #commentaire
  ##commande
  #Salles
  Salle 1 2
  salle 2 1
  #tube
  Salle-salle
```
* Au début de la partie toutes les fourmis seront sur la salle de départ indiquée par la commande ##start et doivent allées à la salle de fin indiqueée par ##end tout en passant par la meilleure combinaison de chemin
```
nombre_de_fourmis
##start
debut 1 2
##end
fin 2 1
0 3 3
debut-0
0-fin
debut-fin
```
* Une fois le problème résolu il faut sortir le résultat sur la sortie standard sous la forme suivante :
```
nombre_de_fourmis
les_salles
les_tubes
Lx-y Lz-w Lu-o
```
où x, z et u sont les numéros des fourmis envoyées et y, w et o sont les noms des salles dans lesquelles les fourmis sont envoyées

