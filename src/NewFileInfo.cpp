#include "NewFileInfo.h"

namespace QMiniZip
{

NewFileInfo::NewFileInfo(const QString& fileName):
        m_fileInfo(fileName)
{
    init();
}

void NewFileInfo::init()
{
    m_dateTime = m_fileInfo.lastModified();
    m_permissions = m_fileInfo.permissions();
}

const QDateTime& NewFileInfo::dateTime() const
{
    return m_dateTime;
}

void NewFileInfo::setDateTime(const QDateTime& dt)
{
    m_dateTime = dt;
}

QString NewFileInfo::fileName() const
{
    return m_fileInfo.absoluteFilePath();
}

QFile::Permissions NewFileInfo::permissions() const
{
    return m_permissions;
}

void NewFileInfo::setPermissions(const QFile::Permissions& permissions)
{
    m_permissions = permissions;
}

bool NewFileInfo::isDir() const
{
    return m_fileInfo.isDir();
}

} /* namespace QMiniZip */
