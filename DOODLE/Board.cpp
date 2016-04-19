#include "Board.h"


Board::Board()
{
	m_x = 0;
	m_y = 0;
	m_hBmpBoard = NULL;
	m_hBmpBoard_mask = NULL;
}


Board::~Board()
{
	::DeleteObject(m_hBmpBoard);
	m_hBmpBoard = NULL;

	::DeleteObject(m_hBmpBoard_mask);
	m_hBmpBoard_mask = NULL;
}


void Board::ShowBoard(HDC hDC)
{
	//利用掩码位图实现透明显示
	//逻辑与 逻辑或
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HDC hMemDC_mask = ::CreateCompatibleDC(hDC);

	::SelectObject(hMemDC, m_hBmpBoard_mask);
	::BitBlt(hDC, m_x, m_y, 80, 20, hMemDC_mask, 0, 0, SRCAND);
	::SelectObject(hMemDC, m_hBmpBoard);
	::BitBlt(hDC, m_x, m_y, 80, 20, hMemDC, 0, 0, SRCPAINT);

	::DeleteDC(hMemDC);
	::DeleteDC(hMemDC_mask);
}
