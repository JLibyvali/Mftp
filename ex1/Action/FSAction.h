#pragma once

#include <qtconfigmacros.h>

QT_BEGIN_NAMESPACE

namespace Ex1::Inner {
class FileSystem;
class FileOptions;
} // namespace Ex1::Inner

namespace Ex1::Inner::Action {
class FSHandler {
public:
  FSHandler(){
  }
  ~FSHandler() = default;


private:


  FileSystem *fs;
  FileOptions *fops;
};

} // namespace Ex1::Inner::Action

QT_END_NAMESPACE
