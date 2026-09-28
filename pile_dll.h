#ifndef PILE_DLL_H
#define PILE_DLL_H

#include <string>
#include <cstddef>

// Macro d'export / import pour Windows DLL (MinGW / MSVC)
#ifdef BUILD_PILE_DLL
  #define PILE_API __declspec(dllexport)
#else
  #define PILE_API __declspec(dllimport)
#endif

#include "Pile_Tableau.hpp"
#include "Pile_Liste.hpp"

// NOTE : les templates restent definis dans les .hpp (header-only).
// La DLL force leur instanciation via les wrappers ci-dessous (<int>,
// <char>, <double>) et exporte une API C++ + une API C stables.

// ---------------------------------------------------------------------------
// Fonction utilitaire exportee (logique de parenthesesCorrectes.cpp, sans main)
// ---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C++" {
#endif

PILE_API bool parenthesesCorrectes(const std::string& expression);

#ifdef __cplusplus
} // extern "C++"
#endif

// ---------------------------------------------------------------------------
// API C (extern "C") : evite le name-mangling C++, ideale pour utiliser la DLL
// depuis n'importe quel langage / compilateur. Operent sur des handles opaques.
// ---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Pile tableau d'int ---
PILE_API void* PileTableauInt_create();
PILE_API void  PileTableauInt_destroy(void* p);
PILE_API void  PileTableauInt_push(void* p, int value);
PILE_API void  PileTableauInt_pop(void* p);
PILE_API int   PileTableauInt_top(void* p, int* ok); // ok=1 si succes, 0 si vide
PILE_API int   PileTableauInt_isEmpty(void* p);
PILE_API size_t PileTableauInt_size(void* p);

// --- Pile liste d'int ---
PILE_API void* PileListeInt_create();
PILE_API void  PileListeInt_destroy(void* p);
PILE_API void  PileListeInt_push(void* p, int value);
PILE_API void  PileListeInt_pop(void* p);
PILE_API int   PileListeInt_top(void* p, int* ok);
PILE_API int   PileListeInt_isEmpty(void* p);
PILE_API size_t PileListeInt_size(void* p);

// --- Verification de parentheses (version C) ---
PILE_API int parenthesesCorrectesC(const char* expression); // 1 = CORRECT, 0 = INCORRECT

#ifdef __cplusplus
} // extern "C"
#endif

#endif // PILE_DLL_H
