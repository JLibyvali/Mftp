#pragma once

#include "constants.h"

#include <QCoreApplication>
#include <QTreeView>

QT_BEGIN_NAMESPACE

namespace Web::UI
{
class MWidgets;
class MainWindow;

namespace Action
{
class TreeView_FS
{
public:

    TreeView_FS() = delete;

    /**
     * @brief Construct a new TreeView_FS object
     *
     * @param _mwidget  Must passed Existed MWidgets
     */
    explicit TreeView_FS(UI::MWidgets *_mwidget);
    ~TreeView_FS() = default;
    /**
     * @brief Set Basic FileSystem
     *
     */
    void setfunc();

private:

    friend class UI::MainWindow;
    UI::MWidgets   *m_mwidget = nullptr;
    FS::FileSystem *m_fs;
};

}  // namespace Action
}  // namespace Web::UI

QT_END_NAMESPACE