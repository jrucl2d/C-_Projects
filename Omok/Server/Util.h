#ifndef GOMOKU_UTIL_H
#define GOMOKU_UTIL_H
using namespace std;
#include <vector>
#include <sstream>
class Util {
public:
	// delimiter�� input ���ڿ��� ��ū���� ������ ��������
	vector<string> getTokens(string input, char delimiter);
};
#endif
