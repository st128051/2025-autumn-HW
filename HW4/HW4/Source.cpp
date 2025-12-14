#include <iostream>
class String {
private:
    const char* str;
    int size;

    // конструктор для подстрок
    String(const char* s, int len) : str(s), size(len) {}

public:
    
    String(const char* s = "") : str(s), size(strlen(s)) {}

    // Получение подстроки через двойной оператор []
    class Helper {
    private:
        const String& s;
        int i;
    public:
        Helper(const String& s, int i) : s(s), i(i) {}
        String operator[](int j) const {
      
            return String(s.str + i, j - i);
        }
    };

    Helper operator[](int i) const {
        return Helper(*this, i);
    }

    const char* c_str() const { return str; }
};
int main() {
    String const hello("hello");
    String const hell = hello[0][4];  // "hell"
    String const ell = hello[1][4];   // "ell"
    String const empty = hello[2][2]; // ""

    std::cout << hell.c_str() << std::endl;  // hell
    std::cout << ell.c_str() << std::endl;   // ell
    std::cout << empty.c_str() << std::endl; // (пустая строка)

    return 0;
}