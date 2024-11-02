#pragma once

#include <QWidget>

// Avoid importing too many user headers.

QT_BEGIN_NAMESPACE

namespace Web::UI {

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

class UI_Base {
public:
    virtual void setfunc(QWidget *parent = nullptr) = 0;
    virtual void setText() = 0;
};

} // namespace Web::UI

QT_END_NAMESPACE