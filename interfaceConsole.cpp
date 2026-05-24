#include<iostream>
#include<string>
#include "Agence.h"
#include "Destinataire.h"
#include "Client_agence.h"
#include "Personne.h"
#include "colis.h"
#include <limits>

using namespace std;

void viderBuffer() {
    // Vide le cin après un >> pour éviter les bugs avec getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
string lireLigne(const string& invite){
    //Lit une ligne de texte non vide, redemande si vide
    string val;
    while(true){
        cout << invite;
        getline(cin, val);
        if (!val.empty()) return val;
        cout << "Ce champ ne peut pas être vide." << endl;
    }
}
int lireEntier(const string& invite, int min, int max) {
    //Lit un entier valide dans un intervalle, redemande si mauvaise saisie
    int val;
    while (true) {
        cout << invite;
        if (cin >> val && val >= min && val <= max) {
            viderBuffer();
            return val;
        }
        cout << "Veuillez entrer un nombre entier entre " << min << " et " << max << "." << endl;
        cin.clear();
        viderBuffer();
    }
}
void separateur() {
    cout << "-----------------------------" << endl;
}
// fct qui permet de saisir les informations d'un client et retourne un objet Client_agence.
Client_agence saisirClient() {
    separateur();
    cout << "Saisie des informations du client :" << endl;
    string nom = lireLigne("Nom : ");
    string prenom = lireLigne("Prénom : ");
    string num_Tele = lireLigne("Numéro de téléphone : ");
    string adresse = lireLigne("Adresse : ");
    return Client_agence(nom, prenom, num_Tele, adresse);
}
// meme chose mais pour le distinataire
Destinataire saisirDestinataire() {
    separateur();
    cout << "Saisie des informations du destinataire :" << endl;
    string nom = lireLigne("Nom : ");
    string prenom = lireLigne("Prénom : ");
    string num_Tele = lireLigne("Numéro de téléphone : ");
    string adresse = lireLigne("Adresse : ");
    return Destinataire(nom, prenom, num_Tele, adresse);
}
void menuClient (Agence& agence , Client_agence client){
    //Assure les fonctionnalites de client tel que  :Créer colis → récapitulatif → historique → annuler → rapport
    int choix ;
    do{
        separateur();
        cout << "Espace Client - " << client.getnom() << " " << client.getprenom() << endl;
        separateur();
        cout << "1. Créer un nouveau colis" << endl;
        cout << "2. Voir l'historique de colis" << endl;
        cout << "3. Annuler un colis" << endl;
        cout << "0. Retour" << endl;
        choix = lireEntier("Veuillez choisir une option : ", 0, 3);
    
        if(choix == 1){
            separateur();
            cout << "Création d'un nouveau colis :" << endl;
            // saisie des dimensions et caractéristiques d'un nouveau colis
            double poids = 0 , largeur = 0 , longueur = 0 , hauteur = 0 , distance = 0 ;
            cout << "Poids (kg) : "; cin >> poids; viderBuffer();
            cout << "Largeur (cm) : "; cin >> largeur; viderBuffer();
            cout << "Longueur (cm) : "; cin >> longueur; viderBuffer();
            cout << "Hauteur (cm) : "; cin >> hauteur; viderBuffer();
            cout << "Distance (km) : "; cin >> distance; viderBuffer();
            //type : enum TypeColis (STANDARD ou FRAGILE) 
            cout << "Type : 1 STANDARD, 2 FRAGILE "<< endl;
            int Choixtype = lireEntier("Choix du type : ", 1, 2);
            TypeColis type = (Choixtype == 1) ? TypeColis::STANDARD : TypeColis::FRAGILE;
            // urgent : booléen  
            int choixUrgent = lireEntier("  Urgent ? (1=Oui / 0=Non) : ", 0, 1);
            bool urgent = (choixUrgent == 1);
            //creation du colis
            Colis colis(poids, largeur, longueur, hauteur, distance, type, urgent);
            //L'agence attribue un transporteur adapté au colis
            Transporteur* t = agence.attribuerTransporteur(colis);
            if (t == nullptr){
                cout << "Aucun transporteur disponible pour ce colis." << endl;
            }else {
                cout <<"Creation suffit avec succes, votre coli va etre transporter par : "<< t->getType() << endl;
                separateur();
                float cout_ = t->computeCost(poids, distance, colis.getTypeString());
                int  delai = t->computeDelay();
                cout << "Transporteur : " << t->getType() << endl;
                cout << "Coût estimé  : " << cout_  << " DH" << endl;
                cout << "Délai estimé : " << delai  << " jour(s)" << endl;
                //Demander la confirmation du client 
                int confirmation = lireEntier("Confirmer la création du colis ? (1=Oui / 0=Non) : ", 0, 1);
                if (confirmation == 1) {
                    agence.ajouterColis(colis);
                    cout << "[✓] Colis enregistré (ID : " << colis.getId() << ")" << endl;
                    agence.genererRapport(colis, t); // génère un rapport détaillé pour ce colis et transporteur
                } else {
                    cout << "[x] Création annulée." << endl;
                }
            }
        }else if(choix == 2){
            //Voir l'historique de colis
            separateur();
            cout << "Historique des colis :" << endl;
            agence.afficherHistoriqueColis();
        }else if(choix == 3){
            //Annuler un colis
            separateur();
            cout << "Annulation d'un colis :" << endl;
            string idColis = lireLigne("ID du colis à annuler : ");
            // changerStatutColis() appelle colis->annuler()
            // annuler() vérifie que statut == EN_ATTENTE sinon refuse le changement de statut 
            agence.changerStatutColis(idColis, "ANNULE");
        }
    }while(choix != 0);
    //Retour au menu principal
}
void menuAgence(Agence& agence){
    int choix ;
    do{
        separateur();
        cout << "Espace Agence" << endl;
        separateur();
        cout << "1. Changer le statut d'un colis" << endl;
        cout << "2. Voir l'historique des colis" << endl;
        cout << "0. Retour" << endl;
        choix = lireEntier("Veuillez choisir une option : ", 0, 2);
        if(choix == 1){
            //Changer le statut d'un colis
            separateur();
            cout << "Changer le statut d'un colis :" << endl;
            string idColis = lireLigne("ID du colis : ");
            cout << "Nouveau statut : 1 EN_TRANSIT, 2 LIVRE, 3 ANNULE" << endl;
            int choixStatut = lireEntier("Choix du nouveau statut : ", 1, 3);
            string nouveauStatut;
            switch (choixStatut) {
                case 1: nouveauStatut = "EN_TRANSIT"; break;
                case 2: nouveauStatut = "LIVRE"; break;
                case 3: nouveauStatut = "ANNULE"; break;
            }
            agence.changerStatutColis(idColis, nouveauStatut);
            cout << "[✓] Statut mis à jour." << endl;
        }else if (choix == 2){
            //Voir l'historique des colis
            separateur();
            cout << "Historique des colis :" << endl;
            agence.afficherHistoriqueColis();
        }

    }while(choix != 0);
    //Retour au menu principal}
}
void menuDestinataire(Agence& agence , Destinataire destinataire){
    int choix ;
    do {
        separateur();
        cout << "Espace Destinataire - " << destinataire.getnom() << " " << destinataire.getprenom() << endl;
        separateur();
        cout << "1. Consulter le status d'un colis" << endl;
        cout << "2. Confirmer la reception d'un colis" << endl;
        cout << "0. Retour" << endl;
        choix = lireEntier("Veuillez choisir une option : ", 0, 2);
        if(choix == 1){
            //Consulter le status d'un colis
            separateur();
            cout << "Consultation du statut d'un colis :" << endl;
            string idColis = lireLigne("ID du colis : ");
            bool trouve = false;
            for (const auto& colis : agence.liste_colis) {
                if (colis->getId() == idColis) {
                    cout << "Statut du colis (ID : " << idColis << ") : " << colis->getStatutString() << endl;
                    trouve = true;
                    break;
                }
            }
            if (!trouve) cout << "Colis avec ID " << idColis << " non trouvé." << endl;
        }else if (choix == 2){
            //Confirmer la reception d'un colis
            separateur();
            cout << "Confirmation de la réception d'un colis :" << endl;
            string idColis = lireLigne("ID du colis recu : ");
            agence.changerStatutColis(idColis, "LIVRE"); 
            // ensuite le destinataire confirme la reception du colis
            destinataire.confirmerLivraison("LIVRE"); 

        }
}while(choix != 0);
}
int menuPrincipale(){
    separateur();
    cout << "Bienvenue dans le système de gestion de livraison" << endl;
    cout << "Qui êtes-vous ?" << endl;
    cout << "1. Client / Expéditeur" << endl;
    cout << "2. Agence de livraison" << endl;
    cout << "3. Destinataire" << endl;
    cout << "0. Quitter" << endl;
    return lireEntier("Veuillez choisir une option : ", 0, 3);
}
int main() {

    // constructeur Agence() crée le tableau de transporteurs :
    // Camion, Avion, Velo, Drone → attribuerTransporteur() les parcourt
    Agence agence;
    int role;
    do {
        role = menuPrincipale();

        if (role == 1) {
            // saisie identité → menu client
            Client_agence client = saisirClient();
            menuClient(agence, client);

        } else if (role == 2) {
            // pas de saisie identité pour l'agence
            menuAgence(agence);

        } else if (role == 3) {
            // saisie identité → menu destinataire
            Destinataire dest = saisirDestinataire();
            menuDestinataire(agence, dest);
        }
    } while (role != 0);

    cout << "Au revoir !" << endl;
    return 0;
    // ~Agence() libère automatiquement :
    // tous les transporteurs, colis et clients (new → delete)
}