#include "PlayCtrl.h"

IMPLEMENT(PlayCtrl)
PlayCtrl::PlayCtrl()
{
	m_hBackbmp = NULL;		//背景的位图
	m_bisKeyUp = false;
}


PlayCtrl::~PlayCtrl()
{
	::DeleteObject(m_hBackbmp);
	m_hBackbmp = NULL;

	//删除所有的跳板
	list<Board *>::iterator ite = lstBoard.begin();
	while (ite != lstBoard.end())
	{
		delete (*ite);
		++ite;
	}
}

void PlayCtrl::InitBack(HINSTANCE hIns)
{
	m_hBackbmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BACK));
}

void PlayCtrl::ShowBack(HDC hDC)   //显示背景
{
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	::SelectObject(hMemDC, m_hBackbmp);
	::BitBlt(hDC, 0, 0, 750, 642, hMemDC, 0, 0, SRCCOPY);
	::DeleteDC(hMemDC);
}


void PlayCtrl::OnCreateGame()
{
	doodle.InitDoodle(m_hIns, Left);	//创建玩家
	InitStartBoard(m_hIns, lstBoard);	//初始化跳板
	InitBack(m_hIns);
	::SetTimer(m_hWnd, DOODLE_JUMP_TIMER_ID, 8, NULL);		//设置跳跃的定时器
}

void PlayCtrl::OnGameDraw()
{
	HDC dc = ::GetDC(m_hWnd);

	//消除闪烁  双缓冲
	HDC hMemDC = ::CreateCompatibleDC(dc);							//创建兼容性DC
	HBITMAP hBitMap = ::CreateCompatibleBitmap(dc, 750, 642);		//创建临时位图 与窗口DC兼容
	::SelectObject(hMemDC, hBitMap);									//选择图片传到兼容性DC中

	//---------------------------显示游戏---------------------------------
	this->ShowBack(hMemDC);
	doodle.ShowDoodle(hMemDC, doodle.nFace);
	this->ShowAllBoard(hMemDC, lstBoard);
	//---------------------------显示游戏---------------------------------


	::BitBlt(dc, 0, 0, 750, 642, hMemDC, 0, 0, SRCCOPY);			//把hMemDC图片传到dc中
	::DeleteObject(hBitMap);
	::DeleteDC(hMemDC);

	::ReleaseDC(m_hWnd, dc);
}

void PlayCtrl::OnGameRun(WPARAM nTimerID)
{
	if (nTimerID == DOODLE_JUMP_TIMER_ID)
	{
		if (doodle.IsDoodleJumpUp() == true)
			{
				doodle.DoodleJumpUp();
			}
		if (doodle.IsDoodleJumpDown() == true)
		{
			doodle.DoodleJumpDown();
		
			list<Board*>::iterator ite = lstBoard.begin();
			while (ite != lstBoard.end())
			{
				if (doodle.IsStepBoard(*ite) == true)
				{
					//如果这块板没到边界 
					if ((*ite)->m_y <= 550)
					{
						if (doodle.m_y <= 200)
							this->AllBoardMove(200);
						else
						//则调用板移动函数
						this->AllBoardMove(20);
						//删除出界的板
						this->DeleteBoard();
					}
					doodle.nState = 1;
					break;
				}
				++ite;
			}
			this->IsGameOver();
		}
		this->OnGameDraw();	//重绘
	}
}

void PlayCtrl::OnKeyDown(WPARAM nKey)
{
	m_bisKeyUp = false;

	while (!m_bisKeyUp)
	{
		//手动调用消息队列  可以左右灵活操作  不用等待消息队列
		MSG msg;
		::GetMessage(&msg, NULL, 0, 0);

		doodle.Move(nKey);

		this->OnGameDraw();

		if (msg.message != WM_KEYDOWN)
		{

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}

void PlayCtrl::OnKeyUp(WPARAM nKey)
{
	m_bisKeyUp = true;
}

void PlayCtrl::InitStartBoard(HINSTANCE hIns, list<Board*>& lstBoard)
{
	//固定第一块绿色跳板
	Board* board = new GreenBoard;
	board->m_x = 335;
	board->m_y = 570;
	board->InitBoard(hIns);
	lstBoard.push_back(board);
	//随机剩余跳板
	int i = 1;
	while (1)
	{
		board = new GreenBoard;
		board->m_x = rand() % (510) + 80;
		board->m_y = 570 - 40 * (i++);
		if (board->m_y<-50)
		{
			break;
		}
		board->InitBoard(hIns);
		lstBoard.push_back(board);
	}
}

void PlayCtrl::ShowAllBoard(HDC hDC, list<Board*> &lstBoard)
{
	list<Board*>::iterator ite = lstBoard.begin();
	while (ite != lstBoard.end())
	{
		(*ite)->ShowBoard(hDC);
		++ite;
	}
}

void PlayCtrl::AllBoardMove(int n)
{
	list<Board*>::iterator ite = lstBoard.begin();
	while (ite != lstBoard.end())
	{
		(*ite)->m_y += n;
		++ite;
	}
}

void PlayCtrl::DeleteBoard()
{
	list<Board*>::iterator ite = lstBoard.begin();
	while (ite != lstBoard.end())
	{
		if ((*ite)->m_y >= 600)
		{
			this->AddBoard(m_hIns);
			delete (*ite);
			ite = lstBoard.erase(ite);
		}
		++ite;
	}
}

void PlayCtrl::AddBoard(HINSTANCE hIns)
{
	Board* board = new GreenBoard;
	board->m_x = rand() % (510) + 80;
	board->m_y = lstBoard.back()->m_y - 40;
	board->InitBoard(hIns);
	lstBoard.push_back(board);
}

void PlayCtrl::IsGameOver()
{
	if (doodle.m_y >= 600)
	{
		::KillTimer(m_hWnd, DOODLE_JUMP_TIMER_ID);
		if (::MessageBox(NULL, "你死翘翘了~~", "23333~", MB_OK))
			::PostQuitMessage(0);
	}
}