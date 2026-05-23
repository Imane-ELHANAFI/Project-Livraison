#ifndef VELO_H
#define VELO_H

#include <string>
#include "Transporteur.h"
using namespace std;

class Velo : public Transporteur {
public:
    Velo(bool urgent = false);
    ~Velo() override {}

    bool  canDeliver  (double poids, double distance, string type) const override;
    float computeCost (double poids, double distance, string type) const override;
    int   computeDelay()                                           const override;
    void  afficher()                                               const override;
};

#endif