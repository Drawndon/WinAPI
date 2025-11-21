#include <Windows.h>
#include "resource.h"

CONST CHAR invitation[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox
	//(
	//	NULL,
	//	"Hello WinAPI!",
	//	"MessageBox",
	//	MB_YESNOCANCEL
	//	| MB_ICONINFORMATION
	//	| MB_HELP 
	//	| MB_DEFBUTTON3
	//	| MB_SYSTEMMODAL
	//	| MB_RIGHT

	//); //MB_YESNO, MB_YESNOCANCEL);
	////MB - Message Box
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //Выполняется один раз при запуске окна.
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)); //Загружаем иконку в handler
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon); //Отправляем иконку на диалоговое окно
		//SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN)); //Установка курсора в поле IDC_EDIT_LOGIN
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)invitation);
	}
	break;
	case WM_COMMAND: //Обрабатывает команды с клавиатуры и мыши.
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
	
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, invitation) == 0) SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");

			if (HIWORD(wParam) == EN_KILLFOCUS && strlen(sz_buffer) == 0) SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)invitation);
		}
		break;
		case IDC_BUTTON_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:
			MessageBox(NULL, "Была нажата кнопка 'OK'", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE: //Выполняется при нажатии кнопки 'Х'.
		EndDialog(hwnd, 0);
	}
	return FALSE;
}