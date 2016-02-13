#include <QtCore/QDebug>
#include <QtCore/QFile>

#include "ZipFileImpl.h"

namespace QMiniZip
{

ZipFileImpl::ZipFileImpl(ZipFile* d) :
        m_d(d),
        m_isOpen(false),
        m_mode(ZipFile::CREATE),
        m_zipFh(NULL),
        m_errcode(0),
        m_compressLevel(Z_DEFAULT_COMPRESSION)
{
}

ZipFileImpl::~ZipFileImpl()
{
    if(m_isOpen)
    {
        close();
    }
}

const QString& ZipFileImpl::zipName() const
{
    return m_name;
}

void ZipFileImpl::setZipName(const QString& name)
{
    m_name = name;
}

bool ZipFileImpl::close()
{
    if(!m_isOpen)
    {
        qWarning()<<"Zip"<<m_name<<"not open";
        return false;
    }

    int m_errcode = zipClose(m_zipFh, NULL);
    if (m_errcode != ZIP_OK)
    {
        qWarning()<<"Error in closing"<<m_name<<"code:"<<m_errcode;
        return false;
    }
    return true;
}

int ZipFileImpl::lastErrorCode() const
{
    return m_errcode;
}

void ZipFileImpl::resetErrorCode()
{
    m_errcode = 0;
}

bool ZipFileImpl::open(ZipFile::Mode mode)
{
    resetErrorCode();

    int overwrite = 0;
    switch(mode)
    {
    case ZipFile::CREATE:
        overwrite = 0;
        break;
    case ZipFile::APPEND:
        overwrite = APPEND_STATUS_ADDINZIP;
        break;
    default:
    {
        qWarning()<<"Mode "<<mode<<" not implemented";
        m_errcode = ZipFile::NOT_IMPLEMENTED;
        return false;
    }
    }

    if(m_name.isNull() || m_name.isEmpty())
    {
        qWarning()<<"Zip name not set";
        m_errcode = ZipFile::ZIP_NAME_NOT_SET;
        return false;
    }

    if((mode == ZipFile::APPEND) && !checkFileExists(m_name))
    {
        overwrite = 1;
    }

    if((mode == ZipFile::CREATE) && checkFileExists(m_name))
    {
        if(!QFile::remove(m_name))
        {
            qWarning()<<"Can not delete the file"<<m_name;
            m_errcode = ZipFile::CAN_NOT_DELETE_FILE;
            return false;
        }
    }

    const std::string fileName = m_name.toStdString();

    m_zipFh = zipOpen64(fileName.c_str(), overwrite);

    if (m_zipFh == NULL)
    {
        m_errcode = ZipFile::OPEN_FILE;
        qWarning()<<"Error opening file"<<m_name;
        return false;
    }

    m_mode = mode;
    m_isOpen = true;
    return true;
}

ZipFile::Mode ZipFileImpl::mode() const
{
    return m_mode;
}


bool ZipFileImpl::checkFileExists(const QString& name) const
{
    return QFile::exists(name);
}

zipFile ZipFileImpl::handler() const
{
    return m_zipFh;
}

void ZipFileImpl::setCompressLevel(quint32 level)
{
    Q_ASSERT(level>=0 && level<9);

    m_compressLevel = level;
}

quint32 ZipFileImpl::compressLevel() const
{
    return m_compressLevel;
}

} /* namespace QMiniZip */
