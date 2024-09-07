#pragma once

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QObject>

QT_BEGIN_NAMESPACE

namespace Ex1::Inner::Action {
class Connections : public QObject {
public:
  Connections(QWidget *parent = nullptr) : QObject(parent) {}
  ~Connections() = default;

  void view2model(QAbstractItemModel &_model, QAbstractItemView &_view);
};

} // namespace Ex1::Inner::Action

QT_END_NAMESPACE
