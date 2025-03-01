#pragma once

#include "pch.h"

#include "Text.h"

TEST(TextTest_Size, TestSize)
{
    Text text("test string!");
    EXPECT_EQ(text.Size(), 12);
}

TEST(TextTest_Size, TestEmptySize)
{
    Text text("");
    EXPECT_EQ(text.Size(), 0);
}

TEST(TextTest_Data, TestData)
{
    Text text("test data");
    EXPECT_EQ(text.Data(), "test data");
}

TEST(TextTest_Data, TestEmptyData)
{
    Text text("");
    EXPECT_EQ(text.Data(), "");
}

TEST(TextTest_Append, TestAppend)
{
    std::string str{ "test data" };
    Text text(str);
    std::string appendStr{ " append!" };
    EXPECT_EQ(text.Append(Text(appendStr)).Data(), str + appendStr);
}

TEST(TextTest_Append, TestAppendEmpty)
{
    std::string str{ "test empty append!" };
    Text text(str);
    EXPECT_EQ(text.Append(Text()).Data(), str);
}

TEST(TextTest_Replace, TestReplace1)
{
    Text text("replace test!");
    EXPECT_EQ(text.Replace("e", "E").Data(), "rEplacE tEst!");
    EXPECT_EQ(text.Replace("!", "!!!").Data(), "rEplacE tEst!!!");
}

TEST(TextTest_Replace, TestReplace2)
{
    std::string str{ "" };
    Text text(str);
    EXPECT_EQ(text.Replace("a", "b").Data(), str);
}

TEST(TextTest_Replace, TestReplace3)
{
    Text text("aaa");
    EXPECT_EQ(text.Replace("a", "bbb").Data(), "bbbbbbbbb");
}

TEST(TextTest_Replace, TestReplaceEmptyOldPattern)
{
    std::string str{ "replace test!" };
    Text text(str);
    EXPECT_EQ(text.Replace("", "ABC").Data(), str);
}

TEST(TextTest_Replace, TestReplaceEmptyNewPattern)
{
    Text text("test empty append!");
    EXPECT_EQ(text.Replace("test", "").Data(), " empty append!");
}

TEST(TextTest_Tail, TestTailStartsWithPattern1)
{
    std::string pattern{ "string" };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    EXPECT_FALSE(text.TailStartsWithPattern(pattern, patternLastPos));
}

TEST(TextTest_Tail, TestTailStartsWithPattern2)
{
    std::string pattern{ "string." };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    EXPECT_FALSE(text.TailStartsWithPattern(pattern, patternLastPos));
}

TEST(TextTest_Tail, TestTailStartsWithPattern3)
{
    std::string pattern{ "This test checks if the specified pattern is on the end of this string." };
    Text text(pattern);
    size_t patternLastPos;
    EXPECT_FALSE(text.TailStartsWithPattern(pattern, patternLastPos));
}

TEST(TextTest_Tail, TestTailStartsWithPattern4)
{
    std::string pattern{ "This" };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    EXPECT_FALSE(text.TailStartsWithPattern(pattern, patternLastPos));
}

TEST(TextTest_Tail, TestTailStartsWithPattern5)
{
    std::string pattern{};
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    EXPECT_FALSE(text.TailStartsWithPattern(pattern, patternLastPos));
}

TEST(TextTest_Tail, TestTailStartsWithPattern6)
{
    std::string pattern{ "This test checks if the specified pattern is on the end of this string. Further sequence" };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    EXPECT_TRUE(text.TailStartsWithPattern(pattern, patternLastPos));
}

TEST(TextTest_Tail, TestTailStartsWithPattern7)
{
    std::string pattern{ "string. Further sequence" };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    EXPECT_TRUE(text.TailStartsWithPattern(pattern, patternLastPos));
}

TEST(TextTest_Tail, TestTailStartsWithPattern8)
{
    std::string pattern{ "This test checks if the specified pattern is on the end of this string. Further sequence" };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    text.TailStartsWithPattern(pattern, patternLastPos);
    EXPECT_EQ(patternLastPos, 0);
}

TEST(TextTest_Tail, TestTailStartsWithPattern9)
{
    std::string pattern{ "the specified pattern is on the end of this string. Further sequence" };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    text.TailStartsWithPattern(pattern, patternLastPos);
    EXPECT_EQ(patternLastPos, 20);
}

TEST(TextTest_Tail, TestTailStartsWithPattern10)
{
    std::string pattern{ "the end of this string. Further sequence" };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    text.TailStartsWithPattern(pattern, patternLastPos);
    EXPECT_EQ(patternLastPos, 48);
}

TEST(TextTest_Tail, TestTailStartsWithPattern11)
{
    std::string pattern{ "This test checks if the specified pattern is on the end of this string." };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    text.TailStartsWithPattern(pattern, patternLastPos);
    EXPECT_EQ(patternLastPos, std::string::npos);
}

TEST(TextTest_Tail, TestTailStartsWithPattern12)
{
    std::string pattern{ "checks" };
    Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPos;
    text.TailStartsWithPattern(pattern, patternLastPos);
    EXPECT_EQ(patternLastPos, std::string::npos);
}