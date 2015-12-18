#include <QtCore/QDebug>
#include <QtCore/QFile>

#include "ZipImpl.h"

namespace QMiniZip
{

ZipImpl::ZipImpl(Zip* d) :
        m_d(d),
        m_isOpen(false),
        m_mode(Zip::CREATE),
        m_zipFh(NULL),
        m_errcode(0),
        m_compressLevel(Z_DEFAULT_COMPRESSION)
{
}

ZipImpl::~ZipImpl()
{
    if(m_isOpen)
    {
        close();
    }
}

const QString& ZipImpl::zipName() const
{
    return m_name;
}

void ZipImpl::setZipName(const QString& name)
{
    m_name = name;
}

bool ZipImpl::close()
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

int ZipImpl::lastErrorCode() const
{
    return m_errcode;
}

void ZipImpl::resetErrorCode()
{
    m_errcode = 0;
}

bool ZipImpl::open(Zip::Mode mode)
{
    resetErrorCode();

    int overwrite = 0;
    switch(mode)
    {
    case Zip::CREATE:
        overwrite = 0;
        break;
    case Zip::APPEND:
        overwrite = APPEND_STATUS_ADDINZIP;
        break;
    default:
    {
        qWarning()<<"Mode "<<mode<<" not implemented";
        m_errcode = Zip::NOT_IMPLEMENTED;
        return false;
    }
    }

    if(m_name.isNull() || m_name.isEmpty())
    {
        qWarning()<<"Zip name not set";
        m_errcode = Zip::ZIP_NAME_NOT_SET;
        return false;
    }

    if((mode == Zip::APPEND) && !checkFileExists(m_name))
    {
        overwrite = 1;
    }

    if((mode == Zip::CREATE) && checkFileExists(m_name))
    {
        if(!QFile::remove(m_name))
        {
            qWarning()<<"Can not delete the file"<<m_name;
            m_errcode = Zip::CAN_NOT_DELETE_FILE;
            return false;
        }
    }

    const std::string fileName = m_name.toStdString();

    m_zipFh = zipOpen64(fileName.c_str(), overwrite);

    if (m_zipFh == NULL)
    {
        m_errcode = Zip::OPEN_FILE;
        qWarning()<<"Error opening file"<<m_name;
        return false;
    }

    m_mode = mode;
    m_isOpen = true;
    return true;
}

Zip::Mode ZipImpl::mode() const
{
    return m_mode;
}


bool ZipImpl::checkFileExists(const QString& name) const
{
    return QFile::exists(name);
}

zipFile ZipImpl::handler() const
{
    return m_zipFh;
}

void ZipImpl::setCompressLevel(quint32 level)
{
    Q_ASSERT(level>=0 && level<9);

    m_compressLevel = level;
}

quint32 ZipImpl::compressLevel() const
{
    return m_compressLevel;
}

} /* namespace QMiniZip */
