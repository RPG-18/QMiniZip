#include <gtest/gtest.h>
#include <config.h>
#include <iostream>

#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QFileInfo>

#include "Archive.h"

using namespace QMiniZip;

TEST(ArchiveTest, compressDir)
{
    QDir dir(TEST_SOURCE_DIR);
    ASSERT_TRUE(dir.cd("data/dataset1"));

    const QDir out(TEST_BIN_DIR);
    const auto zipFileName = out.absoluteFilePath("dataset1.zip");
    ASSERT_TRUE(Archive::compressDir(zipFileName,
            dir.absolutePath()));

    const QFileInfo fInfo(zipFileName);
    ASSERT_EQ(4314, fInfo.size());
}
