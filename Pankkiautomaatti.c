#include <stdio.h>
#include <string.h>

void lueToimenpide( char toimenpide[], int koko );
int vertailu( char toimenpide[], char otto[], char saldo[], char t_tapahtumat[], char talleta[], char poistu[]);
void tulostaRahat( int nostoSumma );
int lueLuku( int kohta );
int kaksi, viisi; //setelien maarat
FILE * tili;

int main( void ){
    
    int yritysKerrat = 3, uudestaan = 0, koko = 15, nostoSumma, tilinSaldo, talletus;
    char tilinro[100], tilintunnusluku[100], tunnusluku[100], toimenpide[15], 
    otto[] = "otto", saldo[] = "saldo", t_tapahtumat[] = "tilitapahtumat", poistu[] = "poistu", talleta[] = "talleta";
    
    
    while( uudestaan == 0 ){
        
        printf("Tervetuloa!\nSyota tilinumero. > ");
        fgets( tilinro, 100, stdin );
        
        if( tilinro[ strlen(tilinro) -1] == '\n')
            tilinro[ strlen(tilinro) -1] = '\0';
        else
             while ( fgetc(stdin) != '\n' );
        
        strcat(tilinro, ".tili");
        if( (tili = fopen(tilinro, "r")) == NULL)
            printf("\nTilinumerolla ei loytynyt yhtaan tilia!\n\n");
        else
            uudestaan = 1;
    }
    uudestaan = 0;
    
    fgets( tilintunnusluku, 100, tili );
    if( tilintunnusluku[ strlen(tilintunnusluku) -1] == '\n')
        tilintunnusluku[ strlen(tilintunnusluku) -1] = '\0';
    
    printf("\nSyota tunnusluku. > ");
    fgets( tunnusluku, 100, stdin );
    if( tunnusluku[ strlen(tunnusluku) -1] == '\n')
        tunnusluku[ strlen(tunnusluku) -1] = '\0';

    
    while ( yritysKerrat >= 0 && strcmp( tunnusluku, tilintunnusluku ) != 0 ){
        
        if ( yritysKerrat == 0 ){
            printf("\nTilisi on lukittu. Ota yhteys pankkiisi.");
            yritysKerrat = yritysKerrat - 1;
        }
        
        else{
            printf("\nTunnusluku vaarin. Kokeile uudelleen. > ");
            yritysKerrat = yritysKerrat - 1;
            fgets( tunnusluku, 100, stdin );
            if( tunnusluku[ strlen(tunnusluku) -1] == '\n')
                tunnusluku[ strlen(tunnusluku) -1] = '\0';
        }
    }
    
    if ( strcmp( tunnusluku, tilintunnusluku ) == 0 ){
        do{
            printf("\nSyota 'otto', 'saldo', 'tilitapahtumat', 'talleta' tai 'poistu'. > ");
            fscanf(tili, "%d", &tilinSaldo);
            lueToimenpide ( toimenpide, koko );
            
            while ( vertailu ( toimenpide, otto, saldo, t_tapahtumat, talleta, poistu) ){
                printf("\nKaskya ei ymmarretty. Kokeile uudelleen. > ");
                lueToimenpide ( toimenpide, koko );
            }
            
            if ( strcmp ( toimenpide, otto ) == 0 ){
                
                if( tilinSaldo >= 20 ){
                    printf("\nNostettava summa on:\n\n1. Joko 0 euroa tai vahintaan 20 euroa.\n2. Korkeintaan 1000 euroa.\n3. Jaollinen 10:lla.\n( ei kuitenkaan 30 euroa )");
                    printf("\n\nSyota nostettava summa. > ");
                    nostoSumma = lueLuku(0);
                    
                    while ( (0 < nostoSumma && nostoSumma < 20) || nostoSumma > 1000 || nostoSumma == 30 || nostoSumma > tilinSaldo ){
                    
                        if( nostoSumma <= tilinSaldo ){
                            printf("\nNostettava summa on:\n\n1. Joko 0 euroa tai vahintaan 20 euroa.\n2. Korkeintaan 1000 euroa.\n3. Jaollinen 10:lla.\n( ei kuitenkaan 30 euroa )\n\nKokeile uudelleen. > ");
                            nostoSumma = lueLuku(0);
                        }
                        else{
                             printf("\nTilin saldo ei riita nostamaan niin suurta summaa.\nKokeile uudelleen. > ");
                             nostoSumma = lueLuku(0);
                        }
                    }
                
                    tilinSaldo = tilinSaldo - nostoSumma;
                    printf("\nOta kortti ole hyva. Rahat tulossa.");
                    tulostaRahat ( nostoSumma );
                    printf("\n\nTulostaa\n%dx 20 euron setelia\n%dx 50 euron setelia", kaksi, viisi);
                    printf("\n\nOta rahat, ole hyva.\n");
                    uudestaan = 1;
                }
                
                else{
                    
                    if( nostoSumma == 0 )
                        uudestaan = 1;
                    else
                    
                        printf("\nTililla ei ole tarpeeksi saldoa nostettavaksi!\n");
                        uudestaan = 1;
                }
            }
                
            else{
                
                if ( strcmp ( toimenpide, saldo ) == 0 ){
                    
                    printf("\n*************************");
                    printf("\n\nTilin saldo: %d euro(a).\n\n", tilinSaldo);
                    printf("*************************\n");
                    uudestaan = 1;
                }
                
                else{
                    
                    if ( strcmp ( toimenpide, t_tapahtumat ) == 0 ){
                        
                        printf("\n**************");
                        printf("\n\nTILITAPAHTUMAT\n\n");
                        printf("**************\n");
                        uudestaan = 1;
                    }
                    
                    else{
 
                        if ( strcmp ( toimenpide, talleta ) == 0 ){
                            
                            printf("\nTalletettava summa on:\n\n1. Vahintaan 0 euroa.\n2. Kymmenella jaollinen."); 
                            printf("\n\nSyota talletettava summa. > ");
                            talletus = lueLuku(2);
                            tilinSaldo = tilinSaldo + talletus;
                            printf("\nTalletus suoritettu! Talletit tilille %d euroa.\n", talletus);
                            uudestaan = 1;
                        }
                        else{
                            
                            if ( strcmp ( toimenpide, poistu ) == 0 )
	                            uudestaan = 0;
                        }
                    }
                }
            }
        } while ( uudestaan == 1 );
    }
    printf("\n\nKiitos kaynnista. Tervetuloa uudelleen.\n\n");
    fclose( tili );
    tili = fopen(tilinro, "w");
    fprintf(tili, "%s\n", tilintunnusluku);
    fprintf(tili, "%d\n", tilinSaldo);
    fclose( tili );
    return 0;
} // Main-funktion loppu

/*
lueToimenpide - kysyy käyttäjältä merkkijonoa.
Varmistaa, että käyttäjän syöttämä merkkijono ei ole liian pitkä.

Parametrit:
- toimenpide (char): käyttäjältä kysyttävä merkkijono.
*/

void lueToimenpide( char toimenpide[], int koko ){
    
    fgets ( toimenpide, koko, stdin );
    
    if ( toimenpide [ strlen ( toimenpide )- 1 ] == '\n' )
        toimenpide [ strlen ( toimenpide ) - 1 ] = '\0';
    
    else
        while ( fgetc(stdin) != '\n' );
    
}

/*
vertailu - Vertaa käyttäjän syöttämää merkkijonoa eri toimenpiteitä kuvaaviin merkkijonoihin.
Jos käyttäjän syöttämä merkkijono vastaa jonkin toimenpiteen merkkijonoa, vertailu tulostaa 0.
Jos käyttäjän syötteelle ei löydy vastaavaa toimenpiteen merkkijonoa, vertailu tulostaa 1.

Parametrit:
- toimenpide (char): käyttäjän syöttämä merkkijono, jolle etsitään vastaavaa merkkijonoa.
- otto (char): olemassaoleva toimenpiteen merkkijono, johon käyttäjän syötettä vertaillaan.
- saldo (char): olemassaoleva toimenpiteen merkkijono, johon käyttäjän syötettä vertaillaan.
- t_tapahtumat (char): olemassaoleva toimenpiteen merkkijono, johon käyttäjän syötettä vertaillaan.
- talleta (char): olemassaoleva toimenpiteen merkkijono, johon käyttäjän syötettä vertaillaan.
- poistu (char): olemassaoleva toimenpiteen merkkijono, johon käyttäjän syötettä vertaillaan.

Paluuarvo (int): tulos, joka kertoo, löytyikö käyttäjän syöttämälle merkkijonolle olemassaolevaa toimenpidettä kuvaavaa vastinetta.
*/

int vertailu( char toimenpide[], char otto[], char saldo[], char t_tapahtumat[], char talleta[], char poistu[]){
    
    int tulos = 1;
    
    if ( strcmp ( toimenpide, otto ) == 0 || strcmp( toimenpide, saldo ) == 0 || strcmp( toimenpide, t_tapahtumat ) == 0 || strcmp( toimenpide, talleta ) == 0 || strcmp( toimenpide, poistu ) == 0 )
        tulos = 0;
        
    return tulos;
}

/*
tulostaRahat - Laskee syötteen jakautumisen 20 ja 50 sarjoihin siten, että syöte jakautuu tasan.

Parametrit:
- nostoSumma (int): käyttäjän syöttämä luku, joka jaetaan tasan 20 ja 50 sarjoihin.
*/

void tulostaRahat( int nostoSumma ){

    viisi = nostoSumma / 50;
    nostoSumma %= 50;
    kaksi = nostoSumma / 20;
    nostoSumma %= 20;
    if ( nostoSumma != 0 ){
        viisi = viisi - 1;
        kaksi = kaksi + 3;
    }
}
/* 
lueLuku - Kysyy käyttäjältä syötteen ja varmistaa, että syötteessä ei ole kirjaimia.
Jos syötteessä havaitaan kirjaimia, tulostetaan ruudulle sopiva viesti ja pyydetään käyttäjää antamaan uusi syöte.
Varmistaa, että syöte on kymmenellä jaollinen silloin, kun syötteen arvo on arvojen 19 ja 1001 välissä.
Jos syötteen arvo on arvojen 19 ja 1001 välissä, mutta se ei ole kymmenellä jaollinen, tulostetaan ruudulle sopiva viesti ja pyydetään käyttäjää antamaan uusi syöte.
Varmistaa, että käyttäjän syöttämä luku on joko 0 tai positiivinen.
Jos syötteen arvo on negatiivinen, tulostetaan ruudulle sopiva viesti ja pyydetään käyttäjää antamaan uusi syöte.
Paluuarvona on varmistukset läpäissyt käyttäjältä syötteenä saatu kokonaisluku.

Parametrit:
- kohta (int): luku, jolla määritetään ruudulle tulostettavan viestin sanoitus.
Kyseistä funktiota kutsutaan eri kohdissa main-funktiota, ja sen vuoksi tarvitaan erotella, mitä ruudulle halutaan tulostaa.

Paluuarvo (int): luku, jonka käyttäjä syöttää.
*/
int lueLuku( int kohta ){
    
    int luku;
    int tulos = 0;
    int loop = 1;
    char merkki, viesti[4][16] = {"Nostettavassa", "Nostettavan", "Talletettavassa", "Talletettavan"};
    do{
        while( ( tulos = scanf( "%d%c", &luku, &merkki ) ) == 0 || ( tulos == 2 && merkki != '\n' ) ){
            printf("\n%s summassa ei saa olla kirjaimia eika erikoismerkkeja!", viesti[kohta]);
            while ( fgetc(stdin) != '\n' );
            printf("\nKokeile uudelleen. > ");
        }
        if( luku > 19 && luku < 1001 || luku < 0 ){
            if( luku < 0 ){
                printf("\n%s summan tulee olla positiivinen!", viesti[kohta+1]);
                printf("\nKokeile uudelleen. > ");
            }
            else{
                if( luku % 10 == 0 )
                    loop = 0;
                else
                    printf("\n%s summan tulee olla jaollinen kymmenella!\nKokeile uudelleen. > ", viesti[kohta+1]);
            }
        }
        
        else loop = 0;
            
    }while( loop );
    return luku;
}
