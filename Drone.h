#ifndef DRONE_H
#define DRONE_H

#include "Transporteur.h"

class Drone : public Transporteur {
public:
    Drone(bool urgent = false);
    ~Drone() override {}

    bool  canDeliver  (double poids, double distance, string type) const override;
    float computeCost (double poids, double distance, string type) const override;
    int   computeDelay()                                           const override;
    void  afficher()                                               const override;
};

#endif