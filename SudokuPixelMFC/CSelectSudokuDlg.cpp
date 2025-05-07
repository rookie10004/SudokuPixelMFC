// CSelectSudokuDlg.cpp : implementation file
//

#include "pch.h"
#include "SudokuPixelMFC.h"
#include "afxdialogex.h"
#include "CSelectSudokuDlg.h"


// CSelectSudokuDlg dialog

IMPLEMENT_DYNAMIC(CSelectSudokuDlg, CDialog)

CSelectSudokuDlg::CSelectSudokuDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIFFICULTY_WINDOW, pParent)
{

}

CSelectSudokuDlg::~CSelectSudokuDlg()
{
}

void CSelectSudokuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectSudokuDlg, CDialog)
END_MESSAGE_MAP()


// CSelectSudokuDlg message handlers
