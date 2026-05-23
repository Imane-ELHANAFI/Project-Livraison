#include"Personne.h"
#include<string>
#include<iostream>
using namespace std ;

Personne::Personne() : nom(""), prenom(""), num_Tele(""), adresse("") {}
Personne::Personne(string nom , string prenom , string num_Tele , string adresse){
    this->nom = nom ;
    this->prenom = prenom ;
    this->num_Tele = num_Tele ;
    this->adresse = adresse ;
}
void Personne::setnom(string nom){ this->nom = nom ; }
void Personne::setprenom(string prenom){ this->prenom = prenom ; }
void Personne::setnum_Tele(string num_Tele){ this->num_Tele = num_Tele ; }
void Personne::setadresse(string adresse){ this->adresse = adresse ; }
string Personne::getnom() const{ return nom ; }
string Personne::getprenom() const{ return prenom ; }
string Personne::getnum_Tele() const{ return num_Tele ; }
string Personne::getadresse() const{ return adresse ; }
void Personne::affichage(){
    cout << "Nom : " << nom << endl;
    cout << "Prenom : " << prenom << endl;
    cout << "Num_Tele : " << num_Tele << endl;
    cout << "Adresse : " << adresse << endl;
}
ostream& operator<<(ostream& os , const Personne& p){
    os << "Nom : " << p.nom << endl ;
    os << "Prenom : " << p.prenom << endl ;
    os << "Num_Tele : " << p.num_Tele << endl ;
    os << "Adresse : " << p.adresse << endl ;
    return os ;
}
Personne::~Personne() {}
