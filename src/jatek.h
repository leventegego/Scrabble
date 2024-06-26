#ifndef JATEK_H
#define JATEK_H

#include <sys/stat.h>

#include "debugmalloc.h"

#include "palya.h"
#include "jatekos.h"
#include "szotar.h"


// Az egy korben valaszthato opciok.
typedef enum e_parancs { KIRAKAS, PASSZ, INFO, MENTES, KILEPES } parancs;

typedef struct s_kirakas
{
    vektor hely, irany;
    char betuk[SZO_MERET]; // a betuk amit a jatekos lerak. lehet kozte '*'
    char szo[SZO_MERET];   // a szo amit a betuk jelentenek. ebben mar nincs '*'
} kirakas;


typedef struct s_jatek
{
    palya p;
    szotar szt;
    betu_k bk;
    jatekos jatekosok[JATEKOS_SZAM];
    int db_jatekos;
    jatekos * j; // a soron kovetkezo jatekos
} jatek;

// Bekeri a felhasznalotol es visszaadja a korben valasztott parancsot.
parancs kormenu(jatek * jat);
// A kapott jatekrol informaciokat ir ki a konzolra.
void jatek_print_info(jatek * jat);
// Bekeri egy kirakas adatait.
kirakas jatek_kirakas_beker(jatek * jat);
// Ellenorzi a kirakas szabalyossagat.
// Ha szabalyos, akkor kirakja a palyara, es megjeleniti a pontszamot.
// Ha nem akkor kiirja a hibauzenetet.
void jatek_kirakas_vegrehajt(jatek * jat, kirakas k);

// Beolvassa egy jatek adatait.
// Visszateresi erteke 0, ha sikeres, kulonben 1.
int jatek_beolvas(char * mappa_nev, jatek * jat);
// A jatek minden adatat torli.
void jatek_torol(jatek * jat);
// A kapott nevu mappaba irja a jatek adatait kulonbozo fileokba.
void jatek_kiir(char * mappa_nev, jatek * jat);

// A konzolra rajzolja a palyat es a jatek tobbi adatat.
void jatek_kirajzol(jatek * jat);
// Igaz erteket ad vissza, ha a jatek a szabalyok szerint mar befejezodott.
bool jatek_vege(jatek * jat);
// A jatek vegen kiirja a gyoztest.
void jatek_befejez(jatek * jat);
// A  jatek mentesi helyet keri be a felhasznalotol.
// A jatekot el is menti.
void jatek_mentes_parbeszed(jatek * jat);

// A soron kovetkezo jatekos tartojat feltolti a betukeszletbol kivett betukkel.
void jatekos_feltolt_betuk(jatek * jat);

// Ellenorzi, hogy a kapott kirakas kifer-e a palyara.
// Azt is ellenorzi, hogy a kapott szo illeszkedik-e a mar a palyan levo betukre.
bool palya_kifer(palya p, kirakas k);
// Ellenorzi, hogy a kapott kirakasban kerul-e le uj betu a palyara.
bool van_uj_betu(palya p, kirakas k);
// Ellenorzi a kirakas soran keletkezo meroleges szavak helyesseget.
bool jo_meroleges_szavak(palya p, szotar sz, kirakas k, char * hibas_szo_ide);
// Ellenorzi, hogy a kirakas egy mar lerakott szohoz kapcsolodik-e.
bool van_szomszed(palya p, kirakas k);
// Ellenorzi, hogy a soron kovetkezo jatekosnak vannak-e a kirakashoz szukseges betui.
bool jatekos_vannak_betuk(jatek * jat, kirakas k);

// Ellenorzi a kirakas helyesseget minden szabaly szerint.
// Ha nem szabalyos, akkor a hiba_ide argumentumba tolti a hiba okat.
bool szabalyos(jatek * jat, kirakas k, char * hiba_ide);

// A soron kovetkezo jatekostol elveszi a kirakashoz szukseges betuket.
void jatekos_levon_betuk(jatek * jat, kirakas k);
// A kapott jatek strukturaban meghatarozza hogy melyik jatekos jon.
void jatek_kovetkezo_jatekos(jatek * jat);
// Kiszamolja, hogy mennyi pontot er az adott kirakas.
// Figyelembe veszi a merolegesen keletkezo szavakat es az akciomezoket is.
int pontszam(palya p, kirakas k, betu_k bk);

// A kapott palyan megvalositja a kirakast.
void palya_kirak(palya p, kirakas k);


#endif