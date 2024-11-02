#pragma once
#include <QWidget>

QT_BEGIN_NAMESPACE

namespace Web
{
struct Tr;
class Exception;
class Person;

namespace UI
{
class Menus;
class MWidgets;

namespace Action
{
class TreeView_FS;
}
}  // namespace UI

namespace FS
{
class FileSystem;
}

#define MainWindowSize 800, 600

#define MenuBarSize    0, 0, 800, 23

const QString ViewRoot {"/home"};
}  // namespace Web

QT_END_NAMESPACE