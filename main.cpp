#include "Exception.h"
#include "MainWindow.h"
#include "UI_MWidgets.h"

#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    auto         mwidgets{Web::UI::MWidgets()};
    auto         mainwindow{Web::UI::MainWindow(&mwidgets)};

    mwidgets.setMainWindow(&mainwindow);
    mwidgets.setText();

    mainwindow.setTreeView();

    mainwindow.show();
    return app.exec();
}
