#pragma once
#include "Ui.h"
#include <QDir>
#include <QFileInfo>
#include <QFileSystemModel>
#include <qabstractitemmodel.h>
#include <qobject.h>
#include <qwidget.h>

QT_BEGIN_NAMESPACE

namespace Ex1::Inner {

class FileSystem final : public Ui,public QWidget {
  Q_OBJECT
public:
  friend class MWidgets;
  FileSystem() = default;
  ~FileSystem() override = default;
  void la();
  void lsmsp();
  void setfunc(QWidget *parent = nullptr) override;

public slots:
  void treeviewClicked(const QModelIndex& _index);
private: 
  QFileSystemModel *fsmodel;

};

class FileOptions final : public Ui {

public:
  FileOptions() = default;
  void setfunc(QWidget *parent = nullptr) override;
  void setText() override;
private: 
  QFile *fileoption;
  QTextStream *textstream;
  QDataStream *datastream;
  QImageReader *imagereader;
};

class IODevice final : public Ui {
public:
  IODevice() = default;
  void setfunc(QWidget *parent = nullptr) override;
  void setText() override;
};

} // namespace Ex1::Inner

QT_END_NAMESPACE