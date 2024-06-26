#include "raylib.h"

#define framesPerSecond 60
#define screenWidth 800
#define screenHeight 600

typedef enum sGameScreen
{
    RAYLIB_SCENE,
    MAIN_MENU,
    // Math
    MATH_MAIN_MENU,
    MATH_GAME,
    MATH_GAME_OVER,
    MATH_INSTRUCTIONS,
    // Geo
    GEO_MAIN_MENU,
    GEO_GAME,
    GEO_GAME_OVER,
    GEO_INSTRUCTIONS,
    // WordQuest
    HIST_MAIN_MENU,
    HIST_GAME,
    HIST_GAME_OVER,
    HIST_INSTRUCTIONS,
} tGameScreen;
// Logo de raylib
int logoPositionX = screenWidth / 2 - 128;
int logoPositionY = screenHeight / 2 - 128;

int framesCounter = 0;
int lettersCount = 0;

int topSideRecWidth = 16;
int leftSideRecHeight = 16;

int bottomSideRecWidth = 16;
int rightSideRecHeight = 16;

int state = 0; // Tracking animation states (State Machine)
float alpha = 1.0f;
//

tGameScreen drawRaylibScene(tGameScreen currentScreen, Sound point);

tGameScreen drawRaylibScene(tGameScreen currentScreen, Sound point)
{

    if (state == 0) // State 0: Small box blinking
    {
        framesCounter++;
        if (framesCounter == 120)
        {
            state = 1;
            framesCounter = 0; // Reset counter... will be used later...
        }
    }
    else if (state == 1) // State 1: Top and left bars growing
    {
        topSideRecWidth += 4;
        leftSideRecHeight += 4;

        if (topSideRecWidth == 256)
            state = 2;
    }
    else if (state == 2) // State 2: Bottom and right bars growing
    {
        bottomSideRecWidth += 4;
        rightSideRecHeight += 4;

        if (bottomSideRecWidth == 256)
            state = 3;
    }
    else if (state == 3) // State 3: Letters appearing (one by one)
    {
        framesCounter++;

        if (framesCounter / 12) // Every 12 frames, one more letter!
        {
            lettersCount++;
            framesCounter = 0;
        }

        if (lettersCount >= 10) // When all letters have appeared, just fade out everything
        {
            alpha -= 0.02f;

            if (alpha <= 0.0f)
            {
                alpha = 0.0f;
                state = 4;
            }
        }
    }
    else if (state == 4) // State 4: Reset and Replay
    {
        if (IsKeyPressed(KEY_R))
        {
            framesCounter = 0;
            lettersCount = 0;

            topSideRecWidth = 16;
            leftSideRecHeight = 16;

            bottomSideRecWidth = 16;
            rightSideRecHeight = 16;

            alpha = 1.0f;
            state = 0; // Return to State 0
            PlaySound(point);
            return MAIN_MENU;
        }
    }
    ClearBackground(RAYWHITE);

    if (state == 0)
    {
        if ((framesCounter / 15) % 2)
            DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
    }
    else if (state == 1)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
    }
    else if (state == 2)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

        DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
    }
    else if (state == 3)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

        DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

        DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, alpha));
    }
    else if (state == 4)
    {
        DrawText("[R] COMENZAR A JUGAR", 270, 200, 20, GRAY);
    }
    return RAYLIB_SCENE;
    //
}