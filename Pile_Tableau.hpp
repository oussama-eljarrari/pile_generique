#ifndef PILE_TABLEAU_HPP
#define PILE_TABLEAU_HPP

#include <vector>
#include <stdexcept>

// Pile générique implémentée à l'aide d'un tableau dynamique.
// Utilise std::vector (STL) comme conteneur sous-jacent : la
// gestion de la capacité et des réallocations est déléguée à la STL.
template <typename T>
class Pile_Tableau {
private:
    std::vector<T> donnees;

public:
    Pile_Tableau() = default;

    // Ajoute une valeur au sommet de la pile.
    void empiler(const T& valeur) {
        donnees.push_back(valeur);
    }

    // Retire la valeur au sommet de la pile.
    void depiler() {
        if (estVide())
            throw std::underflow_error("Pile vide");
        donnees.pop_back();
    }

    // Consulte la valeur au sommet sans la retirer.
    T& sommet() {
        if (estVide())
            throw std::underflow_error("Pile vide");
        return donnees.back();
    }

    // Indique si la pile ne contient aucun élément.
    bool estVide() const {
        return donnees.empty();
    }

    // Retourne le nombre d'éléments contenus dans la pile.
    std::size_t taille() const {
        return donnees.size();
    }
};

#endif
