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
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//hInstance - это экземпляр исполняемого файла программы, загруженного в память (*.exe)
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), 0, (DLGPROC)DlgProc, 0);
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
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				//GetModuleHandle(NULL) возвращает hInstance нашей программы
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcEdit, 0);
			}
		}
		break;
		case IDC_ADD:
		{
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
		}
		break;
		case IDC_DELETE:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
		}
		break;
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

BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SetFocus(GetDlgItem(hwnd, IDC_EDIT));
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			HWND hParent = GetParent(hwnd); //Получаем родительское окно
			HWND hList = GetDlgItem(hParent, IDC_LIST1);
			if (SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer) == LB_ERR)
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			else
			{
				MessageBox(hwnd, "Такой элемент уже существует", "Warning", MB_OK | MB_ICONWARNING);
				break;
			}
		}
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}

BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CONST INT SIZE = 256;
	CHAR sz_buffer[SIZE] = {};
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"Изменить"); //Заголовок диаг окна
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		HWND hParent = GetParent(hwnd);
		HWND hList = GetDlgItem(hParent, IDC_LIST1);
		INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
		SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		SetFocus(hEdit);
		SendMessage(hEdit, EM_SETSEL, strlen(sz_buffer), -1); //начало заведомо больше конца -1, поэтому курсов становится в конец строки
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			HWND hParent = GetParent(hwnd);
			HWND hList = GetDlgItem(hParent, IDC_LIST1);
			INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer) == LB_ERR) //Проверяем на дубликаты, если есть, то не добавляем
			{
				SendMessage(hList, LB_DELETESTRING, i, NULL);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			}
		}
		case IDCANCEL: EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}