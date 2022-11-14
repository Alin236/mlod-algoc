/*******************************************************************************************
*
*   raylib - classic game: space invaders
*
*   Sample game developed by Ian Eito, Albert Martos and Ramon Santamaria
*
*   This game has been created using raylib v1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define NUM_SHOOTS 50
#define NUM_MAX_ENEMIES 50
#define FIRST_WAVE 10
#define SECOND_WAVE 5
#define THIRD_WAVE 10
#define FOURTH_WAVE 5

#define NUM_BONUS 50

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum { FIRST = 0, SECOND, THIRD, FOURTH} EnemyWave;
typedef enum { BASIC = 0, SPEEDY, TANKY, SNAKY } EnemyType;

typedef struct Player{
    Rectangle rec;
    Vector2 speed;
    Color color;
    int life;
    int shootCharge;
} Player;

typedef struct Enemy{
    Rectangle rec[5];
    int numberRec;
    Vector2 speed;
    bool active;
    Color color;
    int life;
    EnemyType type;
} Enemy;

typedef struct Shoot{
    Rectangle rec;
    Vector2 speed;
    bool active;
    Color color;
} Shoot;


typedef struct Bonus{
    Rectangle rec;
    Vector2 speed;
    bool active;
    Color color;
} Bonus;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause =  false;
static bool victory = false;

static Player player = { 0 };
static Enemy enemy[NUM_MAX_ENEMIES] = { 0 };
static Shoot shoot[NUM_SHOOTS] = { 0 };
static EnemyWave wave = { 0 };

static int shootRate = 0;
static float alpha = 0.0f;

static int activeEnemies = 0;
static int enemiesKill = 0;
static bool smooth = false;

static Bonus bonus[NUM_BONUS] = { 0 };
//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

void playerCollideWithEnemy(Enemy*);
void playerCollideWithBonus(Bonus*);
void generateEnemy();
void generateEnemyFirstWave();
void generateEnemySecondWave();
void generateEnemyThirdWave();
void generateEnemyFourthWave();
void enemyShooted(Enemy*);
void mooveEnemy(Enemy*);
bool checkCollisionWithEnemy(Rectangle, Enemy);
void drawAllRectangleEnemy(Enemy);
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "classic game: space invaders");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void)
{
    // Initialize game variables
    shootRate = 0;
    pause = false;
    gameOver = false;
    victory = false;
    smooth = false;
    wave = FIRST;
    activeEnemies = FIRST_WAVE;
    enemiesKill = 0;
    alpha = 0;

    // Initialize player
    player.rec.x =  20;
    player.rec.y = 50;
    player.rec.width = 20;
    player.rec.height = 20;
    player.speed.x = 5;
    player.speed.y = 5;
    player.color = BLACK;
    player.life = 2;
    player.shootCharge = 3;

    // Initialize enemies
    generateEnemy();

    // Initialize shoots
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        shoot[i].rec.x = player.rec.x;
        shoot[i].rec.y = player.rec.y + player.rec.height/4;
        shoot[i].rec.width = 10;
        shoot[i].rec.height = 5;
        shoot[i].speed.x = 7;
        shoot[i].speed.y = 0;
        shoot[i].active = false;
        shoot[i].color = MAROON;
    }

    // Initialize bonus
    for (int i = 0; i < NUM_BONUS; i++)
    {
        bonus[i].rec.x = 0;
        bonus[i].rec.y = 0;
        bonus[i].rec.width = 10;
        bonus[i].rec.height = 10;
        bonus[i].speed.x = 4;
        bonus[i].speed.y = 0;
        bonus[i].active = false;
        bonus[i].color = GREEN;
    }
}

// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            switch (wave)
            {
                case FIRST:
                {
                    if (!smooth)
                    {
                        alpha += 0.02f;

                        if (alpha >= 1.0f) smooth = true;
                    }

                    if (smooth) alpha -= 0.02f;

                    if (enemiesKill == activeEnemies)
                    {
                        enemiesKill = 0;

                        for (int i = 0; i < activeEnemies; i++)
                        {
                            if (!enemy[i].active) enemy[i].active = true;
                        }

                        activeEnemies = SECOND_WAVE;
                        wave = SECOND;
                        generateEnemy();
                        smooth = false;
                        alpha = 0.0f;
                    }
                } break;
                case SECOND:
                {
                    if (!smooth)
                    {
                        alpha += 0.02f;

                        if (alpha >= 1.0f) smooth = true;
                    }

                    if (smooth) alpha -= 0.02f;

                    if (enemiesKill == activeEnemies)
                    {
                        enemiesKill = 0;

                        for (int i = 0; i < activeEnemies; i++)
                        {
                            if (!enemy[i].active) enemy[i].active = true;
                        }

                        activeEnemies = THIRD_WAVE;
                        wave = THIRD;
                        generateEnemy();
                        smooth = false;
                        alpha = 0.0f;
                    }
                } break;
                case THIRD:
                {
                    if (!smooth)
                    {
                        alpha += 0.02f;

                        if (alpha >= 1.0f) smooth = true;
                    }

                    if (smooth) alpha -= 0.02f;

                    if (enemiesKill == activeEnemies)
                    {
                        enemiesKill = 0;

                        for (int i = 0; i < activeEnemies; i++)
                        {
                            if (!enemy[i].active) enemy[i].active = true;
                        }

                        activeEnemies = FOURTH_WAVE;
                        wave = FOURTH;
                        generateEnemy();
                        smooth = false;
                        alpha = 0.0f;
                    }
                } break;
                case FOURTH:
                {
                    if (!smooth)
                    {
                        alpha += 0.02f;

                        if (alpha >= 1.0f) smooth = true;
                    }

                    if (smooth) alpha -= 0.02f;

                    if (enemiesKill == activeEnemies) victory = true;

                } break;
                default: break;
            }

            // Player movement
            if (IsKeyDown(KEY_RIGHT)) player.rec.x += player.speed.x;
            if (IsKeyDown(KEY_LEFT)) player.rec.x -= player.speed.x;
            if (IsKeyDown(KEY_UP)) player.rec.y -= player.speed.y;
            if (IsKeyDown(KEY_DOWN)) player.rec.y += player.speed.y;

            // Player collision with enemy
            for (int i = 0; i < activeEnemies; i++)
            {
                if (enemy[i].active && checkCollisionWithEnemy(player.rec, enemy[i])) playerCollideWithEnemy(enemy+i);
            }

            // Player collision with bonus
            for (int i = 0; i < NUM_BONUS; i++)
            {
                if (bonus[i].active && CheckCollisionRecs(player.rec, bonus[i].rec)) playerCollideWithBonus(bonus+i);
            }

             // Enemy behaviour
            for (int i = 0; i < activeEnemies; i++)
            {
                if (enemy[i].active)
                {
                    mooveEnemy(enemy+i);
                }
            }

            // Bonus behaviour
            for (int i = 0; i < NUM_BONUS; i++)
            {
                if (bonus[i].active)
                {
                    bonus[i].rec.x -= bonus[i].speed.x;

                    if (bonus[i].rec.x < 0)
                    {
                        bonus[i].active = false;
                    }
                }
            }

            // Wall behaviour
            if (player.rec.x <= 0) player.rec.x = 0;
            if (player.rec.x + player.rec.width >= screenWidth) player.rec.x = screenWidth - player.rec.width;
            if (player.rec.y <= 0) player.rec.y = 0;
            if (player.rec.y + player.rec.height >= screenHeight) player.rec.y = screenHeight - player.rec.height;

            // Shoot initialization
            if (IsKeyDown(KEY_SPACE))
            {
                shootRate += 1;

                for (int i = 0; i < NUM_SHOOTS; i++)
                {
                    if (!shoot[i].active && shootRate%player.shootCharge == 0)
                    {
                        shoot[i].rec.x = player.rec.x;
                        shoot[i].rec.y = player.rec.y + player.rec.height/4;
                        shoot[i].active = true;
                        break;
                    }
                }
            }

            // Shoot logic
            for (int i = 0; i < NUM_SHOOTS; i++)
            {
                if (shoot[i].active)
                {
                    // Movement
                    shoot[i].rec.x += shoot[i].speed.x;

                    // Collision with enemy
                    for (int j = 0; j < activeEnemies; j++)
                    {
                        if (enemy[j].active)
                        {
                            if (checkCollisionWithEnemy(shoot[i].rec, enemy[j]))
                            {
                                shoot[i].active = false;
                                if(GetRandomValue(1, 100) >= 75){
                                    for (int k = 0; k < NUM_BONUS; k++)
                                    {
                                        if (!bonus[k].active)
                                        {
                                            bonus[k].rec.x = enemy[j].rec[0].x;
                                            bonus[k].rec.y = enemy[j].rec[0].y;
                                            bonus[k].active = true;
                                            break;
                                        }
                                    }
                                }
                                enemyShooted(enemy+j);
                            }

                            if (shoot[i].rec.x + shoot[i].rec.width >= screenWidth)
                            {
                                shoot[i].active = false;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

        ClearBackground(RAYWHITE);

        if (!gameOver)
        {
            DrawRectangleRec(player.rec, player.color);

            if (wave == FIRST) DrawText("FIRST WAVE", screenWidth/2 - MeasureText("FIRST WAVE", 40)/2, screenHeight/2 - 40, 40, Fade(BLACK, alpha));
            else if (wave == SECOND) DrawText("SECOND WAVE", screenWidth/2 - MeasureText("SECOND WAVE", 40)/2, screenHeight/2 - 40, 40, Fade(BLACK, alpha));
            else if (wave == THIRD) DrawText("THIRD WAVE", screenWidth/2 - MeasureText("THIRD WAVE", 40)/2, screenHeight/2 - 40, 40, Fade(BLACK, alpha));

            for (int i = 0; i < activeEnemies; i++)
            {
                if (enemy[i].active) drawAllRectangleEnemy(enemy[i]);
            }

            for (int i = 0; i < NUM_SHOOTS; i++)
            {
                if (shoot[i].active) DrawRectangleRec(shoot[i].rec, shoot[i].color);
            }

            for (int i = 0; i < NUM_BONUS; i++)
            {
                if (bonus[i].active) DrawRectangleRec(bonus[i].rec, bonus[i].color);
            }

            DrawText(TextFormat("Enemies : %i/%i", enemiesKill, activeEnemies), 20, 20, 40, GRAY);
            DrawText(TextFormat("Life : %i", player.life), 20, 60, 40, GRAY);

            if (victory) DrawText("YOU WIN", screenWidth/2 - MeasureText("YOU WIN", 40)/2, screenHeight/2 - 40, 40, BLACK);

            if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }
        else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);

    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

void playerCollideWithEnemy(Enemy* enemy){
    player.life -= 1;
    float ancienX = enemy->rec[0].x;
    float ancienY = enemy->rec[0].y;
    enemy->rec[0].x = GetRandomValue(screenWidth, screenWidth + 1000);
    enemy->rec[0].y = GetRandomValue(0, screenHeight - enemy->rec[0].height);
    float deltaX = enemy->rec[0].x - ancienX;
    float deltaY = enemy->rec[0].y - ancienY;
    for(int i=1; i<enemy->numberRec; i++){
        enemy->rec[i].x += deltaX;
        enemy->rec[i].y += deltaY;
    }
    if(player.life == 0){
        gameOver = true;
    }
}

void playerCollideWithBonus(Bonus* bonus){
    // Do a bonus
    bonus->active = false;
}


void generateEnemy(){
    switch (wave)
    {
        case FIRST:
            generateEnemyFirstWave();
            break;
        case SECOND:
            generateEnemySecondWave();
            break;
        case THIRD:
            generateEnemyThirdWave();
            break;
        case FOURTH:
            generateEnemyFourthWave();
        default:
            break;
    }
}

void generateEnemyFirstWave(){
    for (int i = 0; i < activeEnemies; i++)
    {
        enemy[i].rec[0].width = 10;
        enemy[i].rec[0].height = 10;
        enemy[i].rec[0].x = GetRandomValue(screenWidth, screenWidth - 1000);
        enemy[i].rec[0].y = GetRandomValue(0, screenHeight - enemy[i].rec[0].height);
        enemy[i].numberRec = 1;
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 5;
        enemy[i].active = true;
        enemy[i].color = GRAY;
        enemy[i].life = 1;
        enemy[i].type = BASIC;
    }
}

void generateEnemySecondWave(){
    for (int i = 0; i < activeEnemies; i++)
    {
        enemy[i].rec[0].width = 15;
        enemy[i].rec[0].height = 5;
        enemy[i].rec[0].x = GetRandomValue(screenWidth, screenWidth + 1000);
        enemy[i].rec[0].y = GetRandomValue(0, screenHeight - enemy[i].rec[0].height);
        enemy[i].numberRec = 1;
        enemy[i].speed.x = 10;
        enemy[i].speed.y = 5;
        enemy[i].active = true;
        enemy[i].color = GRAY;
        enemy[i].life = 1;
        enemy[i].type = SPEEDY;
    }
}

void generateEnemyThirdWave(){
    for (int i = 0; i < activeEnemies; i++)
    {
        enemy[i].rec[0].width = 30;
        enemy[i].rec[0].height = 30;
        enemy[i].rec[0].x = GetRandomValue(screenWidth, screenWidth + 1000);
        enemy[i].rec[0].y = GetRandomValue(0, screenHeight - enemy[i].rec[0].height);
        enemy[i].numberRec = 1;
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 5;
        enemy[i].active = true;
        enemy[i].color = GRAY;
        enemy[i].life = 5;
        enemy[i].type = TANKY;
    }
}

void generateEnemyFourthWave(){
    for (int i = 0; i < activeEnemies; i++)
    {
        enemy[i].rec[0].width = 20;
        enemy[i].rec[0].height = 20;
        enemy[i].rec[0].x = GetRandomValue(screenWidth, screenWidth + 1000);
        enemy[i].rec[0].y = GetRandomValue(0, screenHeight - enemy[i].rec[0].height);
        enemy[i].rec[1].width = 15;
        enemy[i].rec[1].height = 15;
        enemy[i].rec[1].x = enemy[i].rec[0].x - 10;
        enemy[i].rec[1].y = enemy[i].rec[0].y - 15;
        enemy[i].rec[2].width = 15;
        enemy[i].rec[2].height = 15;
        enemy[i].rec[2].x = enemy[i].rec[0].x - 10;
        enemy[i].rec[2].y = enemy[i].rec[0].y + 20;
        enemy[i].rec[3].width = 10;
        enemy[i].rec[3].height = 10;
        enemy[i].rec[3].x = enemy[i].rec[1].x - 10;
        enemy[i].rec[3].y = enemy[i].rec[1].y - 5;
        enemy[i].rec[4].width = 10;
        enemy[i].rec[4].height = 10;
        enemy[i].rec[4].x = enemy[i].rec[2].x - 10;
        enemy[i].rec[4].y = enemy[i].rec[2].y + 10;
        enemy[i].numberRec = 5;
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 0;
        enemy[i].active = true;
        enemy[i].color = GRAY;
        enemy[i].life = 5;
        enemy[i].type = TANKY;
    }
}

void enemyShooted(Enemy* enemy){
    enemy->life--;
    if(enemy->life == 0){
        enemy->active = false;
        enemiesKill++;
    }
}

void mooveEnemy(Enemy* enemy){
    float ancienX = enemy->rec[0].x;
    float ancienY = enemy->rec[0].y;
    enemy->rec[0].x -= enemy->speed.x;

    if (enemy->rec[0].x < 0)
    {
        enemy->rec[0].x = GetRandomValue(screenWidth, screenWidth + 1000);
        enemy->rec[0].y = GetRandomValue(0, screenHeight - enemy->rec[0].height);
    }

    float deltaX = enemy->rec[0].x - ancienX;
    float deltaY = enemy->rec[0].y - ancienY;

    for(int i=1; i<enemy->numberRec; i++){
        enemy->rec[i].x += deltaX;
        enemy->rec[i].y += deltaY;
    }
}

bool checkCollisionWithEnemy(Rectangle rec, Enemy enemy){
    for(int i=0; i<enemy.numberRec; i++){
        if(CheckCollisionRecs(rec, enemy.rec[i])) return true;
    }
    return false;
}

void drawAllRectangleEnemy(Enemy enemy){
    for(int i=0; i<enemy.numberRec; i++)
        DrawRectangleRec(enemy.rec[i], enemy.color);
}