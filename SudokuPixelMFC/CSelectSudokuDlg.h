#pragma once
#include "afxdialogex.h"


// CSelectSudokuDlg dialog

class CSelectSudokuDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectSudokuDlg)

public:
	CSelectSudokuDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSelectSudokuDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIFFICULTY_WINDOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
