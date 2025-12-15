#pragma once
#include <string>
#include <stack>
#include <algorithm>


class TextEditor {
private:

	std::stack<char> left;
	std::stack<char> right;
	int lsize = left.size();
	int rsize = right.size();



public:
	TextEditor();

	void addText(std::string text);
	int deleteText(int k);
	std::string cursorLeft(int k);
	std::string cursorRight(int k);

	std::string getLeft();
	std::string getRight();







};