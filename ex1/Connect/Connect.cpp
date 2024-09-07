#include "Connect.h"

QT_BEGIN_NAMESPACE
using namespace Ex1::Inner::Action;
QT_END_NAMESPACE;

void Connections::view2model(QAbstractItemModel &_model, QAbstractItemView &_view) {
  _view.setModel(&_model);
}
