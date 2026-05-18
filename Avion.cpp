#include "Avion.h"

Avion::Avion(bool urgent) : Transporteur("avion", urgent) {}

bool Avion::canDeliver(double poids, double distance, string type) const
{
    return (distance > 500.0);
}

float Avion::computeCost(double poids, double distance, string type) const
{
    float cost = poids * 3.0f + distance * 0.8f;
    if (urgent)
        cost *= 1.8f;
    return cost;
}

int Avion::computeDelay() const
{
    return urgent ? 1 : 7;
}

void Avion::afficher() const
{
    cout << "=== Avion ===" << endl;
    Transporteur::afficher();
    cout << "Delai : " << computeDelay() << " jour(s)" << endl;
}