#include <windows.h>
#include "CGameCtrl.h"
#include <time.h>

PFUN_CREATE_OBJECT CGameCtrl::pfn_create_object = NULL;   //  给静态的函数指针初始化

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

HINSTANCE g_hIns = NULL;

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR pCmdLine,int nShowCmd)
{

	srand((unsigned int)time(NULL));


	g_hIns = hInstance;

	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wndclass.hCursor = ::LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = "classname";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	if(!::RegisterClassEx(&wndclass))
	{
		::MessageBox(NULL,"注册失败!","提示",MB_OK);
		return 0;
	}

	HWND hWnd = ::CreateWindow("classname","涂鸦跳跃",WS_OVERLAPPEDWINDOW,
		400,50,750,642,NULL,NULL,hInstance,NULL);

	if(!hWnd)
	{
		::MessageBox(NULL,"创建失败!","提示",MB_OK);
		return 0;
	}

	::ShowWindow(hWnd,SW_SHOW/*nShowCmd*/);

	MSG message;
	while(::GetMessage(&message,NULL,0,0))
	{
		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}

	return 0;
}

CGameCtrl* ctrl = NULL;

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		if(CGameCtrl::pfn_create_object == NULL)
		{
			//  游戏创建失败
			::MessageBox(NULL,"游戏创建失败!","提示",MB_OK);
			//  销毁窗口
			::DestroyWindow(hwnd);
			//  结束
			::PostQuitMessage(0);
			return 0;
		}
		//   通过函数指针 得到一个子类的对象
		ctrl = (*CGameCtrl::pfn_create_object)();
		//   设置句柄
		ctrl->SetHandle(g_hIns,hwnd);
		//   初始化游戏
		ctrl->OnCreateGame();
		break;
	case WM_PAINT:
		ctrl->OnGameDraw();
		break;
	case WM_TIMER:
		ctrl->OnGameRun(wParam);
		break;
	case WM_KEYDOWN:
		ctrl->OnKeyDown(wParam);
		break;
	case WM_KEYUP:
		ctrl->OnKeyUp(wParam);
		break;
	case WM_LBUTTONDOWN:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnLButtonDown(point);
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnLButtonUp(point);
		}
		break;
	case WM_RBUTTONDOWN:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnRButtonDown(point);
		}
		break;
	case WM_RBUTTONUP:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnRButtonUp(point);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnMouseMove(point);
		}
		break;
	case WM_CLOSE:
		::PostQuitMessage(0);
		delete ctrl;
		ctrl = NULL;
		break;
	}
	return ::DefWindowProc(hwnd,uMsg,wParam,lParam);
}