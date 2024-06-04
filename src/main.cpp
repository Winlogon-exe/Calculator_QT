#include "../inc/view.h"
#include "../inc/CalculatorModel.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    View view;
    CalculatorModel model;
    view.show();
    return app.exec();
}
