#ifndef CAMION_H
#define CAMION_H

#include "Transporteur.h"

class Camion : public Transporteur {
public:
    Camion(bool urgent = false);
    ~Camion() override {}

    bool  canDeliver  (double poids, double distance, string type) const override;
    float computeCost (double poids, double distance, string type) const override;
    int   computeDelay()                                           const override;
    void  afficher()                                               const override;
};

#endif