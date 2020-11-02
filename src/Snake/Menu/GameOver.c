//This program consists of the gameover screen of the game.

#include "cprocessing.h"
#include <stdio.h>
#include "src/Snake/Snake.h"

char TScore[100];
char TTime[100];
CP_Image GameOver_Image;
CP_Font Pixel;

//initilizing the gameover menu.
// prints the score the player and the total time the player has spend playing the game.
void GameOver_Init(void)
{
	sprintf_s(TScore, 100, "%d", Score);
	sprintf_s(TTime, 100, "%.2f", TotalTime);
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	GameOver_Image = CP_Image_Load("Assets/GameOver.jfif");
	Pixel = CP_Font_Load("Assets/Pixel.ttf");
	CP_Font_Set(Pixel);
}

//Awaits user input to proceed the next game state. To play again or to terminate game engine.

void GameOver_Update(void)
{
	CP_Image_Draw(GameOver_Image, 600, 200, 720, 200, 5);
	CP_Settings_TextSize(70);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("Score: ", 300, 450);
	CP_Font_DrawText("Time: ", 700, 450);
	CP_Font_DrawText(TScore, 490, 450);
	CP_Font_DrawText(TTime, 920, 450);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	if (CP_Input_GetMouseX() >= 240 && CP_Input_GetMouseX() <= 480)
	{
		if (CP_Input_GetMouseY() >= 600 && CP_Input_GetMouseY() <= 700)
		{
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		}
	}
	CP_Graphics_DrawRect(240, 600, 240, 100);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	if (CP_Input_GetMouseX() >= 720 && CP_Input_GetMouseX() <= 960)
	{
		if (CP_Input_GetMouseY() >= 600 && CP_Input_GetMouseY() <= 700)
		{
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		}
	}
	CP_Graphics_DrawRect(720, 600, 240, 100);
	CP_Settings_TextSize(70);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Retry", 350, 660);
	CP_Font_DrawText("Quit", 830, 660);
	if (CP_Input_GetMouseX() >= 240 && CP_Input_GetMouseX() <= 480)
	{
		if (CP_Input_GetMouseY() >= 600 && CP_Input_GetMouseY() <= 700)
		{
			//CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
			if (CP_Input_MouseClicked())
			{
				CP_Engine_SetNextGameState(Snake_Init, Snake_Update, Snake_Exit);
			}
		}
	}
	if (CP_Input_GetMouseX() >= 720 && CP_Input_GetMouseX() <= 960)
	{
		if (CP_Input_GetMouseY() >= 600 && CP_Input_GetMouseY() <= 700)
		{
			//CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
			if (CP_Input_MouseClicked())
			{
				CP_Engine_Terminate();
			}
		}
	}
}

void GameOver_Exit(void)
{

}