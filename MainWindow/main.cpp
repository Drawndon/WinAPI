//MainWindow
#include<Windows.h>
#include "resource.h"


CONST CHAR g_sz_WINDOW_CLASS[] = "My first window";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1)Регистрация класса окна
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass)); //

	//Инициализация размеров и стиля:
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass); //cb - Count Bytes
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	//Инициализируем внешний вид окон:
	//Загружает иконку статически (вкомпиливает в приложение)
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_BITCOIN));
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_PALM));
	//Загружает иконку динамически
	//wClass.hIconSm = (HICON)LoadImage(hInstance /*можно NULL*/, "bitcoin.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);//Sm - small
	//wClass.hIcon = (HICON)LoadImage(hInstance /*можно NULL*/, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	//Сделали свой ресурс для курсора, нарисовали его сами в ресурсе
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	//Сделали изображение из Интернета
	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance,
		"starcraft-original\\Working In Background.ani",
		IMAGE_CURSOR,
		LR_DEFAULTSIZE,
		LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	//Инициализация системных переменных
	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS; //Project properties/Advanced/Use multi-byte character set
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	//Подготовка закончилась, регистрируем класс окна
	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}


	//2) Создание окна:
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	INT window_width = screen_width * 0.75;
	INT window_height = screen_height * 0.75;

	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,	//exStyle
		g_sz_WINDOW_CLASS,	//Имя класса окна
		g_sz_WINDOW_CLASS,	//Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна. Стили всегда зависят от класса окна WS_OVERLAPPEDWINDOW - главное окно
		window_start_x, window_start_y, //CW_USEDEFAULT, CW_USEDEFAULT, //Position
		window_width, window_height, //640, 480, //Размер окна (можно CW_USEDEFAULT, CW_USEDEFAULT,)
		NULL,
		NULL, //Для главного окна это ResourceID главного меню,
		//для дочернего окна (Control) - ResourceID дочернего окна (IDC_BUTTON_COPY), например
		hInstance,
		NULL
	);
	if (hwnd == NULL) //Если окно не создалось
	{
		MessageBox(NULL, "Windows creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); //Задает режим отображения окна - Развернуто на весь экран, свернуто в окно, свернуто на панель задач
	UpdateWindow(hwnd); //Обновляет рабочую область окна, отправляя сообщение 'WM_PAINT', если клиентская область не пустая


	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);//Преобразует сообщения виртуальных клавиш в символьное сообщение 
		DispatchMessage(&msg); //Отправляет сообщение в процедуру окна
	}
	return msg.wParam; //https://learn.microsoft
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_MOVE:
	case WM_SIZE:
	{
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		INT window_width = window_rect.right - window_rect.left;
		INT window_height = window_rect.bottom - window_rect.top;
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE]{};
		wsprintf
		(
			sz_buffer, "%s. Положение: %ix%i; Размер: %ix%i",
			g_sz_WINDOW_CLASS,
			window_rect.left, window_rect.top,
			window_width, window_height
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}