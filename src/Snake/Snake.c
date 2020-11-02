//This program consists main code of the snake game.

#include "cprocessing.h"
#include <stdio.h>
#include "Menu/GameOver.h"

#define GRID_WIDTH 60 //WINDOW_WIDTH/GridUnitWidth
#define GRID_HEIGHT 40 // WINDOW_HEIGHT/GridUnitHeight
#define WALL 1 //VALUE OF WALL IN ARRAY
#define FOOD 2 // VALUE OF FOOD IN ARRAY
#define MAX_TRAIL 2204 // TOTAL POSSIBLE LENGTH OF SNAKE


float GridUnitWidth, GridUnitHeight; //each unti grid size
float SnakeX, SnakeY; //position of snake
int RandX, RandY, RandRF, RandGF, RandBF, RandRS, RandGS, RandBS;//random generator
float VelX, VelY; //velocity of snake
int x, y; //running through 2D array
CP_Vector SnakeTrail[MAX_TRAIL]; //store every position that is following the snake
int SnakeLength; //length of snake
int grid[GRID_WIDTH][GRID_HEIGHT]; //dimension of grid
int Score; //To calculate score
float TotalTime;//To calculate score
float timer, interval; //to regulate snake movement
int PreLength;


//Creating Walls on the borders of the window
void Wall(void)
{
	for (x = 0; x < GRID_WIDTH; x++)
	{
		grid[x][0] = WALL;
		grid[x][GRID_HEIGHT - 1] = WALL;
	}
	for (y = 0; y < GRID_HEIGHT; y++)
	{
		grid[0][y] = WALL;
		grid[GRID_WIDTH - 1][y] = WALL;
	}
	RandX = CP_Random_RangeInt(1, GRID_WIDTH - 2);
	RandY = CP_Random_RangeInt(1, GRID_HEIGHT - 2);
}
//SnakeMovement  by changing the setting of velocity of both axis.
//The function also prevents the snake from moving back into itself.
float SnakeMovement(void)
{

	if (VelY == 0)
	{
		if (SnakeY - VelY == (int)SnakeTrail[0].y)
		{
			if (CP_Input_KeyTriggered(KEY_DOWN))
			{
				VelX = 0;
				VelY = 1;
			}
			if (CP_Input_KeyTriggered(KEY_UP))
			{
				VelX = 0;
				VelY = -1;
			}
		}
	}
	if (VelX == 0)
	{
		if (SnakeX - VelX == (int)SnakeTrail[0].x)
		{
			if (CP_Input_KeyTriggered(KEY_LEFT))
			{
				VelX = -1;
				VelY = 0;
			}
			if (CP_Input_KeyTriggered(KEY_RIGHT))
			{
				VelX = 1;
				VelY = 0;
			}
		}
	}
	return VelX, VelY;
}

//Drawing of blocks by taking in the parameters GridUnitWidth,GridUnitHeight,GridUnitWidth,GridunitHeight
void DrawBlock(void)
{
	CP_Graphics_DrawRect(x * GridUnitWidth, y * GridUnitHeight, GridUnitWidth, GridUnitHeight);
}

//init Snake position, Score, TotalTime after starting the game, interval of each frame and initilizing the walls of the game 
void Snake_Init(void)
{
	// initialize variables and CProcessing settings for this gamestate
	SnakeX = 35; //starting position X
	SnakeY = 25; //starting position Y
	SnakeLength = 10; //length of snake
	GridUnitWidth = 20; //unit grid width
	GridUnitHeight = 20; // unit grid height
	VelX = 1; //moving x-axis by 1 unit
	VelY = 0; //moving y-axis by 0 unit
	Score = 0;
	TotalTime = 0;
	timer = 0; //initial timer
	interval = 0.1f; //every half a seconds
	RandRF = CP_Random_RangeInt(1, 255);
	RandGF = CP_Random_RangeInt(1, 255);
	RandBF = CP_Random_RangeInt(1, 255);
	RandRS = 0;
	RandGS = 255;
	RandBS = 0;

	Wall();
}

//Updating the position of the snake and updating the size of the snake after eating food.
void Snake_Update(void)
{
	timer += CP_System_GetDt();
	TotalTime += CP_System_GetDt();
	grid[RandX][RandY] = FOOD;
	
	if (timer >= interval)
	{
		timer -= interval;
		CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
		for (x = 0; x < GRID_WIDTH; x++)
		{
			for (y = 0; y < GRID_HEIGHT; y++)
			{
				for (int i = 0; i < SnakeLength; i++)
				{
					if (grid[x][y] == WALL)
					{
						CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
						DrawBlock();
					}
					if (grid[x][y] == FOOD && grid[x][y] != grid[(int)SnakeTrail[i].x][(int)SnakeTrail[i].y])
					{
						CP_Settings_Fill(CP_Color_Create(RandRF, RandGF, RandBF, 255));
						DrawBlock();
					}
				}
			}
		}
		for (int i = SnakeLength - 1; i > 0; i--)
		{
			SnakeTrail[i] = SnakeTrail[i - 1];
		}
		SnakeTrail[0] = CP_Vector_Set((float)SnakeX, (float)SnakeY);
		for (int i = 0; i < SnakeLength; i++)
		{
			if (SnakeTrail[i].x != 0 && SnakeTrail[i].y != 0)
			{
				CP_Settings_Fill(CP_Color_Create(RandRS, RandGS, RandBS, 255));
				CP_Graphics_DrawRect(SnakeTrail[i].x * GridUnitWidth, SnakeTrail[i].y * GridUnitHeight, GridUnitWidth, GridUnitHeight);
			}
		}
		SnakeX += VelX;
		SnakeY += VelY;

	}
	SnakeMovement();
	for (int i = 0; i < SnakeLength; i++)
	{
		if (SnakeX == SnakeTrail[i].x && SnakeY == SnakeTrail[i].y)
		{
			CP_Engine_SetNextGameState(GameOver_Init, GameOver_Update, GameOver_Exit);
			break;
		}
	}
	if (grid[(int)SnakeX][(int)SnakeY] == FOOD)
	{
		PreLength = SnakeLength;
		SnakeLength += 1;
		grid[RandX][RandY] = 0;
		RandX = CP_Random_RangeInt(1, GRID_WIDTH - 2);
		RandY = CP_Random_RangeInt(1, GRID_HEIGHT - 2);
		RandRS = RandRF;
		RandGS = RandGF;
		RandBS = RandBF;
		RandRF = CP_Random_RangeInt(1, 255);
		RandGF = CP_Random_RangeInt(1, 255);
		RandBF = CP_Random_RangeInt(1, 255);
		Score += 5;
		interval -= (float)0.003;
	}
	if (grid[(int)SnakeX][(int)SnakeY] == WALL)
	{
		CP_Engine_SetNextGameState(GameOver_Init, GameOver_Update, GameOver_Exit);
	}
}
//Clearing the previous stored values after the user has played the game. snake position,snakelength etc.
void Snake_Exit(void)
{
	for (int i = 0; i < MAX_TRAIL; i++)
	{
		SnakeTrail[i].x = 0;
		SnakeTrail[i].y = 0;
	}
	SnakeX = 35; //starting position X
	SnakeY = 25; //starting position Y
	SnakeLength = 10; //length of snake
	VelX = 1; //moving x-axis by 1 unit
	VelY = 0; //moving y-axis by 0 unit
	grid[RandX][RandY] = 0;
}