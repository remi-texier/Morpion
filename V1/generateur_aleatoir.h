#ifndef GENERATEUR_ALEATOIR_H
#define GENERATEUR_ALEATOIR_H

//Vérification du compteur
void checkSeed();
 
//Générer une nouvelle séquence...
void newSeed(int s);
 
//Générer un nombre aléatoire
int _randi();

//Générer un nombre aléatoire entre [0,max-1]
int randi(int max);

#endif