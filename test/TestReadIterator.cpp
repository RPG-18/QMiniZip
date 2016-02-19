#include <gtest/gtest.h>
#include <config.h>

#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QVector>
#include <QtCore/QStringList>

#include "ZipFile.h"
#include "ZipReadIterator.h"

using namespace QMiniZip;

TEST(ZipReadIterator, next)
{
    QDir dir(TEST_SOURCE_DIR);
    ASSERT_TRUE(dir.cd("data"));

    const auto archive = dir.absoluteFilePath("dataset1.zip");

    ZipFile zipFile(archive);
    ASSERT_TRUE(zipFile.open(ZipFile::UNZIP));

    ZipReadIterator zIiterator(zipFile);
    ASSERT_TRUE(zIiterator.toBegin());
    int cnt = 1;
    while(zIiterator.next())
    {
        ++cnt;
    }

    ASSERT_EQ(4, cnt);
}

TEST(ZipReadIterator, fileInfo)
{
    QDir dir(TEST_SOURCE_DIR);
    ASSERT_TRUE(dir.cd("data"));

    const auto archive = dir.absoluteFilePath("dataset1.zip");

    ZipFile zipFile(archive);
    ASSERT_TRUE(zipFile.open(ZipFile::UNZIP));

    ZipReadIterator zIiterator(zipFile);
    ASSERT_TRUE(zIiterator.toBegin());
    int cnt = 0;

    QStringList files;
    QVector<size_t> unSizes;

    do
    {
        const auto info = zIiterator.fileInfo();
        files<<info.name();
        unSizes.push_back(info.uncompressedSize());
        ++cnt;
    }while(zIiterator.next());

    ASSERT_EQ(4, cnt);

    const QStringList expectedFiles =
        {"folder1/zen2.txt",
        "folder1/zen1.txt",
        "folder3/zen4.txt",
        "folder2/zen3.txt"};

    ASSERT_EQ(expectedFiles, files);

    const QVector<size_t> expectedUnSizes =
        {5099, 916, 1970, 1792};
    ASSERT_EQ(expectedUnSizes, unSizes);
}

TEST(ZipReadIterator, read)
{
    QDir dir(TEST_SOURCE_DIR);
    ASSERT_TRUE(dir.cd("data"));

    const auto archive = dir.absoluteFilePath("dataset1.zip");

    ZipFile zipFile(archive);
    ASSERT_TRUE(zipFile.open(ZipFile::UNZIP));

    ZipReadIterator zIiterator(zipFile);
    ASSERT_TRUE(zIiterator.toBegin());
    ASSERT_TRUE(zIiterator.openCurrentFile());

    QByteArray data;
    QByteArray buff(1024, 0);
    while(qint64 cnt = zIiterator.read(buff.data(), buff.size()))
    {
        if(cnt<0)
        {
            break;
        }
        data.append(buff.data(), cnt);

    }
    ASSERT_EQ(5099, data.size());
}

TEST(ZipReadIterator, readAll)
{
    QDir dir(TEST_SOURCE_DIR);
    ASSERT_TRUE(dir.cd("data"));

    const auto archive = dir.absoluteFilePath("dataset1.zip");

    ZipFile zipFile(archive);
    ASSERT_TRUE(zipFile.open(ZipFile::UNZIP));

    ZipReadIterator zIiterator(zipFile);
    ASSERT_TRUE(zIiterator.toBegin());

    QVector<QByteArray> dataSet;
    do
    {
        ASSERT_TRUE(zIiterator.openCurrentFile());
        dataSet.push_back(zIiterator.readAll());

        ASSERT_TRUE(dataSet.back().size()>0);
    }while(zIiterator.next());

    const QVector<int> expectedUnSizes =
        {5099, 916, 1970, 1792};

    ASSERT_EQ(expectedUnSizes.size(), dataSet.size());

    for(int i = 0; i < expectedUnSizes.size(); ++i)
    {
        ASSERT_EQ(expectedUnSizes[i], dataSet[i].size());
    }
}