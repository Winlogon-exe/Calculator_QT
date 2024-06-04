#ifndef VIEW_H
#define VIEW_H

#include <QGridLayout>
#include <QLineEdit>
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include<QLabel>
#include "../inc/calculatormodel.h"

class View : public QWidget
{
    Q_OBJECT

public:
    explicit View(QWidget* parent = nullptr);
    void createUI();
    void setupDisplay();
    void setupGridLayout();
    void setupButtons();
    void setupConnect();

private slots:
    void showHistoryDialog(const QStringList &history);
    void showDisplayValue(double result);
    void showOperationDisplay(const QString &firstOperand, const QString &operation, const QString &secondOperand);
    void ButtonClicked();

private:
    QPushButton* createButton(const QString& text,State state);

private:
    enum NumButton      { TotalDigitButtons = 10 };
    QPushButton*        digitButtonArray[TotalDigitButtons];

    QLabel*             operationDisplayLabel;
    CalculatorModel     calculatorModel;
    QLineEdit*          displayLineEdit;
    QLineEdit*          mainDisplay;
    QGridLayout*        gridLayout; 

private:
    QPushButton* plusButton;
    QPushButton* minusButton;
    QPushButton* multiplyButton;
    QPushButton* divideButton;
    QPushButton* equalsButton;

    QPushButton* historyButton;
    QPushButton* clearButton;
    QPushButton* clearAllButton;
};

#endif // VIEW_H
