#include <iostream>
#include "Colis.h"
using namespace std;

int main() {

    cout << "\n=== Creation des colis ===" << endl;

    Colis c1(5.0, 30.0, 20.0, 15.0, 100.0, TypeColis::STANDARD, false);
    Colis c2(2.0, 10.0, 10.0, 10.0, 50.0,  TypeColis::FRAGILE,  true);
    Colis c3(8.0, 40.0, 30.0, 20.0, 200.0, TypeColis::STANDARD, true);

    cout << c1 << endl;
    cout << c2 << endl;
    cout << c3 << endl;

    c2.mettreEnTransit();
    c2.confirmerLivraison();
    cout << c2 << endl;


    /*cout << "\n=== Test des setters ===" << endl;
    c1.setPoids(7.5);
    c1.setLargeur(35.0);
    c1.setLongueur(25.0);
    c1.setHauteur(18.0);
    c1.setDistance(150.0);
    c1.setType("fragile");
    c1.setUrgent(true);
    cout << c1 << endl;


    cout << "\n=== Test des transitions d'etat ===" << endl;

    cout << "-- c2 : EN_ATTENTE -> EN_TRANSIT --" << endl;
    c2.mettreEnTransit();
    cout << "Statut : " << c2.getStatutString() << endl;

    cout << "-- c2 : EN_TRANSIT -> LIVRE --" << endl;
    c2.confirmerLivraison();
    cout << "Statut : " << c2.getStatutString() << endl;

    cout << "-- c3 : EN_ATTENTE -> ANNULE --" << endl;
    c3.annuler();
    cout << "Statut : " << c3.getStatutString() << endl;


    cout << "\n=== Test operateur == ===" << endl;
    if (c1 == c2)
        cout << "c1 et c2 sont identiques." << endl;
    else
        cout << "c1 et c2 sont differents." << endl;


    cout << "\n=== Test erreur : poids negatif ===" << endl;
    Colis c4(-1.0, 10.0, 10.0, 10.0, 50.0, TypeColis::STANDARD, false);
*/
    return 0;
}