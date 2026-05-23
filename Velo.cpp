#include "Velo.h"
#include<string>
using namespace std;

Velo::Velo(bool urgent) : Transporteur("velo", urgent) {}

bool Velo::canDeliver(double poids, double distance, string type) const {
    return (distance <= 10.0 &&
            poids    <=  5.0 &&
            type     != "fragile");
}

float Velo::computeCost(double poids, double distance, string type) const {
    float cost = (poids * 2.0f + distance * 0.5f)*10.0f;
    if (urgent) cost *= 1.5f;
    return cost;
}

int Velo::computeDelay() const {
    return urgent ? 1 : 3;
}

void Velo::afficher() const {
    cout << "=== Velo ===" << endl;
    Transporteur::afficher();
    cout << "Delai : " << computeDelay() << " jour(s)" << endl;
}