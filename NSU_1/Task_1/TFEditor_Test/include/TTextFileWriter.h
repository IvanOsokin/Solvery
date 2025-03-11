#pragma once

#include "pch.h"

#include "TextFileWriter.h"

class TextFileWriterTest : public ::testing::Test
{
public:
    TextFileWriterTest()
    {
        const std::filesystem::path executable{ ::testing::internal::GetArgvs().front() };
        std::filesystem::path testOutputFile{ executable.parent_path().parent_path().parent_path() };
        testOutputFile /= "Task_1\\TFEditor_Test\\Files\\outputWrite.txt";

        _textWriter = std::make_unique<TextFileWriter>(testOutputFile);
        _fileName = testOutputFile;
    }

    ~TextFileWriterTest() = default;

protected:
    std::unique_ptr<TextFileWriter> _textWriter;
    std::filesystem::path _fileName;
};

TEST_F(TextFileWriterTest, TestCtor)
{
    ASSERT_NE(_textWriter, nullptr);
}

TEST_F(TextFileWriterTest, TestGetFileName)
{
    const std::filesystem::path executable{ ::testing::internal::GetArgvs().front() };
    std::filesystem::path testOutputFile{ executable.parent_path().parent_path().parent_path() };
    testOutputFile /= "Task_1\\TFEditor_Test\\Files\\outputWrite.txt";
    EXPECT_EQ(_textWriter->GetFileName(), testOutputFile);
}

TEST_F(TextFileWriterTest, TestReset)
{
    TextFileReader textFileReader(_textWriter->GetFileName());

    const std::string stringToWrite{ "string" };
    _textWriter->Write(stringToWrite);
    _textWriter->Reset();
    _textWriter->Write(stringToWrite);
    const std::string readString = textFileReader.Read(100);
    EXPECT_EQ(readString, stringToWrite);
}

TEST_F(TextFileWriterTest, TestWrite)
{
    TextFileReader textFileReader(_textWriter->GetFileName());

    const std::string stringToWrite{ "TestWrite" };
    _textWriter->Write(stringToWrite);
    _textWriter->Flush();
    const std::string readString = textFileReader.Read(100);
    EXPECT_EQ(readString, stringToWrite);
}