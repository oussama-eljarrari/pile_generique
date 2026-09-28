#ifndef PILE_LISTE_HPP
#define PILE_LISTE_HPP

#include <stdexcept>

// Pile générique implémentée à l'aide d'une liste chaînée simple.
// Implémentation manuelle (sans std::list ni std::forward_list) :
// chaque nœud est géré directement avec new/delete.
template <typename T>
class Pile_Liste {
private:
    struct Noeud {
        T valeur;
        Noeud* suivant;
        Noeud(const T& v, Noeud* s) : valeur(v), suivant(s) {}
    };

    Noeud* tete;
    std::size_t compteur;

public:
    Pile_Liste() : tete(nullptr), compteur(0) {}

    ~Pile_Liste() {
        while (!estVide())
            depiler();
    }

    // Ajoute une valeur au sommet de la pile.
    void empiler(const T& valeur) {
        tete = new Noeud(valeur, tete);
        ++compteur;
    }

    // Retire la valeur au sommet de la pile.
    void depiler() {
        if (estVide())
            throw std::underflow_error("Pile vide");
        Noeud* temporaire = tete;
        tete = tete->suivant;
        delete temporaire;
        --compteur;
    }

    // Consulte la valeur au sommet sans la retirer.
    T& sommet() {
        if (estVide())
            throw std::underflow_error("Pile vide");
        return tete->valeur;
    }

    // Indique si la pile ne contient aucun élément.
    bool estVide() const {
        return tete == nullptr;
    }

    // Retourne le nombre d'éléments contenus dans la pile.
    std::size_t taille() const {
        return compteur;
    }
};

#endif
