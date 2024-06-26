#include "palya.h"


vektor vekt_osszead(vektor a, vektor b)
{
    return (vektor){a.x + b.x, a.y + b.y};
}

vektor vekt_negativ(vektor a)
{
    return (vektor){-a.x, -a.y};
}

bool vekt_egyenlo(vektor a, vektor b)
{
    return a.x == b.x && a.y == b.y;
}



void ** tomb2d_letrehoz (int szeles, int magas, size_t elem_meret)
{
    void ** ptr = malloc(szeles * sizeof(void *));
    for(int x = 0; x < szeles; ++x)
        ptr[x] = malloc(magas * elem_meret);
    return ptr;
}

void tomb2d_torol (void ** t, int szeles)
{
    for(int x = 0; x < szeles; ++x)
        free(t[x]);
    free(t);
}


int palya_beolvas(char * file_nev, palya * p)
{

    FILE * file = fopen(file_nev, "r");
    if(file == NULL)
        return 1;

    fscanf(file, "%d %d%*c", &p->szeles, &p->magas);

    p->betuk = (char**)tomb2d_letrehoz(p->szeles, p->magas, sizeof(char));
    p->szorzo_betu = (int**)tomb2d_letrehoz(p->szeles, p->magas, sizeof(int));
    p->szorzo_szo = (int**)tomb2d_letrehoz(p->szeles, p->magas, sizeof(int));

    for(int y = 0; y < p->magas; ++y)
    {
        for(int x = 0; x < p->szeles; ++x)
            fscanf(file, "%c", &p->betuk[x][y]);
        fscanf(file, "%*c");
    }

    for(int y = 0; y < p->magas; ++y)
        for(int x = 0; x < p->szeles; ++x)
            fscanf(file, "%d", &p->szorzo_betu[x][y]);

    for(int y = 0; y < p->magas; ++y)
        for(int x = 0; x < p->szeles; ++x)
            fscanf(file, "%d", &p->szorzo_szo[x][y]);

    fclose(file);

    return 0;
}

void palya_kiir(char * file_nev, palya p)
{
    FILE * file = fopen(file_nev, "w+");

    fprintf(file, "%d %d\n", p.szeles, p.magas);

    for(int y = 0; y < p.magas; ++y)
    {
        for(int x = 0; x < p.szeles; ++x)
            fprintf(file, "%c", p.betuk[x][y]);
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    for(int y = 0; y < p.magas; ++y)
    {
        for(int x = 0; x < p.szeles; ++x)
            fprintf(file, "%d ", p.szorzo_betu[x][y]);
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    for(int y = 0; y < p.magas; ++y)
    {
        for(int x = 0; x < p.szeles; ++x)
            fprintf(file, "%d ", p.szorzo_szo[x][y]);
        fprintf(file, "\n");
    }

    fclose(file);
}

void palya_torol(palya p)
{
    tomb2d_torol((void**)p.betuk, p.szeles);
    tomb2d_torol((void**)p.szorzo_betu, p.szeles);
    tomb2d_torol((void**)p.szorzo_szo, p.szeles);
}


char palya_betu(palya p, vektor hely)
{
    return p.betuk[hely.x][hely.y];
}

bool palya_belul_van(palya p, vektor hely)
{
    return hely.x >= 0 && hely.y >= 0 && hely.x < p.szeles && hely.y < p.magas;
}


void palya_szo_itt(palya p, vektor hely, vektor irany, char * szo)
{
    vektor h = hely;
    while(palya_belul_van(p, h) && palya_betu(p, h) != ' ')
        h = vekt_osszead(h, vekt_negativ(irany));
    h = vekt_osszead(h, irany);

    int sz_i = 0;
    while(palya_belul_van(p, h) && palya_betu(p, h) != ' ')
    {
        szo[sz_i] = palya_betu(p, h);
        h = vekt_osszead(h, irany);
        ++sz_i;
    }

    szo[sz_i] = '\0';
}


