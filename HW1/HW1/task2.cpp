#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

long long evalRPN(const string& line) {
    istringstream s(line);
    stack<long long> st;
    string t;
    while (s >> t) {
        if (t == "+" || t == "-" || t == "*" || t == "/") {
            long long a = st.top(); st.pop();
            long long b = st.top(); st.pop();
            if (t == "+") st.push(b + a);
            else if (t == "-") st.push(b - a);
            else if (t == "*") st.push(b * a);
            else st.push(a == 0 ? 0 : b / a);
        }
        else {
            st.push(stoll(t));
        }
    }
    return st.top();
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string line;
    bool first = true;
    while (getline(in, line)) {
        long long value = evalRPN(line);
        if (!first) out << '\n';
        out << line << " = " << value;
        first = false;
    }
}