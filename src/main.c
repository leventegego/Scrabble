#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "szotar.h"
#include "palya.h"
#include "jatekos.h"
#include "jatek.h"


int main ()
{
    srand(time(0));
    debugmalloc_max_block_size(3 * 1024 * 1024); // kell kb 2 MB csak a szotar eltarolasara.
    debugmalloc_log_file("memlog.txt");

    char mappa_nev [256];
    printf("------------------------------ Scrabble! ------------------------------\n\n");
    printf("Ird be a jatek mappajanak nevet a kezdeshez!\n");
    scanf("%s", mappa_nev);

    jatek jat;
    if(jatek_beolvas(mappa_nev, &jat) != 0)
    {
        printf("Nem sikerult beolvasni a fajlt!\n");
        scanf("%*c");
        return 1;
    }

    while(!jatek_vege(&jat))
    {
        jatekos_feltolt_betuk(&jat);

        printf("\n-----------------------------------------------------------------------\n\n");

        jatek_kirajzol(&jat);

        parancs par = kormenu(&jat);
        switch(par)
        {
            case KIRAKAS:   jatek_kirakas_vegrehajt(&jat, jatek_kirakas_beker(&jat)); break;
            case PASSZ:     jatek_kovetkezo_jatekos(&jat); break;
            case INFO:      jatek_print_info(&jat); break;
            case MENTES:    jatek_mentes_parbeszed(&jat); break;

            case KILEPES:
                jatek_befejez(&jat);
                jatek_torol(&jat);
                return 0;               // ! return es nem break !

            default: break;
        }

        printf("Nyomj entert a folytatashoz.\n");
        scanf("%*c");
    }

    jatek_befejez(&jat);
    jatek_torol(&jat);

    return 0;
}
