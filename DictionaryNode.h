#include <string>
using namespace std;
struct DictionaryNode {
	string key;
	int code;
	DictionaryNode(string s = "", int c = -1) : key(s), code(c) {};

	void operator=(const DictionaryNode& rhs) {
		key = rhs.key;
		code = rhs.code;
	}
	friend bool operator==(const DictionaryNode& lhs, const DictionaryNode& rhs);
	friend bool operator!=(const DictionaryNode& lhs, const DictionaryNode& rhs);
};

bool operator==(const DictionaryNode& lhs, const DictionaryNode& rhs) {
	return (lhs.key == rhs.key);
}
bool operator!=(const DictionaryNode& lhs, const DictionaryNode& rhs) {
	return(lhs.key != rhs.key);
}

unsigned hashing(const DictionaryNode& x, int) {

	if (x.key.length() == 1) {
		return int(unsigned char(x.key[0]));
	}
	else
	{
		return 256;
	}
}
