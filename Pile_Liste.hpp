#ifndef PILE_LISTE_HPP
#define PILE_LISTE_HPP

#include <stdexcept>

// Pile generique implementee a l'aide d'une liste chainee simple.
// Implementation manuelle (pas d'utilisation de std::list ni de
// std::forward_list) : chaque noeud est gere directement avec new/delete.
template <typename T>
class Pile_Liste {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& v, Node* n) : value(v), next(n) {}
    };

    Node* head;
    std::size_t count;

public:
    Pile_Liste() : head(nullptr), count(0) {}

    ~Pile_Liste() {
        while (!isEmpty())
            pop();
    }

    void push(const T& value) {
        head = new Node(value, head);
        ++count;
    }

    void pop() {
        if (isEmpty())
            throw std::underflow_error("Pile vide");
        Node* temp = head;
        head = head->next;
        delete temp;
        --count;
    }

    T& top() {
        if (isEmpty())
            throw std::underflow_error("Pile vide");
        return head->value;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    std::size_t size() const {
        return count;
    }
};

#endif
