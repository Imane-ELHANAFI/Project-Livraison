#ifndef TRANSPORTEUR_H
#define TRANSPORTEUR_H

#include <iostream>
#include <string>
using namespace std;

class Transporteur {
protected:
    string type_trsp;
    bool   urgent;

public:
    Transporteur(string type, bool u = false)
        : type_trsp(type), urgent(u) {}

    virtual ~Transporteur() {}

    string getType()   const { return type_trsp; }
    bool   getUrgent() const { return urgent;    }

    void setType  (string t) { type_trsp = t; }
    void setUrgent(bool   u) { urgent    = u; }

    virtual bool  canDeliver  (double poids, double distance, string type) const = 0;
    virtual float computeCost (double poids, double distance, string type) const = 0;
    virtual int   computeDelay()                                           const = 0;

    virtual void afficher() const {
        cout << "Transporteur : " << type_trsp << endl;
        cout << "Urgent       : " << (urgent ? "oui" : "non") << endl;
    }

    friend ostream& operator<<(ostream& out, const Transporteur& t) {
        out << "Transporteur : " << t.type_trsp << endl;
        out << "Urgent       : " << (t.urgent ? "oui" : "non") << endl;
        return out;
    }
};

#endif