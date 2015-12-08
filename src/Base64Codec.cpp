/*
 * Base64Codec.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: orbeus
 */

#include "Base64Codec.h"

#include <iostream>

using namespace std;

namespace rekognition_api {

namespace {

static const string kBase64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

static inline bool CheckBase64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

void StrAppend(const char c, string* str) {  // no '+' in url
	if (c == '+') {
		str->append("%2B");
	} else {
		str->append(1, c);
	}
}

}

Base64Codec::Base64Codec() {
}

Base64Codec::~Base64Codec() {
}

bool Base64Codec::Encode(const string& input, string* output) {
	if (output == NULL) {
		cerr << "Null output is passed" << endl;
		return false;
	}

	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	int in_len = input.size();
	const char* bytes_to_encode = &(input[0]);
	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4)
					+ ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2)
					+ ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++) {
				StrAppend(kBase64Chars[char_array_4[i]], output);
			}
			i = 0;
		}
	}

	unsigned long temp;
	switch (input.size() % 3) {
	case 1:
		temp = char_array_3[0] << 16; //Convert to big endian
		StrAppend(kBase64Chars[(temp & 0x00FC0000) >> 18], output);
		StrAppend(kBase64Chars[(temp & 0x0003F000) >> 12], output);
		output->append(2, '=');
		break;
	case 2:
		temp = char_array_3[0] << 16; //Convert to big endian
		temp += char_array_3[1] << 8;
		StrAppend(kBase64Chars[(temp & 0x00FC0000) >> 18], output);
		StrAppend(kBase64Chars[(temp & 0x0003F000) >> 12], output);
		StrAppend(kBase64Chars[(temp & 0x00000FC0) >> 6], output);
		output->append(1, '=');
		break;
	}

	return true;
}

bool Base64Codec::Decode(const string& input, string* output) {
	cerr << "Decode Not implemented.";
	return false;
}

} /* namespace rekognition_api */

