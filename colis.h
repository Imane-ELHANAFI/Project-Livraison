// ============================================================
// Fichier : Colis.h
// Description : Déclaration de la classe Colis
// Conforme au cahier de charge (EF-01 à EF-13, CT-05 à CT-09)
// ============================================================

#ifndef COLIS_H
#define COLIS_H

#include <string>
#include <stdexcept> // pour std::invalid_argument

// ── Énumération des statuts possibles d'un colis (règle métier §7.2) ──────────
enum class StatutColis
{
    EN_ATTENTE, // Colis créé, pas encore pris en charge par l'agence
    EN_TRANSIT, // Colis en cours d'acheminement
    LIVRE,      // Livraison confirmée par le destinataire (irréversible)
    ANNULE      // Commande annulée (uniquement si EN_ATTENTE)
};

// ── Énumération des types de colis (règle métier §2.4 point 1) ───────────────
enum class TypeColis
{
    STANDARD,
    FRAGILE;
};

// ============================================================
//  Classe Colis
//  Représente un colis à livrer avec toutes ses caractéristiques.
//  Tous les attributs sont privés (CT-05 : encapsulation).
// ============================================================
class Colis
{

private:
    // ── Identifiant unique auto-généré (CT-08, EF-02) ────────────────────────
    std::string id;

    // ── Caractéristiques physiques du colis (EF-01) ──────────────────────────
    double poids;      // en kg  — doit être > 0 (CT-09)
    double dimensions; // en cm³ (volume) — doit être > 0 (CT-09)
    double distance;   // en km  — doit être > 0 (CT-09)

    // ── Propriétés logistiques ────────────────────────────────────────────────
    TypeColis type; // STANDARD ou FRAGILE
    bool urgent;    // true = livraison prioritaire

    // ── Statut courant du colis (EF-09) ──────────────────────────────────────
    StatutColis statut;

    // ── Compteur statique pour générer des IDs uniques (CT-08) ───────────────
    static int compteurId;

    // ── Méthode privée : génère un ID de la forme "COL-0001" ─────────────────
    static std::string genererID();

    // ── Méthode privée : valide toutes les données avant création (CT-09) ────
    // Lance une exception std::invalid_argument si une valeur est incorrecte.
    void validerDonnees() const;

public:
    // ── Constructeur ─────────────────────────────────────────────────────────
    // Crée un colis, valide les données, génère l'ID, et fixe le statut
    // initial à EN_ATTENTE.
    // Lève std::invalid_argument si une donnée est invalide (CT-07).
    Colis(double poids,
          double dimensions,
          double distance,
          TypeColis type,
          bool urgent);

    // ── Destructeur virtuel ───────────────────────────────────────────────────
    virtual ~Colis() = default;

    // =========================================================
    //  GETTERS  (CT-05 : accès en lecture aux attributs privés)
    // =========================================================
    std::string getId() const;
    double getPoids() const;
    double getDimensions() const;
    double getDistance() const;
    TypeColis getType() const;
    bool isUrgent() const;
    StatutColis getStatut() const;

    // ── Convertit l'énumération StatutColis en chaîne lisible ────────────────
    std::string getStatutString() const;

    // ── Convertit l'énumération TypeColis en chaîne lisible ──────────────────
    std::string getTypeString() const;

    // =========================================================
    //  SETTERS  (CT-05 : modification contrôlée des attributs)
    // =========================================================

    // Seul le statut est modifiable après création,
    // via les méthodes de transition dédiées ci-dessous.
    // Les autres attributs sont fixés à la création et ne changent pas.

    // =========================================================
    //  TRANSITIONS D'ÉTAT  (règle métier §2.4 point 4 & 6)
    // =========================================================

    // Passage EN_ATTENTE → EN_TRANSIT (effectué par l'agence)
    // Lève std::logic_error si le statut actuel n'est pas EN_ATTENTE.
    void mettreEnTransit();

    // Passage EN_TRANSIT → LIVRE (confirmé par le destinataire — EF-10)
    // Lève std::logic_error si le statut actuel n'est pas EN_TRANSIT.
    void confirmerLivraison();

    // Passage EN_ATTENTE → ANNULE (demandé par le client — EF-12)
    // Lève std::logic_error si le colis est déjà EN_TRANSIT ou LIVRE.
    void annuler();

    // =========================================================
    //  SURCHARGE D'OPÉRATEURS  (CT-03 mentionné en §5.2)
    // =========================================================

    // Opérateur << pour afficher les infos du colis dans un flux (ex: cout)
    friend std::ostream &operator<<(std::ostream &os, const Colis &colis);

    // Opérateur == pour comparer deux colis par leur ID
    bool operator==(const Colis &autre) const;
};

#endif // COLIS_H