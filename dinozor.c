#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GENISLIK 800
#define YUKSEKLIK 450

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    InitWindow(GENISLIK, YUKSEKLIK, "Algoritmalar ve Programlama Dinozor Oyunu");
    InitAudioDevice();
    Sound ziplamaSesi = LoadSound("jump.mp3");
    Rectangle dinozor = {50, YUKSEKLIK-80, 40, 80};
    Rectangle kaktus = {GENISLIK, YUKSEKLIK, 0, 0};
    Vector2 hiz = {0, 0};
    bool hareket=false;
    bool kaktusVar = false;
    bool skorArtirildi = false;
    int skor = 0;
    char mesaj[80];
    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        if(kaktusVar && CheckCollisionRecs(dinozor, kaktus)) {
            skor = 0;
            kaktusVar = false;
        }
        if(!kaktusVar) {
            kaktus.x = GENISLIK;
            kaktus.width = 50 + rand() % 31;
            kaktus.height = 100 + rand() % 100;
            kaktus.y = YUKSEKLIK - kaktus.height;
            kaktusVar = true;
            skorArtirildi = false;
        }
        else {
            kaktus.x -= 10;
        }
        if (kaktus.x < -kaktus.width) {
            kaktusVar = false;
        }
        // Dinozor güncellemesi
        hiz.y += 2;
        dinozor.y += hiz.y;
        if(dinozor.y>YUKSEKLIK-80) {
            dinozor.y = YUKSEKLIK-80;
            hareket = false;
        }
        if(!hareket && IsKeyPressed(KEY_SPACE)) {
            //dinozor.y = 0;
            hiz.y = -35;
            hareket = true;
            PlaySound(ziplamaSesi);
        }
        // Skor güncelleme
        if(!skorArtirildi && kaktus.x < dinozor.x) {
            skor += 1;
            skorArtirildi = true;
        }
        BeginDrawing();
        ClearBackground(WHITE);
        //DrawText("Dinozor Oyunu", 0, YUKSEKLIK-40, 40, BLACK);
        DrawRectangleRec(dinozor, GREEN);
        if(kaktusVar)
            DrawRectangleRec(kaktus, GRAY);
        sprintf(mesaj, "Skor: %d", skor);
        DrawText(mesaj,0,0,20,BLACK);
        EndDrawing();
    }
    UnloadSound(ziplamaSesi);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
