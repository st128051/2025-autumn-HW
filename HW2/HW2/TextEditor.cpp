#include "TextEditor.h"


TextEditor::TextEditor() {}

std::string TextEditor::getLeft() {
	std::stack<char> copy = left;
	std::string result;
	result.reserve(copy.size());

	while (!copy.empty()) {
		result.push_back(copy.top());
		copy.pop();
	}

	std::reverse(result.begin(), result.end());
	return result;


};

std::string TextEditor::getRight() {
	std::stack<char> copy = right;
	std::string result;
	result.reserve(copy.size());

	while (!copy.empty()) {
		result.push_back(copy.top());
		copy.pop();
	}
	return result;
};


void TextEditor::addText(std::string text) {
	for (int i = 0; i < text.length(); ++i) {
		left.push(text[i]);
	}


};

int TextEditor::deleteText(int k) {

	int mn = k <= lsize ? k : lsize;

	for (int i = 0; i < mn; ++i) {
		left.pop();
	}
	lsize -= mn;
	return mn;
	

};

std::string TextEditor::cursorLeft(int k) {
	int mn = k <= lsize ? k : lsize;

	for (int i = 0; i < mn; ++i) {
		right.push(left.top());
		++rsize;
		left.pop();
		--lsize;
	}
	return this->getLeft();
};

std::string TextEditor::cursorRight(int k) {
	int mn = k <= rsize ? k : rsize;

	for (int i = 0; i < mn; ++i) {
		left.push(right.top());
		++lsize;
		right.pop();
		--rsize;
	}
	return this->getRight();

};