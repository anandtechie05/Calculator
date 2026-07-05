#include "pch.h"
#include "RoundButton.h"

IMPLEMENT_DYNAMIC(CRoundButton, CButton)

BEGIN_MESSAGE_MAP(CRoundButton, CButton)
    ON_WM_MOUSEMOVE()
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

CRoundButton::CRoundButton()
{
    m_bHover = false;
}

CRoundButton::~CRoundButton()
{
}

void CRoundButton::OnMouseMove(UINT nFlags, CPoint point)
{
    if (!m_bHover)
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = GetSafeHwnd();

        ::_TrackMouseEvent(&tme);

        m_bHover = true;
        Invalidate();
    }

    CButton::OnMouseMove(nFlags, point);
}

LRESULT CRoundButton::OnMouseLeave(WPARAM, LPARAM)
{
    m_bHover = false;
    Invalidate();
    return 0;
}

void CRoundButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC dc;
    dc.Attach(lpDIS->hDC);

    CRect rc = lpDIS->rcItem;

    CString text;
    GetWindowText(text);

    //----------------------------------------------------
    // Button Colors
    //----------------------------------------------------

    COLORREF clrBack = RGB(58, 58, 58);      // Default number buttons

    // Equal button
    if (text == _T("="))
    {
        clrBack = RGB(0, 122, 255);
    }

    // Operators
    else if (text == _T("+") ||
        text == _T("-") ||
        text == _T("*") ||
        text == _T("/") ||
        text == _T("×") ||
        text == _T("÷"))
    {
        clrBack = RGB(255, 149, 0);
    }

    // Memory Buttons
    else if (text == _T("MC") ||
        text == _T("MR") ||
        text == _T("MS") ||
        text == _T("M+") ||
        text == _T("M-"))
    {
        clrBack = RGB(65, 65, 65);
    }

    // Scientific Buttons
    else if (text == _T("√") ||
        text == _T("x²") ||
        text == _T("1/x") ||
        text == _T("%"))
    {
        clrBack = RGB(90, 70, 170);
    }

    //----------------------------------------------------
    // Hover Effect
    //----------------------------------------------------

    if (m_bHover)
    {
        clrBack = RGB(
            min(GetRValue(clrBack) + 40, 255),
            min(GetGValue(clrBack) + 40, 255),
            min(GetBValue(clrBack) + 40, 255));
    }

    //----------------------------------------------------
    // Pressed Effect
    //----------------------------------------------------

    if (lpDIS->itemState & ODS_SELECTED)
    {
        clrBack = RGB(
            max(GetRValue(clrBack) - 25, 0),
            max(GetGValue(clrBack) - 25, 0),
            max(GetBValue(clrBack) - 25, 0));
    }

    //----------------------------------------------------
    // Draw Button
    //----------------------------------------------------

    CPen pen(PS_SOLID, 1, RGB(85, 85, 85));
    CBrush brush(clrBack);

    CPen* pOldPen = dc.SelectObject(&pen);
    CBrush* pOldBrush = dc.SelectObject(&brush);

    // More rounded corners
    dc.RoundRect(rc, CPoint(16, 16));

    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);

    //----------------------------------------------------
    // Draw Text
    //----------------------------------------------------

    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(245, 245, 245));

    CFont font;
    font.CreatePointFont(115, _T("Segoe UI Semibold"));

    CFont* pOldFont = dc.SelectObject(&font);

    dc.DrawText(
        text,
        rc,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    dc.SelectObject(pOldFont);

    dc.Detach();
}