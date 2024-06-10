// Bibliotecas utilizadas
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
//
#define quantityCountrys 85
// Listas
char countryList[][30] = {
    "Mexico", "Ecuador", "Noruega", "Holanda", "España", "Francia", "Alemania", "Italia", "Japón", "Brasil",
    "Argentina", "Canadá", "Australia", "China", "India", "Rusia", "Sudáfrica", "Reino Unido", "Egipto", "Turquía",
    "Portugal", "Suecia", "Suiza", "Grecia", "Dinamarca", "Finlandia", "Irlanda", "Polonia", "Austria", "Bélgica",
    "Chile", "Colombia", "Perú", "Venezuela", "Uruguay", "Paraguay", "Bolivia", "Cuba", "República Dominicana", "Honduras",
    "Guatemala", "El Salvador", "Costa Rica", "Panamá", "Nicaragua", "Belice", "Haití", "Jamaica", "Trinidad y Tobago", "Bahamas",
    "Islandia", "Luxemburgo", "Mónaco", "Liechtenstein", "San Marino", "Malta", "Chipre", "Israel", "Líbano", "Jordania",
    "Arabia Saudita", "Irán", "Iraq", "Afganistán", "Pakistán", "Bangladesh", "Tailandia", "Vietnam", "Indonesia", "Filipinas",
    "Malasia", "Singapur", "Armenia", "Azerbaiyán", "Georgia", "Ucrania", "Bielorrusia", "Moldavia", "Lituania", "Letonia", "Estonia",
    "Serbia", "Croacia", "Eslovenia", "Eslovaquia", "Hungría"};
char capitalList[][30] = {
    "CDMX", "Quito", "Oslo", "Ámsterdam", "Madrid", "París", "Berlín", "Roma", "Tokio", "Brasilia",
    "Buenos Aires", "Ottawa", "Canberra", "Pekín", "Nueva Delhi", "Moscú", "Pretoria", "Londres", "El Cairo", "Ankara",
    "Lisboa", "Estocolmo", "Berna", "Atenas", "Copenhague", "Helsinki", "Dublín", "Varsovia", "Viena", "Bruselas",
    "Santiago", "Bogotá", "Lima", "Caracas", "Montevideo", "Asunción", "La Paz", "La Habana", "Santo Domingo", "Tegucigalpa",
    "Guatemala", "San Salvador", "San José", "Panamá", "Managua", "Belmopán", "Puerto Príncipe", "Kingston", "Puerto España", "Nassau",
    "Reikiavik", "Luxemburgo", "Mónaco", "Vaduz", "San Marino", "La Valeta", "Nicosia", "Jerusalén", "Beirut", "Amán",
    "Riad", "Teherán", "Bagdad", "Kabul", "Islamabad", "Daca", "Bangkok", "Hanoi", "Yakarta", "Manila",
    "Kuala Lumpur", "Singapur", "Ereván", "Bakú", "Tiflis", "Kiev", "Minsk", "Chisináu", "Vilna", "Riga", "Tallin",
    "Belgrado", "Zagreb", "Liubliana", "Bratislava", "Budapest"};
//
typedef struct sGeoCapital
{
    char country[30];
    char answer[30];
} tGeoCapital;
typedef struct sGeoSaveData
{
    int maxScore;
} tGeoSaveData;
// Prototipos
void drawGeoMainMenu(Rectangle easyButton, Rectangle helpButton, Rectangle mainMenuButton, int maxScore);
void drawGeoGameScreen(int randomValue, int randomValue2, int randomValue3, int score, int correctOption, Rectangle optionOne, Rectangle optionTwo, Rectangle optionThree, float remainingTime, int framesPerSecond);
void drawGeoGameOverScreen(int score, tGeoCapital currentGeoCapital);
void drawGeoInstructions(Rectangle exitInstructionsButton);
tGeoCapital generateGeoProblem(int randomValue);
tGeoSaveData loadGeoData(const char *filename);
void saveGeoData(const char *filename, tGeoSaveData data);
//
void drawGeoMainMenu(Rectangle easyButton, Rectangle helpButton, Rectangle mainMenuButton, int maxScore)
{
    DrawText("GeoQuest", 300, 30, 40, DARKGRAY);

    DrawRectangleRec(easyButton, LIGHTGRAY);
    DrawText("Jugar", easyButton.x + 75, easyButton.y + 14, 20, DARKGRAY);

    DrawText(TextFormat("Puntuación Máxima: %d", maxScore), 300, 400, 20, DARKGRAY);

    DrawRectangleRec(helpButton, LIGHTGRAY);
    DrawText("Instrucciones", helpButton.x + 30, helpButton.y + 14, 20, DARKGRAY);

    DrawRectangleRec(mainMenuButton, LIGHTGRAY);
    DrawText("Volver al menu principal", mainMenuButton.x + 10, mainMenuButton.y + 18, 16, DARKGRAY);
}
void drawGeoGameScreen(int randomValue, int randomValue2, int randomValue3, int score, int correctOption, Rectangle optionOne, Rectangle optionTwo, Rectangle optionThree, float remainingTime, int framesPerSecond)
{
    DrawText(TextFormat("Pregunta: Cual es la capital de..."), 70, 100, 40, DARKGRAY);
    DrawText(TextFormat("%s", countryList[randomValue]), 70, 150, 40, DARKGRAY);
    DrawText(TextFormat("Puntuacion actual: %d", score), 70, 200, 40, DARKGRAY);
    DrawText(TextFormat("Tiempo restante: %.2f", remainingTime / framesPerSecond), 100, 450, 40, DARKBLUE);
    //
    switch (correctOption)
    {
    case 1:
        DrawRectangleRec(optionOne, LIGHTGRAY);
        DrawText(TextFormat("%s", capitalList[randomValue]), optionOne.x + 25, optionOne.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionTwo, LIGHTGRAY);
        DrawText(TextFormat("%s", capitalList[randomValue2]), optionTwo.x + 25, optionTwo.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionThree, LIGHTGRAY);
        DrawText(TextFormat("%s", capitalList[randomValue3]), optionThree.x + 25, optionThree.y + 14, 20, DARKGRAY);
        break;
    case 2:
        DrawRectangleRec(optionOne, LIGHTGRAY);
        DrawText(TextFormat("%s", capitalList[randomValue2]), optionOne.x + 25, optionOne.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionTwo, LIGHTGRAY);
        DrawText(TextFormat("%s", capitalList[randomValue]), optionTwo.x + 25, optionTwo.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionThree, LIGHTGRAY);
        DrawText(TextFormat("%s", capitalList[randomValue3]), optionThree.x + 25, optionThree.y + 14, 20, DARKGRAY);
        break;
    case 3:
        DrawRectangleRec(optionOne, LIGHTGRAY);
        DrawText(TextFormat("%s", capitalList[randomValue2]), optionOne.x + 25, optionOne.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionTwo, LIGHTGRAY);
        DrawText(TextFormat("%s", capitalList[randomValue3]), optionTwo.x + 25, optionTwo.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionThree, LIGHTGRAY);
        DrawText(TextFormat("%s", capitalList[randomValue]), optionThree.x + 25, optionThree.y + 14, 20, DARKGRAY);
        break;
    }
    //
}
void drawGeoGameOverScreen(int score, tGeoCapital currentGeoCapital)
{
    ClearBackground(RAYWHITE);
    DrawText("Juego Terminado!", 100, 100, 40, DARKGRAY);
    DrawText(TextFormat("Puntuacion final: %d", score), 100, 200, 40, DARKGRAY);
    DrawText(TextFormat("La respuesta correcta era: %s", currentGeoCapital.answer), 100, 300, 30, DARKGRAY);
    DrawText("Presiona ENTER para volver al menu", 100, 400, 30, DARKGRAY);
}
void drawGeoInstructions(Rectangle exitInstructionsButton)
{
    ClearBackground(RAYWHITE);
    DrawText("Instrucciones:", 100, 100, 40, DARKGRAY);
    DrawText("Responde correctamente la preguntas.", 100, 150, 20, DARKGRAY);
    DrawText("Presiona CLICK para enviar tu respuesta.", 100, 200, 20, DARKGRAY);

    DrawRectangleRec(exitInstructionsButton, LIGHTGRAY);
    DrawText("Volver al menu", exitInstructionsButton.x + 25, exitInstructionsButton.y + 14, 20, DARKGRAY);
}
tGeoCapital generateGeoProblem(int randomValue)
{
    tGeoCapital temp;

    strcpy(temp.country, countryList[randomValue]);
    strcpy(temp.answer, capitalList[randomValue]);

    return temp;
}
tGeoSaveData loadGeoData(const char *filename)
{
    tGeoSaveData temp;
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        temp.maxScore = 0;
        return temp;
    }
    fread(&temp, sizeof(tGeoSaveData), 1, file);
    fclose(file);
    return temp;
}
void saveGeoData(const char *filename, tGeoSaveData data)
{
    FILE *file = fopen(filename, "wb");
    if (file)
    {
        fwrite(&data, sizeof(tGeoSaveData), 1, file);
        fclose(file);
    }
}