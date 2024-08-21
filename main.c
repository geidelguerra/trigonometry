#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

void Example1() {
    Vector2 center = { GetScreenWidth() / 2 , GetScreenHeight() / 2 };
    Vector2 mouse = GetMousePosition();

    float angle = 0;
    float radius = Remap(mouse.y, 0, GetScreenHeight(), 50, 200);
    float increment = Remap(mouse.x, 0, GetScreenWidth(), 1, 0.01);

    while (angle < PI * 2) {
        float x = center.x + cos(angle) * radius;
        float y = center.y + sin(angle) * radius;
        DrawCircle(x, y, 5, WHITE);
        angle += increment;
    }

    DrawText("Move the mouse", 22, GetScreenHeight() - 42, 20, GRAY);
}

void Example2() {
    Vector2 center = { GetScreenWidth() / 2 , GetScreenHeight() / 2 };
    Vector2 mouse = GetMousePosition();

    float radius = Vector2Distance(mouse, center);

    // Same as using: Vector2LineAngle(center, mouse) * -1;
    float angle = -atan2f(mouse.y - center.y, mouse.x - center.x) * -1;
    float x = center.x + cos(angle) * radius;
    float y = center.y + sin(angle) * radius;

    DrawLine(center.x, center.y, x, y, YELLOW);
    DrawCircle(x, y, 10, YELLOW);

    char text[20];
    sprintf(text, "%0.1f°", angle * RAD2DEG);
    DrawText(text, center.x + 20, center.y - 20, 20, GRAY);

    DrawText("Move the mouse", 22, GetScreenHeight() - 42, 20, GRAY);
}

int main() {
    InitWindow(800, 800, "Trigonometry");
    SetTargetFPS(144);
    int activeExample = 1;
    int examplesCount = 2;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) {
            activeExample = 1;
        }

        if (IsKeyPressed(KEY_TWO)) {
            activeExample = 2;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        switch (activeExample) {
            case 1: Example1();
            break;
            case 2: Example2();
            break;
        }

        float textX = 22;
        for (int i = 1; i <= examplesCount; i++) {
            char text[10];
            sprintf(text, "%d", i);
            int length = MeasureText(text, 20);
            Color color = i == activeExample ? WHITE : GRAY;
            DrawText(text, textX, 22, 20, color);
            textX += length + 5;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}