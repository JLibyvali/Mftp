#include "Connect.h"
#include "Exception.h"
#include "FileSystem.h"
#include "Ui.h"
#include "windowtr.h"
#include <QSizePolicy>

QT_BEGIN_NAMESPACE
using namespace Ex1::Inner;

void MWidgets::setfunc(QWidget *parent) {
  verticalLayout = new QVBoxLayout(parent);
  verticalLayout->setObjectName(Tr::tr("verticallayout"));

  QSizePolicy _size(QSizePolicy::Expanding, QSizePolicy::Expanding);
  _size.setHorizontalStretch(0);
  _size.setVerticalStretch(0);

  treeview = new QTreeView(parent);
  treeview->setObjectName(Tr::tr("Tree View"));
  _size.setHeightForWidth(treeview->hasHeightForWidth());
  treeview->setSizePolicy(_size);

  toolbutton = new QToolButton(parent);
  toolbutton->setObjectName(Tr::tr("ToolButton"));
  _size.setHorizontalPolicy(QSizePolicy::Preferred);
  _size.setVerticalPolicy(QSizePolicy::Preferred);
  toolbutton->setSizePolicy(_size);

  verticalLayout->addWidget(treeview);
  verticalLayout->addWidget(toolbutton);
}

void MWidgets::setText() { toolbutton->setText(Tr::tr("Lists")); }

// Other
void MWidgets::setFS() {

  fs = new FileSystem();
  fs->setfunc();
  fs->lsmsp();

  // connect view and model
  if (treeview == nullptr)
    throw NullPointer();
  con = new Action::Connections();
  con->view2model(*(fs->fsmodel), *treeview);

  // connect
  con->connect(treeview, SIGNAL(clicked(QModelIndex)), fs, SLOT(treeviewClicked(QModelIndex)));
}

QT_END_NAMESPACE