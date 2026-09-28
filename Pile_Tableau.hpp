#ifndef PILE_TABLEAU_HPP
#define PILE_TABLEAU_HPP

#include <vector>
#include <stdexcept>

// Pile generique implementee a l'aide d'un tableau dynamique.
// Utilise std::vector (STL) comme conteneur sous-jacent : la
// gestion de la capacite et des reallocations est deleguee a la STL.
template <typename T>
class Pile_Tableau {
private:
    std::vector<T> data;

public:
    Pile_Tableau() = default;

    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (isEmpty())
            throw std::underflow_error("Pile vide");
        data.pop_back();
    }

    T& top() {
        if (isEmpty())
            throw std::underflow_error("Pile vide");
        return data.back();
    }

    bool isEmpty() const {
        return data.empty();
    }

    std::size_t size() const {
        return data.size();
    }
};

#endif
