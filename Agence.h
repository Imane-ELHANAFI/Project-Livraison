#pragma once
#include "Transporteur.h"
#include "colis.h"
#include "Client_agence.h"
#include "Camion.h"
#include "Avion.h"
#include "Velo.h"
#include "Drone.h"
#include <vector>
using namespace std;
class Agence {
    private :
        vector<Transporteur*> transporteurs ;
        vector<Colis*> liste_colis ;
        vector<Client_agence*> liste_clients ;
    public :
        Agence() ;
        void ajouterColis(Colis colis) ;
        void supprimerColis(Colis colis) ;
        void ajouterClient(Client_agence client) ;
        void afficherHistoriqueColis() const ;
        void genererRapport();
        Transporteur* attribuerTransporteur(const Colis& colis) const ;
        void changerStatutColis(const string& idColis, const string& nouveauStatut) ;
        ~Agence() ;
};
