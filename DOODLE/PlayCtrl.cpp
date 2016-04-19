#include "PlayCtrl.h"

IMPLEMENT(PlayCtrl)
PlayCtrl::PlayCtrl()
{
	m_hBackbmp = NULL;		//������λͼ
	m_bisKeyUp = false;
}


PlayCtrl::~PlayCtrl()
{
	::DeleteObject(m_hBackbmp);
	m_hBackbmp = NULL;

	//ɾ�����е�����
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

void PlayCtrl::ShowBack(HDC hDC)   //��ʾ����
{
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	::SelectObject(hMemDC, m_hBackbmp);
	::BitBlt(hDC, 0, 0, 750, 642, hMemDC, 0, 0, SRCCOPY);
	::DeleteDC(hMemDC);
}


void PlayCtrl::OnCreateGame()
{
	doodle.InitDoodle(m_hIns, Left);	//�������
	InitStartBoard(m_hIns, lstBoard);	//��ʼ������
	InitBack(m_hIns);
	::SetTimer(m_hWnd, DOODLE_JUMP_TIMER_ID, 8, NULL);		//������Ծ�Ķ�ʱ��
}

void PlayCtrl::OnGameDraw()
{
	HDC dc = ::GetDC(m_hWnd);

	//������˸  ˫����
	HDC hMemDC = ::CreateCompatibleDC(dc);							//����������DC
	HBITMAP hBitMap = ::CreateCompatibleBitmap(dc, 750, 642);		//������ʱλͼ �봰��DC����
	::SelectObject(hMemDC, hBitMap);									//ѡ��ͼƬ����������DC��

	//---------------------------��ʾ��Ϸ---------------------------------
	this->ShowBack(hMemDC);
	doodle.ShowDoodle(hMemDC, doodle.nFace);
	this->ShowAllBoard(hMemDC, lstBoard);
	//---------------------------��ʾ��Ϸ---------------------------------


	::BitBlt(dc, 0, 0, 750, 642, hMemDC, 0, 0, SRCCOPY);			//��hMemDCͼƬ����dc��
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
					//�������û���߽� 
					if ((*ite)->m_y <= 550)
					{
						if (doodle.m_y <= 200)
							this->AllBoardMove(200);
						else
						//����ð��ƶ�����
						this->AllBoardMove(20);
						//ɾ������İ�
						this->DeleteBoard();
					}
					doodle.nState = 1;
					break;
				}
				++ite;
			}
			this->IsGameOver();
		}
		this->OnGameDraw();	//�ػ�
	}
}

void PlayCtrl::OnKeyDown(WPARAM nKey)
{
	m_bisKeyUp = false;

	while (!m_bisKeyUp)
	{
		//�ֶ�������Ϣ����  ��������������  ���õȴ���Ϣ����
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
	//�̶���һ����ɫ����
	Board* board = new GreenBoard;
	board->m_x = 335;
	board->m_y = 570;
	board->InitBoard(hIns);
	lstBoard.push_back(board);
	//���ʣ������
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
		if (::MessageBox(NULL, "����������~~", "23333~", MB_OK))
			::PostQuitMessage(0);
	}
}