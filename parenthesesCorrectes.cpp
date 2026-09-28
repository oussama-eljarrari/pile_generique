#include <iostream>
#include <string>
#include "Pile_Tableau.hpp"   // ou "Pile_Liste.hpp"

bool parenthesesCorrectes(const std::string& expression) {
    Pile_Tableau<char> pile;
    const std::string ouvrantes = "([{";
    const std::string fermantes = ")]}";

    for (char c : expression) {
        // Symbole ouvrant : on empile
        if (ouvrantes.find(c) != std::string::npos) {
            pile.push(c);
        }
        // Symbole fermant : on verifie la correspondance
        else if (fermantes.find(c) != std::string::npos) {
            if (pile.isEmpty())
                return false; // fermeture sans ouverture correspondante

            char sommet = pile.top();
            pile.pop();

            std::size_t indexOuvrant = ouvrantes.find(sommet);
            std::size_t indexFermant = fermantes.find(c);

            if (indexOuvrant != indexFermant)
                return false; // mauvais type de fermeture (ex : "(]")
        }
        // Tout autre caractere (lettres, chiffres, operateurs) est ignore
    }

    // Correct si tous les symboles ouverts ont ete refermes
    return pile.isEmpty();
}

int main() {
    std::string tests[] = {
        "(A + B) * [C - D]",
        "(A + B] * (C - D)",
        "((A + B) * C",
        "{[A + (B * C)] - D}",
        "A + B) * (C"
    };

    for (const auto& expr : tests) {
        std::cout << expr << "  ->  "
                   << (parenthesesCorrectes(expr) ? "CORRECT" : "INCORRECT")
                   << std::endl;
    }

    

    return 0;
}
