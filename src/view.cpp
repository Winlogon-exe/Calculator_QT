#include "../inc/view.h"

View::View(QWidget *parent) : QWidget(parent)
{
    createUI();
}

void View::createUI()
{
    setWindowTitle("Calculator");

    setupConnect();
    setupDisplay();
    setupButtons();
    setupGridLayout();

    setLayout(gridLayout);
}

void View::setupDisplay()
{
    operationDisplayLabel = new QLabel("0");
    displayLineEdit = new QLineEdit("0");
    displayLineEdit->setReadOnly(true);
    displayLineEdit->setAlignment(Qt::AlignRight);
    displayLineEdit->setMaxLength(15);

    QFont font = displayLineEdit->font();
    font.setPointSize(font.pointSize() + 8);
    displayLineEdit->setFont(font);
}

void View::setupButtons()
{
    for (int i = 0; i < TotalDigitButtons; ++i)
    {
        digitButtonArray[i] = createButton(QString::number(i),Digit);
        digitButtonArray[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    plusButton     = createButton("+",Operator);
    minusButton    = createButton("-",Operator);
    multiplyButton = createButton("*",Operator);
    divideButton   = createButton("/",Operator);
    equalsButton   = createButton("=",Equal);

    clearAllButton = createButton("Clear All",ClearAll);
    historyButton  = createButton("History",History);
    clearButton    = createButton("Clear",Clear);

    QList<QPushButton*> allOperations =
    {
        clearButton, clearAllButton, historyButton,
        plusButton, minusButton, divideButton, multiplyButton, equalsButton
    };

    for (const auto& button : allOperations)
    {
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
}

void View::setupGridLayout()
{
    gridLayout = new QGridLayout;
    gridLayout->addWidget(operationDisplayLabel, 0, 0, 1, 6);
    gridLayout->addWidget(displayLineEdit, 1, 0, 1, 6);
    gridLayout->addWidget(clearButton, 2, 0, 1, 3);
    gridLayout->addWidget(clearAllButton, 2, 3, 1, 2);
    gridLayout->addWidget(digitButtonArray[0], 6, 0, 1, 4);
    gridLayout->addWidget(divideButton, 3, 4);
    gridLayout->addWidget(multiplyButton, 4, 4);
    gridLayout->addWidget(minusButton, 5, 4);
    gridLayout->addWidget(plusButton, 6, 4);
    gridLayout->addWidget(equalsButton, 3, 5, 4, 1);
    gridLayout->addWidget(historyButton, 2, 5);

    for (int i = 1; i < TotalDigitButtons; ++i)
    {
        int row = ((9 - i) / 3) + 3;
        int column = ((i - 1) % 3) + 1;
        gridLayout->addWidget(digitButtonArray[i], row, column);
    }
}

QPushButton* View::createButton(const QString& text, State state)
{
    QPushButton* button = new QPushButton(text, this);
    button->setObjectName(text);
    //Передача состояния
    calculatorModel.setButtonState(button, state);
    connect(button, &QPushButton::clicked, this, &View::ButtonClicked);
    return button;
}

void View::showHistoryDialog(const QStringList &history)
{
    // Создание элементов интерфейса для отображения истории
    QDialog* historyDialog = new QDialog(this);
    QVBoxLayout* verticalLayout = new QVBoxLayout(historyDialog);
    QTextEdit* historyTextEdit = new QTextEdit(historyDialog);
    historyDialog->setWindowTitle("История");

    historyTextEdit->setReadOnly(true);
    historyTextEdit->setText(history.join("\n"));
    verticalLayout->addWidget(historyTextEdit);
    historyDialog->exec();
}

void View::ButtonClicked()
{
    //QObject* senderObj = sender();
    calculatorModel.searchFunc(sender());
}

void View::setupConnect()
{
    connect(&calculatorModel, &CalculatorModel::updateDisplay, this, &View::showDisplayValue);
    connect(&calculatorModel, &CalculatorModel::updateHistory, this, &View::showHistoryDialog);
    connect(&calculatorModel, &CalculatorModel::updateLabel, this, &View::showOperationDisplay);
}

void View::showOperationDisplay(const QString &firstOperand, const QString &operation, const QString &secondOperand)
{
    QString equalText = equalsButton->objectName();
    QString displayText = firstOperand + " " + operation + " " + secondOperand + " " + equalText;
    operationDisplayLabel->setText(displayText);
}

void View::showDisplayValue(double result)
{
    displayLineEdit->setText(QString::number(result));
}
