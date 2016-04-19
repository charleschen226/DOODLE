#include "GreenBoard.h"


GreenBoard::GreenBoard()
{
	m_x = -100;
	m_y = -100;
	m_hBmpBoard = NULL;
	m_hBmpBoard_mask = NULL;
}


GreenBoard::~GreenBoard()
{
	::DeleteObject(m_hBmpBoard);
	m_hBmpBoard = NULL;

	::DeleteObject(m_hBmpBoard_mask);
	m_hBmpBoard_mask = NULL;
}

void GreenBoard::InitBoard(HINSTANCE hIns)
{
	m_hBmpBoard = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_GREEN));
	m_hBmpBoard_mask = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_GREENMASK));
}

