//main.cpp
/************************************************************************/
/*                       
	Created time: 2016/4/14
	Created author: llc
	Function: Christina's entry file
*/
/************************************************************************/
	

//////////////////////////////////////////////////////////////////////////
//Include file
//////////////////////////////////////////////////////////////////////////
#include <windows.h>

//////////////////////////////////////////////////////////////////////////
// 变量声明
//////////////////////////////////////////////////////////////////////////
HWND hWndBtn;	//自定义按钮

//////////////////////////////////////////////////////////////////////////
//窗口主程序
//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch(message)
	{
	case WM_CREATE:
		{
			//创建自定义按钮
			hWndBtn = CreateWindow("button", "", WS_CHILD | BS_OWNERDRAW, 50, 50, 33, 33, hWnd, (HMENU)1, NULL, NULL);
			//因为没有WS_VISIBLE属性，所以需要手动显示出来
			ShowWindow(hWndBtn, TRUE);
			break;
		}
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			DrawText(hdc, "Christina", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &ps);
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	case WM_DRAWITEM:
		{
			//重绘按钮
			static HICON hIconBtnStart, hIconBtnPause;
			LPDRAWITEMSTRUCT pDis = (LPDRAWITEMSTRUCT)lParam;
			SetBkMode(pDis->hDC, TRANSPARENT);
			hIconBtnStart = LoadIcon(NULL, MAKEINTRESOURCE(IDI_QUESTION));
			hIconBtnPause = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ERROR));

			if (pDis->itemState & ODS_SELECTED)
			{
				//Get focus
				DrawIcon(pDis->hDC, pDis->rcItem.left, pDis->rcItem.top, hIconBtnStart);
			}
			else
			{
				//Lose focus
				DrawIcon(pDis->hDC, pDis->rcItem.left, pDis->rcItem.top, hIconBtnPause);
			}
			break;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char* lpszAppName = "Christina";
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = lpszAppName;

	// 注册窗口类
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("Registerclass failed."), lpszAppName, MB_ICONERROR);
		return 0;
	}

	// 创建应用程序主窗口
	hWnd = CreateWindow(lpszAppName, TEXT("Christina"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	// 显示窗口
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	//消息循环
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}