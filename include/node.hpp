#include <utility>
#include <vector>

#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node();
    Node(const T &, Node<T> *_next = nullptr);
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
    List(const List<T> &) = delete;
    List(const List<T> &&) = delete;
    List<T> &operator=(const List<T> &) = delete;
    List<T> &operator=(const List<T> &&l) = delete;
    ~List();

    size_t get_size();
    void insert(const T &_data);
    //void push_tail(const T _data);
    void pop();
    //void pop_tail();
    void erase();

    //wyszukiwanie konkretnej wartości 
    //iterator
    //std::move
    //std::copy

    template<typename U>
    friend std::ostream &operator<<(std::ostream &, const List<U> &);

    class Iterator //klasa dziedzicząca po List
    {
    private:
        Node<T> *iter;
        Iterator(Node<T> *);
    public:
        //metoda at - dostęp do konkretnego indeksu
        Iterator();
        T &operator*() const;
        Iterator operator++(int);
        Iterator &operator++();
        bool operator==(const Iterator &_iter) const;
        bool operator!=(const Iterator &_iter) const;
        friend class List;
    };

    Iterator begin() const;
    Iterator end() const;
    Iterator insert(Iterator, const T &);
    Iterator erase(Iterator);
};

template<typename T>
Node<T>::Node() { this -> next = nullptr; }

template<typename T>
Node<T>::Node(const T &_data, Node<T> *_next) : data(_data), next(_next) {}

template<typename T>
List<T>::List() { head = tail = new Node<T>(); size = 0;}

template<typename T>
void List<T>::insert(const T &_data)
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
    while (head -> next != nullptr)
    {
        auto temp = head;
        head = head -> next;
        delete temp;
    }
    delete head;
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
T &List<T>::Iterator::operator*() const
{
    return iter -> data;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    iter = iter -> next;
    return temp;
}

template<typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++()
{
    iter = iter -> next;
    return *this;
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
typename List<T>::Iterator List<T>::begin() const
{
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() const
{
    return Iterator(nullptr);
}

template<typename T>
typename List<T>::Iterator List<T>::insert(Iterator index, const T &_data)
{
    auto temp = new Node<T>(_data, index.iter -> next);
    if(index.iter == tail)
        tail = temp;
    index.iter -> next = temp;

    return index;
}

template<typename T>
typename List<T>::Iterator List<T>::erase(Iterator index)
{
    auto _del = index.iter -> next;
    index.iter -> next = index.iter -> next -> next;
    if(_del == tail)
        tail = index.iter;
    delete _del;
    
    return index;
}


#endif //NODE_HPP