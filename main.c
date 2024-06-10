#include "mathQuest.h"
#include "geoQuest.h"
#include "histQuest.h"
#include "sceneControl.h"

void drawMainMenu(Rectangle mathButton, Rectangle geoButton, Rectangle histButton);
void drawSoundState(Texture2D volumeOn, Texture2D volumeOff, bool state, Vector2 volumeButtonPossition);
void drawRemainingLives(int remaining, Texture2D heart, Texture2D brokenHeart, Vector2 heartOnePosition, Vector2 heartTwoPosition, Vector2 heartThreePosition, tDifficulty currentDifficulty);

int main()
{
    InitWindow(screenWidth, screenHeight, "Programacion estructurada: CrazyQuest");
    InitAudioDevice();
    SetTargetFPS(framesPerSecond);

    tDifficulty currentDifficulty;

    bool mlgFlag = false;
    int mlgRandom;

    int score;
    int seconds;
    int actualCorrectAnswer = 0;
    int remainingLives = 3;
    int randomValue;
    int randomValue2 = GetRandomValue(1, 100);
    int randomValue3 = GetRandomValue(1, 100);
    int correctOption;

    float remainingTime;
    float cronometer = 0;

    char answerText[10] = {0};

    bool soundState = true;
    bool showGithubButton = true;

    tGameScreen currentScreen = RAYLIB_SCENE;
    // currentScreen = MAIN_MENU;
    Vector2 volumeButtonPossition = {650, 500};
    Rectangle volumeButtonPossitionR = {650, 500, 100, 100};
    //
    float githubButtonPossitionX = 30;
    float githubButtonPossitionY = 520;
    Vector2 githubButtonPossition = {githubButtonPossitionX, githubButtonPossitionY};
    Rectangle githubButtonPossitionR = {100, 500, 100, 100};
    //
    float heartOnePositionX = 560;
    float heartsPositionY = 500;
    Vector2 heartOnePosition = {heartOnePositionX, heartsPositionY};
    Vector2 heartTwoPosition = {heartOnePositionX + 75, heartsPositionY};
    Vector2 heartThreePosition = {heartOnePositionX + 150, heartsPositionY};

    // Botones para los modos    de juego
    Rectangle mathButton = {300, 100, 200, 50};
    Rectangle geoButton = {300, 200, 200, 50};
    Rectangle histButton = {300, 300, 200, 50};
    // Botones para las GeoOpciones
    Rectangle optionOne = {50, 300, 200, 50};
    Rectangle optionTwo = {300, 300, 200, 50};
    Rectangle optionThree = {550, 300, 200, 50};
    // Botones de dificultad
    Rectangle easyButton = {300, 100, 200, 50};
    Rectangle mediumButton = {300, 200, 200, 50};
    Rectangle hardButton = {300, 300, 200, 50};
    // Otros botones
    Rectangle helpButton = {60, 500, 200, 50};
    Rectangle mainMenuButton = {300, 500, 200, 50};
    Rectangle exitInstructionsButton = {300, 500, 200, 50};
    // Declaracion de la estructura de cada problema
    tProblem currentProblem;
    tGeoCapital currentGeoCapital;
    tHistQuestion currentHistAnswer;
    // Sonidos utilizados
    Sound loseSound = LoadSound("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/sounds/loseSound.mp3");
    Sound hurt = LoadSound("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/sounds/hurt.mp3");
    Sound mainMenuMusic = LoadSound("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/sounds/mainMenuMusic.mp3");
    Sound point = LoadSound("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/sounds/point.mp3");
    Sound click = LoadSound("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/sounds/click.mp3");
    Sound damnson = LoadSound("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/sounds/damnson.mp3");
    Sound trapaholics = LoadSound("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/sounds/trapaholics.mp3");
    Sound wmle = LoadSound("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/sounds/wmle.wav");
    // Imagenes utilizadas
    Texture2D volumeOn = LoadTexture("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/images/volumeOn.png");
    Texture2D volumeOff = LoadTexture("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/images/volumeOff.png");
    Texture2D heart = LoadTexture("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/images/heart.png");
    Texture2D brokenHeart = LoadTexture("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/images/brokenHeart.png");
    Texture2D github = LoadTexture("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/resources/images/github.png");
    // Partidas guardadas
    tMathSaveData saveMathDataStruct = loadMathData("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/mathQuestData");
    tGeoSaveData saveGeoDataStruct = loadGeoData("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/geoQuestData");
    tHistSaveData saveHistDataStruct = loadHistData("/Users/pedrocbcmp/Desktop/Tercer semestre/Programacion estructurada/CrazyLearnQuest/histQuestData");
    //
    PlaySound(mainMenuMusic);
    //  Inicio de game loop

    while (!WindowShouldClose())
    {
        if (score != 0 && mlgFlag == false && score % 5 == 0.0000)
        {
            mlgRandom = GetRandomValue(1, 3);
            switch (mlgRandom)
            {
            case 1:
                PlaySound(wmle);
                break;
            case 2:
                PlaySound(damnson);
                break;
            case 3:
                PlaySound(trapaholics);
                break;
            }
            mlgFlag = true;
        }
        if (mlgFlag == true && score % 5 != 0.000)
        {
            mlgFlag = false;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 mousePoint = GetMousePosition();

        switch (currentScreen)
        {
        case RAYLIB_SCENE:
        {
            currentScreen = drawRaylibScene(currentScreen, point);
            break;
        }
        case MAIN_MENU:
        {
            score = 0;
            drawMainMenu(mathButton, geoButton, histButton);
            drawSoundState(volumeOn, volumeOff, soundState, volumeButtonPossition);
            if (showGithubButton)
            {
                DrawTextureV(github, githubButtonPossition, WHITE);
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(mousePoint, mathButton))
                {
                    currentScreen = MATH_MAIN_MENU;
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, geoButton))
                {
                    currentScreen = GEO_MAIN_MENU;
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, histButton))
                {
                    currentScreen = HIST_MAIN_MENU;
                    PlaySound(click);
                }
                //
                else if (CheckCollisionPointRec(mousePoint, githubButtonPossitionR) && showGithubButton)
                {
                    OpenURL("https://github.com/PedroxionX/CrazyLearnQuest");
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, volumeButtonPossitionR))
                {
                    PlaySound(click);
                    if (soundState)
                    {
                        soundState = false;
                        SetMasterVolume(0);
                    }
                    else
                    {
                        soundState = true;
                        SetMasterVolume(100);
                    }
                }
                //
            }
            break;
        }
        //
        case MATH_MAIN_MENU:
        {
            drawMathMainMenu(easyButton, mediumButton, hardButton, helpButton, mainMenuButton, saveMathDataStruct.maxScore);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                remainingLives = 3;
                if (CheckCollisionPointRec(mousePoint, easyButton))
                {
                    currentDifficulty = EASY;
                    currentScreen = MATH_GAME;
                    StopSound(mainMenuMusic);
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, mediumButton))
                {
                    currentDifficulty = MEDIUM;
                    currentScreen = MATH_GAME;
                    seconds = 10;
                    remainingTime = seconds * framesPerSecond;
                    StopSound(mainMenuMusic);
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, hardButton))
                {
                    currentDifficulty = HARD;
                    currentScreen = MATH_GAME;
                    seconds = 5;
                    remainingTime = seconds * framesPerSecond;
                    StopSound(mainMenuMusic);
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, helpButton))
                {
                    currentScreen = MATH_INSTRUCTIONS;
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, mainMenuButton))
                {
                    currentScreen = MAIN_MENU;
                    PlaySound(click);
                }
                if (currentScreen == MATH_GAME)
                {
                    score = 0;
                    currentProblem = generateMathProblem(currentDifficulty);
                }
                remainingTime += 0.01;
            }
            break;
        }
        case MATH_GAME:
        {
            // Dibujar pantalla
            drawMathGameScreen(currentProblem, answerText, score, remainingTime, framesPerSecond, currentDifficulty, cronometer);
            drawRemainingLives(remainingLives, heart, brokenHeart, heartOnePosition, heartTwoPosition, heartThreePosition, currentDifficulty);
            // Quitar vida por tiempo
            if (remainingTime / framesPerSecond <= 0 && currentDifficulty != EASY)
            {
                remainingLives--;
                if (remainingLives != 0)
                {
                    PlaySound(hurt);
                    currentProblem = generateMathProblem(currentDifficulty);
                    answerText[0] = '\0';
                    remainingTime = seconds * framesPerSecond;
                }
            }
            // Revisar respuesta
            if (IsKeyPressed(KEY_ENTER))
            {
                if (atoi(answerText) == currentProblem.answer)
                {
                    PlaySound(point);
                    score++;
                    if (currentDifficulty != EASY)
                    {
                        remainingTime = seconds * framesPerSecond;
                    }
                }
                else
                {
                    remainingLives--;
                    if (remainingLives != 0)
                    {
                        PlaySound(hurt);
                    }
                }
                currentProblem = generateMathProblem(currentDifficulty);
                answerText[0] = '\0';
            }
            int key = GetCharPressed();
            if (key >= '0' && key <= '9')
            {
                int len = strlen(answerText);
                if (len < 9)
                {
                    answerText[len] = (char)key;
                    answerText[len + 1] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                int len = strlen(answerText);
                if (len > 0)
                {
                    answerText[len - 1] = '\0';
                }
            }
            // Perder juego
            if (remainingLives == 0)
            {
                currentScreen = MATH_GAME_OVER;
                PlaySound(loseSound);
            }
            actualCorrectAnswer = currentProblem.answer;
            remainingTime--;
            cronometer++;
            break;
        }
        case MATH_GAME_OVER:
        {
            if (score > saveMathDataStruct.maxScore)
            {
                saveMathDataStruct.maxScore = score;
                saveMathData("mathQuestData", saveMathDataStruct);
            }
            drawMathGameOverScreen(score, actualCorrectAnswer);
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = MATH_MAIN_MENU;
                answerText[0] = '\0';
                PlaySound(mainMenuMusic);
            }
            break;
        }
        case MATH_INSTRUCTIONS:
        {
            drawMathInstructions(exitInstructionsButton);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, exitInstructionsButton))
            {
                currentScreen = MATH_MAIN_MENU;
                PlaySound(click);
            }
            break;
        }
        //
        case GEO_MAIN_MENU:
        {
            remainingLives = 3;
            drawGeoMainMenu(easyButton, helpButton, mainMenuButton, saveGeoDataStruct.maxScore);
            seconds = 60;
            remainingTime = seconds * framesPerSecond;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(mousePoint, easyButton))
                {

                    currentScreen = GEO_GAME;
                    StopSound(mainMenuMusic);
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, helpButton))
                {
                    currentScreen = GEO_INSTRUCTIONS;
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, mainMenuButton))
                {
                    currentScreen = MAIN_MENU;
                    PlaySound(click);
                }
                if (currentScreen == GEO_GAME)
                {
                    score = 0;
                    randomValue = GetRandomValue(1, quantityCountrys); // Valor random que seleccionara el pais aleatorio
                    correctOption = GetRandomValue(1, 3);
                    currentGeoCapital = generateGeoProblem(randomValue);
                    // Logica para que verificar que no se repiten
                    if (randomValue == randomValue2)
                    {
                        randomValue2 = randomValue - 1;
                        if (randomValue2 <= 0)
                        {
                            randomValue2 = GetRandomValue(5, quantityCountrys);
                        }
                    }
                    if (randomValue3 == randomValue || randomValue3 == randomValue2)
                    {
                        randomValue3 = randomValue2 - 1;
                        if (randomValue3 <= 0)
                        {
                            randomValue3 = GetRandomValue(5, quantityCountrys);
                        }
                    }
                }
            }
            break;
        }
        case GEO_GAME:
        {
            // Dibujar pantalla
            drawGeoGameScreen(randomValue, randomValue2, randomValue3, score, correctOption, optionOne, optionTwo, optionThree, remainingTime, framesPerSecond);
            drawRemainingLives(remainingLives, heart, brokenHeart, heartOnePosition, heartTwoPosition, heartThreePosition, currentDifficulty);
            // Perder juego
            if (remainingTime == 0 || remainingLives == 0)
            {
                PlaySound(loseSound);
                currentScreen = GEO_GAME_OVER;
            }
            // Revisar respuesta
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                switch (correctOption)
                {
                case 1:
                    if (CheckCollisionPointRec(mousePoint, optionOne))
                    {
                        PlaySound(point);
                        randomValue = GetRandomValue(1, quantityCountrys); // Valor random que seleccionara el pais aleatorio
                        randomValue2 = GetRandomValue(1, quantityCountrys);
                        randomValue3 = GetRandomValue(1, quantityCountrys);
                        correctOption = GetRandomValue(1, 3);
                        currentGeoCapital = generateGeoProblem(randomValue);
                        // Logica para que verificar que no se repiten
                        if (randomValue == randomValue2)
                        {
                            randomValue2 = randomValue - 1;
                            if (randomValue2 <= 0)
                            {
                                randomValue2 = GetRandomValue(5, quantityCountrys);
                            }
                        }
                        if (randomValue3 == randomValue || randomValue3 == randomValue2)
                        {
                            randomValue3 = randomValue2 - 1;
                            if (randomValue3 <= 0)
                            {
                                randomValue3 = GetRandomValue(5, quantityCountrys);
                            }
                        }
                        score++;
                        drawGeoGameScreen(randomValue, randomValue2, randomValue3, score, correctOption, optionOne, optionTwo, optionThree, remainingTime, framesPerSecond);
                    }
                    if (CheckCollisionPointRec(mousePoint, optionTwo))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    if (CheckCollisionPointRec(mousePoint, optionThree))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    break;
                case 2:
                    if (CheckCollisionPointRec(mousePoint, optionOne))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    if (CheckCollisionPointRec(mousePoint, optionTwo))
                    {
                        PlaySound(point);
                        randomValue = GetRandomValue(1, quantityCountrys); // Valor random que seleccionara el pais aleatorio
                        randomValue2 = GetRandomValue(1, quantityCountrys);
                        randomValue3 = GetRandomValue(1, quantityCountrys);
                        correctOption = GetRandomValue(1, 3);
                        currentGeoCapital = generateGeoProblem(randomValue);
                        // Logica para que verificar que no se repiten
                        if (randomValue == randomValue2)
                        {
                            randomValue2 = randomValue - 1;
                            if (randomValue2 <= 0)
                            {
                                randomValue2 = GetRandomValue(5, quantityCountrys);
                            }
                        }
                        if (randomValue3 == randomValue || randomValue3 == randomValue2)
                        {
                            randomValue3 = randomValue2 - 1;
                            if (randomValue3 <= 0)
                            {
                                randomValue3 = GetRandomValue(5, quantityCountrys);
                            }
                        }
                        score++;
                        drawGeoGameScreen(randomValue, randomValue2, randomValue3, score, correctOption, optionOne, optionTwo, optionThree, remainingTime, framesPerSecond);
                    }
                    if (CheckCollisionPointRec(mousePoint, optionThree))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    break;
                case 3:
                    if (CheckCollisionPointRec(mousePoint, optionOne))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    if (CheckCollisionPointRec(mousePoint, optionTwo))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    if (CheckCollisionPointRec(mousePoint, optionThree))
                    {
                        PlaySound(point);
                        randomValue = GetRandomValue(1, quantityCountrys); // Valor random que seleccionara el pais aleatorio
                        randomValue2 = GetRandomValue(1, quantityCountrys);
                        randomValue3 = GetRandomValue(1, quantityCountrys);
                        correctOption = GetRandomValue(1, 3);
                        currentGeoCapital = generateGeoProblem(randomValue);
                        // Logica para que verificar que no se repiten
                        if (randomValue == randomValue2)
                        {
                            randomValue2 = randomValue - 1;
                            if (randomValue2 <= 0)
                            {
                                randomValue2 = GetRandomValue(5, quantityCountrys);
                            }
                        }
                        if (randomValue3 == randomValue || randomValue3 == randomValue2)
                        {
                            randomValue3 = randomValue2 - 1;
                            if (randomValue3 <= 0)
                            {
                                randomValue3 = GetRandomValue(5, quantityCountrys);
                            }
                        }
                        score++;
                        drawGeoGameScreen(randomValue, randomValue2, randomValue3, score, correctOption, optionOne, optionTwo, optionThree, remainingTime, framesPerSecond);
                    }
                    break;
                }
            }

            remainingTime--;
            break;
        }
        case GEO_GAME_OVER:
        {
            if (score > saveGeoDataStruct.maxScore)
            {
                saveGeoDataStruct.maxScore = score;
                saveGeoData("geoQuestData", saveGeoDataStruct);
            }
            drawGeoGameOverScreen(score, currentGeoCapital);
            if (IsKeyPressed(KEY_ENTER))
            {

                currentScreen = GEO_MAIN_MENU;
                PlaySound(mainMenuMusic);
                score = 0;
            }
            break;
        }
        case GEO_INSTRUCTIONS:
        {
            drawGeoInstructions(exitInstructionsButton);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, exitInstructionsButton))
            {
                currentScreen = GEO_MAIN_MENU;
                PlaySound(click);
            }
            break;
        }
        //
        case HIST_MAIN_MENU:
        {
            remainingLives = 3;
            drawHistMainMenu(easyButton, helpButton, mainMenuButton, saveHistDataStruct.maxScore);
            seconds = 60;
            remainingTime = seconds * framesPerSecond;
            remainingTime--;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(mousePoint, easyButton))
                {
                    currentScreen = HIST_GAME;
                    StopSound(mainMenuMusic);
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, helpButton))
                {
                    currentScreen = HIST_INSTRUCTIONS;
                    PlaySound(click);
                }
                else if (CheckCollisionPointRec(mousePoint, mainMenuButton))
                {
                    currentScreen = MAIN_MENU;
                    PlaySound(click);
                }
                if (currentScreen == HIST_GAME)
                {
                    ClearBackground(RAYWHITE);
                    score = 0;
                    randomValue = GetRandomValue(0, quantityHistQuestions); // Valor random que seleccionara el pais aleatorio
                    randomValue2 = GetRandomValue(0, quantityHistQuestions);
                    randomValue3 = GetRandomValue(0, quantityHistQuestions);
                    correctOption = GetRandomValue(1, 3);
                    currentHistAnswer = generateHistProblem(randomValue, "questions.txt");
                    // Logica para que verificar que no se repiten
                    if (randomValue == randomValue2)
                    {
                        randomValue2 = randomValue - 1;
                        if (randomValue2 <= 0)
                        {
                            randomValue2 = GetRandomValue(5, quantityHistQuestions);
                        }
                    }
                    if (randomValue3 == randomValue || randomValue3 == randomValue2)
                    {
                        randomValue3 = randomValue2 - 1;
                        if (randomValue3 <= 0)
                        {
                            randomValue3 = GetRandomValue(5, quantityHistQuestions);
                        }
                    }
                    drawHistGameScreen(randomValue, randomValue2, randomValue3, score, correctOption, optionOne, optionTwo, optionThree, remainingTime, framesPerSecond);
                }
            }
            break;
        }
        case HIST_GAME:
        {
            // Dibujar pantalla
            drawHistGameScreen(randomValue, randomValue2, randomValue3, score, correctOption, optionOne, optionTwo, optionThree, remainingTime, framesPerSecond);
            drawRemainingLives(remainingLives, heart, brokenHeart, heartOnePosition, heartTwoPosition, heartThreePosition, currentDifficulty);
            // Perder juego
            if (remainingTime == 0 || remainingLives == 0)
            {
                PlaySound(loseSound);
                currentScreen = HIST_GAME_OVER;
            }
            // Revisar respuesta
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                switch (correctOption)
                {
                case 1:
                {
                    if (CheckCollisionPointRec(mousePoint, optionOne))
                    {
                        PlaySound(point);
                        randomValue = GetRandomValue(0, quantityHistQuestions); // Valor random que seleccionara el pais aleatorio
                        randomValue2 = GetRandomValue(0, quantityHistQuestions);
                        randomValue3 = GetRandomValue(0, quantityHistQuestions);
                        correctOption = GetRandomValue(1, 3);
                        currentHistAnswer = generateHistProblem(randomValue, "questions.txt");
                        // Logica para que verificar que no se repiten
                        if (randomValue == randomValue2)
                        {
                            randomValue2 = randomValue - 1;
                            if (randomValue2 <= 0)
                            {
                                randomValue2 = GetRandomValue(5, quantityHistQuestions);
                            }
                        }
                        if (randomValue3 == randomValue || randomValue3 == randomValue2)
                        {
                            randomValue3 = randomValue2 - 1;
                            if (randomValue3 <= 0)
                            {
                                randomValue3 = GetRandomValue(5, quantityHistQuestions);
                            }
                        }
                        score++;
                        drawHistGameScreen(randomValue, randomValue2, randomValue3, score, correctOption, optionOne, optionTwo, optionThree, remainingTime, framesPerSecond);
                    }
                    if (CheckCollisionPointRec(mousePoint, optionTwo))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    if (CheckCollisionPointRec(mousePoint, optionThree))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    break;
                }
                case 2:
                {
                    if (CheckCollisionPointRec(mousePoint, optionOne))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    if (CheckCollisionPointRec(mousePoint, optionTwo))
                    {
                        PlaySound(point);
                        randomValue = GetRandomValue(0, quantityHistQuestions); // Valor random que seleccionara el pais aleatorio
                        randomValue2 = GetRandomValue(0, quantityHistQuestions);
                        randomValue3 = GetRandomValue(0, quantityHistQuestions);
                        correctOption = GetRandomValue(1, 3);
                        currentHistAnswer = generateHistProblem(randomValue, "questions.txt");
                        // Logica para que verificar que no se repiten
                        if (randomValue == randomValue2)
                        {
                            randomValue2 = randomValue - 1;
                            if (randomValue2 <= 0)
                            {
                                randomValue2 = GetRandomValue(5, quantityHistQuestions);
                            }
                        }
                        if (randomValue3 == randomValue || randomValue3 == randomValue2)
                        {
                            randomValue3 = randomValue2 - 1;
                            if (randomValue3 <= 0)
                            {
                                randomValue3 = GetRandomValue(5, quantityHistQuestions);
                            }
                        }
                        score++;
                        drawHistGameScreen(randomValue, randomValue2, randomValue3, score, correctOption, optionOne, optionTwo, optionThree, remainingTime, framesPerSecond);
                    }
                    if (CheckCollisionPointRec(mousePoint, optionThree))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    break;
                }
                case 3:
                {
                    if (CheckCollisionPointRec(mousePoint, optionOne))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    if (CheckCollisionPointRec(mousePoint, optionTwo))
                    {
                        PlaySound(hurt);
                        remainingLives--;
                    }
                    if (CheckCollisionPointRec(mousePoint, optionThree))
                    {
                        PlaySound(point);
                        randomValue = GetRandomValue(0, quantityHistQuestions); // Valor random que seleccionara el pais aleatorio
                        randomValue2 = GetRandomValue(0, quantityHistQuestions);
                        randomValue3 = GetRandomValue(0, quantityHistQuestions);
                        correctOption = GetRandomValue(1, 3);
                        currentHistAnswer = generateHistProblem(randomValue, "questions.txt");
                        // Logica para que verificar que no se repiten
                        if (randomValue == randomValue2)
                        {
                            randomValue2 = randomValue - 1;
                            if (randomValue2 <= 0)
                            {
                                randomValue2 = GetRandomValue(5, quantityHistQuestions);
                            }
                        }
                        if (randomValue3 == randomValue || randomValue3 == randomValue2)
                        {
                            randomValue3 = randomValue2 - 1;
                            if (randomValue3 <= 0)
                            {
                                randomValue3 = GetRandomValue(5, quantityHistQuestions);
                            }
                        }
                        score++;
                        drawHistGameScreen(randomValue, randomValue2, randomValue3, score, correctOption, optionOne, optionTwo, optionThree, remainingTime, framesPerSecond);
                    }
                    break;
                }
                }
            }
            remainingTime--;
            break;
        }
        case HIST_GAME_OVER:
        {
            if (score > saveHistDataStruct.maxScore)
            {
                saveHistDataStruct.maxScore = score;
                saveHistData("histQuestData", saveHistDataStruct);
            }
            drawHistGameOverScreen(score, currentHistAnswer);
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = HIST_MAIN_MENU;
                PlaySound(mainMenuMusic);
                score = 0;
            }
            break;
        }
        case HIST_INSTRUCTIONS:
        {
            drawHistInstructions(exitInstructionsButton);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, exitInstructionsButton))
            {
                currentScreen = HIST_MAIN_MENU;
                PlaySound(click);
            }
            break;
        }
        }
        EndDrawing();
        ClearBackground(RAYWHITE);
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}

void drawMainMenu(Rectangle mathButton, Rectangle geoButton, Rectangle histButton)
{
    DrawText("Selecciona un modo de juego", 120, 30, 40, DARKGRAY);
    DrawRectangleRec(mathButton, LIGHTGRAY);
    DrawText("MathQuest", mathButton.x + 45, mathButton.y + 14, 20, DARKGRAY);
    DrawRectangleRec(geoButton, LIGHTGRAY);
    DrawText("GeoQuest", geoButton.x + 45, geoButton.y + 14, 20, DARKGRAY);
    DrawRectangleRec(histButton, LIGHTGRAY);
    DrawText("HistoryQuest", histButton.x + 37, histButton.y + 14, 20, DARKGRAY);
}
void drawSoundState(Texture2D volumeOn, Texture2D volumeOff, bool state, Vector2 volumeButtonPossition)
{
    switch (state)
    {
    case true:
        DrawTextureV(volumeOn, volumeButtonPossition, WHITE);
        break;
    case false:
        DrawTextureV(volumeOff, volumeButtonPossition, WHITE);
        break;
    }
}
void drawRemainingLives(int remaining, Texture2D heart, Texture2D brokenHeart, Vector2 heartOnePosition, Vector2 heartTwoPosition, Vector2 heartThreePosition, tDifficulty currentDifficulty)
{
    switch (remaining)
    {
    case 1:
    {
        ClearBackground(RAYWHITE);
        DrawTextureV(heart, heartOnePosition, WHITE);
        DrawTextureV(brokenHeart, heartTwoPosition, WHITE);
        DrawTextureV(brokenHeart, heartThreePosition, WHITE);
        break;
    }
    case 2:
    {
        ClearBackground(RAYWHITE);
        DrawTextureV(heart, heartOnePosition, WHITE);
        DrawTextureV(heart, heartTwoPosition, WHITE);
        DrawTextureV(brokenHeart, heartThreePosition, WHITE);
        break;
    }
    case 3:
    {
        ClearBackground(RAYWHITE);
        DrawTextureV(heart, heartOnePosition, WHITE);
        DrawTextureV(heart, heartTwoPosition, WHITE);
        DrawTextureV(heart, heartThreePosition, WHITE);
        break;
    }
    }
}