#pragma once
#include "Personne.h"
#include <string>
using namespace std;

class Client_agence : public Personne {
    public :
        Client_agence();
        Client_agence(string nom , string prenom , string num_Tele , string adresse);
        void affichage() ;
        ~Client_agence() ;
};
