#include "Zip.h"
#include "ZipImpl.h"

namespace QMiniZip
{

Zip::Zip() :
        m_impl(new ZipImpl(this))
{

}

Zip::Zip(const QString& zipName) :
        m_impl(new ZipImpl(this))
{
    m_impl->setZipName(zipName);
}

const QString& Zip::zipName() const
{
    return m_impl->zipName();
}

void Zip::setZipName(const QString& zipName)
{
    m_impl->setZipName(zipName);
}

Zip::ZipHandler Zip::handler()
{
    return m_impl->handler();
}

Zip::Mode Zip::mode() const
{
    return m_impl->mode();
}

quint32 Zip::compressLevel() const
{
    return m_impl->compressLevel();
}

void Zip::setCompressLevel(quint32 level)
{
    m_impl->setCompressLevel(level);
}

bool Zip::open(Mode mode)
{
    return m_impl->open(mode);
}

} /* namespace QMiniZip */
