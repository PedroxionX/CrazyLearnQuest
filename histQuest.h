// Bibliotecas utilizadas
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
//
#define quantityHistQuestions 19
// Listas
char questionList[][200] = {
    "¿En qué año se descubrió América?",
    "¿En qué año se firmó la Declaración de Independencia de EUA?",
    "¿En qué año comenzó la Primera Guerra Mundial?",
    "¿En qué año terminó la Segunda Guerra Mundial y se fundo la ONU?",
    "¿En qué año se construyó el Muro de Berlín?",
    "¿En qué año se cayó el Muro de Berlín?",
    "¿En qué año fue la Revolución Francesa?",
    "¿En qué año llegó el hombre a la Luna?",
    "¿En qué año comenzó la Guerra Civil Española?",
    "¿En qué año terminó la Guerra Civil Española?",
    "¿En qué año ocurrió la Revolución Rusa?",
    "¿En qué año comenzó la Guerra de Independencia de México?",
    "¿En qué año terminó la Guerra de Independencia de México?",
    "¿En qué año fue el ataque a Pearl Harbor?",
    "¿En qué año comenzó la Revolución Industrial?",
    "¿En qué año se firmó el Tratado de Versalles?",
    "¿En qué año ocurrió el Gran Incendio de Londres?",
    "¿En qué año cayó Constantinopla?",
    "¿En qué año fue la batalla de Waterloo?"};
char answerList[][20] = {
    "1492", // Descubrimiento de América
    "1776", // Declaración de Independencia de los EE.UU.
    "1914", // Comienzo de la Primera Guerra Mundial
    "1945", // Fin de la Segunda Guerra Mundial
    "1961", // Construcción del Muro de Berlín
    "1989", // Caída del Muro de Berlín
    "1789", // Revolución Francesa
    "1969", // Llegada del hombre a la Luna
    "1936", // Comienzo de la Guerra Civil Española
    "1939", // Fin de la Guerra Civil Española
    "1917", // Revolución Rusa
    "1810", // Comienzo de la Guerra de Independencia de México
    "1821", // Fin de la Guerra de Independencia de México
    "1941", // Ataque a Pearl Harbor
    "1760", // Comienzo de la Revolución Industrial (aproximado)
    "1919", // Firma del Tratado de Versalles
    "1666", // Gran Incendio de Londres
    "1453", // Caída de Constantinopla
    "1815"  // Batalla de Waterloo
};
//
typedef struct sHistSaveData
{
    int maxScore;
} tHistSaveData;
typedef struct sHistQuestion
{
    char question[200];
    char answer[30];
} tHistQuestion;
// Prototipos
void drawHistMainMenu(Rectangle easyButton, Rectangle helpButton, Rectangle mainMenuButton, int maxScore);
void drawHistGameScreen(int randomValue, int randomValue2, int randomValue3, int score, int correctOption, Rectangle optionOne, Rectangle optionTwo, Rectangle optionThree, float remainingTime, int framesPerSecond);
void drawHistGameOverScreen(int score, tHistQuestion currentHistAnswer);
void drawHistInstructions(Rectangle exitInstructionsButton);
tHistQuestion generateHistProblem(int randomValue, const char *filename);
tHistSaveData loadHistData(const char *filename);
void saveHistData(const char *filename, tHistSaveData data);
//
void drawHistMainMenu(Rectangle easyButton, Rectangle helpButton, Rectangle mainMenuButton, int maxScore)
{
    DrawText("HistoryQuest", 265, 30, 40, DARKGRAY);

    DrawRectangleRec(easyButton, LIGHTGRAY);
    DrawText("Jugar", easyButton.x + 75, easyButton.y + 14, 20, DARKGRAY);

    DrawText(TextFormat("Puntuación Máxima: %d", maxScore), 300, 400, 20, DARKGRAY);

    DrawRectangleRec(helpButton, LIGHTGRAY);
    DrawText("Instrucciones", helpButton.x + 30, helpButton.y + 14, 20, DARKGRAY);

    DrawRectangleRec(mainMenuButton, LIGHTGRAY);
    DrawText("Volver al menu principal", mainMenuButton.x + 10, mainMenuButton.y + 18, 16, DARKGRAY);
}
void drawHistGameScreen(int randomValue, int randomValue2, int randomValue3, int score, int correctOption, Rectangle optionOne, Rectangle optionTwo, Rectangle optionThree, float remainingTime, int framesPerSecond)
{
    DrawText(TextFormat("Pregunta:"), 50, 800, 40, DARKGRAY);
    DrawText(TextFormat("%s", questionList[randomValue]), 50, 130, 20, DARKGRAY);
    DrawText(TextFormat("Puntuacion actual: %d", score), 70, 200, 40, DARKGRAY);
    DrawText(TextFormat("Tiempo restante: %.2f", remainingTime / framesPerSecond), 100, 450, 40, DARKBLUE);
    //
    switch (correctOption)
    {
    case 1:
    {
        DrawRectangleRec(optionOne, LIGHTGRAY);
        DrawText(TextFormat("%s", answerList[randomValue]), optionOne.x + 25, optionOne.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionTwo, LIGHTGRAY);
        DrawText(TextFormat("%s", answerList[randomValue2]), optionTwo.x + 25, optionTwo.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionThree, LIGHTGRAY);
        DrawText(TextFormat("%s", answerList[randomValue3]), optionThree.x + 25, optionThree.y + 14, 20, DARKGRAY);
        break;
    }
    case 2:
    {
        DrawRectangleRec(optionOne, LIGHTGRAY);
        DrawText(TextFormat("%s", answerList[randomValue2]), optionOne.x + 25, optionOne.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionTwo, LIGHTGRAY);
        DrawText(TextFormat("%s", answerList[randomValue]), optionTwo.x + 25, optionTwo.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionThree, LIGHTGRAY);
        DrawText(TextFormat("%s", answerList[randomValue3]), optionThree.x + 25, optionThree.y + 14, 20, DARKGRAY);
        break;
    }
    case 3:
    {
        DrawRectangleRec(optionOne, LIGHTGRAY);
        DrawText(TextFormat("%s", answerList[randomValue2]), optionOne.x + 25, optionOne.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionTwo, LIGHTGRAY);
        DrawText(TextFormat("%s", answerList[randomValue3]), optionTwo.x + 25, optionTwo.y + 14, 20, DARKGRAY);
        DrawRectangleRec(optionThree, LIGHTGRAY);
        DrawText(TextFormat("%s", answerList[randomValue]), optionThree.x + 25, optionThree.y + 14, 20, DARKGRAY);
        break;
    }
    }
    //
}
void drawHistGameOverScreen(int score, tHistQuestion currentHistAnswer)
{
    ClearBackground(RAYWHITE);
    DrawText("Juego Terminado!", 100, 100, 40, DARKGRAY);
    DrawText(TextFormat("Puntuacion final: %d", score), 100, 200, 40, DARKGRAY);
    DrawText(TextFormat("La respuesta correcta era: %s", currentHistAnswer.answer), 100, 300, 30, DARKGRAY);
    DrawText("Presiona ENTER para volver al menu", 100, 400, 30, DARKGRAY);
}
void drawHistInstructions(Rectangle exitInstructionsButton)
{
    ClearBackground(RAYWHITE);
    DrawText("Instrucciones:", 100, 100, 40, DARKGRAY);
    DrawText("Responde correctamente la preguntas.", 100, 150, 20, DARKGRAY);
    DrawText("Presiona CLICK para enviar tu respuesta.", 100, 200, 20, DARKGRAY);

    DrawRectangleRec(exitInstructionsButton, LIGHTGRAY);
    DrawText("Volver al menu", exitInstructionsButton.x + 25, exitInstructionsButton.y + 14, 20, DARKGRAY);
}
tHistQuestion generateHistProblem(int randomValue, const char *filename)
{
    tHistQuestion temp;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("No se pudo abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char line[512];
    int currentLine = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (currentLine == randomValue)
        {
            // Dividir la línea en pregunta y respuesta
            char *token = strtok(line, ";");
            if (token != NULL)
            {
                strcpy(temp.question, token);
                token = strtok(NULL, ";");
                if (token != NULL)
                {
                    strcpy(temp.answer, token);
                    // Eliminar el carácter de nueva línea al final de la respuesta
                    size_t len = strlen(temp.answer);
                    if (len > 0 && temp.answer[len - 1] == '\n')
                    {
                        temp.answer[len - 1] = '\0';
                    }
                }
            }
            break;
        }
        currentLine++;
    }

    fclose(file);
    return temp;
}
tHistSaveData loadHistData(const char *filename)
{
    tHistSaveData temp;
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        temp.maxScore = 0;
        return temp;
    }
    fread(&temp, sizeof(tHistSaveData), 1, file);
    fclose(file);
    return temp;
}
void saveHistData(const char *filename, tHistSaveData data)
{
    FILE *file = fopen(filename, "wb");
    if (file)
    {
        fwrite(&data, sizeof(tHistSaveData), 1, file);
        fclose(file);
    }
}