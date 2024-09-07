#pragma once
#include <QDebug>
#include <QException>

QT_BEGIN_NAMESPACE
namespace Ex1 {

class Exception : public QException {
public:
  void raise() const override { throw *this; }
  Exception *clone() const override { return (new Exception(*this)); }

  virtual QString message() { return *m_msg; }

protected:
  QString *m_msg;
};

class NullPointer final : public Exception {
public:
  NullPointer() = default;
  QString message() override {
    *m_msg = "it's NULL_Pointer exceptions\n";
    qDebug() << m_msg;
    return *m_msg;
  }
};

} // namespace Ex1

QT_END_NAMESPACE