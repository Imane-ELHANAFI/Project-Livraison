#include "Drone.h"

Drone::Drone(bool urgent) : Transporteur("drone", urgent) {}

bool Drone::canDeliver(double poids, double distance, string type) const
{
    return (poids <= 3.0 &&
            distance <= 30.0 &&
            type != "fragile");
}

float Drone::computeCost(double poids, double distance, string type) const
{
    float cost = poids * 4.0f + distance * 1.2f;
    if (urgent)
        cost *= 2.0f;
    return cost;
}

int Drone::computeDelay() const
{
    return urgent ? 0 : 1;
}

void Drone::afficher() const
{
    cout << "=== Drone ===" << endl;
    Transporteur::afficher();
    cout << "Delai : " << computeDelay() << " jour(s)" << endl;
}