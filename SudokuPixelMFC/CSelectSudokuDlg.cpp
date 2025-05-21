// CSelectSudokuDlg.cpp : implementation file
//

#include "pch.h"
#include "SudokuPixelMFC.h"
#include "afxdialogex.h"
#include "CSelectSudokuDlg.h"


// CSelectSudokuDlg dialog

IMPLEMENT_DYNAMIC(CSelectSudokuDlg, CDialogEx)

CSelectSudokuDlg::CSelectSudokuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIFFICULTY_WINDOW, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSelectSudokuDlg::~CSelectSudokuDlg()
{
}

void CSelectSudokuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectSudokuDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CSelectSudokuDlg message handlers

void CSelectSudokuDlg::OnPaint()
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
		userInterface.GetSpriteListSelection().RedrawAll(&dc, 0, 0);

		CDialogEx::OnPaint();
	}
}

void CSelectSudokuDlg::OnTimer(UINT_PTR nIDEvent)
{
	CClientDC dc(this);
	userInterface.GetSpriteListSelection().Update(&dc, 0, 0);
	CDialogEx::OnTimer(nIDEvent);
}

BOOL CSelectSudokuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	try
	{
		userInterface.OnInitSpritesSelection();
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}

	SetWindowPos(NULL, 0, 0, 344, 470, SWP_NOZORDER | SWP_NOMOVE);
	SetTimer(1, 100, NULL);

	return TRUE;
}

HCURSOR CSelectSudokuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSelectSudokuDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	userInterface.OnLButtonDownSelection(point);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CSelectSudokuDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CSudoku sudoku;
	if (userInterface.OnLButtonUpSelection(point, sudoku))
	{
		ShowWindow(SW_HIDE);
		CSudokuPixelMFCDlg dlg(sudoku);
		dlg.DoModal();
		ShowWindow(SW_SHOW);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
