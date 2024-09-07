#include "Exception.h"
#include "Ui.h"
#include <QApplication>
#include <QWidget>
#include <qwidget.h>

QT_BEGIN_NAMESPACE
using namespace Ex1::Inner::Action;

class Start : QWidget {
public:
  Start(QWidget *parent = nullptr)
      : QWidget(parent), ui(new Ex1::Inner::MWidgets) {
    try {
      ui->setfunc(parent);
      ui->setText();
      ui->setFS();

    } catch (Ex1::Exception &ex) {
      ex.message();
    }
  }

private:
  Ex1::Inner::MWidgets *ui;
};
QT_END_NAMESPACE

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  QWidget widget;
  Start window(&widget);
  widget.resize(1080,600);
  widget.show();

  return app.exec();
}
