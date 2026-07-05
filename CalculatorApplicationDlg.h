

// CalculatorApplicationDlg.h : header file
//

#pragma once
#include "CalculatorEngine.h"
#include "RoundButton.h"

// CCalculatorApplicationDlg dialog
class CCalculatorApplicationDlg : public CDialogEx
{
// Construction
public:
	CCalculatorApplicationDlg(CWnd* pParent = nullptr);	// standard constructor

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATORAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

    protected:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

private:
	CRoundButton m_btnEqual;

	CRoundButton m_btnAdd;
	CRoundButton m_btnSub;
	CRoundButton m_btnMul;
	CRoundButton m_btnDiv;

	CRoundButton m_btn0;
	CRoundButton m_btn1;
	CRoundButton m_btn2;
	CRoundButton m_btn3;
	CRoundButton m_btn4;
	CRoundButton m_btn5;
	CRoundButton m_btn6;
	CRoundButton m_btn7;
	CRoundButton m_btn8;
	CRoundButton m_btn9;

	int m_nHoverButton;

private:
	CBrush m_brBackground;
	CBrush m_brEdit;
	COLORREF m_clrText;
	CFont m_fontLarge;
	CFont m_fontMedium;
	CFont m_fontSmall;

	CFont m_fontExpression;
	CFont m_fontHistory;
	



// Implementation
protected:
	HICON m_hIcon;

	// Calculator Engine
	CCalculatorEngine m_Calculator;

	// Refresh Display
	void UpdateDisplay();

	CEdit m_editHistory;

	void AddHistory(const CString& strHistory);


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtn0();
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();
	afx_msg void OnBnClickedBtn3();
	afx_msg void OnBnClickedBtn4();
	afx_msg void OnBnClickedBtn5();
	afx_msg void OnBnClickedBtn6();
	afx_msg void OnBnClickedBtn7();
	afx_msg void OnBnClickedBtn8();
	afx_msg void OnBnClickedBtn9();

	afx_msg void OnBnClickedBtnDot();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSub();
	afx_msg void OnBnClickedBtnMul();
	afx_msg void OnBnClickedBtnDiv();
	afx_msg void OnBnClickedBtnEqual();
	afx_msg void OnBnClickedBtnPercent();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnClearEntry();
	afx_msg void OnBnClickedBtnBack();
	afx_msg void OnBnClickedBtnSign();
	

	afx_msg void OnBnClickedBtnSqrt();
	afx_msg void OnBnClickedBtnSquare();
	afx_msg void OnBnClickedBtnReciprocal();
	afx_msg void OnBnClickedBtnMod();

	afx_msg void OnBnClickedBtnMc();
	afx_msg void OnBnClickedBtnMr();
	afx_msg void OnBnClickedBtnMs();
	afx_msg void OnBnClickedBtnMplus();
	afx_msg void OnBnClickedBtnMminus();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeListHistory();
};
