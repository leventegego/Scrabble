#ifndef JATEKOS_H
#define JATEKOS_H

#include <stdio.h>

#include "debugmalloc.h"

#include "szotar.h"

#define TARTO_MERET 7
#define JATEKOS_SZAM 6
#define NEV_MERET 64

typedef struct s_jatekos
{
    char nev[NEV_MERET];
    int pontszam;
    char tarto[TARTO_MERET + 1];
} jatekos;

// Beolvas egy jatekosokbol allo tombbot a 'jatekosok' argumentumba.
// A tombbot a hivonak kell letrehozni es torolni.
// Legfeljebb annyi jatekost olvas be, amennyit a 'max' argumentumban kap.
// A beolvasott adatok szamat a db valtozoba menti.
// Beolvassa a soron kovetkezo jatekos sorszamat az i_jatekos valtozoba.
// Visszateresi erteke 0, ha sikeres volt, kulonben 1.
int jatekosok_beolvas(char * file_nev, jatekos * jatekosok, int * db, int *i_jatekos, int max);
// Kiirja a kapott nevu fileba a jatekosokbol allo tomb adatait.
void jatekosok_kiir(char * file_nev, jatekos * jatekosok, int i_jatekos, int db);


#endif
