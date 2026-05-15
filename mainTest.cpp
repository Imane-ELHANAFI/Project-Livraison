#include <iostream>
#include "Destinataire.h"
#include "Client_agence.h"
using namespace std;

int main(){

    // ---- TEST 1 : Création du client ----
    std::cout << "\n--- TEST 1 : Creation du client ---" << std::endl;
    Client_agence client("EL HANAFI", "Imane", "0612345678", "12 Rue Taroudant");
    client.affichage();

    // ---- TEST 2 : Création du destinataire ---- 
    std::cout << "\n--- TEST 2 : Creation du destinataire ---" << std::endl;
    Destinataire dest("ETTHABITY", "Simane", "0698765432", "12 Rue Taroudant");
    dest.affichage();

    // ---- TEST 3 : Confirmation de livraison ----
    std::cout << "\n--- TEST 3 : Confirmation de livraison ---" << std::endl;
    string statutColi1 = "Livré";
    string statutColi2 = "En attente";
    cout << "Test avec statut 'Livré' : " << endl;
    dest.confirmerLivraison(statutColi1);//Resultat attendu : "Merci pour votre confiance"
    cout << "Test avec statut 'En attente' : " << endl;
    dest.confirmerLivraison(statutColi2);//Resultat attendu : "Le colis n'est pas encore livre, son etat actuel est : En attente"
    return 0 ;
}