#include "jatekos.h"

// file formatum: [jatekos sorszam][ismetelve ->](\n\n[jatekos nev]\n[pontszam] [\[betuk\]])(..)
int jatekosok_beolvas(char * file_nev, jatekos * jatekosok, int * db, int * i_jatekos, int max)
{
    FILE * file = fopen(file_nev, "r");
    if(file == NULL)
        return 1;

    fscanf(file, "%d%*c", i_jatekos);

    *db = 0;
    char f [64]; // a beolvasas formatuma
    sprintf(f, " %%%d[^\n]%%d [%%%d[^\n]]", NEV_MERET - 1, TARTO_MERET);

    while(*db < max && fscanf(file, f, jatekosok[*db].nev, &jatekosok[*db].pontszam, jatekosok[*db].tarto) != EOF)
        ++*db;

    fclose(file);

    return 0;
}

void jatekosok_kiir(char * file_nev, jatekos * jatekosok, int i_jatekos, int db)
{
    FILE * file = fopen(file_nev, "w+");
    fprintf(file, "%d\n", i_jatekos);

    for(int i = 0; i < db; ++i)
        fprintf(file, "%s\n%d [%s]\n\n", jatekosok[i].nev, jatekosok[i].pontszam, jatekosok[i].tarto);

    fclose(file);
}

