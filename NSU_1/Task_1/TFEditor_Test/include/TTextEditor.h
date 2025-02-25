#pragma once

#include "pch.h"

#include "Utils.h"
#include "TextEditor.h"
#include "TextEditor.cpp"

class TextEditorTest : public ::testing::Test
{
public:
    TextEditorTest()
    {
        fs::path executable(::testing::internal::GetArgvs().front());
        fs::path testReadFile(executable.parent_path().parent_path().parent_path());
        testReadFile /= "Task_1\\TFEditor_Test\\Files\\inputRead.txt";
        _input = testReadFile;

        fs::path testWriteFile(executable.parent_path().parent_path().parent_path());
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
    fs::path _input;
    fs::path _output;
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