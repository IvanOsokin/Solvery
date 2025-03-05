#pragma once

#include "pch.h"

#include "TextEditor.h"

class TextEditorTest : public ::testing::Test
{
public:
    TextEditorTest()
    {
        std::filesystem::path executable(::testing::internal::GetArgvs().front());
        std::filesystem::path testReadFile(executable.parent_path().parent_path().parent_path());
        testReadFile /= "Task_1\\TFEditor_Test\\Files\\inputRead.txt";
        _input = testReadFile;

        std::filesystem::path testWriteFile(executable.parent_path().parent_path().parent_path());
        testWriteFile /= "Task_1\\TFEditor_Test\\Files\\outputWrite.txt";
        _output = testWriteFile;

        _txtEditor = new TextEditor(testReadFile, testWriteFile);
    }

    ~TextEditorTest()
    {
        if (_txtEditor) delete _txtEditor;
    }

protected:
    TextEditor* _txtEditor;
    std::filesystem::path _input;
    std::filesystem::path _output;
};

TEST_F(TextEditorTest, TestReplace)
{
    _txtEditor->ReplaceSubstring("25", "2255");

    TextFileReader tfr1(_input);
    auto initStr = tfr1.Read(100);
    EXPECT_EQ(initStr, "This is an input string!\nSize = 25");

    TextFileReader tfr2(_output);
    auto newStr = tfr2.Read(100);
    EXPECT_EQ(newStr, "This is an input string!\nSize = 2255");
}