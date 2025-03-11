#pragma once

#include "pch.h"

#include "TextEditor.h"

class TextEditorTest : public ::testing::Test
{
public:
    TextEditorTest()
    {
        const std::filesystem::path executable{ ::testing::internal::GetArgvs().front() };

        std::filesystem::path testInputFile{ executable.parent_path().parent_path().parent_path() };
        testInputFile /= "Task_1\\TFEditor_Test\\Files\\inputRead.txt";
        _input = testInputFile;

        std::filesystem::path testOutputFile{ executable.parent_path().parent_path().parent_path() };
        testOutputFile /= "Task_1\\TFEditor_Test\\Files\\outputWrite.txt";
        _output = testOutputFile;

        _textEditor = std::make_unique<TextEditor>(testInputFile, testOutputFile);
    }

    ~TextEditorTest() = default;

protected:
    std::unique_ptr<TextEditor> _textEditor;
    std::filesystem::path _input;
    std::filesystem::path _output;
};

TEST_F(TextEditorTest, TestReplace)
{
    _textEditor->ReplaceSubstring("25", "2255");

    TextFileReader textFileReader1{ _input };
    const std::string initialText = textFileReader1.Read(100);
    EXPECT_EQ(initialText, "This is an input string!\nSize = 25");

    TextFileReader textFileReader2{ _output };
    const std::string resultText = textFileReader2.Read(100);
    EXPECT_EQ(resultText, "This is an input string!\nSize = 2255");
}