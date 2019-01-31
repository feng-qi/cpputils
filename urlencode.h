#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

inline int hex_char_to_int(char c) {
    return isdigit(c) ? c - '0' : tolower(c) - 'a' + 10;
}


/**
 * Percent-encode a string.
 *
 * @author fengqi
 * @param value A string to be encoded.
 * @return      Percent-encoded string.
 *
 * More details:
 *     https://tools.ietf.org/html/rfc3986
 *     https://en.wikipedia.org/wiki/Percent-encoding
 *     https://stackoverflow.com/questions/154536/encode-decode-urls-in-c
 */
std::string url_encode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');          // fill with leading '0' instead of ' '
    escaped << std::hex;

    for (std::string::const_iterator i = value.begin(); i != value.end(); ++i) {
        char c = *i;

        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << std::uppercase;
            escaped << '%' << std::setw(2) << int(static_cast<unsigned char>(c));
            escaped << std::nouppercase;
        }
    }

    return escaped.str();
}

/**
 * Decode a percent-encoded string.
 *
 * @author fengqi
 * @param value A percent-encoded string.
 * @return      Decoded string.
 *
 * More details:
 *     https://tools.ietf.org/html/rfc3986
 *     https://tools.ietf.org/html/rfc1866#section-8.2.1
 *     http://www.geekhideout.com/urlcode.shtml
 *     https://stackoverflow.com/questions/2678551/when-to-encode-space-to-plus-or-20
 */
std::string url_decode(const std::string& value) {
    std::ostringstream oss;
    for (std::string::size_type i = 0; i < value.size(); ++i) {
        switch (value[i]) {
        case '%':
            oss << char((hex_char_to_int(value[i+1]) << 4) | hex_char_to_int(value[i+2]));
            i += 2;
            break;
        case '+':
            // RFC-3986 says nothing special about '+', see RFC-1866 section 8.2.1 for details.
            // You should encode ' ' as '%20',
            // but I decode '+' as ' ' for the purpose of defensive programming.
            oss << ' ';
            break;
        default:
            oss << value[i];
        }
    }

    return oss.str();
}
