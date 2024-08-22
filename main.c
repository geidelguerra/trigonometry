#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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

void Example3() {
    Vector2 center = { GetScreenWidth() / 2 , GetScreenHeight() / 2 };

    time_t currentTime;
    struct tm *timeinfo;
    time(&currentTime);
    timeinfo = localtime(&currentTime);

    float faceRadius = 310;
    float secondsRadius = 290;
    float minutesRadius = 250;
    float hoursRadius = 200;

    DrawCircleV(center, 310, WHITE);

    for (int i = 0; i < 60; i++) {
        float angle = i / 60.0 * (PI * 2) - (PI / 2);
        float tickLength = 20;
        float tickThickness = 2;
        if (i % 5 == 0 ) {
            tickLength = 40;
            tickThickness = 4;
        }

        Vector2 startPos = {
            center.x + cos(angle) * (faceRadius - tickLength),
            center.y + sin(angle) * (faceRadius - tickLength),
        };
        Vector2 endPos = {
            center.x + cos(angle) * faceRadius,
            center.y + sin(angle) * faceRadius,
        };
        DrawLineEx(startPos, endPos, tickThickness, BLACK);
    }

    float secondsAngle = (timeinfo->tm_sec / 60.0 * (PI * 2)) - (PI / 2);
    Vector2 secondsPosition = {
        center.x + cos(secondsAngle) * secondsRadius,
        center.y + sin(secondsAngle) * secondsRadius
    };
    DrawLineEx(center, secondsPosition, 2, BLACK);

    float minutesAngle = (timeinfo->tm_min / 60.0 * (PI * 2)) - (PI / 2);
    Vector2 minutesPosition = {
        center.x + cos(minutesAngle) * minutesRadius,
        center.y + sin(minutesAngle) * minutesRadius
    };
    DrawLineEx(center, minutesPosition, 4, BLACK);

    float hoursAngle = ((timeinfo->tm_hour % 12) / 12.0) * (PI * 2) - (PI / 2);
    Vector2 hoursPosition = {
        center.x + cos(hoursAngle) * hoursRadius,
        center.y + sin(hoursAngle) * hoursRadius
    };
    DrawLineEx(center, hoursPosition, 5, BLACK);

    DrawText(
        TextFormat("Time: %s", asctime(timeinfo)),
        22,
        GetScreenHeight() - 42,
        20,
        GRAY
    );
}

int main() {
    InitWindow(800, 800, "Trigonometry");
    SetTargetFPS(144);
    int activeExample = 1;
    int examplesCount = 3;

    while (!WindowShouldClose()) {
        for (int i = 1; i <= examplesCount; i++) {
            if (IsKeyPressed(KEY_ZERO + i)) {
                activeExample = i;
                break;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        switch (activeExample) {
            case 1: Example1();
            break;
            case 2: Example2();
            break;
            case 3: Example3();
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