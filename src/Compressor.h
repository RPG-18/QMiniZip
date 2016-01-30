#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

#include <QtCore/QDir>

namespace QMiniZip
{
class ZipFile;
class NewFileInfo;

class Compressor
{
public:

    static const size_t WRITE_BUFFER_SIZE = 16384;
    static bool compressFile(ZipFile& zip, const NewFileInfo& file, const QString& baseDir = QString());
};

} /* namespace QMiniZip */

#endif
