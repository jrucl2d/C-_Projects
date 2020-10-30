#ifndef GOMOKU_UTIL_H
#define GOMOKU_UTIL_H
using namespace std;
#include <vector>
#include <sstream>
class Util {
public:
	// delimiter로 input 문자열을 토큰으로 나눠서 리턴해줌
	vector<string> getTokens(string input, char delimiter);
};
#endif
