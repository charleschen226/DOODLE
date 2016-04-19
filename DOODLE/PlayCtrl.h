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
	HBITMAP m_hBackbmp;		//������λͼ
	Doodle doodle;			//���
	list<Board*> lstBoard;	//���������
	bool m_bisKeyUp;		//�жϼ����Ƿ�̧��
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
	void ShowAllBoard(HDC hDC, list<Board*> &lstBoard);					//��ʾ��������
	void InitStartBoard(HINSTANCE hIns, list<Board*>& lstBoard);		//��ʼ������
	void AllBoardMove(int n);
	void DeleteBoard();
	void AddBoard(HINSTANCE hIns);
	void IsGameOver();
};

