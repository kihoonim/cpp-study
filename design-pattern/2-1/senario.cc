#include <iostream>
#include <sstream>

#include "senario.h"

HtmlElement::HtmlElement() {
    cout << "First Ctr" << endl;
}

HtmlElement::HtmlElement(const string& name, const string& text) : name(name), text(text) {
    cout << "Second Ctr" << endl;
}

string HtmlElement::str(int indent = 0) const {
    ostringstream oss;
    string i(indent_size * indent, ' ');
    oss << i << "<" << name << ">" << endl;
    if (text.size() > 0)
        oss << string(indent_size * (indent + 1), ' ') << text << endl;

    for (const auto& e : elements)
        oss << e.str(indent + 1);

    oss << i << "</" << name << ">" << endl;
    return oss.str();
}

int main() {
    string words[] = { "hello", "world" };
    HtmlElement list {"ul", ""};
    for (auto w : words)
        list.elements.emplace_back(HtmlElement{"li", w});
    printf(list.str().c_str());
}