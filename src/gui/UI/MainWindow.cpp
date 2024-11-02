#include "FileSystem.h"
#include "MainWindow.h"
#include "TreeViewAction.h"
#include "UI_MWidgets.h"

#include <QObject>
#include <QOverload>
#include <QTreeView>

using namespace Web::UI;

MainWindow::MainWindow(MWidgets *_mwidgets, QMainWindow *parent) : m_mwidgets(_mwidgets), QMainWindow(parent) {}

void MainWindow::setTreeView(Action::TreeView_FS *_treefs)
{
    if (_treefs == nullptr)
        _treefs = new Action::TreeView_FS(m_mwidgets);

    _treefs->setfunc();
    setSignals(_treefs);
}

void MainWindow::setSignals(Action::TreeView_FS *_sigSrc)
{
    QObject::connect(
        _sigSrc->m_mwidget->u_treeview, &QTreeView::clicked, _sigSrc->m_fs, &Web::FS::FileSystem::on_treeviewClicked
    );
}