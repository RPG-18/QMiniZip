#include <QtCore/QDebug>
#include <QtCore/QByteArray>

#include "unzip.h"
#include "ZipReadIterator.h"

namespace QMiniZip
{
ZipReadIterator::ZipReadIterator(ZipFile& file):
    m_file(file),
    m_errorCode(0)
{

}

bool ZipReadIterator::toBegin()
{
    resetErrorCode();

    if(m_file.mode() != ZipFile::UNZIP)
    {
        return false;
    }

    const int err = unzGoToFirstFile(m_file.handler());
    if(err != UNZ_OK)
    {
        m_errorCode = err;
        return false;
    }

    return true;
}

void ZipReadIterator::resetErrorCode()
{
    m_errorCode = 0;
}

bool ZipReadIterator::next()
{
    resetErrorCode();
    if(m_file.mode() != ZipFile::UNZIP)
    {
        return false;
    }

    const int err = unzGoToNextFile(m_file.handler());
    if(err != UNZ_OK)
    {
        m_errorCode = err;
        return false;
    }

    return true;
}

FileInfo ZipReadIterator::fileInfo()
{
    resetErrorCode();
    QByteArray fileName(ZIP_FILE_NAME_LENGHT, 0);

    unz_file_info64 file_info = {0};
    const int err = unzGetCurrentFileInfo64(m_file.handler(), &file_info,
                                            fileName.data(),
                                            fileName.size(),
                                            NULL, 0, NULL, 0);

    if(err != UNZ_OK)
    {
        m_errorCode = err;
        return FileInfo();
    }

    FileInfo fInfo(QString::fromUtf8(fileName));
    fInfo.setCompressedSize(file_info.compressed_size);
    fInfo.setUncompressedSize(file_info.uncompressed_size);

    return fInfo;
}

bool ZipReadIterator::openCurrentFile()
{
    const int err = unzOpenCurrentFile(m_file.handler());
    if(err != UNZ_OK)
    {
        m_errorCode = err;
    }

    return true;
}

qint64 ZipReadIterator::read(char* data, qint64 maxSize)
{
    resetErrorCode();
    const qint64 cnt = unzReadCurrentFile(m_file.handler(), data, maxSize);
    if(cnt>=0)
    {
        return cnt;
    }

    m_errorCode = UNZ_ERRNO;
    return -1;
}

QByteArray ZipReadIterator::readAll()
{
    resetErrorCode();

    QByteArray data;
    QByteArray buff(READ_BLOCK_SIZE, 0);
    while(qint64 cnt = read(buff.data(), buff.size()))
    {
        if(m_errorCode!=0)
        {
            break;
        }

        data.append(buff.data(), cnt);
    }

    return data;
}


}
