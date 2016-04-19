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

// ��ͨ�� C ��ĺ���ָ�� Ҫָ��ĺ���Ӧ����ȫ�ֺ���  ����������������ĳ�Ա������ô���Ҫstatic

typedef CGameCtrl* (*PFUN_CREATE_OBJECT)();   //  ��������ĺ���ָ�������

class CGameCtrl
{
protected:
	HINSTANCE m_hIns;
	HWND m_hWnd;
public:
	static PFUN_CREATE_OBJECT pfn_create_object;    //  ��������ĺ���ָ��
public:
	CGameCtrl():m_hIns(NULL),m_hWnd(NULL)
	{
	}
	virtual ~CGameCtrl()   //  �ͷ� ����Ķ����
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


class Init     //   ������� ����� ��������ĺ���ָ��  ���¸�ֵ
{
public:
	Init(PFUN_CREATE_OBJECT pfn)
	{
		CGameCtrl::pfn_create_object = pfn;
	}
};


#endif 