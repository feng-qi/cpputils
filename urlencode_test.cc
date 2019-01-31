#include "urlencode.h"
#include <gtest/gtest.h>

//-------------------- url_encode test --------------------
TEST(UrlEncodeTest, Empty) {
    ASSERT_EQ(url_encode(""), "");
}

TEST(UrlEncodeTest, UnreservedCharacters) {
    ASSERT_EQ(url_encode("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ASSERT_EQ(url_encode("abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz");
    ASSERT_EQ(url_encode("0123456789-_.~"), "0123456789-_.~");
}

TEST(UrlEncodeTest, ReservedCharacters) {
    ASSERT_EQ(url_encode("!*'();:@&=+$,/?#[]"), "%21%2A%27%28%29%3B%3A%40%26%3D%2B%24%2C%2F%3F%23%5B%5D");
}

TEST(UrlEncodeTest, SpecialCharacters) {
    ASSERT_EQ(url_encode("\"\\ %<>^`{|}"), "%22%5C%20%25%3C%3E%5E%60%7B%7C%7D");
    ASSERT_EQ(url_encode("\r\n"), "%0D%0A");
}

// char value > 0b1000'0000.
// In this case, char will be expanded to negative int, we have to handle it.
TEST(UrlEncodeTest, NegativeChar) {
    unsigned char arr[] = {0xff,0xfe,0xef,0xee,0xdd,0xcc,0xbb};
    ASSERT_EQ(url_encode(std::string(arr,arr+sizeof(arr))), "%FF%FE%EF%EE%DD%CC%BB");
}

TEST(UrlEncodeTest, Chinese) {
    ASSERT_EQ(url_encode("我有一头小毛驴"), "%E6%88%91%E6%9C%89%E4%B8%80%E5%A4%B4%E5%B0%8F%E6%AF%9B%E9%A9%B4");
}

TEST(UrlEncodeTest, MixedUp) {
    ASSERT_EQ(url_encode("我有一头\r\n\"\\ %89-_.~ABCDEF!*"),
              "%E6%88%91%E6%9C%89%E4%B8%80%E5%A4%B4%0D%0A%22%5C%20%2589-_.~ABCDEF%21%2A");
}


//-------------------- url_decode test --------------------
TEST(UrlDecodeTest, Empty) {
    ASSERT_EQ(url_decode(""), "");
}

TEST(UrlDecodeTest, UnreservedCharacters) {
    ASSERT_EQ(url_decode("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ASSERT_EQ(url_decode("abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz");
    ASSERT_EQ(url_decode("0123456789-_.~"), "0123456789-_.~");
}

TEST(UrlDecodeTest, ReservedCharacters) {
    ASSERT_EQ(url_decode("%21%2A%27%28%29%3B%3A%40%26%3D%2B%24%2C%2F%3F%23%5B%5D"), "!*'();:@&=+$,/?#[]");
}

TEST(UrlDecodeTest, SpecialCharacters) {
    ASSERT_EQ(url_decode("%22%5C%20%25%3C%3E%5E%60%7B%7C%7D"), "\"\\ %<>^`{|}");
    ASSERT_EQ(url_decode("%0D%0A"), "\r\n");
}

// char value > 0b1000'0000.
// In this case, char will be expanded to negative int, we have to handle it.
TEST(UrlDecodeTest, NegativeChar) {
    unsigned char arr[] = {0xff,0xfe,0xef,0xee,0xdd,0xcc,0xbb};
    ASSERT_EQ(url_decode("%FF%FE%EF%EE%DD%CC%BB"), std::string(arr,arr+sizeof(arr)));
}

TEST(UrlDecodeTest, Chinese) {
    ASSERT_EQ(url_decode("%E6%88%91%E6%9C%89%E4%B8%80%E5%A4%B4%E5%B0%8F%E6%AF%9B%E9%A9%B4"), "我有一头小毛驴");
}

TEST(UrlDecodeTest, MixedUp) {
    ASSERT_EQ(url_decode("%E6%88%91%E6%9C%89%E4%B8%80%E5%A4%B4%0D%0A%22%5C%20%2589-_.~ABCDEF%21%2A"),
              "我有一头\r\n\"\\ %89-_.~ABCDEF!*");
}
