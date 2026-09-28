#include <iostream>
#include <iomanip>
#include <chrono>
#include "Pile_Tableau.hpp"
#include "Pile_Liste.hpp"

using namespace std::chrono;

int main() {
    const int N = 100000;

    std::cout << N << " elements a traiter.\n" << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    // ===== TEST 1 : Pile_Tableau<int> =====
    {
        Pile_Tableau<int> pile;

        auto debut = high_resolution_clock::now();
        for (int i = 0; i < N; i++) pile.empiler(i);
        auto apresEmpilement = high_resolution_clock::now();

        volatile int valeur = pile.sommet();
        (void)valeur;
        auto apresConsultation = high_resolution_clock::now();

        for (int i = 0; i < N; i++) pile.depiler();
        auto apresDepilement = high_resolution_clock::now();

        double empilement   = duration<double, std::milli>(apresEmpilement - debut).count();
        double consultation = duration<double, std::milli>(apresConsultation - apresEmpilement).count();
        double depilement   = duration<double, std::milli>(apresDepilement - apresConsultation).count();

        std::cout << "===== TEST 1 : Pile_Tableau<int> (tableau dynamique) =====" << std::endl;
        std::cout << "Empilement   : " << empilement   << " ms" << std::endl;
        std::cout << "Consultation : " << consultation << " ms" << std::endl;
        std::cout << "Depilement   : " << depilement   << " ms" << std::endl;
        std::cout << std::endl;
    }

    // ===== TEST 2 : Pile_Liste<int> =====
    {
        Pile_Liste<int> pile;

        auto debut = high_resolution_clock::now();
        for (int i = 0; i < N; i++) pile.empiler(i);
        auto apresEmpilement = high_resolution_clock::now();

        volatile int valeur = pile.sommet();
        (void)valeur;
        auto apresConsultation = high_resolution_clock::now();

        for (int i = 0; i < N; i++) pile.depiler();
        auto apresDepilement = high_resolution_clock::now();

        double empilement   = duration<double, std::milli>(apresEmpilement - debut).count();
        double consultation = duration<double, std::milli>(apresConsultation - apresEmpilement).count();
        double depilement   = duration<double, std::milli>(apresDepilement - apresConsultation).count();

        std::cout << "===== TEST 2 : Pile_Liste<int> (liste chainee) =====" << std::endl;
        std::cout << "Empilement   : " << empilement   << " ms" << std::endl;
        std::cout << "Consultation : " << consultation << " ms" << std::endl;
        std::cout << "Depilement   : " << depilement   << " ms" << std::endl;
        std::cout << std::endl;
    }

    std::cout << "=== FIN DU TEST ===" << std::endl;

    return 0;
}
