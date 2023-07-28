#include <cassert>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <vector>

class HTMLElement {
protected:
    std::string text;
public:
    explicit HTMLElement(const std::string& text): text{text} {}
    virtual std::string getHTMLString() = 0;
};

class HTMLImage: public HTMLElement {
public:
    explicit HTMLImage(const std::string& text): HTMLElement(text) {}
    std::string getHTMLString() override;
};

std::string HTMLImage::getHTMLString() {
    std::string result;
    result.append("<img>");
    result.append(this->text);
    result.append("</img>");
    return result;
}

class HTMLParagraph: public HTMLElement{
public:
    explicit HTMLParagraph(const std::string& text): HTMLElement(text) {}
    std::string getHTMLString() override;
};

std::string HTMLParagraph::getHTMLString() {
    std::string result;
    result.append("<p>");
    result.append(this->text);
    result.append("</p>");
    return result;
}

template <typename TElem>
class HTMLBuilder {
protected:
    std::vector<TElem> elements;
public:
    HTMLBuilder() = default;
    std::vector<TElem> getElements() const;
    HTMLBuilder<TElem>& operator+=(HTMLElement* element);
    friend std::ostream& operator<<(std::ostream& ostream,const HTMLBuilder& htmlBuilder) {
        std::string result;
        result.append("<html><body>");
        for (auto element: htmlBuilder.getElements()) {
            result.append(element->getHTMLString());
        }
        result.append("</body></html>");
        ostream << result;
        return ostream;
    }
};

template<typename TElem>
HTMLBuilder<TElem> &HTMLBuilder<TElem>::operator+=(HTMLElement *element) {
    if (element == nullptr)
        throw std::runtime_error("Cannot add a null element!");
    this->elements.push_back(element);
    return *this;
}

template<typename TElem>
std::vector<TElem> HTMLBuilder<TElem>::getElements() const {
    return this->elements;
}

void fct1() {
    HTMLElement* p1 = new HTMLParagraph{"Examination"};
    assert(p1->getHTMLString() == "<p>Examination</p>");
    HTMLElement* p2 = nullptr;
    HTMLElement* i1 = new HTMLImage{"a.jpg"};
    HTMLElement* i2 = new HTMLImage{"b.jpg"};
    assert(i2->getHTMLString() == "<img>b.jpg</img>");
    HTMLBuilder<HTMLElement*> html{};
    try {
        html += p2;
        assert(false);
    } catch (std::runtime_error& e) {
        assert(strcmp(e.what(), "Cannot add a null element!") == 0);
    }

    ((html += p1) += i1) += i2;
    std::cout << html;
    delete p1; delete p2;
    delete i1; delete i2;
}

int main() {
    fct1();
    return 0;
}
