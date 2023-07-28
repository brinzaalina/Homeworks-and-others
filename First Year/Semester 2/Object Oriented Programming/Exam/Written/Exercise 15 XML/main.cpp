#include <iostream>
#include <cassert>
#include <vector>

class XMLAttribute {
private:
    std::string type;
    std::string attribute;
public:
    XMLAttribute(const std::string& type, const std::string& attribute): type(type), attribute(attribute) {}
    std::string getXMLString() {
        return type+"=\""+attribute+"\"";
    }
};

class XMLNode {
private:
    std::string type;
    std::string attribute;
    std::vector<XMLAttribute> attributes;
    std::vector<XMLNode*> childNodes;
public:
    XMLNode(const std::string& type, const std::string& attribute): type(type), attribute(attribute) {}
    std::string getXMLString() {
        std::string result;
        result.append("<");
        result.append(type);
        for (auto attr: attributes) {
            result.append(" ");
            result.append(attr.getXMLString());
        }
        result.append(">");
        for (auto child: childNodes) {
            result.append(child->getXMLString());
        }
        result.append(attribute);
        result.append("</");
        result.append(type);
        result.append(">");
        return result;
    }

    XMLNode& addAttribute(XMLAttribute& attribute1) {
        attributes.push_back(attribute1);
        return *this;
    }

    XMLNode& addChildNode(XMLNode* node) {
        childNodes.push_back(node);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& ostream, XMLNode& xmlNode) {
        ostream << xmlNode.getXMLString();
        return ostream;
    }
};

void fct2() {
    XMLAttribute a1{"age", "40"};
    assert(a1.getXMLString() == "age=\"40\"");
    XMLAttribute a2{"profession", "comedian"};
    XMLNode ch1{"firstname", "Anna"};
    assert(ch1.getXMLString() == "<firstname>Anna</firstname>");
    XMLNode ch2{"lastname", "Smith"};

    XMLNode p1{"person", ""};
    p1.addAttribute(a1).addAttribute(a2);
    p1.addChildNode(&ch1).addChildNode(&ch2);

    XMLNode p2{"dog", "happy"};

    XMLNode rootNode{"root", ""};
    rootNode.addChildNode(&p1).addChildNode(&p2);

    std::cout << rootNode;
}

int main() {
    fct2();
    return 0;
}