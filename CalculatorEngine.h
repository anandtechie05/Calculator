#pragma once

class CCalculatorEngine
{
public:

    CCalculatorEngine();

    void Clear();
    void ClearEntry();
    void Backspace();

    void InputDigit(int nDigit);
    void InputDecimal();
    void ChangeSign();

    void SetOperator(TCHAR chOperator);
    void Calculate();
    void CalculateIntermediate();

    void Percent();
    void SquareRoot();
    void Square();
    void Reciprocal();

    void MemoryClear();
    void MemoryRecall();
    void MemoryStore();
    void MemoryAdd();
    void MemorySubtract();

    void ClearExpression();

    

    CString GetDisplay() const;
    CString GetExpression() const;

    CString FormatNumber(double dValue);

private:

    double m_dFirstValue;
    double m_dSecondValue;

    TCHAR m_chOperator;

    BOOL m_bOperatorPressed;
    BOOL m_bNewNumber;

    CString m_strDisplay;
    CString m_strExpression;
  

    // Memory
    double m_dMemory;
};