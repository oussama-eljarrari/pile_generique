#ifndef PILE_DLL_H
#define PILE_DLL_H

#include <string>
#include <cstddef>

// Macro d'export / import pour les DLL Windows (MinGW / MSVC).
// Définir CONSTRUCTION_PILE_DLL côté DLL pour exporter,
// ne rien définir côté client pour importer.
#ifdef CONSTRUCTION_PILE_DLL
  #define API_PILE __declspec(dllexport)
#else
  #define API_PILE __declspec(dllimport)
#endif

#include "Pile_Tableau.hpp"
#include "Pile_Liste.hpp"

// NOTE : les patrons restent définis dans les .hpp (en-têtes seuls).
// La DLL force leur instanciation via les enveloppes ci-dessous (<int>,
// <char>, <double>) et exporte une API C++ + une API C stables.

// ---------------------------------------------------------------------------
// Fonction utilitaire exportée (logique de parenthesesCorrectes.cpp, sans main)
// ---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C++" {
#endif

API_PILE bool parenthesesCorrectes(const std::string& expression);

#ifdef __cplusplus
} // extern "C++"
#endif

// ---------------------------------------------------------------------------
// API C (extern "C") : évite la décoration des noms C++, idéale pour utiliser
// la DLL depuis n'importe quel langage / compilateur. Travaille sur des
// poignées opaques.
// ---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Pile tableau d'entiers ---
API_PILE void* PileTableauInt_creer();
API_PILE void  PileTableauInt_detruire(void* pile);
API_PILE void  PileTableauInt_empiler(void* pile, int valeur);
API_PILE void  PileTableauInt_depiler(void* pile);
API_PILE int   PileTableauInt_sommet(void* pile, int* reussi); // reussi=1 si succès, 0 si vide
API_PILE int   PileTableauInt_estVide(void* pile);
API_PILE size_t PileTableauInt_taille(void* pile);

// --- Pile liste d'entiers ---
API_PILE void* PileListeInt_creer();
API_PILE void  PileListeInt_detruire(void* pile);
API_PILE void  PileListeInt_empiler(void* pile, int valeur);
API_PILE void  PileListeInt_depiler(void* pile);
API_PILE int   PileListeInt_sommet(void* pile, int* reussi);
API_PILE int   PileListeInt_estVide(void* pile);
API_PILE size_t PileListeInt_taille(void* pile);

// --- Vérification des parenthèses (version C) ---
API_PILE int parenthesesCorrectesC(const char* expression); // 1 = CORRECT, 0 = INCORRECT

#ifdef __cplusplus
} // extern "C"
#endif

#endif // PILE_DLL_H
