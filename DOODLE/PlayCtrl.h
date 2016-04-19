#pragma once
#include "CGameCtrl.h"
#include<Windows.h>
#include"Doodle.h"
#include"GreenBoard.h"
#include<list>
#include"sys.h"

using namespace std;

class PlayCtrl :
	public CGameCtrl
{
public:
	HBITMAP m_hBackbmp;		//背景的位图
	Doodle doodle;			//玩家
	list<Board*> lstBoard;	//跳板的链表
	bool m_bisKeyUp;		//判断键盘是否抬起
public:
	PlayCtrl();
	~PlayCtrl();
public:
	DECLARE()
public:
	virtual void OnCreateGame();                  //WM_CREATE
	virtual void OnGameDraw();                    //WM_PAINT
	virtual void OnGameRun(WPARAM nTimerID);      //WM_TIMER
	virtual void OnKeyDown(WPARAM nKey);          //WM_KEYDOWM
	virtual void OnKeyUp(WPARAM nKey);
public:
	void InitBack(HINSTANCE hIns);
	void ShowBack(HDC hDC);
	void ShowAllBoard(HDC hDC, list<Board*> &lstBoard);					//显示所有跳板
	void InitStartBoard(HINSTANCE hIns, list<Board*>& lstBoard);		//初始化跳板
	void AllBoardMove(int n);
	void DeleteBoard();
	void AddBoard(HINSTANCE hIns);
	void IsGameOver();
};

