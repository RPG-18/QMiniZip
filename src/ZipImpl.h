#ifndef ZIPIMPL_H_
#define ZIPIMPL_H_

#include <QtCore/QString>

#include "zip.h"
#include "Zip.h"

namespace QMiniZip
{

class ZipImpl
{
public:

    ZipImpl(Zip* d);
    ~ZipImpl();

    const QString& zipName() const;
    void setZipName(const QString& name);

    bool open(Zip::Mode mode);

    Zip::Mode mode() const;


    bool close();

    int lastErrorCode() const;

    /*!
     * Set compress level
     * @param level value in [0, 9]
     */
    void setCompressLevel(quint32 level);
    quint32 compressLevel() const;

    bool isOpen() const;

    zipFile handler() const;

private:

    void resetErrorCode();

    bool checkFileExists(const QString& name) const;

private:

    Zip* m_d;
    bool m_isOpen;
    Zip::Mode m_mode;
    QString m_name;

    zipFile m_zipFh;
    int m_errcode;
    quint32 m_compressLevel;
};

}

#endif
