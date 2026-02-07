#include "raylib.h"
#include <assert.h>
#include <math.h>

#include "base.c"
// Coordinates normalized
// Shoks
// fusions
// DT
// scale
// trajectories

constexpr u32 BALLS_NUMBER = 3;
constexpr double G = 6.674;
constexpr u32 TARGET_FPS = 120;
constexpr double TIME_FACTOR = 20.;
constexpr double MAX_ACUMULATOR = 0.25;
constexpr double PHYS_DT = TIME_FACTOR / TARGET_FPS;

typedef struct {
    double mass[BALLS_NUMBER];
    double radius[BALLS_NUMBER];
    Vec2 position[BALLS_NUMBER];
    Vec2 velocity[BALLS_NUMBER];
    Vec2 acceleration[BALLS_NUMBER];
} Balls;

Balls balls_init();
void balls_accelerate(Balls *balls);
void balls_move(Balls *balls);
void balls_draw(Balls *balls);

int main(void) {

    InitWindow(800, 600, "N-body??");
    SetTargetFPS(TARGET_FPS);

    Balls balls = balls_init();
    double acumulator = 0.;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        acumulator += GetFrameTime();
        acumulator = MIN(acumulator, MAX_ACUMULATOR);
        while (acumulator >= PHYS_DT) {
            balls_accelerate(&balls);
            balls_move(&balls);
            acumulator -= PHYS_DT;
        }
        balls_draw(&balls);

        DrawText("N-body??", 10, 10, 20, LIGHTGRAY);
        DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

Balls balls_init() {
    return (Balls){
        .mass = {10, 30, 50},
        .radius = {10, 30, 50},
        .position = {(Vec2){100, 100}, (Vec2){100, 200}, (Vec2){400, 400}},
        .velocity = {(Vec2){1, 0}, (Vec2){-0.5, 0}, (Vec2){0, 0}}};
}

void balls_accelerate(Balls *balls) {
    for (u32 i = 0; i < BALLS_NUMBER; ++i) {
        balls->acceleration[i].x = 0.0;
        balls->acceleration[i].y = 0.0;
    }
    for (u32 i = 0; i < BALLS_NUMBER - 1; ++i) {
        for (u32 j = i + 1; j < BALLS_NUMBER; ++j) {
            Vec2 r = {.x = balls->position[j].x - balls->position[i].x,
                      .y = balls->position[j].y - balls->position[i].y};
            double r_size = sqrt(r.x * r.x + r.y * r.y);
            double M = balls->mass[j];
            double m = balls->mass[i];
            balls->acceleration[i].x +=
                G * M / (r_size * r_size * r_size) * r.x;
            balls->acceleration[i].y +=
                G * M / (r_size * r_size * r_size) * r.y;

            balls->acceleration[j].x +=
                -G * m / (r_size * r_size * r_size) * r.x;
            balls->acceleration[j].y +=
                -G * m / (r_size * r_size * r_size) * r.y;
        }
    }
}

void balls_move(Balls *balls) {
    for (u32 i = 0; i < BALLS_NUMBER; ++i) {
        balls->velocity[i].x += balls->acceleration[i].x * PHYS_DT;
        balls->velocity[i].y += balls->acceleration[i].y * PHYS_DT;

        balls->position[i].x += balls->velocity[i].x * PHYS_DT;
        balls->position[i].y += balls->velocity[i].y * PHYS_DT;
    }
}

void balls_draw(Balls *balls) {
    for (u32 i = 0; i < BALLS_NUMBER; ++i) {
        i32 x = (i32)balls->position[i].x;
        i32 y = (i32)balls->position[i].y;
        double r = balls->radius[i];
        DrawCircle(x, y, r, LIGHTGRAY);
    }
}
