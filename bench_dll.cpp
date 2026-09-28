#include <iostream>
#include <iomanip>
#include <chrono>
#include "pile_dll.h"

using namespace std::chrono;

struct Mesures {
    double empilement = 0;    // push x N
    double consultation = 0;  // top x 1
    double depilement = 0;    // pop x N
    double total = 0;
};

static Mesures benchTableau(int N) {
    Mesures m;
    void* p = PileTableauInt_create();

    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < N; i++) PileTableauInt_push(p, i);
    auto t1 = high_resolution_clock::now();

    int ok = 0;
    volatile int val = PileTableauInt_top(p, &ok);
    (void)val;
    auto t2 = high_resolution_clock::now();

    for (int i = 0; i < N; i++) PileTableauInt_pop(p);
    auto t3 = high_resolution_clock::now();

    PileTableauInt_destroy(p);

    m.empilement   = duration<double, std::milli>(t1 - t0).count();
    m.consultation = duration<double, std::milli>(t2 - t1).count();
    m.depilement   = duration<double, std::milli>(t3 - t2).count();
    m.total = m.empilement + m.consultation + m.depilement;
    return m;
}

static Mesures benchListe(int N) {
    Mesures m;
    void* p = PileListeInt_create();

    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < N; i++) PileListeInt_push(p, i);
    auto t1 = high_resolution_clock::now();

    int ok = 0;
    volatile int val = PileListeInt_top(p, &ok);
    (void)val;
    auto t2 = high_resolution_clock::now();

    for (int i = 0; i < N; i++) PileListeInt_pop(p);
    auto t3 = high_resolution_clock::now();

    PileListeInt_destroy(p);

    m.empilement   = duration<double, std::milli>(t1 - t0).count();
    m.consultation = duration<double, std::milli>(t2 - t1).count();
    m.depilement   = duration<double, std::milli>(t3 - t2).count();
    m.total = m.empilement + m.consultation + m.depilement;
    return m;
}

int main() {
    const int N = 100000;
    const int REP = 1; // 1 run identique au main avant-DLL

    std::cout << "Benchmark via pile.dll (API C exportee)" << std::endl;
    std::cout << N << " elements, 1 run (identique au main avant-DLL).\n" << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    Mesures moyT, moyL;
    for (int r = 0; r < REP; r++) {
        Mesures t = benchTableau(N);
        Mesures l = benchListe(N);
        moyT.empilement += t.empilement; moyT.consultation += t.consultation;
        moyT.depilement += t.depilement; moyT.total += t.total;
        moyL.empilement += l.empilement; moyL.consultation += l.consultation;
        moyL.depilement += l.depilement; moyL.total += l.total;
        std::cout << "Run " << (r + 1) << " : Tableau total=" << t.total
                  << " ms | Liste total=" << l.total << " ms" << std::endl;
    }
    moyT.empilement /= REP; moyT.consultation /= REP; moyT.depilement /= REP; moyT.total /= REP;
    moyL.empilement /= REP; moyL.consultation /= REP; moyL.depilement /= REP; moyL.total /= REP;

    std::cout << "\n===== TEST 1 : Pile_Tableau<int> via DLL (tableau dynamique) =====" << std::endl;
    std::cout << "Empilement   : " << moyT.empilement   << " ms" << std::endl;
    std::cout << "Consultation : " << moyT.consultation << " ms" << std::endl;
    std::cout << "Depilement   : " << moyT.depilement   << " ms" << std::endl;
    std::cout << "Total        : " << moyT.total        << " ms" << std::endl;

    std::cout << "\n===== TEST 2 : Pile_Liste<int> via DLL (liste chainee) =====" << std::endl;
    std::cout << "Empilement   : " << moyL.empilement   << " ms" << std::endl;
    std::cout << "Consultation : " << moyL.consultation << " ms" << std::endl;
    std::cout << "Depilement   : " << moyL.depilement   << " ms" << std::endl;
    std::cout << "Total        : " << moyL.total        << " ms" << std::endl;

    std::cout << "\n===== COMPARAISON =====" << std::endl;
    std::cout << std::setprecision(2);
    auto cmp = [](const char* nom, double t, double l) {
        std::string gagnant = (t < l) ? "Tableau" : (l < t ? "Liste" : "Egalite");
        double ratio = (t > 0 && l > 0) ? ((t < l) ? l / t : t / l) : 0;
        std::cout << nom << " : Tableau=" << t << " ms | Liste=" << l
                  << " ms -> " << gagnant << " gagne (x" << ratio << ")" << std::endl;
    };
    cmp("Empilement  ", moyT.empilement, moyL.empilement);
    cmp("Consultation", moyT.consultation, moyL.consultation);
    cmp("Depilement  ", moyT.depilement, moyL.depilement);
    cmp("Total       ", moyT.total, moyL.total);

    std::cout << "\n=== FIN DU TEST ===" << std::endl;
    return 0;
}
