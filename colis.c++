// ============================================================
// Fichier : Colis.cpp
// Description : Implémentation de la classe Colis
// ============================================================

#include "Colis.h"
#include <iostream>
#include <sstream>
#include <iomanip>  // pour std::setw, std::setfill


// ── Initialisation du compteur statique ──────────────────────────────────────
int Colis::compteurId = 0;


// ── Génération de l'ID unique au format "COL-0001" (CT-08, EF-02) ────────────
std::string Colis::genererID() {
    ++compteurId;
    std::ostringstream oss;
    oss << "COL-" << std::setw(4) << std::setfill('0') << compteurId;
    return oss.str();
}


// ── Validation des données saisies (CT-09, EF-03) ───────────────────────────
// Cette méthode est appelée dans le constructeur AVANT tout traitement.
// Si une donnée est invalide, elle lève une exception pour stopper la création.
void Colis::validerDonnees() const {

    // Règle : poids doit être strictement positif
    if (poids <= 0)
        throw std::invalid_argument("Erreur : le poids doit être supérieur à 0.");

    // Règle : dimensions doivent être strictement positives
    if (dimensions <= 0)
        throw std::invalid_argument("Erreur : les dimensions doivent être supérieures à 0.");

    // Règle : distance doit être strictement positive
    if (distance <= 0)
        throw std::invalid_argument("Erreur : la distance doit être supérieure à 0.");

    // Le type (STANDARD / FRAGILE) et l'urgence (bool) sont déjà contraints
    // par leurs types C++ — aucune vérification supplémentaire nécessaire.
}


// ── Constructeur (EF-01, EF-02, EF-03, EF-04) ───────────────────────────────
// Étapes :
//  1. Stocker les valeurs
//  2. Valider (lève une exception si invalide)
//  3. Générer l'ID unique
//  4. Fixer le statut initial à EN_ATTENTE
Colis::Colis(double poids, double dimensions, double distance,
             TypeColis type, bool urgent)
    : poids(poids),
      dimensions(dimensions),
      distance(distance),
      type(type),
      urgent(urgent),
      statut(StatutColis::EN_ATTENTE)
{
    // Étape 2 : validation — peut lever std::invalid_argument (CT-07)
    validerDonnees();

    // Étape 3 : génération de l'ID unique
    this->id = genererID();
}


// =============================================================================
//  GETTERS
// =============================================================================

std::string Colis::getId()         const { return id; }
double      Colis::getPoids()      const { return poids; }
double      Colis::getDimensions() const { return dimensions; }
double      Colis::getDistance()   const { return distance; }
TypeColis   Colis::getType()       const { return type; }
bool        Colis::isUrgent()      const { return urgent; }
StatutColis Colis::getStatut()     const { return statut; }

// Convertit le statut en texte lisible (utile pour l'affichage console)
std::string Colis::getStatutString() const {
    switch (statut) {
        case StatutColis::EN_ATTENTE:  return "En attente";
        case StatutColis::EN_TRANSIT:  return "En transit";
        case StatutColis::LIVRE:       return "Livré";
        case StatutColis::ANNULE:      return "Annulé";
        default:                       return "Inconnu";
    }
}

// Convertit le type en texte lisible
std::string Colis::getTypeString() const {
    return (type == TypeColis::FRAGILE) ? "Fragile" : "Standard";
}


// =============================================================================
//  TRANSITIONS D'ÉTAT  (règles métier §2.4 point 4 & 6)
// =============================================================================

// Règle : EN_ATTENTE → EN_TRANSIT
// L'agence prend en charge le colis.
// Interdit si le colis est déjà en transit, livré ou annulé.
void Colis::mettreEnTransit() {
    if (statut != StatutColis::EN_ATTENTE)
        throw std::logic_error(
            "Erreur [" + id + "] : impossible de passer EN_TRANSIT "
            "depuis l'état '" + getStatutString() + "'.");
    statut = StatutColis::EN_TRANSIT;
}

// Règle : EN_TRANSIT → LIVRE
// Le destinataire confirme la réception — action irréversible (EF-10, §2.4 pt5).
void Colis::confirmerLivraison() {
    if (statut != StatutColis::EN_TRANSIT)
        throw std::logic_error(
            "Erreur [" + id + "] : impossible de confirmer la livraison "
            "depuis l'état '" + getStatutString() + "'.");
    statut = StatutColis::LIVRE;
}

// Règle : annulation autorisée UNIQUEMENT si EN_ATTENTE (EF-12, §2.4 pt6).
// Interdit si EN_TRANSIT ou LIVRE.
void Colis::annuler() {
    if (statut == StatutColis::LIVRE)
        throw std::logic_error(
            "Erreur [" + id + "] : un colis livré ne peut pas être annulé.");

    if (statut == StatutColis::EN_TRANSIT)
        throw std::logic_error(
            "Erreur [" + id + "] : un colis en transit ne peut pas être annulé.");

    if (statut == StatutColis::ANNULE)
        throw std::logic_error(
            "Erreur [" + id + "] : ce colis est déjà annulé.");

    // Ici statut == EN_ATTENTE → annulation autorisée
    statut = StatutColis::ANNULE;
}


// =============================================================================
//  SURCHARGE D'OPÉRATEURS
// =============================================================================

// Opérateur << : affiche toutes les infos du colis (EF-08, rapport §8 CL-08)
std::ostream& operator<<(std::ostream& os, const Colis& c) {
    os << "┌─────────────────────────────────────┐\n"
       << "│  Colis ID    : " << c.getId()           << "\n"
       << "│  Poids       : " << c.getPoids()        << " kg\n"
       << "│  Dimensions  : " << c.getDimensions()   << " cm³\n"
       << "│  Distance    : " << c.getDistance()     << " km\n"
       << "│  Type        : " << c.getTypeString()   << "\n"
       << "│  Urgent      : " << (c.isUrgent() ? "Oui" : "Non") << "\n"
       << "│  Statut      : " << c.getStatutString() << "\n"
       << "└─────────────────────────────────────┘";
    return os;
}

// Opérateur == : deux colis sont identiques si et seulement si leurs IDs sont égaux
bool Colis::operator==(const Colis& autre) const {
    return this->id == autre.id;
}