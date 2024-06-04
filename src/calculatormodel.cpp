#include "../inc/calculatormodel.h"

CalculatorModel::CalculatorModel(QObject* parent) :
    QObject(parent),
    secondOperand (0.0),
    firstOperand (0.0),
    result(0.0),
    operatorClicked(false)
{}

void CalculatorModel::searchFunc(QObject* sender)
{
    State state = buttonStateMap[sender]; // Получаем состояние из отправителя сигнала
    QString operationInput = sender->objectName();
    int digit = sender->objectName().toInt();

    switch (state)
    {
    case Digit:
        handleDigit(digit);
        break;
    case Operator:
        handleOperator(operationInput);
        break;
    case Equal:
        calculateResult();
        break;
    case Clear:
        clear();
        break;
    case ClearAll:
        clearAll();
        break;
    case History:
        emit updateHistory(getHistory());
        break;
    default:
        qDebug()<<"unknown";
        break;
    }
    emit updateLabel(QString::number(firstOperand),currentOperation,QString::number(secondOperand));
}

//можно и по другому сделать,хз как лучше?
void CalculatorModel::handleDigit(int digit)
{
    // Определяем, к какому операнду добавлять цифру, и обновляем его значение
    if (!operatorClicked)
    {
        // Добавляем цифру к первому операнду, если оператор не был выбран
        firstOperand = firstOperand * 10 + digit;
        emit updateDisplay(firstOperand);
    }
    else
    {
        // Добавляем цифру ко второму операнду, если оператор был выбран
        secondOperand = secondOperand * 10 + digit;
        emit updateDisplay(secondOperand);
    }
}

void CalculatorModel::handleOperator(const QString &operationInput)
{
    if (secondOperand != 0.0)
    {
        calculateResult();
    }
    currentOperation = operationInput;
    operatorClicked = true; //оператор был выбран
}

void CalculatorModel::calculateResult()
{
    if(!operatorClicked)
        return;

    if (currentOperation == "+")
    {
        plus();
    }
    else if (currentOperation == "-")
    {
        minus();
    }
    else if (currentOperation == "*")
    {
        multiply();
    }
    else if (currentOperation == "/")
    {
        divide();
    }

    addToHistory(firstOperand, currentOperation, secondOperand, result);
    firstOperand = result; // Сохранение результата в firstOperand для последующих вычислений
    secondOperand = 0.0;
    emit updateDisplay(result);
}

void CalculatorModel::clear()
{
    firstOperand = 0.0;
    secondOperand = 0.0;
    result = 0.0;
    operatorClicked = false;
    emit updateDisplay(result);
}

void CalculatorModel::clearAll()
{
    clear();
    currentOperation.clear();
    history.clear();
    emit updateDisplay(result);
}

void CalculatorModel::plus()
{
    result = firstOperand + secondOperand;
}

void CalculatorModel::minus()
{
    result = firstOperand - secondOperand;
}

void CalculatorModel::multiply()
{
    result = firstOperand * secondOperand;
}

void CalculatorModel::divide()
{
    if (secondOperand == 0.0)
    {
        QMessageBox::critical(nullptr, "Error", "Cannot divide by zero!");
        clear();
        return;
    }
    result = firstOperand / secondOperand ;
}

void CalculatorModel::addToHistory(double firstOperand, const QString& currentOperation, double secondOperand, double result)
{
    QString historyEntry = QString("%1 %2 %3 = %4")
                               .arg(firstOperand )
                               .arg(currentOperation)
                               .arg(secondOperand )
                               .arg(result);
    history.append(historyEntry);
}

const QStringList& CalculatorModel::getHistory() const
{
    return history;
}

void CalculatorModel::setButtonState(QObject* button, State state)
{
    buttonStateMap[button] = state;
}
