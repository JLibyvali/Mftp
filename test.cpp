#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QtLogging>



int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    QWidget      window;
    auto         button = new QPushButton(&window);
    auto         msg    = new QMessageBox();
    window.setObjectName("window");
    window.resize(1024, 600);
    button->setObjectName("Button");
    button->setEnabled(true);
    button->setGeometry(100, 100, 700, 300);

    msg->setObjectName("Msg");
    msg->setEnabled(true);
    msg->setText("Test box");
    QObject::connect(button, SIGNAL(clicked()), msg, SLOT(show()));
    window.show();
    app.exec();
}