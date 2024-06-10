// Bibliotecas utilizadas
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef enum sDifficulty
{
    EASY,
    MEDIUM,
    HARD
} tDifficulty;
typedef struct sProblem
{
    int num1;
    int num2;
    int answer;
    char operation;
} tProblem;
typedef struct sMathSaveData
{
    int maxScore;
} tMathSaveData;

// Prototipos de funciones
tProblem generateMathProblem(tDifficulty difficulty);
void drawMathMainMenu(Rectangle easyButton, Rectangle mediumButton, Rectangle hardButton, Rectangle helpButton, Rectangle mainMenuButton, int maxScore);
void drawMathGameScreen(tProblem currentProblem, char *answerText, int score, float remainingTime, int framesPerSecond, tDifficulty currentDifficulty, float cronometer);
void drawMathGameOverScreen(int score, int answer);
void drawMathInstructions(Rectangle exitInstructionsButton);
tMathSaveData loadMathData(const char *filename);
void saveMathData(const char *filename, tMathSaveData data);
// Desarrollo de funciones
tProblem generateMathProblem(tDifficulty difficulty)
{
    int operacionAleatoria = GetRandomValue(1, 3);
    tProblem problem;
    if (difficulty == EASY)
    {
        problem.num1 = GetRandomValue(1, 10);
        problem.num2 = GetRandomValue(1, 10);
    }
    else if (difficulty == MEDIUM)
    {
        problem.num1 = GetRandomValue(1, 50);
        problem.num2 = GetRandomValue(1, 50);
    }
    else if (difficulty == HARD)
    {
        problem.num1 = GetRandomValue(30, 120);
        problem.num2 = GetRandomValue(30, 120);
    }

    switch (operacionAleatoria)
    {
    case 1:
        problem.answer = problem.num1 + problem.num2;
        problem.operation = '+';
        break;
    case 2:
        problem.answer = problem.num1 - problem.num2;
        if (problem.answer < 0)
        {
            int temporal = problem.num1;
            problem.num1 = problem.num2;
            problem.num2 = temporal;
            problem.answer = problem.num1 - problem.num2;
        }
        problem.operation = '-';
        break;
    case 3:
        if (problem.num2 > 10)
        {
            problem.num2 = 10;
        }
        problem.answer = problem.num1 * problem.num2;
        problem.operation = '*';
        break;
    }

    return problem;
}
//
void drawMathMainMenu(Rectangle easyButton, Rectangle mediumButton, Rectangle hardButton, Rectangle helpButton, Rectangle mainMenuButton, int maxScore)
{
    DrawText("MathQuest", 293, 30, 40, DARKGRAY);

    DrawRectangleRec(easyButton, LIGHTGRAY);
    DrawText("Facil", easyButton.x + 75, easyButton.y + 14, 20, DARKGRAY);

    DrawRectangleRec(mediumButton, LIGHTGRAY);
    DrawText("Medio", mediumButton.x + 75, mediumButton.y + 14, 20, DARKGRAY);

    DrawRectangleRec(hardButton, LIGHTGRAY);
    DrawText("Dificil", hardButton.x + 75, hardButton.y + 14, 20, DARKGRAY);

    DrawRectangleRec(helpButton, LIGHTGRAY);
    DrawText("Instrucciones", helpButton.x + 30, helpButton.y + 14, 20, DARKGRAY);

    DrawRectangleRec(mainMenuButton, LIGHTGRAY);
    DrawText("Volver al menu principal", mainMenuButton.x + 10, mainMenuButton.y + 18, 16, DARKGRAY);

    DrawText(TextFormat("Puntuación Máxima: %d", maxScore), 300, 400, 20, DARKGRAY);
}
void drawMathGameScreen(tProblem currentProblem, char *answerText, int score, float remainingTime, int framesPerSecond, tDifficulty currentDifficulty, float cronometer)
{
    DrawText(TextFormat("Problema: %d %c %d = ?", currentProblem.num1, currentProblem.operation, currentProblem.num2), 100, 100, 40, DARKGRAY);
    DrawText(answerText, 100, 200, 40, DARKGRAY);
    DrawText(TextFormat("Puntuacion: %d", score), 100, 300, 40, DARKGRAY);
    // DrawTextureV(heart, volumeButtonPossition, WHITE);
    switch (currentDifficulty)
    {
    case EASY:
    {
        DrawText(TextFormat("Tiempo: %.2f", cronometer / framesPerSecond), 100, 450, 40, DARKBLUE);
        break;
    }

    case MEDIUM:
    {
        DrawText(TextFormat("Tiempo restante: %.2f", remainingTime / framesPerSecond), 100, 450, 40, DARKBLUE);
        break;
    }
    case HARD:
    {
        DrawText(TextFormat("Tiempo restante: %.2f", remainingTime / framesPerSecond), 100, 450, 40, DARKBLUE);
        break;
    }
    }
}
void drawMathGameOverScreen(int score, int answer)
{
    ClearBackground(RAYWHITE);
    DrawText("Juego Terminado!", 100, 100, 40, DARKGRAY);
    DrawText(TextFormat("Puntuacion final: %d", score), 100, 200, 40, DARKGRAY);
    DrawText(TextFormat("La respuesta correcta era: %d", answer), 100, 300, 40, DARKGRAY);
    DrawText("Presiona ENTER para volver al menu", 100, 400, 30, DARKGRAY);
}
void drawMathInstructions(Rectangle exitInstructionsButton)
{
    ClearBackground(RAYWHITE);
    DrawText("Instrucciones:", 80, 100, 40, DARKGRAY);
    DrawText("Resuelve los problemas matemáticos antes de que se acabe el tiempo.", 80, 150, 20, DARKGRAY);
    DrawText("Presiona ENTER para enviar tu respuesta.", 80, 200, 20, DARKGRAY);
    DrawText("Presiona BACKSPACE para corregir tu respuesta.", 80, 250, 20, DARKGRAY);

    DrawRectangleRec(exitInstructionsButton, LIGHTGRAY);
    DrawText("Volver al menu", exitInstructionsButton.x + 25, exitInstructionsButton.y + 14, 20, DARKGRAY);
}
tMathSaveData loadMathData(const char *filename)
{
    tMathSaveData temp;
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        temp.maxScore = 0;
        return temp;
    }
    fread(&temp, sizeof(tMathSaveData), 1, file);
    fclose(file);
    return temp;
}
void saveMathData(const char *filename, tMathSaveData data)
{
    FILE *file = fopen(filename, "wb");
    if (file)
    {
        fwrite(&data, sizeof(tMathSaveData), 1, file);
        fclose(file);
    }
}