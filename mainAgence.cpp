#include "Agence.h"
#include <iostream>
using namespace std;
int main() {
    Agence agence;

    // Ajouter des clients
    Client_agence client1("Alice", "Smith", "123456789", "123 Main St");
    Client_agence client2("Bob", "Johnson", "987654321", "456 Elm St");
    agence.ajouterClient(client1);
    agence.ajouterClient(client2);

    // Ajouter des colis
    Colis c1(10.5, 30.0, 40.0, 20.0, 150.0, TypeColis::STANDARD, false);
    Colis c2(2.0,  15.0, 10.0, 8.0,  600.0, TypeColis::FRAGILE,  true);
    agence.ajouterColis(c1);
    agence.ajouterColis(c2);

    // Afficher l'historique des colis
    agence.afficherHistoriqueColis();

    // Générer un rapport de l'agence
    agence.genererRapport();

    return 0;
}