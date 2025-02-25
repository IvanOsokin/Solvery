#pragma once

#include "pch.h"

#include "Utils.h"
#include "TextFileWriter.h"
#include "TextFileWriter.cpp"

class TextFileWriterTest : public ::testing::Test
{
public:
    TextFileWriterTest()
    {
        fs::path executable(::testing::internal::GetArgvs().front());
        fs::path testWriteFile(executable.parent_path().parent_path().parent_path());
        testWriteFile /= "Task_1\\TFEditor_Test\\Files\\outputWrite.txt";

        _txtWriter = new TextFileWriter(testWriteFile);
        _fileName = testWriteFile;
    }

    ~TextFileWriterTest()
    {
        if (_txtWriter) delete _txtWriter;
    }

protected:
    TextFileWriter* _txtWriter;
    fs::path _fileName;
};

TEST_F(TextFileWriterTest, TestCtor)
{
    ASSERT_NE(_txtWriter, nullptr);
}

TEST_F(TextFileWriterTest, TestGetFileName)
{
    fs::path executable(::testing::internal::GetArgvs().front());
    fs::path testWriteFile(executable.parent_path().parent_path().parent_path());
    testWriteFile /= "Task_1\\TFEditor_Test\\Files\\outputWrite.txt";
    EXPECT_EQ(_txtWriter->GetFileName(), testWriteFile);
}

TEST_F(TextFileWriterTest, TestReset)
{
    TextFileReader tfr(_txtWriter->GetFileName());

    std::string str{"string"};
    _txtWriter->Write(str);
    _txtWriter->Reset();
    _txtWriter->Write(str);
    auto result = tfr.Read(100);
    EXPECT_EQ(result, str);
}

TEST_F(TextFileWriterTest, TestWrite)
{
    TextFileReader tfr(_txtWriter->GetFileName());

    std::string str{"TestWrite"};
    _txtWriter->Write(str);
    _txtWriter->Flush();
    auto result = tfr.Read(100);
    EXPECT_EQ(result, str);
}