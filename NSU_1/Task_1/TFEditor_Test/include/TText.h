#pragma once

#include "pch.h"

#include "Text.h"

TEST(TextTest_Size, TestSize)
{
    const Text text{ "test string!" };
    EXPECT_EQ(text.Size(), 12);
}

TEST(TextTest_Size, TestEmptySize)
{
    const Text text{ "" };
    EXPECT_EQ(text.Size(), 0);
}

TEST(TextTest_Data, TestData)
{
    const Text text{ "test data" };
    EXPECT_EQ(text.Data(), "test data");
}

TEST(TextTest_Data, TestEmptyData)
{
    const Text text{ "" };
    EXPECT_EQ(text.Data(), "");
}

TEST(TextTest_Append, TestAppend)
{
    const std::string testString{ "test data" };
    Text text{ testString };
    const std::string appendString{ " append!" };
    EXPECT_EQ(text.Append(Text{ appendString }).Data(), testString + appendString);
}

TEST(TextTest_Append, TestAppendEmpty)
{
    const std::string testString{ "test empty append!" };
    Text text{ testString };
    EXPECT_EQ(text.Append(Text{}).Data(), testString);
}

TEST(TextTest_Replace, TestReplace1)
{
    Text text{ "replace test!" };
    EXPECT_EQ(text.Replace("e", "E").Data(), "rEplacE tEst!");
    EXPECT_EQ(text.Replace("!", "!!!").Data(), "rEplacE tEst!!!");
}

TEST(TextTest_Replace, TestReplace2)
{
    const std::string testString{ "" };
    Text text{ testString };
    EXPECT_EQ(text.Replace("a", "b").Data(), testString);
}

TEST(TextTest_Replace, TestReplace3)
{
    Text text{ "aaa" };
    EXPECT_EQ(text.Replace("a", "bbb").Data(), "bbbbbbbbb");
}

TEST(TextTest_Replace, TestReplaceEmptyOldPattern)
{
    const std::string testString{ "replace test!" };
    Text text{ testString };
    EXPECT_EQ(text.Replace("", "ABC").Data(), testString);
}

TEST(TextTest_Replace, TestReplaceEmptyNewPattern)
{
    Text text{ "test empty append!" };
    EXPECT_EQ(text.Replace("test", "").Data(), " empty append!");
}

TEST(TextTest_Tail, TestTailStartsWithPattern1)
{
    const std::string searchPattern{ "string" };
    const Text text{ "This test checks if the specified pattern is on the end of this string." };
    size_t patternLastPosition;
    EXPECT_FALSE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
}

TEST(TextTest_Tail, TestTailStartsWithPattern2)
{
    const std::string searchPattern{ "string." };
    const Text text{ "This test checks if the specified pattern is on the end of this string." };
    size_t patternLastPosition;
    EXPECT_FALSE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
}

TEST(TextTest_Tail, TestTailStartsWithPattern3)
{
    const std::string searchPattern{ "This test checks if the specified pattern is on the end of this string." };
    const Text text{ searchPattern };
    size_t patternLastPosition;
    EXPECT_FALSE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
}

TEST(TextTest_Tail, TestTailStartsWithPattern4)
{
    const std::string searchPattern{ "This" };
    const Text text{ "This test checks if the specified pattern is on the end of this string." };
    size_t patternLastPosition;
    EXPECT_FALSE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
}

TEST(TextTest_Tail, TestTailStartsWithPattern5)
{
    const std::string searchPattern{};
    const Text text{ "This test checks if the specified pattern is on the end of this string." };
    size_t patternLastPosition;
    EXPECT_FALSE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
}

TEST(TextTest_Tail, TestTailStartsWithPattern6)
{
    const std::string searchPattern{ "This test checks if the specified pattern is on the end of this string. Further sequence" };
    const Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPosition;
    EXPECT_TRUE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
}

TEST(TextTest_Tail, TestTailStartsWithPattern7)
{
    const std::string searchPattern{ "string. Further sequence" };
    const Text text{ "This test checks if the specified pattern is on the end of this string." };
    size_t patternLastPosition;
    EXPECT_TRUE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
}

TEST(TextTest_Tail, TestTailStartsWithPattern8)
{
    const std::string searchPattern{ "This test checks if the specified pattern is on the end of this string. Further sequence" };
    const Text text("This test checks if the specified pattern is on the end of this string.");
    size_t patternLastPosition;
    EXPECT_TRUE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
    EXPECT_EQ(patternLastPosition, 0);
}

TEST(TextTest_Tail, TestTailStartsWithPattern9)
{
    const std::string searchPattern{ "the specified pattern is on the end of this string. Further sequence" };
    const Text text{ "This test checks if the specified pattern is on the end of this string." };
    size_t patternLastPosition;
    EXPECT_TRUE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
    EXPECT_EQ(patternLastPosition, 20);
}

TEST(TextTest_Tail, TestTailStartsWithPattern10)
{
    const std::string searchPattern{ "the end of this string. Further sequence" };
    const Text text{ "This test checks if the specified pattern is on the end of this string." };
    size_t patternLastPosition;
    EXPECT_TRUE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
    EXPECT_EQ(patternLastPosition, 48);
}

TEST(TextTest_Tail, TestTailStartsWithPattern11)
{
    const std::string searchPattern{ "This test checks if the specified pattern is on the end of this string." };
    const Text text{ "This test checks if the specified pattern is on the end of this string." };
    size_t patternLastPosition;
    EXPECT_FALSE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
    EXPECT_EQ(patternLastPosition, std::string::npos);
}

TEST(TextTest_Tail, TestTailStartsWithPattern12)
{
    const std::string searchPattern{ "checks" };
    const Text text{ "This test checks if the specified pattern is on the end of this string." };
    size_t patternLastPosition;
    EXPECT_FALSE(text.TailStartsWithPattern(searchPattern, patternLastPosition));
    EXPECT_EQ(patternLastPosition, std::string::npos);
}