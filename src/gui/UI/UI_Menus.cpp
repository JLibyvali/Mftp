#include "Exception.h"
#include "UI_MWidgets.h"
#include "constants.h"
#include "windowtr.h"

QT_BEGIN_NAMESPACE
using namespace Web::UI;

void Menus::setfunc() {
  if (u_menubar == nullptr)
    throw NullPointer();

  u_menubar->setObjectName(Tr::tr("Menu Bar"));
  u_menubar->setGeometry(MenuBarSize);
  u_menubar->setEnabled(true);

  u_menuOpt1 = new QMenu(u_menubar);
  u_menuOpt1->setObjectName(Tr::tr("Menu Option 1"));
  u_menuOpt1->setTitle(Tr::tr("Options"));

  u_menubar->addAction(u_menuOpt1->menuAction());
}
QT_END_NAMESPACE
