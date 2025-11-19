#include<Windows.h>
#include<stdio.h>
#include<windowsx.h>
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hWnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hWnd, IDC_COMBO1); //Получаем ручку для IDC_COMBO1
			//Gets the index of the currently selected item in a combo box.
			//Send the CB_GETCURSEL message explicitly.
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);

			//Создаем временный буфер для хранения текста
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};

			//Gets a string from a list in a combo box.
			//Send the CB_GETLBTEXT message explicitly.
			//Создаем ответ для отправки в MessageBox
			CHAR sz_answer[SIZE] = {};
			if (i != CB_ERR)
			{
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);

				//заголовочный файл stdio.h
				//Для использования без предупреждений пришлось добавить _CRT_SECURE_NO_WARNINGS в свойствах проекта
				//C/C++/Preprocessor/Preprocessor Definition/_CRT_SECURE_NO_WARNINGS <different options>
				//Write formatted data to a string.
				wsprintf(sz_answer, "Выбран элемент \"%s\", номер %d", sz_buffer, i); //Используем С-шную функцию для помещения
				//в сообщение текста, номера элемента и содержимого элемента

				//Вывожу окончательный результат на экран
				MessageBox(hWnd, sz_answer, "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hWnd, "Вы ничего не выбрали", "Info", MB_OK | MB_ICONINFORMATION);
			}
		}
		break;
		case IDCANCEL:
			EndDialog(hWnd, 0);
			break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	}
	return FALSE;
}