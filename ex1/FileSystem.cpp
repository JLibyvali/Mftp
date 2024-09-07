#include "Exception.h"
#include "FileSystem.h"
#include "windowtr.h"
#include <qlogging.h>


QT_BEGIN_NAMESPACE
using namespace Ex1::Inner;

void FileSystem::setfunc(QWidget *parent) {
  fsmodel = new QFileSystemModel(parent);
  fsmodel->setObjectName(Tr::tr("Filesystem Model"));
  QDir::setCurrent("/home");
  fsmodel->setRootPath(QDir::currentPath());
  fsmodel->setReadOnly(true);
}

void FileSystem::la() {
  if (fsmodel == nullptr)
    throw NullPointer();
  fsmodel->setFilter(QDir::AllDirs | QDir::Files | QDir::Hidden |
                     QDir::NoDotAndDotDot);
}

void FileSystem::lsmsp() {
  if (fsmodel == nullptr)
    throw NullPointer();
  fsmodel->setFilter(QDir::AllDirs | QDir::Files | QDir::Hidden |
                     QDir::NoDotAndDotDot);
  QStringList _filters;
  _filters << "*.msp";
  fsmodel->setNameFilters(_filters);
  fsmodel->setNameFilterDisables(true);
}

void FileSystem::treeviewClicked(const QModelIndex &_index) {
  qDebug() << "You clicked!\n";
}

QT_END_NAMESPACE