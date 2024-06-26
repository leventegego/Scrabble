#ifndef PALYA_INCLUDE
#define PALYA_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"

typedef struct s_vektor
{
    int x;
    int y;
} vektor;

#define VIZSZINTES (vektor){1, 0}
#define FUGGOLEGES (vektor){0, 1}

vektor vekt_osszead(vektor a, vektor b);
vektor vekt_negativ(vektor a);
bool vekt_egyenlo(vektor a, vektor b);

typedef struct s_palya
{
    int szeles, magas;
    char ** betuk;
    int ** szorzo_betu, ** szorzo_szo;
} palya;

// Dinamikusan letrehoz egy 2 dimenzios tombbot.
// A tombbot a hivonak kell felszabaditani a tomb2d_torol fuggveny hivasaval.
void ** tomb2d_letrehoz (int szeles, int magas, size_t elem_meret);
// Torli a tomb2d_letrehoz altal letrehozott tombbot.
void tomb2d_torol (void ** t, int szeles);
// A kapott nevu filebol beolvassa egy palya adatait a p parameterbe.
// A palyat a hivonak kell torolni a palya_torol fuggveny hivasaval.
// Visszateresi erteke 0, ha sikeres, kulonben 1.
int palya_beolvas(char * file_nev, palya * p);
// A kapott nevu fileba irja a palya adatait.
void palya_kiir(char * file_nev, palya p);
// Torli a palya adatait.
void palya_torol(palya p);

// A kapott vektort helyvektornak tekintve a palyan levo betut adja vissza.
char palya_betu(palya p, vektor hely);

// Igaz, ha a kapott vektor koordinatai a palya korlatain belul vannak.
bool palya_belul_van(palya p, vektor hely);
// Az "szo" nevu argumentumkent kapott tombbe tolt egy szot.
// Azt a szot valasztja ki, ami az adott palyan, adott helyen adott iranyban helyezkedik el.
void palya_szo_itt(palya p, vektor hely, vektor irany, char * szo);


#endif

