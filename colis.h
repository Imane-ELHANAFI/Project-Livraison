#ifndef COLIS_H
#define COLIS_H
#include <string>
#include <iostream>

enum class StatutColis {
    EN_ATTENTE,
    EN_TRANSIT,
    LIVRE,
    ANNULE
};

enum class TypeColis {
    STANDARD,
    FRAGILE
};

class Colis {
private:
    std::string id;
    double poids;
    double largeur;
    double longueur;
    double hauteur;
    double distance;
    TypeColis type;
    bool urgent;
    StatutColis statut;

    static int compteurId;
    static std::string genererID();
    void validerDonnees() const;

public:
    Colis(double poids, double largeur, double longueur, double hauteur,
          double distance, TypeColis type, bool urgent);

    virtual ~Colis() = default;

    // Getters
    std::string getId() const;
    double getPoids() const;
    double getLargeur() const;
    double getLongueur() const;
    double getHauteur() const;
    double getDistance() const;
    TypeColis getType() const;
    bool isUrgent() const;
    StatutColis getStatut() const;
    std::string getStatutString() const;
    std::string getTypeString() const;

    // Setters
    void setPoids(double poids);
    void setLargeur(double largeur);
    void setLongueur(double longueur);
    void setHauteur(double hauteur);
    void setDistance(double distance);
    void setType(std::string type);   // vérifie "fragile" ou "standard"
    void setUrgent(bool urgent);

    // Transitions d'état : EN_ATTENTE → EN_TRANSIT → LIVRE (irréversible)
    void mettreEnTransit();
    void confirmerLivraison();

    // Annulation autorisée uniquement si EN_ATTENTE
    void annuler();

    // Fonction amie pour l'affichage
    friend std::ostream& operator<<(std::ostream& os, const Colis& colis);

    bool operator==(const Colis& autre) const;
};

#endif