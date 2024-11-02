#pragma once

#include "MainWindow.h"
#include "TreeViewAction.h"
#include "UI_base.h"

// Qt Widget include
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTextBrowser>
#include <QToolButton>
#include <QTreeView>
#include <QWidget>

QT_BEGIN_NAMESPACE

namespace Web::UI
{
class Menus
{
public:

    explicit Menus(QMenuBar *parent = nullptr) : u_menubar(parent) {}

    void      setfunc();
    QMenuBar *u_menubar;
    QMenu    *u_menuOpt1;
};

class MWidgets : public UI_Base
{
public:

    MWidgets() = default;
    /**
     * @brief Set the Main Window object
     * 
     * @param parent , Must passed in existed MainWindow
     */
    void setMainWindow(QMainWindow *parent = nullptr);
    void setText() override;

private:

    friend class Action::TreeView_FS;
    friend class MainWindow;
    void          setMenu(QMenuBar *_menu);
    void          setfunc(QWidget *parent = nullptr) override;
    QWidget      *u_widget;
    QGridLayout  *u_gridlayout;
    QTreeView    *u_treeview;
    QTextBrowser *u_textbrowser;
    QToolButton  *u_toolbutton;
    QLabel       *u_label1, *u_label2;
    QFrame       *u_line;

    Menus        *u_Menus;
};

}  // namespace Web::UI

QT_END_NAMESPACE