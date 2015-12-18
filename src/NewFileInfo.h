#ifndef NEWFILEINFO_H_
#define NEWFILEINFO_H_

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QFileInfo>

namespace QMiniZip
{

class NewFileInfo
{
public:

    NewFileInfo(const QString& fileName);

    const QDateTime& dateTime() const;
    void setDateTime(const QDateTime& dt);

    QFile::Permissions permissions() const;
    void setPermissions(const QFile::Permissions& permissions);

    QString fileName() const;

    bool isDir() const;

private:

    void init();

private:

    QFileInfo m_fileInfo;
    QDateTime m_dateTime;
    QFile::Permissions m_permissions;
};

} /* namespace QMiniZip */

#endif
