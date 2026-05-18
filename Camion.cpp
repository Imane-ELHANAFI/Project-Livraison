#include "Camion.h"

Camion::Camion(bool urgent) : Transporteur("camion", urgent) {}

bool Camion::canDeliver(double poids, double distance, string type) const {
    return true;
}

float Camion::computeCost(double poids, double distance, string type) const {
    float cost = poids * 1.5f + distance * 0.3f;
    if (urgent) cost *= 1.3f;
    return cost;
}

int Camion::computeDelay() const {
    return urgent ? 1 : 5;
}

void Camion::afficher() const {
    cout << "=== Camion ===" << endl;
    Transporteur::afficher();
    cout << "Delai : " << computeDelay() << " jour(s)" << endl;
}