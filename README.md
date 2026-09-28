# Benchmark Pile C++ — Tableau Dynamique vs Liste Chaînée (Avant / Après DLL)

## Prérequis
- Windows + `g++` MinGW (testé : GCC 6.3.0, `mingw32`, `-std=c++11`)
- Tous les fichiers sources à la racine du dossier

## 1. Générer la DLL

```powershell
g++ -shared -o pile.dll pile_dll.cpp "-Wl,--out-implib,libpile.dll.a" -O2 -std=c++11
```

Produit :
- `pile.dll` — vrai code (sert au **run**)
- `libpile.dll.a` — lib d'import / stubs (sert au **link** avec `-L. -lpile`)

## 2. Compiler les programmes

```powershell
# Benchmark AVANT DLL (headers directs)
g++ -o main.exe main.cpp -O2 -std=c++11

# Benchmark APRÈS DLL (via pile.dll, 1 run identique au main)
g++ -o bench_dll.exe bench_dll.cpp -L. -lpile -O2 -std=c++11


## 3. Exécuter (`pile.dll` doit être à côté des `.exe`)

```powershell
.\main.exe
.\bench_dll.exe
```

## Variante sans `.a` (lien direct)

```powershell
g++ -shared -o pile.dll pile_dll.cpp -O2 -std=c++11
g++ -o bench_dll.exe bench_dll.cpp pile.dll -O2 -std=c++11
```