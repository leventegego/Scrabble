#ifndef SZOTAR_H
#define SZOTAR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "debugmalloc.h"

// Egy szo merete vegjellel egyutt.
#define SZO_MERET 32


typedef struct s_betukeszlet
{
    char * betuk;
    int * ertekek;
    int * darabszam;
    int ossz;
    int meret;
} betu_k;

// A kapott nevu filebol beolvassa egy betukeszlet adatait a bk parameterbe.
// A hivo feladata azt torolni a bk_torol fuggvennyel.
// Visszateresi erteke 0, ha sikeres, kulonben 1.
int bk_beolvas(char * file_nev, betu_k * bk);
// A kapott nevu fileba irja a betukeszlet adatait.
void bk_kiir(char * file_nev, betu_k bk);
// Torli a betukeszlet adatait.
void bk_torol(betu_k bk);

// Visszaadja a betukeszletben tarolt, az adott betuhoz rendelt erteket.
// Ha nincs ilyen betu a keszletben, akkor -1
int betu_ertek(char b, betu_k bk);
// Veletlenszeruen ad vissza egy betut, amit ki is vesz a keszletbol.
// Figyelembe veszi a bent levo betuk szamat.
char random_betu_kivesz(betu_k * bk);



typedef struct s_szotar
{
    char (*szavak)[SZO_MERET];
    int meret;
} szotar;

// A kapott nevu vilebol beolvassa egy szotar adatait.
// A hivo felelossege torolni a szotar_torol fuggvennyel.
// Visszateresi erteke 0, ha sikeres volt, kulonben 1.
int szotar_beolvas(char * file_nev, szotar * sz);
// Ellenorzi, hogy a kapott szo benne van-e a szotarban.
bool szotar_benne_van(szotar szt, char * szo);
// Torli a szotar adatait.
void szotar_torol(szotar szt);
// Visszaadja egy szo osszes betujenek ertekenek osszeget.
int szo_ertek(char * szo, betu_k bk);




#endif

