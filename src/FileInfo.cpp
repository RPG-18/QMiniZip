#include "FileInfo.h"

namespace QMiniZip
{

FileInfo::FileInfo():
    m_isNull(true),
    m_compressedSize(0),
    m_uncompressedSize(0)
{
}

FileInfo::FileInfo(const QString& fileName):
    m_isNull(false),
    m_fileName(fileName),
    m_compressedSize(0),
    m_uncompressedSize(0)
{
}

bool FileInfo::isNull() const
{
    return m_isNull;
}

const QString& FileInfo::name() const
{
    return m_fileName;
}

quint64 FileInfo::compressedSize() const
{
    return m_compressedSize;
}

void FileInfo::setCompressedSize(quint64 size)
{
    m_compressedSize = size;
}

quint64 FileInfo::uncompressedSize() const
{
    return m_uncompressedSize;
}

void FileInfo::setUncompressedSize(quint64 size)
{
    m_uncompressedSize = size;
}

}
