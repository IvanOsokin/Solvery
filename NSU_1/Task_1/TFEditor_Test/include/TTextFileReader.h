#pragma once

#include "pch.h"

#include "TextFileReader.h"

class TextFileReaderTest : public ::testing::Test
{
public:
    TextFileReaderTest()
    {
        std::filesystem::path executable(::testing::internal::GetArgvs().front());
        std::filesystem::path testReadFile(executable.parent_path().parent_path().parent_path());
        testReadFile /= "Task_1\\TFEditor_Test\\Files\\inputRead.txt";

        _txtReader = new TextFileReader(testReadFile);
        _fileName = testReadFile;
    }

    ~TextFileReaderTest()
    {
        if (_txtReader) delete _txtReader;
    }

protected:
    TextFileReader* _txtReader;
    const size_t _size = 1024;
    std::filesystem::path _fileName;
};

TEST_F(TextFileReaderTest, TestCtor)
{
    ASSERT_NE(_txtReader, nullptr);
}

TEST_F(TextFileReaderTest, TestGetFileName)
{
    std::filesystem::path executable(::testing::internal::GetArgvs().front());
    std::filesystem::path testReadFile(executable.parent_path().parent_path().parent_path());
    testReadFile /= "Task_1\\TFEditor_Test\\Files\\inputRead.txt";
    EXPECT_EQ(_txtReader->GetFileName(), testReadFile);
}

TEST_F(TextFileReaderTest, TestEofFile_True1)
{
    _txtReader->Read(_size);
    EXPECT_TRUE(_txtReader->Eof());
}

TEST_F(TextFileReaderTest, TestEofFile_True2)
{
    _txtReader->Read(35);
    EXPECT_TRUE(_txtReader->Eof());
}

TEST_F(TextFileReaderTest, TestEofFile_False)
{
    _txtReader->Read(10);
    EXPECT_FALSE(_txtReader->Eof());
}

TEST_F(TextFileReaderTest, TestReadFile)
{
    auto str = _txtReader->Read(25);
    EXPECT_EQ(str, "This is an input string!\n");
}

TEST_F(TextFileReaderTest, TestReadFile_All)
{
    auto str = _txtReader->Read(_size);
    EXPECT_EQ(str, "This is an input string!\nSize = 25");
}

TEST_F(TextFileReaderTest, TestReadFile_Empty)
{
    auto str = _txtReader->Read(0);
    EXPECT_EQ(str, "");
}

TEST_F(TextFileReaderTest, TestReadFile_ByChar)
{
    int i = 0;
    while (!_txtReader->Eof())
    {
        _txtReader->Read(1);
        ++i;
    }
    EXPECT_EQ(i, 35);
}

TEST_F(TextFileReaderTest, TestReset1)
{
    auto str1 = _txtReader->Read(_size);
    _txtReader->Reset();
    auto str2 = _txtReader->Read(_size);
    EXPECT_EQ(str1, str2);
}

TEST_F(TextFileReaderTest, TestReset2)
{
    auto str1 = _txtReader->Read(_size);
    auto str2 = _txtReader->Read(_size);
    EXPECT_NE(str1, str2);
}

/////////////////////////////////////////////////////////////////////////

class TextFileReaderTest_InvalidTestFile : public ::testing::Test
{
public:
    TextFileReaderTest_InvalidTestFile()
    {
        std::filesystem::path executable(::testing::internal::GetArgvs().front());
        std::filesystem::path testReadFile(executable.parent_path().parent_path().parent_path());
        testReadFile /= "Task_1\\TFEditor_Test\\Files\\inputReadInvalid.txt";

        _txtReader = new TextFileReader(testReadFile);
        _fileName = testReadFile;
    }

    ~TextFileReaderTest_InvalidTestFile()
    {
        if (_txtReader) delete _txtReader;
    }

protected:
    TextFileReader* _txtReader;
    std::filesystem::path _fileName;
};

TEST_F(TextFileReaderTest_InvalidTestFile, TestCtor1)
{
    try
    {
        TextFileReaderTest_InvalidTestFile tfr();
        EXPECT_FALSE(true);
    }
    catch (...)
    {
        EXPECT_TRUE(true);
    }
}

/////////////////////////////////////////////////////////////////////////

class TextFileReaderTest_EmptyTestFile : public ::testing::Test
{
public:
    TextFileReaderTest_EmptyTestFile()
    {
        std::filesystem::path executable(::testing::internal::GetArgvs().front());
        std::filesystem::path testReadFile(executable.parent_path().parent_path().parent_path());
        testReadFile /= "Task_1\\TFEditor_Test\\Files\\inputRead_Empty.txt";

        _txtReader = new TextFileReader(testReadFile);
        _fileName = testReadFile;
    }

    ~TextFileReaderTest_EmptyTestFile()
    {
        if (_txtReader) delete _txtReader;
    }

protected:
    TextFileReader* _txtReader;
    const size_t _size = 1024;
    std::filesystem::path _fileName;
};

TEST_F(TextFileReaderTest_EmptyTestFile, TestEofFile_True)
{
    _txtReader->Read(_size);
    EXPECT_TRUE(_txtReader->Eof());
}

TEST_F(TextFileReaderTest_EmptyTestFile, TestEofFile_False)
{
    EXPECT_FALSE(_txtReader->Eof());
}

TEST_F(TextFileReaderTest_EmptyTestFile, TestEofFile_Combi)
{
    EXPECT_FALSE(_txtReader->Eof());
    _txtReader->Read(1);
    EXPECT_TRUE(_txtReader->Eof());
}