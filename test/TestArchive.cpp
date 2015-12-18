#include <gtest/gtest.h>

#include "Archive.h"

using namespace QMiniZip;

TEST(ArchiveTest, compressDir)
{
    ASSERT_TRUE(Archive::compressDir("/tmp/test.zip", "/tmp/testDir"));
}
