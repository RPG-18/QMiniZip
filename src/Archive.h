#ifndef ARCHIVE_H_
#define ARCHIVE_H_

#include <QtCore/QString>

namespace QMiniZip
{

class Archive
{
public:

    static bool compressDir(const QString& archive, const QString dir, bool recursive = true);
};

} /* namespace QMiniZip */

#endif
