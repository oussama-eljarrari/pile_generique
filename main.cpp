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
        Pile_Tableau<int> s;

        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) s.push(i);
        auto afterPush = high_resolution_clock::now();

        volatile int val = s.top();
        (void)val;
        auto afterTop = high_resolution_clock::now();

        for (int i = 0; i < N; i++) s.pop();
        auto afterPop = high_resolution_clock::now();

        double empilement   = duration<double, std::milli>(afterPush - start).count();
        double consultation = duration<double, std::milli>(afterTop - afterPush).count();
        double depilement   = duration<double, std::milli>(afterPop - afterTop).count();

        std::cout << "===== TEST 1 : Pile_Tableau<int> (tableau dynamique) =====" << std::endl;
        std::cout << "Empilement   : " << empilement   << " ms" << std::endl;
        std::cout << "Consultation : " << consultation << " ms" << std::endl;
        std::cout << "Depilement   : " << depilement   << " ms" << std::endl;
        std::cout << std::endl;
    }

    // ===== TEST 2 : Pile_Liste<int> =====
    {
        Pile_Liste<int> s;

        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) s.push(i);
        auto afterPush = high_resolution_clock::now();

        volatile int val = s.top();
        (void)val;
        auto afterTop = high_resolution_clock::now();

        for (int i = 0; i < N; i++) s.pop();
        auto afterPop = high_resolution_clock::now();

        double empilement   = duration<double, std::milli>(afterPush - start).count();
        double consultation = duration<double, std::milli>(afterTop - afterPush).count();
        double depilement   = duration<double, std::milli>(afterPop - afterTop).count();

        std::cout << "===== TEST 2 : Pile_Liste<int> (liste chainee) =====" << std::endl;
        std::cout << "Empilement   : " << empilement   << " ms" << std::endl;
        std::cout << "Consultation : " << consultation << " ms" << std::endl;
        std::cout << "Depilement   : " << depilement   << " ms" << std::endl;
        std::cout << std::endl;
    }

    std::cout << "=== FIN DU TEST ===" << std::endl;

    return 0;
}
