#include <string>
#include <iostream>

/*
 * 0x00000000 - 0x0000007F:
 * 0xxxxxxx
 *
 * 0x00000080 - 0x000007FF:
 * 110xxxxx 10xxxxxx
 *
 * 0x00000800 - 0x0000FFFF:
 * 1110xxxx 10xxxxxx 10xxxxxx
 *
 * 0x00010000 - 0x001FFFFF:
 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 * Count all first-bytes (the ones that don't match 10xxxxxx).
 * https://stackoverflow.com/a/4063229/7961156
 */

/**
 * Get the length of a string encoded in UTF-8
 *
 * @author fengqi
 *
 * @param s  A string encoded in UTF-8.
 * @return   Number of UTF-8 character in s.
 */
int utf8_strlen(const std::string& s) {
    int len = 0;
    for (int i = 0; i < s.size(); ++i)
        len += (s[i] & 0xc0) != 0x80;
    return len;
}

/**
 * Return a truncated string of s.
 *
 * @author fengqi
 *
 * @param s       A string encoded in UTF-8.
 * @param length  How many characters to reserve.
 * @return        New string with size `length', if `length' > s.size(),
 *                a copy of `s' will be returned.
 */
std::string utf8_truncate(const std::string& s, size_t length) {
    // if (utf8_strlen(s) < length)
    //     return s;
    std::string truncated;
    ++length;
    for (int i = 0; i < s.size(); ++i) {
        if (((s[i] & 0xc0) != 0x80) && --length <= 0)
            break;
        truncated.push_back(s[i]);
    }
    return truncated;
}
