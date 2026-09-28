#define CONSTRUCTION_PILE_DLL
#include "pile_dll.h"

// (Pas d'instanciation explicite avec __declspec ici : MinGW ignore
// l'attribut après définition du patron et émet un avertissement.
// L'instanciation est forcée par les enveloppes <int> et la fonction
// parenthesesCorrectes qui utilise Pile_Tableau<char>.)

// ---------------------------------------------------------------------------
// Fonction C++ exportée (reprise de parenthesesCorrectes.cpp)
// ---------------------------------------------------------------------------
bool parenthesesCorrectes(const std::string& expression) {
    Pile_Tableau<char> pile;
    const std::string ouvrantes = "([{";
    const std::string fermantes = ")]}";

    for (char c : expression) {
        // Symbole ouvrant : on empile
        if (ouvrantes.find(c) != std::string::npos) {
            pile.empiler(c);
        }
        // Symbole fermant : on vérifie la correspondance
        else if (fermantes.find(c) != std::string::npos) {
            if (pile.estVide())
                return false; // fermeture sans ouverture correspondante

            char dessus = pile.sommet();
            pile.depiler();

            std::size_t indiceOuvrant = ouvrantes.find(dessus);
            std::size_t indiceFermant = fermantes.find(c);

            if (indiceOuvrant != indiceFermant)
                return false; // mauvais type de fermeture (ex : "(]")
        }
        // Tout autre caractère (lettres, chiffres, opérateurs) est ignoré
    }

    // Correct si tous les symboles ouverts ont été refermés
    return pile.estVide();
}

// ---------------------------------------------------------------------------
// API C : enveloppes autour des classes patrons instanciées en <int>
// ---------------------------------------------------------------------------
extern "C" {

void* PileTableauInt_creer() {
    return new Pile_Tableau<int>();
}
void PileTableauInt_detruire(void* pile) {
    delete static_cast<Pile_Tableau<int>*>(pile);
}
void PileTableauInt_empiler(void* pile, int valeur) {
    static_cast<Pile_Tableau<int>*>(pile)->empiler(valeur);
}
void PileTableauInt_depiler(void* pile) {
    static_cast<Pile_Tableau<int>*>(pile)->depiler();
}
int PileTableauInt_sommet(void* pile, int* reussi) {
    try {
        int v = static_cast<Pile_Tableau<int>*>(pile)->sommet();
        if (reussi) *reussi = 1;
        return v;
    } catch (...) {
        if (reussi) *reussi = 0;
        return 0;
    }
}
int PileTableauInt_estVide(void* pile) {
    return static_cast<Pile_Tableau<int>*>(pile)->estVide() ? 1 : 0;
}
size_t PileTableauInt_taille(void* pile) {
    return static_cast<Pile_Tableau<int>*>(pile)->taille();
}

void* PileListeInt_creer() {
    return new Pile_Liste<int>();
}
void PileListeInt_detruire(void* pile) {
    delete static_cast<Pile_Liste<int>*>(pile);
}
void PileListeInt_empiler(void* pile, int valeur) {
    static_cast<Pile_Liste<int>*>(pile)->empiler(valeur);
}
void PileListeInt_depiler(void* pile) {
    static_cast<Pile_Liste<int>*>(pile)->depiler();
}
int PileListeInt_sommet(void* pile, int* reussi) {
    try {
        int v = static_cast<Pile_Liste<int>*>(pile)->sommet();
        if (reussi) *reussi = 1;
        return v;
    } catch (...) {
        if (reussi) *reussi = 0;
        return 0;
    }
}
int PileListeInt_estVide(void* pile) {
    return static_cast<Pile_Liste<int>*>(pile)->estVide() ? 1 : 0;
}
size_t PileListeInt_taille(void* pile) {
    return static_cast<Pile_Liste<int>*>(pile)->taille();
}

int parenthesesCorrectesC(const char* expression) {
    if (!expression) return 0;
    return parenthesesCorrectes(std::string(expression)) ? 1 : 0;
}

} // extern "C"
