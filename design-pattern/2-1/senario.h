#include <string>
#include <vector>

using namespace std;

class HtmlElement
{
public:
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement();
    HtmlElement(const string& name, const string& text);
    string str(int indent = 0) const;
};
