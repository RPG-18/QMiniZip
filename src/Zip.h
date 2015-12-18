#ifndef ZIP_H_
#define ZIP_H_

#include <memory>

#include <QtCore/QString>

namespace QMiniZip
{

class ZipImpl;
class Zip
{
    friend class ZipImpl;
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

    Zip();

    Zip(const QString& zipName);

    bool open(Mode mode);
    Mode mode() const;

    const QString& zipName() const;
    void setZipName(const QString& zipName);

    ZipHandler handler();

    quint32 compressLevel() const;
    void setCompressLevel(quint32 level);

private:

    Q_DISABLE_COPY(Zip)

private:
    std::shared_ptr<ZipImpl> m_impl;
};

} /* namespace QMiniZip */

#endif
