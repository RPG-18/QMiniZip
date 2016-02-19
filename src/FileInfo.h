#pragma once

#include <QtCore/QString>
#include <QtCore/QDateTime>

namespace QMiniZip
{

class FileInfo
{
public:

    FileInfo();

    FileInfo(const QString& fileName);

    bool isNull() const;

    const QString& name() const;

    quint64 compressedSize() const;
    void setCompressedSize(quint64 size);

    quint64 uncompressedSize() const;
    void setUncompressedSize(quint64 size);

private:

    bool m_isNull;
    QString m_fileName;
    quint64 m_compressedSize;
    quint64 m_uncompressedSize;
    QDateTime m_dt;
};

}
