#include "ZipFile.h"

#include "ZipFileImpl.h"

namespace QMiniZip
{

ZipFile::ZipFile() :
        m_impl(new ZipFileImpl(this))
{

}

ZipFile::ZipFile(const QString& zipName) :
        m_impl(new ZipFileImpl(this))
{
    m_impl->setZipName(zipName);
}

ZipFile::~ZipFile() = default;

const QString& ZipFile::zipName() const
{
    return m_impl->zipName();
}

void ZipFile::setZipName(const QString& zipName)
{
    m_impl->setZipName(zipName);
}

ZipFile::ZipHandler ZipFile::handler()
{
    return m_impl->handler();
}

ZipFile::Mode ZipFile::mode() const
{
    return m_impl->mode();
}

quint32 ZipFile::compressLevel() const
{
    return m_impl->compressLevel();
}

void ZipFile::setCompressLevel(quint32 level)
{
    m_impl->setCompressLevel(level);
}

bool ZipFile::open(Mode mode)
{
    return m_impl->open(mode);
}

} /* namespace QMiniZip */
