#define BUILD_PILE_DLL
#include "pile_dll.h"

// (Pas d'instanciation explicite avec __declspec ici : MinGW ignore
// l'attribut apres definition du template et emet un warning.
// L'instanciation est forcee par les wrappers <int> et la fonction
// parenthesesCorrectes qui utilisent Pile_Tableau<char>.)

// ---------------------------------------------------------------------------
// Fonction C++ exportee (reprise de parenthesesCorrectes.cpp)
// ---------------------------------------------------------------------------
bool parenthesesCorrectes(const std::string& expression) {
    Pile_Tableau<char> pile;
    const std::string ouvrantes = "([{";
    const std::string fermantes = ")]}";

    for (char c : expression) {
        if (ouvrantes.find(c) != std::string::npos) {
            pile.push(c);
        } else if (fermantes.find(c) != std::string::npos) {
            if (pile.isEmpty())
                return false;

            char sommet = pile.top();
            pile.pop();

            std::size_t indexOuvrant = ouvrantes.find(sommet);
            std::size_t indexFermant = fermantes.find(c);

            if (indexOuvrant != indexFermant)
                return false;
        }
    }

    return pile.isEmpty();
}

// ---------------------------------------------------------------------------
// API C : wrappers autour des classes templates instanciees en <int>
// ---------------------------------------------------------------------------
extern "C" {

void* PileTableauInt_create() {
    return new Pile_Tableau<int>();
}
void PileTableauInt_destroy(void* p) {
    delete static_cast<Pile_Tableau<int>*>(p);
}
void PileTableauInt_push(void* p, int value) {
    static_cast<Pile_Tableau<int>*>(p)->push(value);
}
void PileTableauInt_pop(void* p) {
    static_cast<Pile_Tableau<int>*>(p)->pop();
}
int PileTableauInt_top(void* p, int* ok) {
    try {
        int v = static_cast<Pile_Tableau<int>*>(p)->top();
        if (ok) *ok = 1;
        return v;
    } catch (...) {
        if (ok) *ok = 0;
        return 0;
    }
}
int PileTableauInt_isEmpty(void* p) {
    return static_cast<Pile_Tableau<int>*>(p)->isEmpty() ? 1 : 0;
}
size_t PileTableauInt_size(void* p) {
    return static_cast<Pile_Tableau<int>*>(p)->size();
}

void* PileListeInt_create() {
    return new Pile_Liste<int>();
}
void PileListeInt_destroy(void* p) {
    delete static_cast<Pile_Liste<int>*>(p);
}
void PileListeInt_push(void* p, int value) {
    static_cast<Pile_Liste<int>*>(p)->push(value);
}
void PileListeInt_pop(void* p) {
    static_cast<Pile_Liste<int>*>(p)->pop();
}
int PileListeInt_top(void* p, int* ok) {
    try {
        int v = static_cast<Pile_Liste<int>*>(p)->top();
        if (ok) *ok = 1;
        return v;
    } catch (...) {
        if (ok) *ok = 0;
        return 0;
    }
}
int PileListeInt_isEmpty(void* p) {
    return static_cast<Pile_Liste<int>*>(p)->isEmpty() ? 1 : 0;
}
size_t PileListeInt_size(void* p) {
    return static_cast<Pile_Liste<int>*>(p)->size();
}

int parenthesesCorrectesC(const char* expression) {
    if (!expression) return 0;
    return parenthesesCorrectes(std::string(expression)) ? 1 : 0;
}

} // extern "C"
