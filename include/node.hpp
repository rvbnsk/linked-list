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
    List(const List<T> &list) noexcept;
    List(List<T> &&list) noexcept;
    constexpr auto operator=(const List<T> &list) noexcept -> List<T> &;
    constexpr auto operator=(List<T> &&list) noexcept -> List<T> &;
    auto operator[](std::size_t) -> T &;
    auto operator[](std::size_t) const -> const T &;
    auto at(std::size_t) -> T &;
    auto at(std::size_t) const -> const T &;
    ~List();

    auto size() const -> std::size_t;
    void insert(const T &data_);
    void pop();
    void erase();

    template <typename U>
    friend auto operator<<(std::ostream &, const List<U> &) -> std::ostream &;

    class Iterator {
       private:
        detail::Node<T> *iter{.next = nullptr};
        explicit Iterator(detail::Node<T> *iter_);

       public:
        Iterator();
        auto operator*() const -> T &;
        auto operator++(int) -> Iterator;
        auto operator++() -> Iterator &;
        auto operator==(const Iterator &iter_) const -> bool;
        auto operator!=(const Iterator &iter_) const -> bool;
        friend class List;
    };

    auto begin() const -> Iterator;
    auto end() const -> Iterator;
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
constexpr auto List<T>::operator=(const List<T> &list) noexcept -> List<T> &
{
    if (&list != this) {
        this->head = list.head;
        this->size_ = list.size_;
    }

    return *this;
}

template <typename T>
constexpr auto List<T>::operator=(List<T> &&list) noexcept -> List<T> &
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
auto List<T>::operator[](std::size_t index) -> T &
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
auto List<T>::operator[](std::size_t index) const -> const T &
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
auto List<T>::at(std::size_t index) -> T &
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
auto List<T>::at(std::size_t index) const -> const T &
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
auto List<T>::size() const -> std::size_t
{
    return size_;
}

template <typename T>
auto operator<<(std::ostream &os, const List<T> &list) -> std::ostream &
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
auto List<T>::Iterator::operator*() const -> T &
{
    return iter->data;
}

template <typename T>
auto List<T>::Iterator::operator++(int) -> typename List<T>::Iterator
{
    Iterator temp = *this;
    iter = iter->next;
    return temp;
}

template <typename T>
auto List<T>::Iterator::operator++() -> typename List<T>::Iterator &
{
    iter = iter->next;
    return *this;
}

template <typename T>
auto List<T>::Iterator::operator!=(const Iterator &iter_) const -> bool
{
    return iter != iter_.iter;
}

template <typename T>
auto List<T>::Iterator::operator==(const Iterator &iter_) const -> bool
{
    return !(iter != iter_.iter);
}

template <typename T>
auto List<T>::begin() const -> typename List<T>::Iterator
{
    return Iterator(head);
}

template <typename T>
auto List<T>::end() const -> typename List<T>::Iterator
{
    return Iterator(nullptr);
}

#endif  // NODE_HPP