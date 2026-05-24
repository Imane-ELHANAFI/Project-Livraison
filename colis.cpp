#include "Colis.h"
#include <string>
#include <iostream>
using namespace std;

int Colis::compteurId = 0;

std::string Colis::genererID()
{
    ++compteurId;
    char buffer[10];
    sprintf(buffer, "COL-%04d", compteurId);
    return std::string(buffer);
}

void Colis::validerDonnees() const
{
    if (poids <= 0)
    {
        cout << "Erreur : le poids doit être supérieur à 0." << endl;
        exit(1);
    }
    if (largeur <= 0)
    {
        cout << "Erreur : la largeur doit être supérieure à 0." << endl;
        exit(1);
    }
    if (longueur <= 0)
    {
        cout << "Erreur : la longueur doit être supérieure à 0." << endl;
        exit(1);
    }
    if (hauteur <= 0)
    {
        cout << "Erreur : la hauteur doit être supérieure à 0." << endl;
        exit(1);
    }
    if (distance <= 0)
    {
        cout << "Erreur : la distance doit être supérieure à 0." << endl;
        exit(1);
    }
}

Colis::Colis(double poids, double largeur, double longueur, double hauteur,
             double distance, TypeColis type, bool urgent)
    : poids(poids), largeur(largeur), longueur(longueur), hauteur(hauteur),
      distance(distance), type(type), urgent(urgent), statut(StatutColis::EN_ATTENTE)
{
    validerDonnees();
    this->id = genererID();
}

// Getters
std::string Colis::getId() const { return id; }
double Colis::getPoids() const { return poids; }
double Colis::getLargeur() const { return largeur; }
double Colis::getLongueur() const { return longueur; }
double Colis::getHauteur() const { return hauteur; }
double Colis::getDistance() const { return distance; }
TypeColis Colis::getType() const { return type; }
bool Colis::isUrgent() const { return urgent; }
StatutColis Colis::getStatut() const { return statut; }

std::string Colis::getStatutString() const
{
    switch (statut)
    {
    case StatutColis::EN_ATTENTE:
        return "En attente";
    case StatutColis::EN_TRANSIT:
        return "En transit";
    case StatutColis::LIVRE:
        return "Livré";
    case StatutColis::ANNULE:
        return "Annulé";
    default:
        return "Inconnu";
    }
}

std::string Colis::getTypeString() const
{
    return (type == TypeColis::FRAGILE) ? "Fragile" : "Standard";
}

// Setters
void Colis::setPoids(double poids)
{
    if (poids <= 0)
    {
        cout << "Erreur : le poids doit être supérieur à 0." << endl;
        exit(1);
    }
    this->poids = poids;
}

void Colis::setLargeur(double largeur)
{
    if (largeur <= 0)
    {
        cout << "Erreur : la largeur doit être supérieure à 0." << endl;
        exit(1);
    }
    this->largeur = largeur;
}

void Colis::setLongueur(double longueur)
{
    if (longueur <= 0)
    {
        cout << "Erreur : la longueur doit être supérieure à 0." << endl;
        exit(1);
    }
    this->longueur = longueur;
}

void Colis::setHauteur(double hauteur)
{
    if (hauteur <= 0)
    {
        cout << "Erreur : la hauteur doit être supérieure à 0." << endl;
        exit(1);
    }
    this->hauteur = hauteur;
}

void Colis::setDistance(double distance)
{
    if (distance <= 0)
    {
        cout << "Erreur : la distance doit être supérieure à 0." << endl;
        exit(1);
    }
    this->distance = distance;
}

void Colis::setType(string type)
{
    if (type == "fragile" || type == "Fragile")
        this->type = TypeColis::FRAGILE;
    else if (type == "standard" || type == "Standard")
        this->type = TypeColis::STANDARD;
    else
    {
        cout << "Erreur : le type doit être 'fragile' ou 'standard'." << endl;
        exit(1);
    }
}

void Colis::setUrgent(bool urgent)
{
    this->urgent = urgent;
}

// Transitions d'état : EN_ATTENTE → EN_TRANSIT → LIVRE (irréversible)
void Colis::mettreEnTransit()
{
    if (statut != StatutColis::EN_ATTENTE)
    {
        cout << "Erreur [" << id << "] : impossible de passer EN_TRANSIT "
             << "depuis l'état '" << getStatutString() << "'." << endl;
        exit(1);
    }
    statut = StatutColis::EN_TRANSIT;
}

void Colis::confirmerLivraison()
{
    if (statut != StatutColis::EN_TRANSIT)
    {
        cout << "Erreur [" << id << "] : impossible de confirmer la livraison "
             << "depuis l'état '" << getStatutString() << "'." << endl;
        exit(1);
    }
    statut = StatutColis::LIVRE;
}

// Annulation autorisée uniquement si EN_ATTENTE
void Colis::annuler()
{
    if (statut == StatutColis::LIVRE)
    {
        cout << "Erreur [" << id << "] : un colis livré ne peut pas être annulé." << endl;
        exit(1);
    }
    if (statut == StatutColis::EN_TRANSIT)
    {
        cout << "Erreur [" << id << "] : un colis en transit ne peut pas être annulé." << endl;
        exit(1);
    }
    if (statut == StatutColis::ANNULE)
    {
        cout << "Erreur [" << id << "] : ce colis est déjà annulé." << endl;
        exit(1);
    }
    statut = StatutColis::ANNULE;
}

// Fonction amie pour l'affichage
std::ostream &operator<<(std::ostream &os, const Colis &c)
{
    os << "┌─────────────────────────────────────┐\n"
       << "│  Colis ID    : " << c.getId() << "\n"
       << "│  Poids       : " << c.getPoids() << " kg\n"
       << "│  Largeur     : " << c.getLargeur() << " cm\n"
       << "│  Longueur    : " << c.getLongueur() << " cm\n"
       << "│  Hauteur     : " << c.getHauteur() << " cm\n"
       << "│  Distance    : " << c.getDistance() << " km\n"
       << "│  Type        : " << c.getTypeString() << "\n"
       << "│  Urgent      : " << (c.isUrgent() ? "Oui" : "Non") << "\n"
       << "│  Statut      : " << c.getStatutString() << "\n"
       << "└─────────────────────────────────────┘";
    return os;
}

bool Colis::operator==(const Colis &autre) const
{
    return this->id == autre.id;
}