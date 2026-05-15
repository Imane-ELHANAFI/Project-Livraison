#include "Destinataire.h"
#include <iostream>
using namespace std;
Destinataire::Destinataire() : Personne() {}
Destinataire::Destinataire(string nom , string prenom , string num_Tele , string adresse) : Personne(nom , prenom , num_Tele , adresse) {}
void Destinataire::affichage() {
    Personne::affichage();
}
bool Destinataire::confirmerLivraison(const string& statutColi) const {
    char reponse ;
    if (statutColi == "Livré") {
        cout << "Avez-vous recu votre colis ? (o/n) : ";
        cin >> reponse ;
        if (reponse == 'o' || reponse == 'O') {
            cout << "Merci pour votre confiance" << endl;
        } else {
            cout << "Erreur : reception non confirmee." << endl;
            return false;
        }
        return true;
    } else {
        cout << "Le colis n'est pas encore livre, son etat actuel est : " << statutColi << endl;
        return false;
    } 
}
Destinataire::~Destinataire() {}