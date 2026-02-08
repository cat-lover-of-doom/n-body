#include "raylib.h"
#include <assert.h>
#include <math.h>

#include "base.c"
// Coordinates normalized
// Shoks
// fusions
// scale
// trajectories
// RK 4
// assert
constexpr u32 TARGET_FPS = 120;

struct Window {
    u32 height;
    u32 width;
} window;

constexpr u32 BALLS_NUMBER = 3;
constexpr double G = 6.674;
constexpr double MAX_ACUMULATOR = 0.25;
constexpr double PHYS_DT = 1. / 120;
constexpr double SIM_SPEED = 2000.0;

typedef struct {
    double mass[BALLS_NUMBER];
    double radius[BALLS_NUMBER];
    Vec2 position[BALLS_NUMBER];
    Vec2 velocity[BALLS_NUMBER];
    Vec2 acceleration[BALLS_NUMBER];
} Balls;

Vec2 screen_coordinates(Vec2 central_coordinates);
Balls balls_init();
void balls_accelerate(Balls *balls);
void balls_move(Balls *balls);
void balls_draw(Balls *balls);

struct Window window = {.width = 800, .height = 600};
int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(window.width, window.height, "N-body??");
    SetTargetFPS(TARGET_FPS);

    Balls balls = balls_init();
    double acumulator = 0.;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        acumulator += GetFrameTime() * SIM_SPEED;
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

inline Vec2 screen_coordinates(Vec2 central_coordinates) {
    if (IsWindowResized()) {
        window.width = GetScreenWidth();
        window.height = GetScreenHeight();
    }

    central_coordinates.x += window.width / 2.;
    central_coordinates.y = (window.height - central_coordinates.y) - window.height / 2.;
    return central_coordinates;
}

Balls balls_init() {
    return (Balls){
        .mass = {10, 30, 50},
        .radius = {10, 30, 50},
        .position = {(Vec2){0, 0}, (Vec2){0, 100}, (Vec2){-200, -100}},
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
        Vec2 screen_p = screen_coordinates(balls->position[i]); 
        double r = balls->radius[i];
        DrawCircle(screen_p.x,screen_p.y, r, LIGHTGRAY);
    }
}
