#include "pch.h"
#include "CalculatorEngine.h"

CCalculatorEngine::CCalculatorEngine()
{
    m_dFirstValue = 0.0;
    m_dSecondValue = 0.0;

    m_dMemory = 0.0;

    m_chOperator = 0;

    m_bOperatorPressed = FALSE;
    m_bNewNumber = TRUE;

    m_strDisplay = _T("0");
    m_strExpression.Empty();


}

CString CCalculatorEngine::GetDisplay() const
{
    return m_strDisplay;
}

CString CCalculatorEngine::GetExpression() const
{
    return m_strExpression;
}

void CCalculatorEngine::Clear()
{
    m_dFirstValue = 0.0;
    m_dSecondValue = 0.0;

    m_chOperator = 0;

    m_bOperatorPressed = FALSE;
    m_bNewNumber = TRUE;

    m_strDisplay = _T("0");
    m_strExpression.Empty();
}

void CCalculatorEngine::ClearEntry()
{
    m_strDisplay = _T("0");
    m_bNewNumber = TRUE;
}

void CCalculatorEngine::InputDigit(int nDigit)
{
    if (m_bNewNumber)
    {
        m_strDisplay.Empty();
        m_bNewNumber = FALSE;
    }

    if (m_strDisplay == _T("0"))
    {
        m_strDisplay.Empty();
    }

    m_strDisplay.AppendFormat(_T("%d"), nDigit);

    // Update expression while entering second number
    if (m_bOperatorPressed)
    {
        CString strFirst = FormatNumber(m_dFirstValue);

        m_strExpression.Format(
            _T("%s %c %s"),
            strFirst.GetString(),
            m_chOperator,
            m_strDisplay.GetString()
        );
    }
}

void CCalculatorEngine::InputDecimal()
{
    if (m_bNewNumber)
    {
        m_strDisplay = _T("0.");
        m_bNewNumber = FALSE;
        return;
    }

    if (m_strDisplay.Find('.') == -1)
    {
        m_strDisplay += '.';
    }
    if (m_bOperatorPressed)
    {
        CString strFirst = FormatNumber(m_dFirstValue);

        m_strExpression.Format(
            _T("%s %c %s"),
            strFirst.GetString(),
            m_chOperator,
            m_strDisplay.GetString()
        );
    }
}

void CCalculatorEngine::Backspace()
{
    if (m_bNewNumber)
        return;

    if (!m_strDisplay.IsEmpty())
    {
        m_strDisplay.Delete(m_strDisplay.GetLength() - 1);

        if (m_strDisplay.IsEmpty())
        {
            m_strDisplay = _T("0");
            m_bNewNumber = TRUE;
        }
    }
}

void CCalculatorEngine::ChangeSign()
{
    if (m_strDisplay == _T("0"))
        return;

    if (m_strDisplay[0] == '-')
    {
        m_strDisplay.Delete(0);
    }
    else
    {
        m_strDisplay = _T("-") + m_strDisplay;
    }

    if (m_bOperatorPressed)
    {
        CString strFirst = FormatNumber(m_dFirstValue);

        m_strExpression.Format(
            _T("%s %c %s"),
            strFirst.GetString(),
            m_chOperator,
            m_strDisplay.GetString()
        );
    }
}

void CCalculatorEngine::SetOperator(TCHAR chOperator)
{
    if (m_bOperatorPressed && !m_bNewNumber)
    {
        CalculateIntermediate();
    }
    else
    {
        m_dFirstValue = _tstof(m_strDisplay);
    }

    m_chOperator = chOperator;
    m_bOperatorPressed = TRUE;

    CString strOperator;

    if (m_chOperator == 'M')
        strOperator = _T("mod");
    else
        strOperator.Format(_T("%c"), m_chOperator);

    m_strExpression.Format(
        _T("%s %s"),
        (LPCTSTR)FormatNumber(m_dFirstValue),
        (LPCTSTR)strOperator
    );

    m_bNewNumber = TRUE;
}
void CCalculatorEngine::Calculate()
{
    if (m_chOperator == 0)
        return;

    m_dSecondValue = _tstof(m_strDisplay);

    double dOldFirstValue = m_dFirstValue;

    switch (m_chOperator)
    {
    case '+':
        m_dFirstValue += m_dSecondValue;
        break;

    case '-':
        m_dFirstValue -= m_dSecondValue;
        break;

    case '*':
        m_dFirstValue *= m_dSecondValue;
        break;

    case '/':
        if (m_dSecondValue == 0)
        {
            m_strDisplay = _T("Cannot divide by zero");
            m_bOperatorPressed = FALSE;
            m_bNewNumber = TRUE;
            return;
        }

        m_dFirstValue /= m_dSecondValue;
        break;

    case 'M':
        if ((int)m_dSecondValue == 0)
        {
            m_strDisplay = _T("Cannot divide by zero");
            return;
        }

        m_dFirstValue = (int)m_dFirstValue % (int)m_dSecondValue;
        break;
    }

    m_strDisplay = FormatNumber(m_dFirstValue);

    CString strOperator;

    if (m_chOperator == 'M')
        strOperator = _T("mod");
    else
        strOperator.Format(_T("%c"), m_chOperator);

    m_strExpression.Format(
        _T("%s %s %s = %s"),
        (LPCTSTR)FormatNumber(dOldFirstValue),
        (LPCTSTR)strOperator,
        (LPCTSTR)FormatNumber(m_dSecondValue),
        (LPCTSTR)FormatNumber(m_dFirstValue)
    );

    m_bOperatorPressed = FALSE;
    m_bNewNumber = TRUE;
}

void CCalculatorEngine::CalculateIntermediate()
{
    m_dSecondValue = _tstof(m_strDisplay);

    switch (m_chOperator)
    {
    case '+':
        m_dFirstValue += m_dSecondValue;
        break;

    case '-':
        m_dFirstValue -= m_dSecondValue;
        break;

    case '*':
        m_dFirstValue *= m_dSecondValue;
        break;

    case '/':
        if (m_dSecondValue == 0)
        {
            m_strDisplay = _T("Cannot divide by zero");
            return;
        }

        m_dFirstValue /= m_dSecondValue;
        break;
    }

    m_strDisplay.Format(_T("%.0f"), m_dFirstValue);
}

CString CCalculatorEngine::FormatNumber(double dValue)
{
    CString str;

    // Convert to string with up to 10 decimal places
    str.Format(_T("%.10f"), dValue);

    // Remove trailing zeros
    while (str.Right(1) == _T("0"))
        str.Delete(str.GetLength() - 1);

    // Remove trailing decimal point
    if (str.Right(1) == _T("."))
        str.Delete(str.GetLength() - 1);

    // Split integer and decimal parts
    int nDot = str.Find('.');

    CString strInt = (nDot == -1) ? str : str.Left(nDot);
    CString strDec = (nDot == -1) ? _T("") : str.Mid(nDot);

    // Handle negative numbers
    BOOL bNegative = FALSE;

    if (!strInt.IsEmpty() && strInt[0] == '-')
    {
        bNegative = TRUE;
        strInt.Delete(0);
    }

    // Insert commas every 3 digits
    for (int i = strInt.GetLength() - 3; i > 0; i -= 3)
    {
        strInt.Insert(i, _T(','));
    }

    if (bNegative)
        strInt = _T("-") + strInt;

    return strInt + strDec;
}

void CCalculatorEngine::SquareRoot()
{
    double dOldValue = _tstof(m_strDisplay);

    if (dOldValue < 0)
    {
        m_strDisplay = _T("Invalid Input");
        return;
    }

    double dResult = sqrt(dOldValue);

    m_strDisplay = FormatNumber(dResult);

    CString strOld = FormatNumber(dOldValue);
    CString strResult = FormatNumber(dResult);

    m_strExpression.Format(
        _T("sqrt(%s) = %s"),
        strOld,
        strResult);

    m_bNewNumber = TRUE;
}




void CCalculatorEngine::Square()
{
    double dOldValue = _tstof(m_strDisplay);

    double dResult = dOldValue * dOldValue;

    m_strDisplay = FormatNumber(dResult);

    CString strOld = FormatNumber(dOldValue);
    CString strResult = FormatNumber(dResult);

    m_strExpression.Format(
        _T("sqr(%s) = %s"),
        strOld,
        strResult);
}

void CCalculatorEngine::Reciprocal()
{
    double dOldValue = _tstof(m_strDisplay);

    if (dOldValue == 0)
    {
        m_strDisplay = _T("Cannot divide by zero");
        return;
    }

    double dResult = 1.0 / dOldValue;

    m_strDisplay = FormatNumber(dResult);
    CString strOld = FormatNumber(dOldValue);
    CString strResult = FormatNumber(dResult);

    m_strExpression.Format(
        _T("1/(%s) = %s"),
        strOld,
        strResult);

    m_bNewNumber = TRUE;
}

void CCalculatorEngine::MemoryClear()
{
    m_dMemory = 0.0;
}

void CCalculatorEngine::MemoryStore()
{
    m_dMemory = _tstof(m_strDisplay);
}

void CCalculatorEngine::MemoryRecall()
{
    m_strDisplay = FormatNumber(m_dMemory);
    m_bNewNumber = TRUE;
}

void CCalculatorEngine::MemoryAdd()
{
    m_dMemory += _tstof(m_strDisplay);
}

void CCalculatorEngine::MemorySubtract()
{
    m_dMemory -= _tstof(m_strDisplay);
}

void CCalculatorEngine::Percent()
{
    double dValue = _tstof(m_strDisplay);
    double dOldValue = dValue;
    double dResult = 0.0;

    if (m_bOperatorPressed)
    {
        switch (m_chOperator)
        {
        case '+':
        case '-':
            dResult = (m_dFirstValue * dValue) / 100.0;
            break;

        case '*':
        case '/':
            dResult = dValue / 100.0;
            break;

        default:
            dResult = dValue / 100.0;
            break;
        }
    }
    else
    {
        dResult = dValue / 100.0;
    }

    m_dSecondValue = dResult;
    m_strDisplay = FormatNumber(dResult);

    if (m_bOperatorPressed)
    {
        CString strOperator;
        strOperator.Format(_T("%c"), m_chOperator);

        m_strExpression.Format(
            _T("%s %s %s%%"),
            FormatNumber(m_dFirstValue),
            strOperator,
            FormatNumber(dOldValue));
    }
    else
    {
        m_strExpression.Format(
            _T("%s%% = %s"),
            FormatNumber(dOldValue),
            FormatNumber(dResult));
    }

    m_bNewNumber = FALSE;
}

void CCalculatorEngine::ClearExpression()
{
    m_strExpression.Empty();
}


