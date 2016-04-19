#pragma once 

#ifndef _GAMECTRL_H_
#define _GAMECTRL_H_

#include <windows.h>


#define DECLARE() static CGameCtrl* CreateObject();

#define IMPLEMENT(ThisClass) \
	CGameCtrl* ThisClass::CreateObject()\
	{\
		return new ThisClass;\
	}\
	Init init##ThisClass(&ThisClass::CreateObject);

class CGameCtrl;

// 普通的 C 里的函数指针 要指向的函数应该是全局函数  如果这个函数是类里的成员函数那么这个要static

typedef CGameCtrl* (*PFUN_CREATE_OBJECT)();   //  创建对象的函数指针的类型

class CGameCtrl
{
protected:
	HINSTANCE m_hIns;
	HWND m_hWnd;
public:
	static PFUN_CREATE_OBJECT pfn_create_object;    //  创建对象的函数指针
public:
	CGameCtrl():m_hIns(NULL),m_hWnd(NULL)
	{
	}
	virtual ~CGameCtrl()   //  释放 子类的对象的
	{
	
	}
public:
	void SetHandle(HINSTANCE hIns,HWND hWnd)
	{
		m_hIns = hIns;
		m_hWnd = hWnd;
	}
public:
	virtual void OnCreateGame(){}                //WM_CREATE
	virtual void OnGameDraw(){}                   //WM_PAINT
	virtual void OnGameRun(WPARAM nTimerID){}      //WM_TIMER
	virtual void OnKeyDown(WPARAM nKey){}          //WM_KEYDOWM
	virtual void OnKeyUp(WPARAM nKey){}            //WM_KEYUP
	virtual void OnLButtonDown(POINT point){}       //WM_LBUTTONDOWN
	virtual void OnRButtonDown(POINT point){}        //WM_RBUTTONDOWN
	virtual void OnLButtonUp(POINT point){}         //WM_LBUTTONUP
	virtual void OnRButtonUp(POINT point){}         //WM_RBUTTONUP
	virtual void OnMouseMove(POINT point){}         //WM_MOUSEMOVE
};


class Init     //   这个类是 负责给 创建对象的函数指针  重新赋值
{
public:
	Init(PFUN_CREATE_OBJECT pfn)
	{
		CGameCtrl::pfn_create_object = pfn;
	}
};


#endif 