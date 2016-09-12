#include <iostream>
#include <stdexcept>

using namespace std;

const static char codes[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const static char padChar = '=';

int index_of(char const c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    if (c >= 'a' && c <= 'z')
        return (c - 'a') + 26;
    if (c >= '0' && c <= '9')
        return (c - '0') + 52;
    if (c == '+')
        return 62;
    if (c == '/')
        return 63;
    return 64;
}

template<typename T = char>
std::basic_string<T> base64_encode(std::basic_string<T> const &input) {

    std::basic_string<T> encoded;
    encoded.reserve((input.size() * 4) / 3);

    for (auto i = 0; i < input.size(); i += 3) {
        int b = (input[i] & 0xfc) >> 2;
        encoded.append(1, codes[b]);
        b = (input[i] & 0x03) << 4;
        if (i + 1 < input.size()) {
            b |= (input[i + 1] & 0xf0) >> 4;
            encoded.append(1, codes[b]);
            b = (input[i + 1] & 0x0f) << 2;
            if (i + 2 < input.size()) {
                b |= (input[i + 2] & 0xc0) >> 6;
                encoded.append(1, codes[b]);
                b = input[i + 2] & 0x3f;
                encoded.append(1, codes[b]);
            } else {
                encoded.append(1, codes[b]);
                encoded.append(1, padChar);
            }
        } else {
            encoded.append(1, codes[b]);
            encoded.append(2, padChar);
        }
    }
    return encoded;
}

template<typename T = char>
std::basic_string<T> base64_decode(std::basic_string<T> const &input) {

    if (input.size() % 4) {
        throw invalid_argument("invalid base64 input");
    }

    std::basic_string<T> decoded;
    decoded.reserve((input.length() * 3) / 4);

    for (auto i = 0, j = 0; i < input.size(); i += 4) {
        int b[4]{0};
        b[0] = index_of(input[i]);
        b[1] = index_of(input[i + 1]);
        b[2] = index_of(input[i + 2]);
        b[3] = index_of(input[i + 3]);
        decoded.append(1, (b[0] << 2) | (b[1] >> 4));
        if (b[2] < 64) {
            decoded.append(1, (b[1] << 4) | (b[2] >> 2));
            if (b[3] < 64) {
                decoded.append(1, (b[2] << 6) | b[3]);
            }
        }
    }
    return decoded;
}

int main() {

    for (string s; std::getline(cin, s);) {
        string enc = base64_encode(s);
        cout << enc << ' ';
        string dec = base64_decode(enc);
        cout << dec << '\n';
    }

    return 0;
}
