#include <map>
#include <string>
#include <iostream>

// Очень некрасиво, но работает. Потом приведу в порядок.

class PrefixTree {
public:
    struct Node {
        Node() :
            word(""), is_used(false),
            children({}), parent(nullptr) {}
        Node(const std::string& word_, bool used_, Node* parent_) :
            word(word_), is_used(used_), children({}), parent(parent_) {}

        std::string word;
        bool is_used;
        Node* parent;
        std::map<char, Node*> children = {};
    };

public:
    PrefixTree() : _root(new Node) {}
    //~PrefixTree() {
    //    //TO DO: delete all nodes
    //}

    Node* find(const std::string& word_to_find) {
        Node* search = _root;
        std::size_t i = 0;
        while (search->word != word_to_find) {
            char search_character = word_to_find[i++];
            auto it = search->children.find(search_character);
            if (it != search->children.end()) 
            {
                search = it->second;
            }
            else {
                search = nullptr;
                break;
            }
        }
        if (search != nullptr && search->is_used == false)
            search = nullptr;

        return search;
    }

    Node* insert(const std::string& word_to_insert) {
        Node* insert = _root;
        std::string word_part;
        std::size_t i = 0;
        while (i != word_to_insert.length()) {
            char search_character = word_to_insert[i];
            auto it = insert->children.find(search_character);
            word_part += word_to_insert[i];
            ++i;
            if (it != insert->children.end())
            {
                insert = it->second;
            }
            else {
                Node* add = new Node(word_part, i == word_to_insert.length(), insert);
                insert->children[search_character] = add;
                insert = add;
            }
        }
        if (insert != _root)
            insert->is_used = true;
        else
            insert = nullptr;

        return insert;
    }


public:
    Node* _root;
};

void autocomplete() {
    unsigned input;
    std::cin >> input;
    unsigned counter = 0;
    PrefixTree tree;
    for (unsigned i = 0; i < input; ++i) {

        std::string word;
        std::cin >> word;

        PrefixTree::Node* search = tree.find(word);
        if (search != nullptr && search->children.empty()) {
            while (search->parent != nullptr
                && !search->parent->is_used
                && search->parent->children.size() == 1) {
                search = search->parent;
            }
            if (search == tree._root)
                counter += 1;
            else
                counter += search->parent->word.length() + 1;
        }
        else if (search == nullptr) {
            tree.insert(word);
            counter += word.length();
        }
        else if (!search->children.empty()) {
            counter += word.length();
        }
    }
    std::cout << counter;
}


int main() {
    autocomplete();
    return 0;
}
