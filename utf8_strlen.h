#include <string>

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

int utf8_strlen(const std::string& s) {
    int len = 0;
    for (int i = 0; i < s.size(); ++i)
        len += (s[i] & 0xc0) != 0x80;
    return len;
}
