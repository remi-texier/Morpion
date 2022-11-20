#include "generateur_aleatoir.h"
#include <time.h>

//Mis en place du compteur
static int cnt = 0;
 
//Vérification du compteur
void checkSeed()
{
        //Si on a trop appelé le générateur de nombres, on remet le tout à zéro
        if((!cnt)||(cnt>10000))
                {
                srand(time(NULL));
                cnt=0;
                }
}
 
//Générer une nouvelle séquence...
void newSeed(int s)
{
        srand(s);
}
 
//Générer un nombre aléatoire
int _randi()
{
        checkSeed();
        return rand();
}
 
//Générer un nombre aléatoire entre [0,max-1]
int randi(int max)
{
        checkSeed();
        if(max)
                return rand()%max;
        return 0;
}