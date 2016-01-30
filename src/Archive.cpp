#include <QtCore/QDebug>
#include <QtCore/QDirIterator>

#include "Archive.h"
#include "Compressor.h"
#include "NewFileInfo.h"
#include "ZipFile.h"

namespace QMiniZip
{
bool Archive::compressDir(const QString& archive, const QString dir,
        bool recursive)
{
    ZipFile zp(archive);
    if (!zp.open(ZipFile::CREATE))
    {
        return false;
    }

    auto flag =
            recursive ?
                    QDirIterator::Subdirectories :
                    QDirIterator::NoIteratorFlags;

    QDirIterator it(dir, flag | QDirIterator::FollowSymlinks);
    while (it.hasNext())
    {
        it.next();
        if (it.fileInfo().isFile())
        {
            NewFileInfo nfi(it.filePath());

            if (!Compressor::compressFile(zp, nfi, dir))
            {
                return false;
            }
        }

    }

    return true;
}

} /* namespace QMiniZip */
