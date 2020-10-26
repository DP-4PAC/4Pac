#include "cprocessing.h"
#include <stdio.h>
#include "src/Snake/Snake.h"

void GameOver_Init(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
	CP_Graphics_DrawRect(240, 600, 240, 100);
	CP_Graphics_DrawRect(720, 600, 240, 100);
	CP_Settings_TextSize(100);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	CP_Font_DrawText("Play", 360, 650);
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Font_DrawText("Quit", 840, 650);
}

void GameOver_Update(void)
{
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
}

void GameOver_Exit(void)
{

}