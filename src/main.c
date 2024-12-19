#include <stdio.h>
#include "raylib.h"


typedef struct {
    Rectangle rect;         
    char title[5];         
    Color color;            
    float borderRadius;     
    Color borderColor;      
    Color gradientStart;    
    Color gradientEnd;      
} Button;

// const char *BUTTONS[] = {
    
// };

bool DrawButton(Button *button) {
    bool clicked = false;
    return clicked;
}

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED);
    const int SCREEN_HEIGHT = GetMonitorHeight(0);
    const int SCREEN_WIDTH = GetMonitorWidth(0);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Nemu");
    ToggleFullscreen();
	SetTargetFPS(GetMonitorRefreshRate(0));

    Color topBg = (Color){ 20, 30, 48, 230 };
    Color bottomBg = (Color){ 36, 59, 85, 230 };

    const int columns = 3; 
    const int rows = 3;    
    const int buttonWidth = 150;
    const int buttonHeight = 50;
    const int gap = 20;

    Button buttons[columns * rows];

    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int index = i * columns + j;
            if (index < columns * rows) {
                buttons[index].rect = (Rectangle){
                    .x = j * (buttonWidth + gap) + (SCREEN_WIDTH - (columns * buttonWidth + (columns - 1) * gap)) / 2,
                    .y = i * (buttonHeight + gap) + (SCREEN_HEIGHT - (rows * buttonHeight + (rows - 1) * gap)) / 2,
                    .width = buttonWidth,
                    .height = buttonHeight
                };
            }
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), topBg, bottomBg);

        for (int i = 0; i < columns * rows; i++) {
          
        }

        EndDrawing();
    }


    CloseWindow();
    return 0;
}

