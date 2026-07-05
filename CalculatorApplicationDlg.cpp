
// CalculatorApplicationDlg.cpp : implementation file
//

#include "CalculatorEngine.h"
#include "pch.h"
#include "framework.h"
#include "CalculatorApplication.h"
#include "CalculatorApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorApplicationDlg dialog



void CCalculatorApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_HISTORY, m_editHistory);
}

void CCalculatorApplicationDlg::UpdateDisplay()
{
	CString strDisplay = m_Calculator.GetDisplay();

	SetDlgItemText(IDC_EDITDISPLAY, strDisplay);

	SetDlgItemText(
		IDC_EDITEXPRESSION,
		m_Calculator.GetExpression());

	int nLength = strDisplay.GetLength();

	if (nLength <= 10)
	{
		GetDlgItem(IDC_EDITDISPLAY)->SetFont(&m_fontLarge);
	}
	else if (nLength <= 18)
	{
		GetDlgItem(IDC_EDITDISPLAY)->SetFont(&m_fontMedium);
	}
	else
	{
		GetDlgItem(IDC_EDITDISPLAY)->SetFont(&m_fontSmall);
	}

	GetDlgItem(IDC_EDITDISPLAY)->Invalidate();
}


BEGIN_MESSAGE_MAP(CCalculatorApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_0, &CCalculatorApplicationDlg::OnBnClickedBtn0)
	ON_BN_CLICKED(IDC_BTN_1, &CCalculatorApplicationDlg::OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN_2, &CCalculatorApplicationDlg::OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTN_3, &CCalculatorApplicationDlg::OnBnClickedBtn3)
	ON_BN_CLICKED(IDC_BTN_4, &CCalculatorApplicationDlg::OnBnClickedBtn4)
	ON_BN_CLICKED(IDC_BTN_5, &CCalculatorApplicationDlg::OnBnClickedBtn5)
	ON_BN_CLICKED(IDC_BTN_6, &CCalculatorApplicationDlg::OnBnClickedBtn6)
	ON_BN_CLICKED(IDC_BTN_7, &CCalculatorApplicationDlg::OnBnClickedBtn7)
	ON_BN_CLICKED(IDC_BTN_8, &CCalculatorApplicationDlg::OnBnClickedBtn8)
	ON_BN_CLICKED(IDC_BTN_9, &CCalculatorApplicationDlg::OnBnClickedBtn9)

	ON_BN_CLICKED(IDC_BTN_DOT, &CCalculatorApplicationDlg::OnBnClickedBtnDot)
	ON_BN_CLICKED(IDC_BTN_ADD, &CCalculatorApplicationDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SUB, &CCalculatorApplicationDlg::OnBnClickedBtnSub)
	ON_BN_CLICKED(IDC_BTN_MUL, &CCalculatorApplicationDlg::OnBnClickedBtnMul)
	ON_BN_CLICKED(IDC_BTN_DIV, &CCalculatorApplicationDlg::OnBnClickedBtnDiv)
	ON_BN_CLICKED(IDC_BTN_EQUAL, &CCalculatorApplicationDlg::OnBnClickedBtnEqual)
	ON_BN_CLICKED(IDC_BTN_PERCENT, &CCalculatorApplicationDlg::OnBnClickedBtnPercent)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CCalculatorApplicationDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_CLEARENTRY, &CCalculatorApplicationDlg::OnBnClickedBtnClearEntry)
	ON_BN_CLICKED(IDC_BTN_BACK, &CCalculatorApplicationDlg::OnBnClickedBtnBack)
	ON_BN_CLICKED(IDC_BTN_SIGN, &CCalculatorApplicationDlg::OnBnClickedBtnSign)

	ON_BN_CLICKED(IDC_BTN_SQRT, &CCalculatorApplicationDlg::OnBnClickedBtnSqrt)
	ON_BN_CLICKED(IDC_BTN_SQUARE, &CCalculatorApplicationDlg::OnBnClickedBtnSquare)
	ON_BN_CLICKED(IDC_BTN_RECIPROCAL, &CCalculatorApplicationDlg::OnBnClickedBtnReciprocal)
	ON_BN_CLICKED(IDC_BTN_MOD, &CCalculatorApplicationDlg::OnBnClickedBtnMod)

	ON_BN_CLICKED(IDC_BTN_MC, &CCalculatorApplicationDlg::OnBnClickedBtnMc)
	ON_BN_CLICKED(IDC_BTN_MR, &CCalculatorApplicationDlg::OnBnClickedBtnMr)
	ON_BN_CLICKED(IDC_BTN_MS, &CCalculatorApplicationDlg::OnBnClickedBtnMs)
	ON_BN_CLICKED(IDC_BTN_MPLUS, &CCalculatorApplicationDlg::OnBnClickedBtnMplus)
	ON_BN_CLICKED(IDC_BTN_MMINUS, &CCalculatorApplicationDlg::OnBnClickedBtnMminus)
	ON_LBN_SELCHANGE(IDC_LIST_HISTORY, &CCalculatorApplicationDlg::OnLbnSelchangeListHistory)

	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCalculatorApplicationDlg message handlers

BOOL CCalculatorApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_fontLarge.CreatePointFont(240, _T("Segoe UI Semibold"));

	m_fontMedium.CreatePointFont(180, _T("Segoe UI Semibold"));

	m_fontSmall.CreatePointFont(130, _T("Segoe UI Semibold"));

	m_fontExpression.CreatePointFont(110, _T("Segoe UI"));

	GetDlgItem(IDC_EDITDISPLAY)->SetFont(&m_fontLarge);

	GetDlgItem(IDC_EDITEXPRESSION)->SetFont(&m_fontExpression);

	UpdateDisplay();

	m_btnEqual.SubclassDlgItem(IDC_BTN_EQUAL, this);


	m_btnAdd.SubclassDlgItem(IDC_BTN_ADD, this);
	m_btnSub.SubclassDlgItem(IDC_BTN_SUB, this);
	m_btnMul.SubclassDlgItem(IDC_BTN_MUL, this);
	m_btnDiv.SubclassDlgItem(IDC_BTN_DIV, this);

	m_btn0.SubclassDlgItem(IDC_BTN_0, this);
	m_btn1.SubclassDlgItem(IDC_BTN_1, this);
	m_btn2.SubclassDlgItem(IDC_BTN_2, this);
	m_btn3.SubclassDlgItem(IDC_BTN_3, this);
	m_btn4.SubclassDlgItem(IDC_BTN_4, this);
	m_btn5.SubclassDlgItem(IDC_BTN_5, this);
	m_btn6.SubclassDlgItem(IDC_BTN_6, this);
	m_btn7.SubclassDlgItem(IDC_BTN_7, this);
	m_btn8.SubclassDlgItem(IDC_BTN_8, this);
	m_btn9.SubclassDlgItem(IDC_BTN_9, this);

	//m_fontDisplay.CreatePointFont(260, _T("Segoe UI Semibold"));


	GetDlgItem(IDC_EDITDISPLAY)->SetFont(&m_fontLarge);

	m_fontHistory.CreatePointFont(100, _T("Segoe UI"));   // 10pt

	m_editHistory.SetFont(&m_fontHistory);



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Calculator Engine

void CCalculatorApplicationDlg::OnBnClickedBtn0()
{
	m_Calculator.InputDigit(0);
	UpdateDisplay();
}


void CCalculatorApplicationDlg::OnBnClickedBtn1()
{
	m_Calculator.InputDigit(1);
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtn2()
{
	m_Calculator.InputDigit(2);
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtn3()
{
	m_Calculator.InputDigit(3);
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtn4()
{
	m_Calculator.InputDigit(4);
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtn5()
{
	m_Calculator.InputDigit(5);
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtn6()
{
	m_Calculator.InputDigit(6);
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtn7()
{
	m_Calculator.InputDigit(7);
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtn8()
{
	m_Calculator.InputDigit(8);
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtn9()
{
	m_Calculator.InputDigit(9);
	UpdateDisplay();
}

// ================= Decimal =================

void CCalculatorApplicationDlg::OnBnClickedBtnDot()
{
	m_Calculator.InputDecimal();
	UpdateDisplay();
}

// ================= Operators =================

void CCalculatorApplicationDlg::OnBnClickedBtnAdd()
{
	m_Calculator.SetOperator('+');
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnSub()
{
	m_Calculator.SetOperator('-');
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnMul()
{
	m_Calculator.SetOperator('*');
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnDiv()
{
	m_Calculator.SetOperator('/');
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnPercent()
{
	m_Calculator.Percent();

	AddHistory(m_Calculator.GetExpression());

	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnMod()
{
	m_Calculator.SetOperator('M');
	UpdateDisplay();
}


// ================= Clear =================

void CCalculatorApplicationDlg::OnBnClickedBtnEqual()
{
	m_Calculator.Calculate();

	AddHistory(m_Calculator.GetExpression());

	m_Calculator.ClearExpression();

	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnClearEntry()
{
	m_Calculator.ClearEntry();
	UpdateDisplay();
}

// ================= Backspace =================

void CCalculatorApplicationDlg::OnBnClickedBtnBack()
{
	m_Calculator.Backspace();
	UpdateDisplay();
}

// ================= Sign =================

void CCalculatorApplicationDlg::OnBnClickedBtnSign()
{
	m_Calculator.ChangeSign();
	UpdateDisplay();
}

BOOL CCalculatorApplicationDlg::PreTranslateMessage(MSG* pMsg)
{
	// Ctrl + C / Ctrl + V
	if ((GetKeyState(VK_CONTROL) & 0x8000) && pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case 'C':
		case 'c':
		{
			CString strText = m_Calculator.GetDisplay();

			if (OpenClipboard())
			{
				EmptyClipboard();

				HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE,
					(strText.GetLength() + 1) * sizeof(TCHAR));

				if (hGlob)
				{
					LPTSTR pData = (LPTSTR)GlobalLock(hGlob);
					lstrcpy(pData, strText);
					GlobalUnlock(hGlob);

#ifdef _UNICODE
					SetClipboardData(CF_UNICODETEXT, hGlob);
#else
					SetClipboardData(CF_TEXT, hGlob);
#endif
				}

				CloseClipboard();
			}

			return TRUE;
		}

		case 'V':
		case 'v':
		{
			if (OpenClipboard())
			{
#ifdef _UNICODE
				HANDLE hData = GetClipboardData(CF_UNICODETEXT);
#else
				HANDLE hData = GetClipboardData(CF_TEXT);
#endif

				if (hData)
				{
					LPCTSTR pText = (LPCTSTR)GlobalLock(hData);

					if (pText)
					{
						CString strNumber(pText);

						for (int i = 0; i < strNumber.GetLength(); i++)
						{
							TCHAR ch = strNumber[i];

							if (ch >= '0' && ch <= '9')
								m_Calculator.InputDigit(ch);
							else if (ch == '.')
								m_Calculator.InputDecimal();
						}

						UpdateDisplay();
						GlobalUnlock(hData);
					}
				}

				CloseClipboard();
			}

			return TRUE;
		}
		}
	}

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case '0': case VK_NUMPAD0: OnBnClickedBtn0(); return TRUE;
		case '1': case VK_NUMPAD1: OnBnClickedBtn1(); return TRUE;
		case '2': case VK_NUMPAD2: OnBnClickedBtn2(); return TRUE;
		case '3': case VK_NUMPAD3: OnBnClickedBtn3(); return TRUE;
		case '4': case VK_NUMPAD4: OnBnClickedBtn4(); return TRUE;
		case '5': case VK_NUMPAD5: OnBnClickedBtn5(); return TRUE;
		case '6': case VK_NUMPAD6: OnBnClickedBtn6(); return TRUE;
		case '7': case VK_NUMPAD7: OnBnClickedBtn7(); return TRUE;
		case '8': case VK_NUMPAD8: OnBnClickedBtn8(); return TRUE;
		case '9': case VK_NUMPAD9: OnBnClickedBtn9(); return TRUE;

		case '.':
			OnBnClickedBtnDot();
			return TRUE;

		case '+': case VK_ADD:
			OnBnClickedBtnAdd();
			return TRUE;

		case '-': case VK_SUBTRACT:
			OnBnClickedBtnSub();
			return TRUE;

		case '*': case VK_MULTIPLY:
			OnBnClickedBtnMul();
			return TRUE;

		case '/': case VK_DIVIDE:
			OnBnClickedBtnDiv();
			return TRUE;

		case '=':
		case VK_RETURN:
			OnBnClickedBtnEqual();
			return TRUE;

		case VK_BACK:
			OnBnClickedBtnBack();
			return TRUE;

		case VK_ESCAPE:
			OnBnClickedBtnClear();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
void CCalculatorApplicationDlg::OnBnClickedBtnSqrt()
{
	m_Calculator.SquareRoot();

	AddHistory(m_Calculator.GetExpression());

	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnSquare()
{
	m_Calculator.Square();

	AddHistory(m_Calculator.GetExpression());

	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnReciprocal()
{
	m_Calculator.Reciprocal();

	AddHistory(m_Calculator.GetExpression());

	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnMc()
{
	m_Calculator.MemoryClear();
}

void CCalculatorApplicationDlg::OnBnClickedBtnMr()
{
	m_Calculator.MemoryRecall();
	UpdateDisplay();
}

void CCalculatorApplicationDlg::OnBnClickedBtnMs()
{
	m_Calculator.MemoryStore();
}

void CCalculatorApplicationDlg::OnBnClickedBtnMplus()
{
	m_Calculator.MemoryAdd();
}

void CCalculatorApplicationDlg::OnBnClickedBtnMminus()
{
	m_Calculator.MemorySubtract();
}



void CCalculatorApplicationDlg::OnLbnSelchangeListHistory()
{
	// TODO: Add your control notification handler code here
}

void CCalculatorApplicationDlg::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	
}

CCalculatorApplicationDlg::CCalculatorApplicationDlg(CWnd* pParent)
	: CDialogEx(IDD_CALCULATORAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_brBackground.CreateSolidBrush(RGB(32, 32, 32));   // Dark background
	m_brEdit.CreateSolidBrush(RGB(45, 45, 45));         // Display background
	m_clrText = RGB(255, 255, 255);                       // White text
}

HBRUSH CCalculatorApplicationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
		return (HBRUSH)m_brBackground.GetSafeHandle();

	case CTLCOLOR_EDIT:
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDITDISPLAY)
		{
			pDC->SetTextColor(RGB(0, 120, 215));     // Windows Blue
		}
		else
		{
			pDC->SetTextColor(RGB(220, 220, 220));   // Expression
		}

		pDC->SetBkColor(RGB(30, 30, 30));

		return (HBRUSH)m_brEdit.GetSafeHandle();
	}

	case CTLCOLOR_STATIC:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)m_brBackground.GetSafeHandle();
	}

	return hbr;
}

void CCalculatorApplicationDlg::OnBnClickedBtnClear()
{
	m_Calculator.Clear();
	UpdateDisplay();
}

void CCalculatorApplicationDlg::AddHistory(const CString& strHistory)
{
	if (strHistory.IsEmpty())
		return;

	CString oldText;
	m_editHistory.GetWindowText(oldText);

	CString history = strHistory;

	// If line is too long, insert a newline after '='
	if (history.GetLength() > 45)
	{
		int pos = history.Find(_T("="));

		if (pos != -1)
		{
			history.Insert(pos + 1, _T("\r\n"));
		}
	}

	CString newText;

	if (oldText.IsEmpty())
		newText = history;
	else
		newText = history + _T("\r\n\r\n") + oldText;

	m_editHistory.SetWindowText(newText);
}