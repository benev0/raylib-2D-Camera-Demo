#include "raylib.h"
#include "raymath.h"

#define DOT_COUNT 1000

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float size;
    Color color;
} t_dot;


int main(void)
{
    const int screenWidth = 960;
    const int screenHeight = 720;
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_ALWAYS_RUN | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetWindowMinSize(screenWidth, screenHeight);

    Camera2D camera = {};
    camera.target = (Vector2){0.0f, 0.0f};
    camera.offset = (Vector2){0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Vector2 mouseDeltaData = {};
    Vector2 mousePositionData = {};

    t_dot* dots = MemAlloc(sizeof(t_dot) * DOT_COUNT);

    for (int i=0; i<DOT_COUNT; i++)
    {
        (dots + i)->position = (Vector2) {GetRandomValue(0, screenWidth), GetRandomValue(0, screenWidth)};
        (dots + i)->velocity = (Vector2) {GetRandomValue(-3, 3), GetRandomValue(-3, 3)};
        (dots + i)->size = GetRandomValue(10, 20);
        (dots + i)->color = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        mouseDeltaData = GetMouseDelta();
        mousePositionData = GetMousePosition();

        if (IsKeyDown(KEY_RIGHT))
            camera.target.x += 10 / camera.zoom;
        if (IsKeyDown(KEY_LEFT))
            camera.target.x -= 10 / camera.zoom;
        if (IsKeyDown(KEY_UP))
            camera.target.y -= 10 / camera.zoom;
        if (IsKeyDown(KEY_DOWN))
            camera.target.y += 10 / camera.zoom;

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            camera.target.x -= mouseDeltaData.x / camera.zoom;
            camera.target.y -= mouseDeltaData.y / camera.zoom;
        }

        // camera offset
        camera.offset = mousePositionData;
        camera.target.x += mouseDeltaData.x / camera.zoom;
        camera.target.y += mouseDeltaData.y / camera.zoom;
        // change camera pos
        camera.target.x = camera.target.x;
        camera.target.y = camera.target.y;
        // zoom adjust
        camera.zoom *= powf(1.05f, GetMouseWheelMove());


        BeginDrawing();
            DrawFPS(10.0, 10.0);

            ClearBackground(BLACK);

            BeginMode2D(camera);
                for (int i=0; i<DOT_COUNT; i++)
                {
                    (dots + i)->position.x += (dots + i)->velocity.x;
                    (dots + i)->position.y += (dots + i)->velocity.y;
                    DrawCircle((dots + i)->position.x, (dots + i)->position.y, (dots + i)->size, (dots + i)->color);
                }
            EndMode2D();

            if (IsCursorOnScreen()) {
                DrawPixel(GetMouseX(), GetMouseY(), GREEN);
                HideCursor();
            }
            else {
                ShowCursor();
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}