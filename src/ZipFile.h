#pragma once

#include <memory>

#include <QtCore/QString>

namespace QMiniZip
{

class ZipImplImpl;
class ZipFile
{
    friend class ZipImplImpl;

public:

    typedef void* ZipHandler;

    enum Mode
    {
        UNZIP,
        CREATE,
        APPEND
    };

    enum ErrorCode
    {
        OPEN_FILE,
        CAN_NOT_DELETE_FILE,
        FILE_NOT_EXISTS,
        ZIP_NAME_NOT_SET = 127,
        NOT_IMPLEMENTED = 128,
        NO_ERROR
    };

    ZipFile();
    ~ZipFile();

    ZipFile(const QString& zipName);

    bool open(Mode mode);
    Mode mode() const;

    const QString& zipName() const;
    void setZipName(const QString& zipName);

    ZipHandler handler();

    quint32 compressLevel() const;
    void setCompressLevel(quint32 level);

    ZipFile(const ZipFile&) = delete;
    ZipFile& operator=(const ZipFile&) = delete;


private:

    std::unique_ptr<ZipImplImpl> m_impl;
};

} /* namespace QMiniZip */
