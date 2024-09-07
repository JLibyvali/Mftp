#pragma once

#include "Connect.h"
#include <QToolButton>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>
#include <qobject.h>
#include <qtypes.h>
#include <qwidget.h>

// Avoid importing too many user headers.

QT_BEGIN_NAMESPACE

namespace Ex1::Inner {

template <typename Datatype> class DataStore {
public:
  explicit DataStore(Datatype &&_data) noexcept : _datastore(new QList<Datatype>()) {
    _datastore->push_back(std::move(_data));
  }
  ~DataStore();

  qsizetype append(Datatype &&_data) {
    _datastore->push_back(std::move(_data));
    return (_datastore->back());
  }

  Datatype get(qsizetype _index) { return (_datastore->at(_index)); }

private:
  QList<Datatype> *_datastore;
};

class Ui{
public:
  Ui() = default;
  virtual ~Ui() = default;

  virtual void setfunc(QWidget *parent = nullptr) = 0;
  virtual void setText() {};
};

} // namespace Ex1::Inner

namespace Ex1::Inner {

class FileSystem;

class MWidgets final : public Ui {
public:
  MWidgets(){}
  ~MWidgets() override = default;

  void setfunc(QWidget *parent = nullptr) override;
  void setText() override;
  void setFS();

private:
  QVBoxLayout *verticalLayout;
  QToolButton *toolbutton;
  QTreeView *treeview;

  // Other
  Action::Connections *con = nullptr;
  FileSystem *fs;
};

} // namespace Ex1::Inner

QT_END_NAMESPACE