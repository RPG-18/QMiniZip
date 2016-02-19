#pragma once

#include "ZipFile.h"
#include "FileInfo.h"

namespace QMiniZip
{

class ZipReadIterator
{
public:

    static const size_t ZIP_FILE_NAME_LENGHT = 1024;
    static const size_t READ_BLOCK_SIZE = 2048;

    ZipReadIterator(ZipFile& file);

    bool toBegin();
    bool next();

    FileInfo fileInfo();

    /*!
     * Open for reading data the current file in the zipfile
     */
    bool openCurrentFile();

    /*!
     * Read bytes from the current file
     */
    qint64 read(char * data, qint64 maxSize);

    /*!
     * REad all bytes from the current file
     */
    QByteArray readAll();

private:

    void resetErrorCode();

private:

    ZipFile& m_file;
    int m_errorCode;
};

}