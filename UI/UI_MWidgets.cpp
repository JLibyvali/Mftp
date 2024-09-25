#include "Exception.h"
#include "UI_MWidgets.h"
#include "constants.h"
#include "windowtr.h"

QT_BEGIN_NAMESPACE

void Web::UI::MWidgets::setMainWindow(QMainWindow *parent)
{

    if (parent == nullptr)
        throw NullPointer();
    // MainWindow
    if (parent->objectName().isEmpty())
        parent->setObjectName(Tr::tr("Mainwindow"));
    parent->resize(MainWindowSize);
    parent->setWindowTitle(Tr::tr("M-server"));
    setfunc(parent);

    // Menu
    u_Menus = new Menus(new QMenuBar(parent));
    u_Menus->setfunc();

    parent->setCentralWidget(u_widget);
    parent->setMenuBar(u_Menus->u_menubar);
    QMetaObject::connectSlotsByName(parent);
}

void Web::UI::MWidgets::setfunc(QWidget *parent)
{

    if (parent == nullptr)
        throw NullPointer();

    // Central Widget
    u_widget = new QWidget(parent);
    u_widget->setObjectName(Tr::tr("Main Widget"));

    // Grid Layout
    u_gridlayout = new QGridLayout(u_widget);
    u_gridlayout->setObjectName(Tr::tr("Grid Layout"));

    // Others
    u_label1 = new QLabel(u_widget);
    u_label1->setObjectName(Tr::tr("Label 1"));
    u_label2 = new QLabel(u_widget);
    u_label2->setObjectName(Tr::tr("label 2"));
    u_treeview = new QTreeView(u_widget);
    u_treeview->setObjectName(Tr::tr("Tree View"));
    u_textbrowser = new QTextBrowser(u_widget);
    u_textbrowser->setObjectName(Tr::tr("Text Browser"));
    u_toolbutton = new QToolButton(u_widget);
    u_toolbutton->setObjectName(Tr::tr("Tool button"));
    u_line = new QFrame(u_widget);
    u_line->setObjectName(Tr::tr("Horizontal line"));

    // add widgets to gridlayout
    u_gridlayout->addWidget(u_label1, 0, 0, 1, 1);
    u_gridlayout->addWidget(u_label2, 0, 1, 1, 1);
    u_gridlayout->addWidget(u_treeview, 2, 0, 1, 1);
    u_gridlayout->addWidget(u_textbrowser, 2, 1, 1, 1);
    u_gridlayout->addWidget(u_toolbutton, 3, 0, 1, 2);
    u_gridlayout->addWidget(u_line, 1, 0, 1, 2);

    // Toolbutton and Line
    QSizePolicy _size(QSizePolicy::Preferred, QSizePolicy::Fixed);
    _size.setHorizontalStretch(0);
    _size.setVerticalStretch(0);
    _size.setHeightForWidth(u_toolbutton->hasHeightForWidth());
    u_toolbutton->setSizePolicy(_size);

    _size.setHeightForWidth(u_line->hasHeightForWidth());
    u_line->setSizePolicy(_size);
    u_line->setFrameShape(QFrame::Shape::HLine);
    u_line->setFrameShadow(QFrame::Sunken);
}

void Web::UI::MWidgets::setText()
{

    u_label1->setText(Tr::tr("File Lists"));
    u_label2->setText(Tr::tr("Show File content"));
    u_toolbutton->setText(Tr::tr("Lists"));
    u_Menus->u_menuOpt1->setTitle(Tr::tr("Options"));
}

QT_END_NAMESPACE