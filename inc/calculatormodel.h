#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H

#include <QObject>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>
#include <QMap>
#include <map>

enum State
{
    Digit,
    Operator,
    Equal,
    Clear,
    ClearAll,
    History,
};

class CalculatorModel : public QObject
{
    Q_OBJECT

public:
    explicit CalculatorModel(QObject* parent = nullptr);
    void searchFunc(QObject* sender);

signals:
    void updateDisplay(double value);
    void updateHistory(const QStringList &history);
    void updateLabel(const QString &currentValue, const QString &operation, const QString &nextValu);

public:
    void handleDigit(int digit);
    void handleOperator(const QString &op);

    void plus();
    void minus();
    void multiply();
    void divide();
    void clear();
    void clearAll();
    void calculateResult();
    void addToHistory(double resultBefore, const QString& operation, double operand, double result);
    void setButtonState(QObject* button, State state);

    const QStringList& getHistory() const;
private:
    QString                   currentOperation; // Текущая операция
    bool                      operatorClicked;
    std::map<QObject*, State> buttonStateMap;
    double                    secondOperand;
    double                    firstOperand;
    double                    result;
    QStringList               history;
    State                     state;
};

#endif // CALCULATORMODEL_H
