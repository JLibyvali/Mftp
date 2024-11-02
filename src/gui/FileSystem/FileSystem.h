#pragma once

#include <QDir>
#include <QFileSystemModel>
#include <QFileSystemWatcher>

QT_BEGIN_NAMESPACE

namespace Web::FS {
class FileSystem final : public QObject {
    Q_OBJECT
public:
    // Remember Init FileSystemModel Property
    FileSystem(QObject *parent = nullptr) : QObject(parent), fsmodel(new QFileSystemModel(parent)) {}
    ~FileSystem() = default;
    void la();
    void lsmsp();

    QFileSystemModel *fsmodel;
public slots:
    void on_treeviewClicked(const QModelIndex &_index);
};

template <typename DataType> class FileOptions {

public:
    FileOptions() = default;

    DataType read();
    int write(DataType &&_data);
    int append(DataType &&_data);

private:
    QFile *fileoption;
    QTextStream *textstream;
    QDataStream *datastream;
    QImageReader *imagereader;
};

class IODevice {
public:
    IODevice() = default;
};

} // namespace Web::FS
