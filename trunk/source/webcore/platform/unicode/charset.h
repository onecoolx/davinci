
#ifndef Charset_H
#define Charset_H

struct charset_ops {
	const char* charset;

	int (*len_first_char)(const unsigned char*, int);
	unsigned short (*conv_to_uchar)(const unsigned char*, int);
	int (*conv_from_uchar)(unsigned short, unsigned char*);
};

struct charset_ops* create_charset_ops(const char* name);
void destory_charset_ops(struct charset_ops* ops);

#endif
