#ifndef AVION_H
#define AVION_H

#include "Transporteur.h"

class Avion : public Transporteur
{
public:
    Avion(bool urgent = false);
    ~Avion() override {}

    bool canDeliver(double poids, double distance, string type) const override;
    float computeCost(double poids, double distance, string type) const override;
    int computeDelay() const override;
    void afficher() const override;
};

#endif