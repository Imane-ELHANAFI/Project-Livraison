# Simulateur de Système de Livraison

> Projet C++ — Module : Programmation Orientée Objet  
> Professeur : Youssef ES-SAADY  
> Auteurs : Imane ELHANAFI / Simane ETTHABITY  
> Établissement : Faculté Polydisciplinaire de Taroudant  
> Date : 20/04/2026

---

## Description

Un simulateur de gestion de livraison de colis développé en C++.  
Il modélise un système pour une entreprise de livraison gérant différents types de colis acheminés par différents moyens de transport (vélo, camion, drone, avion) avec calcul des coûts, délais et suivi logistique.

---

## Objectifs

| #   | Objectif                                                                              |
| --- | ------------------------------------------------------------------------------------- |
| 1   | Permettre la création de colis (poids, fragilité, états)                              |
| 2   | Calculer automatiquement le coût et le délai selon le transporteur                    |
| 3   | Assurer le suivi logistique (en attente → en transit → livré)                         |
| 4   | Générer un historique et un rapport récapitulatif des livraisons                      |
| 5   | Implémenter un algorithme d'attribution automatique SANS condition sur les types      |
| 6   | Code propre, versionné sur GitHub, avec README, rapport PDF et vidéo de démonstration |

---

## Structure du projet

```
Simulateur de Système de Livraison/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── Colis.h
│   ├── Transporteur.h
│   ├── Avion.h
│   ├── Camion.h
│   ├── Drone.h
│   ├── Velo.h
│   ├── Personne.h
│   ├── Client_agence.h
│   └── Destinataire.h
├── src/
│   ├── main.cpp
│   ├── Colis.cpp
│   ├── Avion.cpp
│   ├── Camion.cpp
│   ├── Drone.cpp
│   ├── Velo.cpp
│   ├── Client_agence.cpp
│   └── Destinataire.cpp
└── rapport/
    └── rapport_final.pdf
```

---

## Compilation et exécution

### Avec CMake (recommandé)

```bash
mkdir build
cd build
cmake ..
make
./simulateur
```

### Avec g++ directement

```bash
g++ src/*.cpp -I include -o simulateur
./simulateur
```

---

## Transporteurs et règles d'attribution

| Transporteur | Conditions d'éligibilité                        |
| ------------ | ----------------------------------------------- |
| Vélo         | distance ≤ 10 km ET poids ≤ 5 kg ET non fragile |
| Drone        | poids ≤ 3 kg ET distance ≤ 30 km ET non fragile |
| Camion       | toujours disponible (cas par défaut)            |
| Avion        | distance > 500 km                               |

---

## Calcul des coûts

| Transporteur | Formule de base              | Supplément urgence |
| ------------ | ---------------------------- | ------------------ |
| Vélo         | poids × 2 + distance × 0.5   | × 1.5              |
| Camion       | poids × 1.5 + distance × 0.3 | × 1.3              |
| Drone        | poids × 4 + distance × 1.2   | × 2.0              |
| Avion        | poids × 3 + distance × 0.8   | × 1.8              |

---

## Délais de livraison

| Transporteur | Délai normal | Délai urgent |
| ------------ | ------------ | ------------ |
| Vélo         | 3 jours      | 1 jour       |
| Camion       | 5 jours      | 1 jour       |
| Drone        | 1 jour       | Même jour    |
| Avion        | 7 jours      | 1 jour       |

---

## Statuts d'un colis

```
EN_ATTENTE → EN_TRANSIT → LIVRE
EN_ATTENTE → ANNULE
```

| Statut     | Description                                            |
| ---------- | ------------------------------------------------------ |
| EN_ATTENTE | Colis créé, pas encore pris en charge                  |
| EN_TRANSIT | Colis en cours d'acheminement                          |
| LIVRE      | Livraison confirmée par le destinataire (irréversible) |
| ANNULE     | Commande annulée (uniquement si EN_ATTENTE)            |

---

## Rôles et droits

| Rôle         | Droits                                         |
| ------------ | ---------------------------------------------- |
| Client       | Créer / Suivre / Annuler / Recevoir le rapport |
| Agence       | Valider / Calculer / Générer le rapport        |
| Destinataire | Confirmer la livraison                         |

---

## Concepts C++ utilisés

- Encapsulation (attributs privés, getters/setters)
- Héritage (`Personne` → `Client_agence`, `Destinataire`)
- Classe abstraite (`Transporteur` avec méthodes virtuelles pures)
- Polymorphisme (`computeCost()`, `computeDelay()`, `canDeliver()`)
- Surcharge d'opérateurs (`<<`, `==`)
- Fonctions amies

---

## Dépôt GitHub

[https://github.com/Imane-ELHANAFI/Project-Livraison](https://github.com/Imane-ELHANAFI/Project-Livraison)
