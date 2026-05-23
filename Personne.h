#pragma once
#include <string>
using namespace std ;
class Personne{
    protected: 
        string nom ;
        string prenom ;
        string num_Tele ;
        string adresse ;
    public :
        Personne();
        Personne(string nom , string prenom , string num_Tele , string adresse);

        string getnom() const;
        string getprenom() const;
        string getnum_Tele() const;
        string getadresse() const;

        void setnom(string nom);
        void setprenom(string prenom);
        void setnum_Tele(string num_Tele);
        void setadresse(string adresse);

        virtual void affichage() ;
        friend ostream& operator<<(ostream& os , const Personne& p) ;
        ~Personne() ;
};