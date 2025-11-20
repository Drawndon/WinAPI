//ListBox
#define _CRT_SECURE_NO_WARNINGS	//для sprintf()
#include<Windows.h>
#include<cstdio>	//для sprintf()
#include"resource.h"

CONST CHAR* string[] =
{
	"Fist item",
	"Second item",
	"Third item",
	"And so on item"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
			
		}
	}
	break;
	case WM_COMMAND:	
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};	//в эту строку мы скопируем выделенную строку ListBox.
			CHAR sz_message[SIZE] = {};	//этy строку мы будем отображать в MessageBox.

			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "Выбран элемент \"%s\", номер %d.", sz_buffer, index);
			
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION | MB_HELP);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}