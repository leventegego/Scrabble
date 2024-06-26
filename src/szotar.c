#include "szotar.h"

int bk_beolvas(char * file_nev, betu_k * bk)
{
    FILE * file = fopen(file_nev, "r");
    if(file == NULL)
        return 1;

    fscanf(file, "%d%*c", &bk->meret);
    bk->betuk = malloc(bk->meret * sizeof(char));
    bk->ertekek = malloc(bk->meret * sizeof(int));
    bk->darabszam = malloc(bk->meret * sizeof(int));

    bk->ossz = 0;
    for(int i = 0; i < bk->meret; ++i)
    {
        fscanf(file, "%c %d %d\n", &bk->betuk[i], &bk->ertekek[i], &bk->darabszam[i]);
        bk->ossz += bk->darabszam[i];
    }

    fclose(file);

    return 0;
}

void bk_kiir(char * file_nev, betu_k bk)
{
    FILE * file = fopen(file_nev, "w+");

    fprintf(file, "%d\n", bk.meret);
    for(int i = 0; i < bk.meret; ++i)
        fprintf(file, "%c %d %d\n", bk.betuk[i], bk.ertekek[i], bk.darabszam[i]);

    fclose(file);
}

void bk_torol(betu_k bk)
{
    free(bk.betuk);
    free(bk.ertekek);
    free(bk.darabszam);
}

int betu_ertek(char b, betu_k bk)
{
    b = tolower(b);
    for(int i = 0; i < bk.meret; ++i)
        if(bk.betuk[i] == b)
            return bk.ertekek[i];

    return -1;
}


int szotar_beolvas(char * file_nev, szotar * sz)
{
    sz->meret = 0;
    sz->szavak = malloc(0);
    int max_db = 0;

    FILE * file = fopen(file_nev, "r");
    if(file == NULL)
        return 1;

    bool vege = false;
    while(!vege)
    {
        max_db += 100; // 100-asaval noveljuk a tomb meretet
        sz->szavak = realloc(sz->szavak, max_db * SZO_MERET * sizeof(char));

        while(sz->meret < max_db && !vege)
        {
            char str [128];
            if(fscanf(file, "%s", str) == EOF)
                vege = true;

            int len = strlen(str);
            if(len > 1 && len < SZO_MERET) // csak 1 betunel hosszabb szavakat hasznalunk
            {
                for(int i = 0; i < len; ++i)
                    sz->szavak[sz->meret][i] = tolower(str[i]); // minden szot kis betuvel tarolunk
                sz->szavak[sz->meret][len] = '\0';
                ++sz->meret;
            }
        }
    }

    fclose(file);

    return 0;
}

bool szotar_benne_van(szotar szt, char * szo)
{
    int min = 0, max = szt.meret - 1;
    while(max - min > 1)
    {
        int i = min + (max - min - 1) / 2;
        int cmp = strcmp(szo, szt.szavak[i]);

        if(cmp < 0) max = i + 1;
        else if (cmp > 0) min = i + 1;
        else return true;
    }

    return false;
}

void szotar_torol(szotar szt)
{
    free(szt.szavak);
}

char random_betu_kivesz(betu_k * bk)
{
    int r = rand() % bk->ossz;
    int j = 0;
    for(int i = 0; i < bk->meret; ++i)
    {
        j += bk->darabszam[i];
        if(j > r)
        {
            --bk->darabszam[i];
            --bk->ossz;
            return bk->betuk[i];
        }
    }

    return ' ';
}


int szo_ertek(char * szo, betu_k bk)
{
    int sum = 0;
    for(char * i = szo; *i != '\0'; ++i)
        sum += betu_ertek(*i, bk);

    return sum;
}

