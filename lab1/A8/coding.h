#ifndef LIST_H
#define LIST_H

/*
 * Encodes and decodes a file.
 */
class Coding {
public:
	Coding();
	~Coding();

	/* For any character c, encode(c) is a character different from c */
	static unsigned char encode(unsigned char c) {
		if (c == 255) {
			return 0;
		} else {
			return c + 1;
		}
	}

	/* For any character c, decode(encode(c)) == c */
	static unsigned char decode(unsigned char c) {
		if (c == 0) {
			return 255;
		} else {
			return c - 1;
		}
	}

private:
};

#endif
