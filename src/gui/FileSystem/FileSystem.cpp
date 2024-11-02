#include "Exception.h"
#include "FileSystem.h"
#include "windowtr.h"

#include <QMessageBox>
#include <qmessagebox.h>
#include <qnumeric.h>

QT_BEGIN_NAMESPACE
using namespace Web::FS;
QT_END_NAMESPACE

void FileSystem::la()
{
    if (fsmodel == nullptr)
        throw NullPointer();
    fsmodel->setFilter(QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot);
}

void FileSystem::lsmsp()
{
    if (fsmodel == nullptr)
        throw NullPointer();

    QStringList _filters;
    _filters << "*.msp";
    fsmodel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    fsmodel->setNameFilters(_filters);
    fsmodel->setNameFilterDisables(true);
}

void FileSystem::on_treeviewClicked(const QModelIndex &_index) { qInfo("@@@@@@@@@@@@@@@@@\n\tTest Slots called\n@@@@@@@@@@@@@@@@"); }