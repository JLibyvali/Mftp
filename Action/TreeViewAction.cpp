#include "Exception.h"
#include "FileSystem.h"
#include "TreeViewAction.h"
#include "UI_MWidgets.h"
#include "constants.h"

QT_BEGIN_NAMESPACE
using namespace Web::UI;

Action::TreeView_FS::TreeView_FS(MWidgets *_mwidget) : m_mwidget(_mwidget), m_fs(new FS::FileSystem()) {}

void Action::TreeView_FS::setfunc()
{
    if (m_mwidget == nullptr || m_fs == nullptr)
        throw NullPointer();

    // FileSystem Model
    m_fs->fsmodel->setObjectName("FileSystem Model");
    m_fs->fsmodel->setRootPath(ViewRoot);
    m_fs->fsmodel->setReadOnly(true);

    m_fs->la();

    // Treeview
    m_mwidget->u_treeview->setModel(m_fs->fsmodel);
    m_mwidget->u_treeview->setRootIndex(m_fs->fsmodel->index(ViewRoot));
    
    auto fsmodel_columns = m_fs->fsmodel->columnCount();
    for (int i = 1; i < fsmodel_columns; i++)
    {
        m_mwidget->u_treeview->setColumnHidden(i, true);
    }
    m_mwidget->u_treeview->setAnimated(true);
}

QT_END_NAMESPACE