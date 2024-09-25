#pragma once

#include "constants.h"

#include <QMainWindow>

namespace Web::UI
{

class MainWindow : public QMainWindow
{
public:

    // MainWindow() = delete;
    explicit MainWindow(MWidgets *_mwidgets,QMainWindow *parent = nullptr);

    void setTreeView(Action::TreeView_FS * _treefs = nullptr);


private:
    /**
     * @brief Set Ui Signals and Slots
     * 
     * @param m_mwidgets , Must existed MWidget Object
     */
    void setSignals(Action::TreeView_FS * _sigSrc);

    MWidgets *m_mwidgets = nullptr;
};

}  // namespace Web::UI