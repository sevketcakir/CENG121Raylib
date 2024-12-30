#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define GENISLIK 450
#define YUKSEKLIK 600
#define RAKIP_SAYISI 20
#define MERMI_SAYISI 10

typedef struct Rakip
{
    Rectangle konum;
    Color renk;
    bool aktif;
} Rakip;

void rakipOlustur(Rakip rakipler[], int rakipSayisi) {
    for(int i=0;i<rakipSayisi;i++) {
        if(!rakipler[i].aktif) {
            rakipler[i].aktif = true;
            rakipler[i].konum.x = rand() % GENISLIK;
            rakipler[i].konum.y = 0;
            rakipler[i].konum.width = 20;
            rakipler[i].konum.height = 40;
            rakipler[i].renk = MAGENTA;
            break;
        }
    }
}

void rakipKonumGuncelle(Rakip rakipler[], int rakipSayisi) {
    for (int i = 0; i < rakipSayisi; i++)
    {
        if(rakipler[i].aktif) {
            rakipler[i].konum.y += 5;
        }
        if(rakipler[i].konum.y > YUKSEKLIK) {
            rakipler[i].aktif = false;
        }
    }
    
}

void rakipCizdir(Rakip rakipler[], int rakipSayisi) {
    for (int i = 0; i < rakipSayisi; i++)
    {
        if(rakipler[i].aktif) {
            DrawRectangleRec(rakipler[i].konum, rakipler[i].renk);
        }
    }
    
}

bool rakipleCarpisma(Rectangle ucak, Rakip rakipler[], int rakipSayisi) {
    for (int i = 0; i < rakipSayisi; i++)
    {
        if (rakipler[i].aktif &&
            CheckCollisionRecs(ucak, rakipler[i].konum)) {
                return true;
            }
    }
    return false;
}

void mermiOlustur(Rectangle konum, Rakip mermiler[], int mermiSayisi) {
    for (int i = 0; i < mermiSayisi; i++)
    {
        if(!mermiler[i].aktif) {
            mermiler[i].aktif = true;
            mermiler[i].konum.x = konum.x+8;
            mermiler[i].konum.y = konum.y;
            mermiler[i].konum.width = 3;
            mermiler[i].konum.height = 8;
            mermiler[i].renk = WHITE;
            break;
        }
    }
}

void mermiKonumGuncelle(Rakip mermiler[], int mermiSayisi) {
    for (int i = 0; i < mermiSayisi; i++)
    {
        if(mermiler[i].aktif) {
            mermiler[i].konum.y -= 5;
        }
        if(mermiler[i].konum.y < 0) {
            mermiler[i].aktif = false;
        }
    }
}

int mermiCarpismaTesti(Rakip mermiler[], int mermiSayisi, Rakip rakipler[], int rakipSayisi) {
    int skor = 0;
    for (int i = 0; i < mermiSayisi; i++)
    {
        for (int j = 0; j < rakipSayisi; j++)
        {
            if(mermiler[i].aktif && rakipler[j].aktif &&
                CheckCollisionRecs(mermiler[i].konum, rakipler[j].konum)) {
                    skor += 1;
                    mermiler[i].aktif = false;
                    rakipler[j].aktif = false;
                }
        }
        
    }
    return skor;
}

int main(int argc, char const *argv[])
{
    InitWindow(GENISLIK, YUKSEKLIK, "Algoritmalar ve Programlama Dersi Oyun");
    SetTargetFPS(60);
    Rectangle ucak = {GENISLIK/2, YUKSEKLIK-40, 20, 40};
    Rakip rakipler[RAKIP_SAYISI];
    Rakip mermiler[MERMI_SAYISI];
    int skor = 0;
    char skorMesaji[80];
    while (!WindowShouldClose())
    {
        if(IsKeyDown(KEY_LEFT)) {
            ucak.x -= 5;
        }
        if(IsKeyDown(KEY_RIGHT)) {
            ucak.x += 5;
        }
        if(IsKeyPressed(KEY_SPACE)) {
            mermiOlustur(ucak, mermiler, MERMI_SAYISI);
        }

        if(ucak.x < 0) {
            ucak.x = 0;
        }
        if(ucak.x+ucak.width > GENISLIK) {
            ucak.x = GENISLIK - ucak.width;
        }
        if(rand()%100 == 0) {
            rakipOlustur(rakipler, RAKIP_SAYISI);
        }
        rakipKonumGuncelle(rakipler, RAKIP_SAYISI);
        mermiKonumGuncelle(mermiler, MERMI_SAYISI);
        if(rakipleCarpisma(ucak, rakipler, RAKIP_SAYISI)) {
            skor = 0;
            for(int i=0; i< RAKIP_SAYISI; i++) {
                rakipler[i].aktif = false;
            }
        }
        skor += mermiCarpismaTesti(mermiler, MERMI_SAYISI, rakipler, RAKIP_SAYISI);
        BeginDrawing();
        ClearBackground(BLACK);
        //DrawText("Ilk Oyunum", 10, 150, 20, BLUE);
        sprintf(skorMesaji, "Skor: %d", skor);
        DrawText(skorMesaji, 0, 0, 20, BLUE);
        DrawRectangleRec(ucak, YELLOW);
        rakipCizdir(rakipler, RAKIP_SAYISI);
        rakipCizdir(mermiler, MERMI_SAYISI);
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}
