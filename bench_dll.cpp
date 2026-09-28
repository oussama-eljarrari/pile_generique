#include <iostream>
#include <iomanip>
#include <chrono>
#include "pile_dll.h"

using namespace std::chrono;

// Mesures d'un passage complet : empilement x N, consultation x 1, dépilement x N.
struct Mesures {
    double empilement = 0;
    double consultation = 0;
    double depilement = 0;
    double total = 0;
};

static Mesures mesurerTableau(int n) {
    Mesures mesures;
    void* pile = PileTableauInt_creer();

    auto debut = high_resolution_clock::now();
    for (int i = 0; i < n; i++) PileTableauInt_empiler(pile, i);
    auto apresEmpilement = high_resolution_clock::now();

    int reussi = 0;
    volatile int valeur = PileTableauInt_sommet(pile, &reussi);
    (void)valeur;
    auto apresConsultation = high_resolution_clock::now();

    for (int i = 0; i < n; i++) PileTableauInt_depiler(pile);
    auto apresDepilement = high_resolution_clock::now();

    PileTableauInt_detruire(pile);

    mesures.empilement   = duration<double, std::milli>(apresEmpilement - debut).count();
    mesures.consultation = duration<double, std::milli>(apresConsultation - apresEmpilement).count();
    mesures.depilement   = duration<double, std::milli>(apresDepilement - apresConsultation).count();
    mesures.total = mesures.empilement + mesures.consultation + mesures.depilement;
    return mesures;
}

static Mesures mesurerListe(int n) {
    Mesures mesures;
    void* pile = PileListeInt_creer();

    auto debut = high_resolution_clock::now();
    for (int i = 0; i < n; i++) PileListeInt_empiler(pile, i);
    auto apresEmpilement = high_resolution_clock::now();

    int reussi = 0;
    volatile int valeur = PileListeInt_sommet(pile, &reussi);
    (void)valeur;
    auto apresConsultation = high_resolution_clock::now();

    for (int i = 0; i < n; i++) PileListeInt_depiler(pile);
    auto apresDepilement = high_resolution_clock::now();

    PileListeInt_detruire(pile);

    mesures.empilement   = duration<double, std::milli>(apresEmpilement - debut).count();
    mesures.consultation = duration<double, std::milli>(apresConsultation - apresEmpilement).count();
    mesures.depilement   = duration<double, std::milli>(apresDepilement - apresConsultation).count();
    mesures.total = mesures.empilement + mesures.consultation + mesures.depilement;
    return mesures;
}

int main() {
    const int N = 100000;
    const int REPETITIONS = 1; // 1 passage, à l'identique du main avant-DLL

    std::cout << "Comparaison via pile.dll (API C exportee)" << std::endl;
    std::cout << N << " elements, 1 passage (identique au main avant-DLL).\n" << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    Mesures moyenneTableau, moyenneListe;
    for (int essai = 0; essai < REPETITIONS; essai++) {
        Mesures tableau = mesurerTableau(N);
        Mesures liste = mesurerListe(N);
        moyenneTableau.empilement += tableau.empilement;
        moyenneTableau.consultation += tableau.consultation;
        moyenneTableau.depilement += tableau.depilement;
        moyenneTableau.total += tableau.total;
        moyenneListe.empilement += liste.empilement;
        moyenneListe.consultation += liste.consultation;
        moyenneListe.depilement += liste.depilement;
        moyenneListe.total += liste.total;
        std::cout << "Passage " << (essai + 1) << " : Tableau total=" << tableau.total
                  << " ms | Liste total=" << liste.total << " ms" << std::endl;
    }
    moyenneTableau.empilement /= REPETITIONS;
    moyenneTableau.consultation /= REPETITIONS;
    moyenneTableau.depilement /= REPETITIONS;
    moyenneTableau.total /= REPETITIONS;
    moyenneListe.empilement /= REPETITIONS;
    moyenneListe.consultation /= REPETITIONS;
    moyenneListe.depilement /= REPETITIONS;
    moyenneListe.total /= REPETITIONS;

    std::cout << "\n===== TEST 1 : Pile_Tableau<int> via DLL (tableau dynamique) =====" << std::endl;
    std::cout << "Empilement   : " << moyenneTableau.empilement   << " ms" << std::endl;
    std::cout << "Consultation : " << moyenneTableau.consultation << " ms" << std::endl;
    std::cout << "Depilement   : " << moyenneTableau.depilement   << " ms" << std::endl;
    std::cout << "Total        : " << moyenneTableau.total        << " ms" << std::endl;

    std::cout << "\n===== TEST 2 : Pile_Liste<int> via DLL (liste chainee) =====" << std::endl;
    std::cout << "Empilement   : " << moyenneListe.empilement   << " ms" << std::endl;
    std::cout << "Consultation : " << moyenneListe.consultation << " ms" << std::endl;
    std::cout << "Depilement   : " << moyenneListe.depilement   << " ms" << std::endl;
    std::cout << "Total        : " << moyenneListe.total        << " ms" << std::endl;

    std::cout << "\n===== COMPARAISON =====" << std::endl;
    std::cout << std::setprecision(2);
    auto comparer = [](const char* nom, double tableau, double liste) {
        std::string gagnant = (tableau < liste) ? "Tableau" : (liste < tableau ? "Liste" : "Egalite");
        double ratio = (tableau > 0 && liste > 0) ? ((tableau < liste) ? liste / tableau : tableau / liste) : 0;
        std::cout << nom << " : Tableau=" << tableau << " ms | Liste=" << liste
                  << " ms -> " << gagnant << " gagne (x" << ratio << ")" << std::endl;
    };
    comparer("Empilement  ", moyenneTableau.empilement, moyenneListe.empilement);
    comparer("Consultation", moyenneTableau.consultation, moyenneListe.consultation);
    comparer("Depilement  ", moyenneTableau.depilement, moyenneListe.depilement);
    comparer("Total       ", moyenneTableau.total, moyenneListe.total);

    std::cout << "\n=== FIN DU TEST ===" << std::endl;
    return 0;
}
