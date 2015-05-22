/*
 * The MIT License (MIT)
 * Copyright (C) 2015 Tokuhiro Matsuno, http://64p.org/ <tokuhirom@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef NANOBASE_H_
#define NANOBASE_H_

#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

// do not use this directly
static char nb_base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

int nb_base64_needed_encoded_length (int length_of_data) {
    int nb_base64_chars = (length_of_data + 2) / 3 * 4;

    return nb_base64_chars +               /* base64 char incl padding */
           (nb_base64_chars - 1) / 76 +    /* newlines */
           1;                              /* NUL termination of string */
}

/**
 * buf_ is allocated by malloc(3).The size is grater than nb_base64_needed_encoded_length(src_len).
 */
void nb_base64_encode(const unsigned char * src, int src_len, unsigned char *buf_) {
    unsigned char *buf = buf_;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3] = {0};
    unsigned char char_array_4[4] = {0};

    while (src_len--) {
        char_array_3[i++] = *(src++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] =
                ((char_array_3[0] & 0x03) << 4) +
                ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] =
                ((char_array_3[1] & 0x0f) << 2) +
                ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (i = 0; (i < 4); i++) {
                *buf++ = nb_base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] =
            ((char_array_3[0] & 0x03) << 4) +
            ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] =
            ((char_array_3[1] & 0x0f) << 2) +
            ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++) {
            *buf++ = nb_base64_chars[char_array_4[j]];
        }

        while ((i++ < 3)) {
            *buf++ = '=';
        }
    }
    *buf++ = '\0';
}

#ifdef __cplusplus
};
#endif

#endif // NANOBASE_H_
