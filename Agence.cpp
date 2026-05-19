#include "Agence.h"
#include <iostream>
using namespace std;

Agence::Agence() {
    // Initialisation des transporteurs disponibles
    transporteurs.push_back(new Camion);
    transporteurs.push_back(new Avion);
    transporteurs.push_back(new Velo);
    transporteurs.push_back(new Drone);
}
void Agence::ajouterColis(Colis colis) {
    liste_colis.push_back(new Colis(colis));
}
void Agence::supprimerColis(Colis colis) {
    for (auto it = liste_colis.begin(); it != liste_colis.end(); ++it) {
        if (**it == colis) {
            delete *it; 
            liste_colis.erase(it); 
            cout << "Colis avec ID " << colis.getId() << " supprimé." << endl;
            return;
        }
    }
    cout << "Colis avec ID " << colis.getId() << " non trouvé." << endl;
}
void Agence::ajouterClient(Client_agence client) {
    liste_clients.push_back(new Client_agence(client));
}
void Agence::afficherHistoriqueColis() const {
    if (liste_colis.empty()) {
        cout << "Aucun colis enregistre." << endl;
        return;
    }
    cout << "Historique des colis :" << endl;
    for (const auto& colis : liste_colis) {
        cout << *colis << endl;
    }
}
void Agence::genererRapport() {
    cout << "Rapport de l'agence :" << endl;
    for (const auto& colis : liste_colis) {
        cout << *colis << endl;
    }
}
Transporteur* Agence::attribuerTransporteur(const Colis& colis) const {
    for (const auto& transporteur : transporteurs) {
        if (transporteur->canDeliver(colis.getPoids(), colis.getDistance(), colis.getTypeString())) {
            return transporteur;
        }
    }
    return nullptr; // Aucun transporteur ne peut livrer ce colis
}
void Agence::changerStatutColis(const string& idColis, const string& nouveauStatut) {
    for (auto& colis : liste_colis) {
        if (colis->getId() == idColis) {
            if (nouveauStatut == "EN_TRANSIT") {
                colis->mettreEnTransit();
            } else if (nouveauStatut == "LIVRE") {
                colis->confirmerLivraison();
            } else if (nouveauStatut == "ANNULE") {
                colis->annuler();
            } else {
                cout << "Statut invalide : " << nouveauStatut << endl;
            }
            return;
        }
    }
    cout << "Colis avec ID " << idColis << " non trouvé." << endl;
}
Agence::~Agence() {
    for (auto& transporteur : transporteurs) {
        delete transporteur;
    }
    for (auto& colis : liste_colis) {
        delete colis;
    }
    for (auto& client : liste_clients) {
        delete client;
    }
}