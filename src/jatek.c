#include "jatek.h"

parancs kormenu(jatek * jat)
{
    printf("\n--- Opciok ---\n0: kirakas\n1: passz\n2: info\n3: mentes\n4: kilepes\n");
    int parancs;
    scanf("%d%*c", &parancs);
    return parancs;
}

void jatek_print_info(jatek * jat)
{
    printf("Betukeszlet:\n");
    for(int i = 0; i < jat->bk.meret; ++i)
        printf("%c:%2d%s", jat->bk.betuk[i], jat->bk.ertekek[i], i % 3 == 2 ? "\n" : "   ");

    printf(" \nPontszam-tablazat:\n");
    for(int i = 0; i < jat->db_jatekos; ++i)
        printf("%-15s: %d\n", jat->jatekosok[i].nev, jat->jatekosok[i].pontszam);
}

kirakas jatek_kirakas_beker(jatek * jat)
{
    // bekerjuk az adatokat
    kirakas k;
    char x; int y;  // a helyvektor koordinatai
    char irany_c;   // irany karaktere
    printf("Kirakas (betuk hely irany): ");
    scanf("%s %c%d %c%*c", k.betuk, &x, &y, &irany_c);

    // az input alapjan meghatarozzuk a kirakas helyet es iranyat
    k.hely = (vektor){ toupper(x) - 'A', y - 1 };
    if(irany_c == 'f')      k.irany = FUGGOLEGES;
    else if(irany_c == 'v') k.irany = VIZSZINTES;
    else
    {
        k.irany = VIZSZINTES; // ha nem 'v' es nem 'f', akkor legyen vizszintes
    }

    // minden joker-re megkerdezi, hogy az milyen betukent lesz lerakva
    strcpy(k.szo, k.betuk);
    for(char * joker = strchr(k.szo, '*'); joker != NULL; joker = strchr(k.szo, '*'))
    {
        printf("Milyen betut raknal a '*' helyere? ");
        scanf("%c%*c", joker);
    }


    return k;
}

void jatek_kirakas_vegrehajt(jatek * jat, kirakas k)
{
    // eldontjuk, hogy szabalyos e a kirakas es ha igen akkor meg is valositjuk
    char hiba[256];
    if(szabalyos(jat, k, hiba)) // a 'hiba' valtozoba tolti a hiba uzenetet ha van.
    {
        int pont = pontszam(jat->p, k, jat->bk);
        jat->j->pontszam += pont;
        printf("Pontszam: %d\n", pont);

        jatekos_levon_betuk(jat, k);
        palya_kirak(jat->p, k);
        jatek_kovetkezo_jatekos(jat);
    }
    else
        printf("HIBA: %s\n", hiba);
}

int jatek_beolvas(char * mappa_nev, jatek * jat)
{
    if(szotar_beolvas("szotar/magyar_ascii_modositott.txt", &jat->szt) != 0)
        return 1;

    char str [256];
    sprintf(str, "%s/palya.txt", mappa_nev);
    if(palya_beolvas(str, &jat->p) != 0)
        return 1;

    sprintf(str, "%s/jatekosok.txt", mappa_nev);
    int i_jatekos;
    if(jatekosok_beolvas(str, jat->jatekosok, &jat->db_jatekos, &i_jatekos ,JATEKOS_SZAM) != 0)
        return 1;
    jat->j = jat->jatekosok + i_jatekos;

    sprintf(str, "%s/betukeszlet.txt", mappa_nev);
    if (bk_beolvas(str, &jat->bk) != 0)
        return 1;

    return 0;
}

void jatek_torol(jatek * jat)
{
    bk_torol(jat->bk);
    szotar_torol(jat->szt);
    palya_torol(jat->p);
}

void jatek_kiir(char * mappa_nev, jatek * jat)
{
    mkdir(mappa_nev);

    char str[256];

    sprintf(str, "%s/palya.txt", mappa_nev);
    palya_kiir(str, jat->p);

    sprintf(str, "%s/jatekosok.txt", mappa_nev);
    jatekosok_kiir(str, jat->jatekosok, jat->j - jat->jatekosok, jat->db_jatekos);

    sprintf(str, "%s/betukeszlet.txt", mappa_nev);
    bk_kiir(str, jat->bk);

    sprintf(str, "%s/jatek.txt", mappa_nev);
}

void jatek_kirajzol(jatek * jat)
{
    printf("  ");
    for(int x = 0; x < jat->p.szeles; ++x)
        printf("  %c", 'A' + x); // betuk a tetejen
    printf("\n");

    for(int y = 0; y < jat->p.magas; ++y)
    {
        printf("   ");
        for(int i = 0; i < jat->p.szeles; ++i)
            printf("+--"); // vizszintes vonal
        printf("+\n%02d ", y + 1); // szam bal oldalt

        for(int x = 0; x < jat-> p.szeles; ++x) // sor
        {
            if(jat->p.betuk[x][y] == ' ')
            {
                if     (jat->p.szorzo_szo[x][y] > 1)     printf("|*%d", jat->p.szorzo_szo[x][y]);
                else if(jat->p.szorzo_betu[x][y] > 1)    printf("|+%d", jat->p.szorzo_betu[x][y]);
                else printf("|  ");
            }
            else printf("| %c", toupper(jat->p.betuk[x][y]));
        }

        printf("| %02d\n", y + 1); // szam jobb oldalt
    }

    printf("   ");
    for(int i = 0; i < jat->p.szeles; ++i)
        printf("+--"); // legalso vizszintes vonal
    printf("+\n  ");

    for(int x = 0; x < jat->p.szeles; ++x) printf("  %c", 'A' + x); // betuk alatta
    printf("\n\n");

    printf(" \n%s jon.\nBetuk: %s\n", jat->j->nev, jat->j->tarto);
}

bool jatek_vege(jatek * jat)
{
    return jat->bk.ossz <= 0;
}

void jatek_befejez(jatek * jat)
{
    // kivalasztjuk a nyertest
    int i_nyertes = 0;
    for(int i = 1; i < jat->db_jatekos; ++i)
        if(jat->jatekosok[i].pontszam > jat->jatekosok[i_nyertes].pontszam)
            i_nyertes = i;

    printf("Jatek vege. %s nyert.\nNyomj entert a befejezeshez.\n", jat->jatekosok[i_nyertes].nev);
    scanf("%*c");
}

void jatek_mentes_parbeszed(jatek * jat)
{
    char mappa_nev [256];
    printf("Mentesi mappa? ");
    scanf("%s%*c", mappa_nev);
    jatek_kiir(mappa_nev, jat);
}

void jatekos_feltolt_betuk(jatek * jat)
{
    for(int i = 0; i < TARTO_MERET; ++i)
        if(jat->j->tarto[i] == ' ')
            jat->j->tarto[i] = random_betu_kivesz(&jat->bk);
}

bool jo_meroleges_szavak(palya p, szotar sz, kirakas k, char * hibas_szo_ide)
{
    vektor h = k.hely;
    vektor meroleges_irany = vekt_egyenlo(k.irany, VIZSZINTES) ? FUGGOLEGES : VIZSZINTES;

    for(char * pb = k.szo; *pb != '\0'; ++pb)
    {
        if(palya_betu(p, h) == ' ')
        {
            char meroleges_szo[SZO_MERET]; // a szo kirakasaval arra merolegesen is keletkezhetnek szavak
            p.betuk[h.x][h.y] = *pb;  // behelyettesitjuk a betut megnezzuk milyen szo jon ki
            palya_szo_itt(p, h, meroleges_irany, meroleges_szo);
            p.betuk[h.x][h.y] = ' ';

            if(strlen(meroleges_szo) > 1 && !szotar_benne_van(sz, meroleges_szo))
            {
                sprintf(hibas_szo_ide, meroleges_szo);
                return false;
            }
        }

        h = vekt_osszead(h, k.irany);
    }

    return true;
}

bool van_szomszed(palya p, kirakas k)
{
    vektor h = k.hely;
    vektor kozep = (vektor){p.szeles / 2, p.magas / 2};
    vektor meroleges_irany = vekt_egyenlo(k.irany, VIZSZINTES) ? FUGGOLEGES : VIZSZINTES;

    for(char * pb = k.szo; *pb != '\0'; ++pb)
    {
        vektor szomszed1 = vekt_osszead(h, meroleges_irany);
        vektor szomszed2 = vekt_osszead(h, vekt_negativ(meroleges_irany));
        if(vekt_egyenlo(h, kozep) // kozepre akkor is lehet rakni, ha nincs szomszed (itt kell kezdeni)
            || (palya_belul_van(p, szomszed1) && palya_betu(p, szomszed1) != ' ')
            || (palya_belul_van(p, szomszed2) && palya_betu(p, szomszed2) != ' '))
            return true;

        h = vekt_osszead(h, k.irany);
    }

    return false;
}

bool palya_kifer(palya p, kirakas k)
{
    vektor elotte = vekt_osszead(k.hely, vekt_negativ(k.irany));
    if(palya_belul_van(p, elotte) && palya_betu(p, elotte) != ' ')
        return false;

    vektor h = k.hely;

    for(char * pb = k.szo; *pb != '\0'; ++pb)
    {
        if(!palya_belul_van(p, h) || (palya_betu(p, h) != ' ' && palya_betu(p, h) != *pb))
            return false;

        h = vekt_osszead(h, k.irany);
    }

    if(palya_belul_van(p, h) && palya_betu(p, h) != ' ')
        return false;

    return true;
}

bool van_uj_betu(palya p, kirakas k)
{
    vektor h = k.hely;

    for(char * pb = k.szo; *pb != '\0'; ++pb)
    {
        if(palya_betu(p, h) == ' ')
            return true;
        h = vekt_osszead(h, k.irany);
    }

    return false;
}

bool jatekos_vannak_betuk(jatek * jat, kirakas k)
{
    vektor h = k.hely;
    jatekos j_masolat = *jat->j;
    for(char * pb = k.betuk; *pb != '\0'; ++pb)
    {
        if(palya_betu(jat->p, h) == ' ')
        {
            char * t = strchr(j_masolat.tarto, *pb);
            if(t == NULL)
                return false;
            *t = ' '; // a masolattol elvesszuk a betut, hogy ne lehessen ketszer hasznalni egy korben
        }

        h = vekt_osszead(h, k.irany);
    }
    return true;
}


bool szabalyos(jatek * jat, kirakas k, char * hiba_ide)
{
    char hibas[SZO_MERET]; // jo_meroleges_szavak ide tolti a hibas szot ha van

    if     (!szotar_benne_van(jat->szt, k.szo))                 strcpy(hiba_ide, "Nincs ilyen szo!");
    else if(!palya_kifer(jat->p, k))                            strcpy(hiba_ide, "Ez a szo nem illik oda!");
    else if(!van_uj_betu(jat->p, k))                            strcpy(hiba_ide, "Legalabb egy betut le kell rakni!");
    else if(!van_szomszed(jat->p, k))                           strcpy(hiba_ide, "Ide nem lehet rakni!");
    else if(!jatekos_vannak_betuk(jat, k))                      strcpy(hiba_ide, "Nincsenek ilyen betuid!");
    else if(!jo_meroleges_szavak(jat->p, jat->szt, k, hibas))   sprintf(hiba_ide, "Nincs olyan szo hogy \"%s\"!", hibas);

    else return true;

    return false;
}



void jatekos_levon_betuk(jatek * jat, kirakas k)
{
    vektor h = k.hely;
    for(char * pb = k.betuk; *pb != '\0'; ++pb)
    {
        if(palya_betu(jat->p, h) == ' ')
        {
            char * t = strchr(jat->j->tarto, *pb);
            *t = ' '; // itt a valodi jatekostol vesszuk el a betuket
        }

        h = vekt_osszead(h, k.irany);
    }
}

void jatek_kovetkezo_jatekos(jatek * jat)
{
    ++jat->j;
    if(jat->j == jat->jatekosok + jat->db_jatekos)
        jat->j = jat->jatekosok;
}

int pontszam(palya p, kirakas k, betu_k bk)
{
    int fo_pont = szo_ertek(k.betuk, bk);
    int mellek_pont = 0;
    int fo_pont_szorzo = 1;

    vektor h = k.hely;
    vektor meroleges_irany = vekt_egyenlo(k.irany, VIZSZINTES) ? FUGGOLEGES : VIZSZINTES;

    for(char * pb = k.betuk; *pb != '\0'; ++pb)
    {
        if(palya_betu(p, h) == ' ')
        {
            char meroleges_szo[SZO_MERET]; // a szo kirakasaval arra merolegesen is keletkezhetnek szavak
            p.betuk[h.x][h.y] = *pb;  // behelyettesitjuk a betut es megnezzuk milyen szo jon ki
            palya_szo_itt(p, h, meroleges_irany, meroleges_szo);
            p.betuk[h.x][h.y] = ' '; // visszarakjuk a ' '-t ami ott volt mielott behelyesitettunk

            int betu_extra_pont = (p.szorzo_betu[h.x][h.y] - 1) * betu_ertek(*pb, bk);
            fo_pont += betu_extra_pont;
            fo_pont_szorzo *= p.szorzo_szo[h.x][h.y];
            if(strlen(meroleges_szo) > 1) // ha csak 1 betu hosszu a meroleges szo, akkor az valojaban nem is szo
                mellek_pont += p.szorzo_szo[h.x][h.y] * (szo_ertek(meroleges_szo, bk) + betu_extra_pont);
        }

        h = vekt_osszead(h, k.irany);
    }


    return fo_pont * fo_pont_szorzo + mellek_pont;
}

void palya_kirak(palya p, kirakas k)
{
    vektor h = k.hely;
    for(char * ptr = k.szo; *ptr != '\0'; ++ptr)
    {
        p.betuk[h.x][h.y] = *ptr;

        h = vekt_osszead(h, k.irany);
    }
}

