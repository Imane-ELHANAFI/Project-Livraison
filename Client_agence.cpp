#include "Client_agence.h"
#include <iostream>
#include<string>
using namespace std;

Client_agence::Client_agence() : Personne() {}
Client_agence::Client_agence(string nom , string prenom , string num_Tele , string adresse)
    :Personne(nom , prenom , num_Tele , adresse) {}
void Client_agence::affichage() {
    Personne::affichage();
}
Client_agence::~Client_agence() {}
