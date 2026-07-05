#pragma once
#include <afxwin.h>

class CRoundButton : public CButton
{
    DECLARE_DYNAMIC(CRoundButton)

public:
    CRoundButton();
    virtual ~CRoundButton();

protected:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);

    DECLARE_MESSAGE_MAP()

private:
    bool m_bHover;
};