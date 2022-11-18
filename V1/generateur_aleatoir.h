#ifndef GENERATEUR_ALEATOIR_H
#define GENERATEUR_ALEATOIR_H

//-------------------------------------IMPORTANTE-------------------------------------
//Cette class a ete utlise et sera utlise par la suite pour ameliorer l algo Alpha beta
//-----------------------------------------------------------------------------------

//Vérification du compteur
void checkSeed();
 
//Générer une nouvelle séquence...
void newSeed(int s);
 
//Générer un nombre aléatoire
int _randi();

//Générer un nombre aléatoire entre [0,max-1]
int randi(int max);

#endif