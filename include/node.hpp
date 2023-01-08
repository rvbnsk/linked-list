#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

namespace lst {

namespace detail {

template <typename T>
struct Node {
   public:
    T data;
    Node<T>* next;
};

}  // namespace detail

// NOLINTBEGIN(hicpp-named-parameter,readability-named-parameter)
template <typename T>
class List {
   private:
    detail::Node<T>* head{nullptr};
    std::size_t size_{0};

   public:
    constexpr List() = default;
    constexpr List(std::initializer_list<T>);
    constexpr List(const List<T>&) noexcept;
    constexpr List(List<T>&&) noexcept;
    constexpr ~List();

    constexpr auto operator=(const List<T>&) noexcept -> List<T>&;
    constexpr auto operator=(List<T>&&) noexcept -> List<T>&;

    auto operator[](std::size_t) -> T&;
    auto operator[](std::size_t) const -> const T&;
    auto at(std::size_t) -> T&;
    auto at(std::size_t) const -> const T&;
    auto indices() -> std::vector<std::size_t>;
    auto indices() const -> std::vector<std::size_t>;

    auto size() const -> std::size_t;
    auto insert(const T&, std::size_t);
    auto push_back(const T&);
    auto pop();
    auto pop(std::size_t);
    auto remove(const T&);
    auto clear();

    auto sort(bool = true);
    auto reverse();

    template <typename U>
    friend constexpr auto operator<<(std::ostream&, const List<U>&)
        -> std::ostream&;

    template <typename T1, typename T2>
    friend constexpr auto operator==(const List<T1>& lhs, const List<T2>& rhs)
        -> bool;

    template <typename T1, typename T2>
    friend constexpr auto operator!=(const List<T1>& lhs, const List<T2>& rhs)
        -> bool;

    class iterator {
       private:
        detail::Node<T>* iter{.next = nullptr};
        explicit constexpr iterator(detail::Node<T>*);

       public:
        iterator();
        auto operator*() const -> T&;
        auto operator++(int) -> iterator;
        auto operator++() -> iterator&;
        auto operator==(const iterator&) const -> bool;
        auto operator!=(const iterator&) const -> bool;
        friend class List;
    };

    auto begin() const -> iterator;
    auto end() const -> iterator;
};
// NOLINTEND(hicpp-named-parameter,readability-named-parameter)

template <typename T>
constexpr List<T>::List(std::initializer_list<T> elems)
{
    for (const auto& elem : elems) { push_back(elem); }
}

template <typename T>
constexpr List<T>::List(const List<T>& list) noexcept
{
    *this = list;
}

template <typename T>
constexpr List<T>::List(List<T>&& list) noexcept
{
    *this = std::move(list);
}

template <typename T>
constexpr auto List<T>::operator=(const List<T>& list) noexcept -> List<T>&
{
    if (&list != this) {
        for (const auto elem : list) { push_back(elem); }
    }

    return *this;
}

template <typename T>
constexpr auto List<T>::operator=(List<T>&& list) noexcept -> List<T>&
{
    if (&list != this) {
        for (const auto elem : list) { push_back(elem); }
    }

    list.clear();
    list.head = nullptr;
    list.size_ = 0;

    return *this;
}

template <typename T1, typename T2>
constexpr auto operator==(const List<T1>& lhs, const List<T2>& rhs) -> bool
{
    if (lhs.size() != rhs.size()) { return false; }
    if constexpr (not std::is_same_v<T1, T2>) { return false; }
    for (const auto index : lhs.indices()) {
        if (lhs[index] != rhs[index]) { return false; }
    }
    return true;
}

template <typename T1, typename T2>
constexpr auto operator!=(const List<T1>& lhs, const List<T2>& rhs) -> bool
{
    return not(lhs == rhs);
}

template <typename T>
auto List<T>::insert(const T& data, std::size_t index)
{
    if (index > size_) { throw std::out_of_range("Index out of range"); }

    auto new_node = new detail::Node<T>{.data{data}, .next{nullptr}};

    if (index == 0) {
        new_node->next = head;
        head = new_node;
    }
    else {
        detail::Node<T>* current = head;
        while (--index != 0U) { current = current->next; }
        new_node->next = current->next;
        current->next = new_node;
    }

    ++size_;
}

template <typename T>
auto List<T>::push_back(const T& data)
{
    insert(data, size_);
}

template <typename T>
auto List<T>::pop()
{
    if (head == nullptr) { return; }

    if (head->next == nullptr) {
        head = nullptr;
        --size_;
        return;
    }

    auto* temp = head;

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
auto List<T>::pop(std::size_t index)
{
    if (index >= size_) { throw std::out_of_range("Index out of range"); }

    detail::Node<T>* current = head;
    if (index == 0) {
        head = head->next;
        delete current;
        size_--;
        return;
    }

    detail::Node<T>* prev = nullptr;
    while (index-- != 0U) {
        prev = current;
        current = current->next;
    }

    prev->next = current->next;
    delete current;
    size_--;
}

template <typename T>
auto List<T>::remove(const T& value)
{
    for (std::size_t idx = 0; idx < size_; idx++) {
        if ((*this)[idx] == value) {
            pop(idx);
            idx--;
        }
    }
}

template <typename T>
auto List<T>::clear()
{
    if (head != nullptr) {
        while (head->next != nullptr) {
            const auto* temp = head;
            head = head->next;
            delete temp;
        }
        delete head;
    }
    head = nullptr;
    size_ = 0;
}

template <typename T>
auto List<T>::sort(bool ascending)
{
    if (size_ == 0) { return; }

    if (ascending) { std::sort(begin(), end()); }
    else {
        std::sort(begin(), end(), std::greater<T>());
    }
}

template <typename T>
auto List<T>::reverse()
{
    std::reverse(begin(), end());
}

template <typename T>
auto List<T>::operator[](std::size_t index) -> T&
{
    auto idx{0};
    auto* node = head;
    while (node != nullptr and idx != index) {
        node = node->next;
        ++idx;
    }
    return node->data;
}

template <typename T>
auto List<T>::operator[](std::size_t index) const -> const T&
{
    std::size_t idx{0};
    auto* node = head;
    while (node != nullptr and idx != index) {
        node = node->next;
        ++idx;
    }
    return node->data;
}

template <typename T>
auto List<T>::at(std::size_t index) -> T&
{
    if (index > size_) { throw std::out_of_range{"List::at"}; }
    std::size_t idx{0};
    auto* node = head;
    while (node != nullptr and idx != index) {
        node = node->next;
        ++idx;
    }
    return node->data;
}

template <typename T>
auto List<T>::at(std::size_t index) const -> const T&
{
    if (index > size_) { throw std::out_of_range{"List::at"}; }
    auto idx{0};
    auto* node = head;
    while (node != nullptr and idx != index) {
        node = node->next;
        ++idx;
    }
    return node->data;
}

template <typename T>
auto List<T>::indices() -> std::vector<std::size_t>
{
    std::vector<std::size_t> result;
    for (std::size_t i = 0; i < size(); ++i) { result.push_back(i); }
    return result;
}

template <typename T>
auto List<T>::indices() const -> std::vector<std::size_t>
{
    std::vector<std::size_t> result;
    for (std::size_t i = 0; i < size(); ++i) { result.push_back(i); }
    return result;
}

template <typename T>
constexpr List<T>::~List()
{
    if (head != nullptr) {
        while (head->next != nullptr) {
            const auto* temp = head;
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
// NOLINTNEXTLINE(readability-identifier-length)
constexpr auto operator<<(std::ostream& os, const List<T>& list)
    -> std::ostream&
{
    auto* node = list.head;

    while (node != nullptr) {
        os << node->data << std::endl;
        node = node->next;
    }
    os << "size: " << list.size_ << std::endl;

    return os;
}

template <typename T>
List<T>::iterator::iterator() : iter{nullptr}
{
}

template <typename T>
constexpr List<T>::iterator::iterator(detail::Node<T>* iter_) : iter{iter_}
{
}

template <typename T>
auto List<T>::iterator::operator*() const -> T&
{
    return iter->data;
}

template <typename T>
auto List<T>::iterator::operator++(int) -> typename List<T>::iterator
{
    iterator temp = *this;
    iter = iter->next;
    return temp;
}

template <typename T>
auto List<T>::iterator::operator++() -> typename List<T>::iterator&
{
    iter = iter->next;
    return *this;
}

template <typename T>
auto List<T>::iterator::operator!=(const iterator& iter_) const -> bool
{
    return iter != iter_.iter;
}

template <typename T>
auto List<T>::iterator::operator==(const iterator& iter_) const -> bool
{
    return !(iter != iter_.iter);
}

template <typename T>
auto List<T>::begin() const -> typename List<T>::iterator
{
    return iterator(head);
}

template <typename T>
auto List<T>::end() const -> typename List<T>::iterator
{
    return iterator(nullptr);
}

}  // namespace lst

#endif  // NODE_HPP