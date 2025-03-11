#pragma once

#include "pch.h"

#include "TextFileReader.h"

class TextFileReaderTest : public ::testing::Test
{
public:
    TextFileReaderTest()
    {
        const std::filesystem::path executable{ ::testing::internal::GetArgvs().front() };
        std::filesystem::path testInputFile{ executable.parent_path().parent_path().parent_path() };
        testInputFile /= "Task_1\\TFEditor_Test\\Files\\inputRead.txt";

        _textReader = std::make_unique<TextFileReader>(testInputFile);
        _fileName = testInputFile;
    }

    ~TextFileReaderTest() = default;

protected:
    std::unique_ptr<TextFileReader> _textReader;
    const size_t _size = 1024;
    std::filesystem::path _fileName;
};

TEST_F(TextFileReaderTest, TestCtor)
{
    ASSERT_NE(_textReader, nullptr);
}

TEST_F(TextFileReaderTest, TestGetFileName)
{
    const std::filesystem::path executable{ ::testing::internal::GetArgvs().front() };
    std::filesystem::path testInputFile{ executable.parent_path().parent_path().parent_path() };
    testInputFile /= "Task_1\\TFEditor_Test\\Files\\inputRead.txt";
    EXPECT_EQ(_textReader->GetFileName(), testInputFile);
}

TEST_F(TextFileReaderTest, TestEofFile_True1)
{
    _textReader->Read(_size);
    EXPECT_TRUE(_textReader->Eof());
}

TEST_F(TextFileReaderTest, TestEofFile_True2)
{
    _textReader->Read(35);
    EXPECT_TRUE(_textReader->Eof());
}

TEST_F(TextFileReaderTest, TestEofFile_False1)
{
    _textReader->Read(10);
    EXPECT_FALSE(_textReader->Eof());
}

TEST_F(TextFileReaderTest, TestEofFile_False2)
{
    _textReader->Read(34);
    EXPECT_FALSE(_textReader->Eof());
    _textReader->Read(1);
    EXPECT_TRUE(_textReader->Eof());
}

TEST_F(TextFileReaderTest, TestReadFile1)
{
    const std::string readString = _textReader->Read(25);
    EXPECT_EQ(readString, "This is an input string!\n");
}

TEST_F(TextFileReaderTest, TestReadFile3)
{
    const std::string readString = _textReader->Read(34);
    EXPECT_EQ(readString, "This is an input string!\nSize = 25");
}

TEST_F(TextFileReaderTest, TestReadFile4)
{
    const std::string readString = _textReader->Read(35);
    EXPECT_EQ(readString, "This is an input string!\nSize = 25");
}

TEST_F(TextFileReaderTest, TestReadFile_All)
{
    const std::string readString = _textReader->Read(_size);
    EXPECT_EQ(readString, "This is an input string!\nSize = 25");
}

TEST_F(TextFileReaderTest, TestReadFile_Empty)
{
    const std::string readString = _textReader->Read(0);
    EXPECT_EQ(readString, "");
}

TEST_F(TextFileReaderTest, TestReadFile_ByChar)
{
    int i = 0;
    while (!_textReader->Eof())
    {
        _textReader->Read(1);
        ++i;
    }
    EXPECT_EQ(i, 35);
}

TEST_F(TextFileReaderTest, TestReset1)
{
    const std::string readString1 = _textReader->Read(_size);
    _textReader->Reset();
    const std::string readString2 = _textReader->Read(_size);
    EXPECT_EQ(readString1, readString2);
}

TEST_F(TextFileReaderTest, TestReset2)
{
    const std::string readString1 = _textReader->Read(_size);
    const std::string readString2 = _textReader->Read(_size);
    EXPECT_NE(readString1, readString2);
}

/////////////////////////////////////////////////////////////////////////

class TextFileReaderTest_InvalidTestFile : public ::testing::Test
{
public:
    TextFileReaderTest_InvalidTestFile()
    {
        const std::filesystem::path executable{ ::testing::internal::GetArgvs().front() };
        std::filesystem::path testInputFile{ executable.parent_path().parent_path().parent_path() };
        testInputFile /= "Task_1\\TFEditor_Test\\Files\\inputReadInvalid.txt";
        _fileName = testInputFile;
    }

    ~TextFileReaderTest_InvalidTestFile() = default;

protected:
    std::filesystem::path _fileName;
};

TEST_F(TextFileReaderTest_InvalidTestFile, TestCtor1)
{
    try
    {
        TextFileReader textFileReader{ _fileName };
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
        const std::filesystem::path executable{ ::testing::internal::GetArgvs().front() };
        std::filesystem::path testInputFile{ executable.parent_path().parent_path().parent_path() };
        testInputFile /= "Task_1\\TFEditor_Test\\Files\\inputRead_Empty.txt";

        _textReader = std::make_unique<TextFileReader>(testInputFile);
        _fileName = testInputFile;
    }

    ~TextFileReaderTest_EmptyTestFile() = default;

protected:
    std::unique_ptr<TextFileReader> _textReader;
    const size_t _size = 1024;
    std::filesystem::path _fileName;
};

TEST_F(TextFileReaderTest_EmptyTestFile, TestEofFile_True)
{
    _textReader->Read(_size);
    EXPECT_TRUE(_textReader->Eof());
}

TEST_F(TextFileReaderTest_EmptyTestFile, TestEofFile_False)
{
    EXPECT_FALSE(_textReader->Eof());
}

TEST_F(TextFileReaderTest_EmptyTestFile, TestEofFile_Combined)
{
    EXPECT_FALSE(_textReader->Eof());
    _textReader->Read(1);
    EXPECT_TRUE(_textReader->Eof());
}