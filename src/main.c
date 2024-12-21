#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#define FONT_SIZE 46
#define COLUMNS 3
#define ROWS 2
#define BTN_WIDTH 200
#define BTN_HEIGHT 200
#define GAP 100
#define BTN_COLOR WHITE
#define TOP_BTN_BG_COLOR \
    (Color) { 36, 59, 85, 255 }
#define BOTTOM_BTN_BG_COLOR \
    (Color) { 20, 30, 48, 255 }

#define BG_COLOR \
    (Color) { 219, 181, 181, 255 }
#define BTN_COLOR_SECOND BLACK
#define BTN_BG_COLOR_SECOND \
    (Color) { 219, 181, 181, 255 }

const float FONT_CORRECTION = 0.25 * FONT_SIZE;

typedef struct
{
    Rectangle rect;
    int icon;
    char command[10];
    char *args[4];
} Button;

void runCommand(char *command, char *args[4])
{
    execvp(command, args);
}

short drawButton(Button *button, Font *font, Vector2 *mousePoint)
{
    if (CheckCollisionPointRec(*mousePoint, button->rect))
    {
        DrawRectangleRec(button->rect, BOTTOM_BTN_BG_COLOR);
        SetMouseCursor(4);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            runCommand(button->command, button->args);
            return 1;
        }
    }
    else
    {
        DrawRectangleGradientV(button->rect.x, button->rect.y, button->rect.width, button->rect.height, TOP_BTN_BG_COLOR, BOTTOM_BTN_BG_COLOR);
    }
    DrawTextCodepoint(*font, button->icon, (Vector2){.x = button->rect.x + (button->rect.width - FONT_SIZE + FONT_CORRECTION) / 2, .y = button->rect.y + (button->rect.height - FONT_SIZE) / 2}, FONT_SIZE, BTN_COLOR);
    return 0;
}

short drawButtonSecondTheme(Button *button, Font *font, Vector2 *mousePoint)
{
    if (CheckCollisionPointRec(*mousePoint, button->rect))
    {
        DrawRectangleGradientV(button->rect.x, button->rect.y, BTN_WIDTH * 0.8, BTN_HEIGHT * 0.2, (Color){186, 154, 154, 10}, BLANK);
        DrawRectangleGradientH(button->rect.x, button->rect.y + BTN_HEIGHT * 0.2, BTN_WIDTH * 0.2, BTN_HEIGHT * 0.8, (Color){186, 154, 154, 10}, BLANK);
        DrawRectangleGradientV(button->rect.x, button->rect.y + BTN_HEIGHT * 0.8, BTN_WIDTH, BTN_HEIGHT * 0.2, (Color){252, 208, 208, 0}, (Color){252, 208, 208, 20});
        DrawRectangleGradientH(button->rect.x + BTN_WIDTH * 0.8, button->rect.y - BTN_HEIGHT * 0.2, BTN_WIDTH * 0.2, BTN_HEIGHT, (Color){252, 208, 208, 0}, (Color){252, 208, 208, 20});
        SetMouseCursor(4);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            runCommand(button->command, button->args);
            return 1;
        }
    }
    else
    {

        DrawRectangleGradientV(button->rect.x, button->rect.y + 25, BTN_WIDTH, BTN_HEIGHT, (Color){186, 154, 154, 50}, BLANK);
        DrawRectangleGradientH(button->rect.x + 25, button->rect.y, BTN_WIDTH, BTN_HEIGHT, (Color){186, 154, 154, 50}, BLANK);
        DrawRectangleGradientV(button->rect.x, button->rect.y - 25, BTN_WIDTH, BTN_HEIGHT, (Color){252, 208, 208, 0}, (Color){252, 208, 208, 255});
        DrawRectangleGradientH(button->rect.x - 25, button->rect.y, BTN_WIDTH, BTN_HEIGHT, (Color){252, 208, 208, 0}, (Color){252, 208, 208, 255});

        DrawRectangleRec(button->rect, BTN_BG_COLOR_SECOND);
    }

    DrawTextCodepoint(*font, button->icon, (Vector2){.x = button->rect.x + (button->rect.width - FONT_SIZE + FONT_CORRECTION) / 2, .y = button->rect.y + (button->rect.height - FONT_SIZE) / 2}, FONT_SIZE, BTN_COLOR_SECOND);
    return 0;
}

int main(int argc, char *argv[])
{
    SetTraceLogLevel(LOG_NONE);

    bool isHyprland = false;
    char *user;
    char *dsk = getenv("DESKTOP_SESSION");
    if (dsk != NULL && strcmp(dsk, "hyprland") == 0)
    {
        isHyprland = true;
    }
    else
    {
        user = getenv("USER");
        if (user == NULL)
        {
            fprintf(stderr, "USER environment variable not set\n");
            return 1;
        }
    }

    short (*drawBtnFunc)(Button *, Font *, Vector2 *) = drawButton;
    bool secondTheme = false;
    if (argc == 2 && strcmp(argv[1], "-") == 0)
    {
        secondTheme = true;
        drawBtnFunc = drawButtonSecondTheme;
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNDECORATED);
    }
    else
    {
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED);
    }

    InitWindow(3840, 2160, "Nemu");
    const int SCREEN_HEIGHT = GetMonitorHeight(0);
    const int SCREEN_WIDTH = GetMonitorWidth(0);

    int codepoints[6] = {0xf011, 0xf04b2, 0xf0343, 0xead2, 0xf033e, 0xf0901};
    Font font = LoadFontEx("resources/fonts/nemu.ttf", FONT_SIZE, codepoints, 6); //! change for deployment
    ToggleFullscreen();
    SetTargetFPS(GetMonitorRefreshRate(0));

    Color topBg = (Color){20, 30, 48, 230};
    Color bottomBg = (Color){36, 59, 85, 230};

    char *_command = "loginctl";
    char *_args[4] = {"loginctl", "terminate-session", user, NULL};
    if (isHyprland)
    {
        _command = "hyprctl";
        _args[0] = "hyprctl";
        _args[1] = "dispatch";
        _args[2] = "exit";
        _args[3] = NULL;
    }

    Button BUTTONS[6] = {
        (Button){
            .rect = (Rectangle){0, 0, 0, 0},
            .icon = 0xf0343,
            .command = {*_command},
            .args = {*_args}},
        (Button){
            .rect = (Rectangle){0, 0, 0, 0},
            .icon = 0xf04b2,
            .command = "systemctl",
            .args = {"systemctl", "suspend", NULL}},
        (Button){
            .rect = (Rectangle){0, 0, 0, 0},
            .icon = 0xf033e,
            .command = "loginctl",
            .args = {"loginctl", "lock-session", NULL}},
        (Button){
            .rect = (Rectangle){0, 0, 0, 0},
            .icon = 0xf011,
            .command = "systemctl",
            .args = {"systemctl", "poweroff", NULL}},
        (Button){
            .rect = (Rectangle){0, 0, 0, 0},
            .icon = 0xf0901,
            .command = "systemctl",
            .args = {"systemctl", "hibernate", NULL}},
        (Button){
            .rect = (Rectangle){0, 0, 0, 0},
            .icon = 0xead2,
            .command = "systemctl",
            .args = {"systemctl", "reboot", NULL}},
    };

    const int len = COLUMNS * ROWS;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            int index = i * COLUMNS + j;
            if (index < len)
            {
                BUTTONS[index].rect.x = j * (BTN_WIDTH + GAP) + (SCREEN_WIDTH - (COLUMNS * BTN_WIDTH + (COLUMNS - 1) * GAP)) / 2;
                BUTTONS[index].rect.y = i * (BTN_HEIGHT + GAP) + (SCREEN_HEIGHT - (ROWS * BTN_HEIGHT + (ROWS - 1) * GAP)) / 2;
                BUTTONS[index].rect.width = BTN_WIDTH;
                BUTTONS[index].rect.height = BTN_HEIGHT;
            }
        }
    };

    Vector2 mousePoint = {0.0f, 0.0f};

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_O))
        {
            runCommand(BUTTONS[0].command, BUTTONS[0].args);
            break;
        }

        if (IsKeyDown(KEY_S))
        {
            runCommand(BUTTONS[1].command, BUTTONS[1].args);
            break;
        }

        if (IsKeyDown(KEY_L))
        {
            runCommand(BUTTONS[2].command, BUTTONS[2].args);
            break;
        }

        if (IsKeyDown(KEY_P))
        {
            runCommand(BUTTONS[3].command, BUTTONS[3].args);
            break;
        }

        if (IsKeyDown(KEY_H))
        {
            runCommand(BUTTONS[4].command, BUTTONS[4].args);
            break;
        }

        if (IsKeyDown(KEY_R))
        {
            runCommand(BUTTONS[5].command, BUTTONS[5].args);
            break;
        }

        mousePoint = GetMousePosition();

        BeginDrawing();
        if (secondTheme)
        {
            ClearBackground(BG_COLOR);
        }
        else
        {
            DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, topBg, bottomBg);
        }
        for (int i = 0; i < len; i++)
        {
            if (drawBtnFunc(&BUTTONS[i], &font, &mousePoint))
            {
                break;
            }
        };

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
