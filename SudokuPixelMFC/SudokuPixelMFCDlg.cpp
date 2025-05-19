
// SudokuPixelMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SudokuPixelMFC.h"
#include "SudokuPixelMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSudokuPixelMFCDlg dialog



CSudokuPixelMFCDlg::CSudokuPixelMFCDlg(CSudoku& sudoku, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUDOKUPIXELMFC_DIALOG, pParent), sudoku(sudoku)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSudokuPixelMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSudokuPixelMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

BOOL CSudokuPixelMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	if (!userInterface.OnInitSpritesSudoku(sudoku))
	{
		OnCancel();
	}

	SetWindowPos(NULL, 0, 0, userInterface.GetBuffer().DibWidth(), userInterface.GetBuffer().DibHeight(), SWP_NOZORDER | SWP_NOMOVE);
	SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CSudokuPixelMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_CHAR)
	{
		TCHAR ch = (TCHAR)pMsg->wParam;
		userInterface.OnChar(ch, sudoku, undo);
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSudokuPixelMFCDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		userInterface.GetSpriteListSudoku().RedrawAll(&dc, 0, 0);

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSudokuPixelMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSudokuPixelMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	CClientDC dc(this);
	userInterface.GetSpriteListSudoku().Update(&dc, 0, 0);
	if (nIDEvent == 2)
	{
		userInterface.ButtonCheckRemove();
		KillTimer(2);
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CSudokuPixelMFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!userInterface.OnLButtonUpSudoku(point, sudoku, undo, solve))
	{
		OnCancel();
	}

	SetTimer(2, 1000, NULL);
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CSudokuPixelMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	userInterface.OnLButtonDownSudoku(point);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CSudokuPixelMFCDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}
