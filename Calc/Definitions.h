#pragma once
#include <Windows.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc PV_521";

CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_INTERVAL = 1;
CONST INT g_i_DISPLAY_INTERVAL = 10;
CONST INT g_i_DOUBLE_BUTTON_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;
CONST INT g_i_DISPLAY_WIDTH = g_i_BUTTON_SIZE * 5 + g_i_INTERVAL * 4;
CONST INT g_i_DISPLAY_HEIGHT = g_i_BUTTON_SIZE;
CONST INT g_i_FONT_HEIGHT = g_i_DISPLAY_HEIGHT - 2; //Убрали по пикселю сверху и снизу
CONST INT g_i_FONT_WIDTH = g_i_FONT_HEIGHT / 2.5;
CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;
CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISPLAY_INTERVAL;

CONST INT g_i_WINDOW_WIDTH = g_i_DISPLAY_WIDTH + g_i_START_X * 2 + 16;
CONST INT g_i_WINDOW_HEIGHT = g_i_DISPLAY_HEIGHT + g_i_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4 + 48 + g_i_DISPLAY_INTERVAL;
CONST CHAR* g_sz_BTN_FILENAMES[] = {"point", "plus", "minus", "aster", "slash", "bsp", "clr", "equal"};

#define X_BUTTON_POSITION(position) g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (position) //position взяли в скобки, чтобы когда будет не одно число, а выражение, то тогда
//будет вычислено выражение и подставлено
#define Y_BUTTON_POSITION(position) g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (position)

CONST CHAR g_OPERATIONS[] = "+-*/";

CONST INT g_i_WINDOW_COLOR = 0;
CONST INT g_i_DISPLAY_COLOR = 1;
CONST INT g_i_FONT_COLOR = 2;
CONST COLORREF g_clr_COLORS[][3] =
{
	{RGB(0, 0, 150), RGB(0, 0, 100), RGB(255, 0, 0)},
	{RGB(150, 150, 150), RGB(50, 50, 50), RGB(0, 255, 0)},
};

CONST CHAR* g_sz_SKIN[] = { "square_blue", "metal_mistral" };