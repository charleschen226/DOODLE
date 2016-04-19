#include "Doodle.h"


Doodle::Doodle()
{
	m_x = 333;
	m_y = 485;
	nState = 1;
	nFace = Left;
	m_hBmpDoodle_left = NULL;
	m_hBmpDoodle_left_mask = NULL;
	m_hBmpDoodle_right = NULL;
	m_hBmpDoodle_right_mask = NULL;
}


Doodle::~Doodle()
{
	::DeleteObject(m_hBmpDoodle_left);
	m_hBmpDoodle_left = NULL;

	::DeleteObject(m_hBmpDoodle_left_mask);
	m_hBmpDoodle_left_mask = NULL;

	::DeleteObject(m_hBmpDoodle_right);
	m_hBmpDoodle_right = NULL;

	::DeleteObject(m_hBmpDoodle_right_mask);
	m_hBmpDoodle_right_mask = NULL;

}

void Doodle::InitDoodle(HINSTANCE hIns, int nFace)
{
	//加载向左的图片
	m_hBmpDoodle_left = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_LEFT));
	m_hBmpDoodle_left_mask = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_LEFTMASK));
	//加载向右的图片
	m_hBmpDoodle_right = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_RIGHT));
	m_hBmpDoodle_right_mask = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_RIGHTMASK));

}
void Doodle::ShowDoodle(HDC hDC, int nFace)
{
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HDC hMemDC_mask = ::CreateCompatibleDC(hDC);

	switch (nFace)
	{
	case Left:
		::SelectObject(hMemDC, m_hBmpDoodle_left_mask);
		::BitBlt(hDC, m_x, m_y, 85, 85, hMemDC_mask, 0, 0, SRCAND);
		::SelectObject(hMemDC, m_hBmpDoodle_left);
		::BitBlt(hDC, m_x, m_y, 85, 85, hMemDC, 0, 0, SRCPAINT);
		break;
	case Right:
		::SelectObject(hMemDC, m_hBmpDoodle_right_mask);
		::BitBlt(hDC, m_x, m_y, 85, 85, hMemDC_mask, 0, 0, SRCAND);
		::SelectObject(hMemDC, m_hBmpDoodle_right);
		::BitBlt(hDC, m_x, m_y, 85, 85, hMemDC, 0, 0, SRCPAINT);
		break;
	}
	::DeleteDC(hMemDC);
	::DeleteDC(hMemDC_mask);
}

bool Doodle::IsDoodleJumpUp()
{
	if (this->nState>0 && nState<30)
	{
		return true;
	}
	return false;
}
void Doodle::DoodleJumpUp()
{
	++nState;
	this->m_y -= 5;
}
bool Doodle::IsDoodleJumpDown()
{
	if (this->nState >= 30 || nState == 0)
	{
		return true;
	}
	return false;
}
void Doodle::DoodleJumpDown()
{
	nState = 0;
	this->m_y += 5;
}
bool Doodle::IsStepBoard(Board *board)
{
	if (m_x + 28 >= board->m_x && m_x + 28 <= board->m_x + 80 && m_y + 85 == board->m_y)
	{
		return true;
	}
	if (m_x + 56 >= board->m_x && m_x+56 <= board->m_x + 80 && m_y + 85 == board->m_y)
	{
		return true;
	}
	return false;
}

void Doodle::Move(WPARAM nKey)
{
	switch (nKey)
	{
	case VK_LEFT:
		nFace = Left;
		if (m_x>0)
			m_x -= 5;
		else if (m_x <= 0)
		{
			m_x = 665;
			m_x -= 5;
		}
		break;
	case VK_RIGHT:
		nFace = Right;
		if (m_x<665)
			m_x += 5;
		else if (m_x >= 665)
		{
			m_x = 0;
			m_x += 5;
		}
		break;
	}
}
