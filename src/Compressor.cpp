#include <vector>

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QDebug>

#include "zip.h"

#include "NewFileInfo.h"
#include "Compressor.h"
#include "ZipFile.h"

namespace
{

void writeData(QMiniZip::ZipFile& zip, QIODevice& in)
{
    std::vector<char> buffer(QMiniZip::Compressor::WRITE_BUFFER_SIZE, 0);
    auto handler = zip.handler();

    while (!in.atEnd())
    {
        const quint64 cnt = in.read(buffer.data(),
                QMiniZip::Compressor::WRITE_BUFFER_SIZE);

        if (cnt > 0)
        {
            int err = zipWriteInFileInZip(handler, buffer.data(), cnt);
            if (err != ZIP_OK)
            {
                qWarning() << "Error in writing" << zip.zipName()
                        << "in the zipfile";
                break;
            }
        }
    }
}
}
namespace QMiniZip
{

bool Compressor::compressFile(ZipFile& zip, const NewFileInfo& file,
        const QString& baseDir)
{
    zip_fileinfo zipInfo =
    { 0 };

    auto dt = file.dateTime();
    zipInfo.tmz_date.tm_hour = dt.time().hour();
    zipInfo.tmz_date.tm_min = dt.time().minute();
    zipInfo.tmz_date.tm_sec = dt.time().second();

    zipInfo.tmz_date.tm_mday = dt.date().day();
    zipInfo.tmz_date.tm_mon = dt.date().month() - 1;
    zipInfo.tmz_date.tm_year = dt.date().year();

    zipInfo.dosDate = 0;
    zipInfo.external_fa = file.permissions();

    QString saveFilenameInZip = file.fileName();

    if (!baseDir.isNull() && !baseDir.isEmpty())
    {
        QDir dir(baseDir);
        saveFilenameInZip = dir.relativeFilePath(saveFilenameInZip);
    }

    const std::string fn = saveFilenameInZip.toStdString();
    const quint32 level = zip.compressLevel();
    int err = zipOpenNewFileInZip3_64(zip.handler(), fn.c_str(), &zipInfo,
    NULL, 0, NULL, 0, NULL /* comment*/, level != 0 ? Z_DEFLATED : 0, level, 0,
            -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, 0, 0, 0);

    if (err != ZIP_OK)
    {
        qWarning() << "Error in opening"
                << zip.zipName() << "in zipfile, code:"
                << err;
        return false;
    }

    if (!file.isDir())
    {
        QFile inFile(file.fileName());
        if (!inFile.open(QIODevice::ReadOnly))
        {
            qWarning() << "Error in opening" << file.fileName()
                    << "for reading";
            return false;
        }

        writeData(zip, inFile);
        inFile.close();
    }

    err = zipCloseFileInZip(zip.handler());

    if (err != ZIP_OK)
    {
        qWarning() << "Error in closing" << zip.zipName()
                << "in the zipfile, code:" << err;
        return false;
    }

    return true;
}

} /* namespace QMiniZip */
