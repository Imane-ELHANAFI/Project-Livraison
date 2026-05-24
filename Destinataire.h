#pragma once
#include "Personne.h"
#include <string>
using namespace std;
class Destinataire : public Personne {
    public :
        Destinataire();
        Destinataire(string nom , string prenom , string num_Tele , string adresse);
        void affichage() ;
        bool confirmerLivraison(const string& statutColi)const ;//il prend en parametre le status de colis 
        ~Destinataire() ;
};