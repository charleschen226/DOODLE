#pragma once
#include<Windows.h>
#include"resource.h"

class Board			//Ìø°å
{
public:
	int m_x;
	int m_y;
	HBITMAP m_hBmpBoard;
	HBITMAP m_hBmpBoard_mask;
public:
	Board();
	virtual ~Board();
public:
	virtual void InitBoard(HINSTANCE hIns) = 0;
	void ShowBoard(HDC hDC);

};

