
// SudokuPixelMFCDlg.h : header file
//

#pragma once
#include "CUserInterface.h"

// CSudokuPixelMFCDlg dialog
class CSudokuPixelMFCDlg : public CDialogEx
{
// Construction
public:
	CSudokuPixelMFCDlg(CSudoku& sudoku, CWnd* pParent = nullptr);	// standard constructor


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUDOKUPIXELMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	CUserInterface userInterface;
	CSudoku& sudoku;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
