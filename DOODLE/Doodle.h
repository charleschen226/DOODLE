#pragma once
#include<Windows.h>
#include"Board.h"

#define  Left   1
#define  Right  2

class Doodle		//Íæ¼Ò
{
public:
	Doodle();
	~Doodle();
public:
	int m_x;
	int m_y;
	int nFace;
	int nState;
	HBITMAP m_hBmpDoodle_left;
	HBITMAP m_hBmpDoodle_left_mask;
	HBITMAP m_hBmpDoodle_right;
	HBITMAP m_hBmpDoodle_right_mask;
public:
	void InitDoodle(HINSTANCE hIns, int nFace);
	void ShowDoodle(HDC hDC, int nFace);
	void Jump();
	bool IsStepBoard(Board *board);
	void Move(WPARAM nKey);

	bool IsDoodleJumpUp();
	void DoodleJumpUp();
	bool IsDoodleJumpDown();
	void DoodleJumpDown();
};

