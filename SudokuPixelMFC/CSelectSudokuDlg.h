#pragma once
#include "afxdialogex.h"
#include "CUserInterface.h"
#include "SudokuPixelMFCDlg.h"
#include "Exceptions.h"


// CSelectSudokuDlg dialog

class CSelectSudokuDlg : public CDialogEx
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
	HICON m_hIcon;
	CUserInterface userInterface;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
