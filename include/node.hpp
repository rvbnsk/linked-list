#include <utility>

#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node();
    Node(T, Node<T> *);
};

template<typename T>
class List
{
private:
    Node<T> *head;
    Node<T> *tail;
    size_t size;
public:
    List();
    List(const List<T> &list);
    List<T> &operator=(const List<T> &list);
    //List(T *, T *);
    ~List();
    size_t get_size();
    void insert(const T _data);
    void push_tail(const T _data);
    void pop();
    void pop_tail();
    

    template<typename U>
    friend std::ostream &operator<<(std::ostream &, const List<U> &);

    class Iterator
    {
        Node<T> *iter;
    public:
        Iterator();
        Iterator(Node<T> *);
        Iterator begin();
        Iterator end();
        const T &operator*() const;
        Iterator &operator++();
        bool operator==(const Iterator &_iter) const;
        bool operator!=(const Iterator &_iter) const;
    };
};

template<typename T>
Node<T>::Node() { this -> next = nullptr; }

template<typename T>
Node<T>::Node(T _data, Node<T> *_next) : data(_data), next(nullptr) {}

template<typename T>
List<T>::List() { head = nullptr; tail = nullptr; size = 0;}

template<typename T>
void List<T>::insert(const T _data)
{
    auto temp = new Node<T>;
    temp -> data = _data;

    if(head == nullptr)
    {
        head = temp;
        tail = temp;
        ++size;
        return;
    }

    temp -> next = head;
    head = temp;

    ++size;
}

template<typename T>
void List<T>::pop()
{
    if(head == nullptr)
    {
        std::cout << "list is empty" << std::endl;
        return;
    }

    if(head -> next == nullptr)
    {
        head = nullptr;
        std::cout << "last item removed" << std::endl;
        --size;
        return;
    }

    auto temp = head;

    while(temp != nullptr)
    {
        if(temp -> next -> next == nullptr)
        {
            temp -> next = nullptr;
            std::cout << "last item removed" << std::endl;
            break;
        }
        temp = temp -> next;
    }

    --size;
}

template<typename T>
List<T>::~List()
{
    auto current = head;
    while (current != nullptr)
    {
        auto next = current -> next;
        delete current;
        current = next;
    }
}

template<typename T>
size_t List<T>::get_size()
{
    return size;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &list)
{
    if(list.head == nullptr)
        os << "list empty" << std::endl;

    auto node = list.head;

    while(node != nullptr)
    {
        os << node -> data << std::endl;
        node = node -> next;
    }
    os << "size: " << list.size << std::endl;

    return os;
}

template<typename T>
List<T>::Iterator::Iterator() { iter = nullptr; }

template<typename T>
List<T>::Iterator::Iterator(Node<T> *_iter) : iter(_iter) {}


template<typename T>
const T &List<T>::Iterator::operator*() const
{
    return iter -> data;
}

template<typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++()
{
    iter = iter -> next;
    return this;
}

template<typename T>
bool List<T>::Iterator::operator!=(const Iterator &_iter) const
{
    return iter != _iter.iter;
}

template<typename T>
bool List<T>::Iterator::operator==(const Iterator &_iter) const
{
    return !(iter != _iter.iter); 
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::begin()
{
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::end()
{
    return Iterator(nullptr);
}


#endif //NODE_HPP