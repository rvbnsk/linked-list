#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <stdexcept>

namespace detail {

template <typename T>
struct Node {
   public:
    T data;
    Node<T> *next;
};

}  // namespace detail

template <typename T>
class List {
   private:
    detail::Node<T> *head = nullptr;
    std::size_t size_ = 0;

   public:
    List() = default;
    List(const List<T> &) noexcept;
    List(List<T> &&) noexcept;
    List<T> &operator=(const List<T> &) noexcept;
    List<T> &operator=(List<T> &&) noexcept;
    T &operator[](std::size_t);
    const T &operator[](std::size_t) const;
    T &at(std::size_t);
    const T &at(std::size_t) const;
    ~List();

    std::size_t size() const;
    void insert(const T &data_);
    void pop();
    void erase();

    template <typename U>
    friend std::ostream &operator<<(std::ostream &, const List<U> &);

    class Iterator {
       private:
        detail::Node<T> *iter{.next = nullptr};
        Iterator(detail::Node<T> *);

       public:
        Iterator();
        T &operator*() const;
        Iterator operator++(int);
        Iterator &operator++();
        bool operator==(const Iterator &iter_) const;
        bool operator!=(const Iterator &iter_) const;
        friend class List;
    };

    Iterator begin() const;
    Iterator end() const;
};

template <typename T>
List<T>::List(const List<T> &list) noexcept : head(nullptr), size_(0)
{
    head = list.head;
    size_ = list.size_;
}

template <typename T>
List<T>::List(List<T> &&list) noexcept : head(nullptr), size_(0)
{
    head = list.head;
    size_ = list.size_;

    list.head = nullptr;
    list.size_ = 0;
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &list) noexcept
{
    this->head = list.head;
    this->size_ = list.size_;

    return *this;
}

template <typename T>
List<T> &List<T>::operator=(List<T> &&list) noexcept
{
    this->head = list.head;
    this->size_ = list.size_;

    list.head = nullptr;
    list.size_ = 0;

    return *this;
}

template <typename T>
void List<T>::insert(const T &data_)
{
    auto *temp = new detail::Node<T>;
    temp->next = nullptr;
    temp->data = data_;

    if (head == nullptr) {
        head = temp;
        ++size_;
        return;
    }

    temp->next = head;
    head = temp;

    ++size_;
}

template <typename T>
void List<T>::pop()
{
    if (head == nullptr) { return; }

    if (head->next == nullptr) {
        head = nullptr;
        --size_;
        return;
    }

    auto *temp = head;

    while (temp != nullptr) {
        if (temp->next->next == nullptr) {
            temp->next = nullptr;
            break;
        }
        temp = temp->next;
    }

    --size_;
}

template <typename T>
void List<T>::erase()
{
    if (head != nullptr) {
        while (head->next != nullptr) {
            auto *temp = head;
            head = head->next;
            delete temp;
        }
        delete head;
    }
    head = nullptr;
    size_ = 0;
}

template <typename T>
T &List<T>::operator[](std::size_t index)
{
    auto i{0};
    auto *node = head;
    while (node != nullptr && i != index) {
        node = node->next;
        ++i;
    }
    return node->data;
}

template <typename T>
const T &List<T>::operator[](std::size_t index) const
{
    auto i{0};
    auto *node = head;
    while (node != nullptr && i != index) {
        node = node->next;
        ++i;
    }
    return node->data;
}

template <typename T>
T &List<T>::at(std::size_t index)
{
    if (index < size_) {
        auto i{0};
        auto *node = head;
        while (node != nullptr && i != index) {
            node = node->next;
            ++i;
        }

        return node->data;
    }
    else {
        throw std::out_of_range{"List::at"};
    }
}

template <typename T>
const T &List<T>::at(std::size_t index) const
{
    if (index < size_) {
        auto i{0};
        auto *node = head;
        while (node != nullptr && i != index) {
            node = node->next;
            ++i;
        }

        return node->data;
    }
    else {
        throw std::out_of_range{"List::at"};
    }
}

template <typename T>
List<T>::~List()
{
    if (head != nullptr) {
        while (head->next != nullptr) {
            auto *temp = head;
            head = head->next;
            delete temp;
        }
        delete head;
    }
    size_ = 0;
}

template <typename T>
std::size_t List<T>::size() const
{
    return size_;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &list)
{
    auto *node = list.head;

    while (node != nullptr) {
        os << node->data << std::endl;
        node = node->next;
    }
    os << "size: " << list.size_ << std::endl;

    return os;
}

template <typename T>
List<T>::Iterator::Iterator()
{
    iter = nullptr;
}

template <typename T>
List<T>::Iterator::Iterator(detail::Node<T> *iter_) : iter(iter_)
{
}

template <typename T>
T &List<T>::Iterator::operator*() const
{
    return iter->data;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    iter = iter->next;
    return temp;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++()
{
    iter = iter->next;
    return *this;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator &iter_) const
{
    return iter != iter_.iter;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator &iter_) const
{
    return !(iter != iter_.iter);
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const
{
    return Iterator(head);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const
{
    return Iterator(nullptr);
}

#endif  // NODE_HPP