//This program consists of the main menu of the game.

#include "cprocessing.h"
#include <stdio.h>
#include "src/Snake/Snake.h"

CP_Image Snake_Image;
CP_Font Pixel;

//initilizing the menu state and image of the main menu
void Menu_Init(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	Snake_Image = CP_Image_Load("Assets/Snake.png");
	Pixel = CP_Font_Load("Assets/Pixel.ttf");
	CP_Font_Set(Pixel);
}

//Changes game state from menu to game when user clicks on play button or terminates the engine when button quit is clicked on.
//includes when user mouse hovers over both the buttons.
//Game state changes only when user click within the area of both the button
void Menu_Update(void)
{
	CP_Image_Draw(Snake_Image, 600, 200, 720, 200, 1);
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
	CP_Settings_TextSize(75);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("PLAY", 350, 660);
	CP_Font_DrawText("QUIT", 830, 660);

	if (CP_Input_GetMouseX() >= 240 && CP_Input_GetMouseX() <= 480)
	{
		if (CP_Input_GetMouseY() >= 600 && CP_Input_GetMouseY() <= 700)
		{
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
			if (CP_Input_MouseClicked())
			{
				CP_Engine_Terminate();
			}
		}
	}
}

void Menu_Exit(void)
{

}