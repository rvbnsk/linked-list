#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

template <typename T> class Node {
public:
  T data;
  Node<T> *next;
  Node();
  Node(const T &, Node<T> *_next = nullptr);
};

template <typename T> class List {
private:
  Node<T> *head;
  size_t size;

public:
  List();
  List(const List<T> &) = delete;
  List(const List<T> &&) = delete;
  List<T> &operator=(const List<T> &) = delete;
  List<T> &operator=(const List<T> &&) = delete;
  T operator[](const int &);
  T at(const int &);
  ~List();

  size_t get_size();
  void insert(const T &_data);
  void pop();
  void erase();

  template <typename U>
  friend std::ostream &operator<<(std::ostream &, const List<U> &);

  class Iterator {
  private:
    Node<T> *iter;
    Iterator(Node<T> *);

  public:
    // metoda at - dostęp do konkretnego indeksu
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
};

template <typename T> Node<T>::Node() { this->next = nullptr; }

template <typename T>
Node<T>::Node(const T &_data, Node<T> *_next) : data(_data), next(_next) {}

template <typename T> List<T>::List() {
  head = nullptr;
  size = 0;
}

template <typename T> void List<T>::insert(const T &_data) {
  auto temp = new Node<T>;
  temp->data = _data;

  if (head == nullptr) {
    head = temp;
    ++size;
    return;
  }

  temp->next = head;
  head = temp;

  ++size;
}

template <typename T> void List<T>::pop() {
  if (head == nullptr) {
    std::cout << "list is empty" << std::endl;
    return;
  }

  if (head->next == nullptr) {
    head = nullptr;
    std::cout << "last item removed" << std::endl;
    --size;
    return;
  }

  auto temp = head;

  while (temp != nullptr) {
    if (temp->next->next == nullptr) {
      temp->next = nullptr;
      std::cout << "last item removed" << std::endl;
      break;
    }
    temp = temp->next;
  }

  --size;
}

template <typename T> void List<T>::erase() {
  if (head != nullptr) {
    while (head->next != nullptr) {
      auto temp = head;
      head = head->next;
      delete temp;
    }
    delete head;
  }
  head = nullptr;
  size = 0;
}

template <typename T> T List<T>::operator[](const int &index) {
  int i = 0;
  auto node = head;
  while (node != nullptr && i != index) {
    node = node->next;
    ++i;
  }
  return node->data;
}

template <typename T> T List<T>::at(const int &index) {
  if (index < size) {
    int i = 0;
    auto node = head;
    while (node != nullptr && i != index) {
      node = node->next;
      ++i;
    }

    return node->data;
  } else {
    throw "Out of range\n";
  }
}

template <typename T> List<T>::~List() {
  if (head != nullptr) {
    while (head->next != nullptr) {
      auto temp = head;
      head = head->next;
      delete temp;
    }
    delete head;
  }
}

template <typename T> size_t List<T>::get_size() { return size; }

template <typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &list) {
  if (list.head == nullptr)
    os << "list empty" << std::endl;

  auto node = list.head;

  while (node != nullptr) {
    os << node->data << std::endl;
    node = node->next;
  }
  os << "size: " << list.size << std::endl;

  return os;
}

template <typename T> List<T>::Iterator::Iterator() { iter = nullptr; }

template <typename T>
List<T>::Iterator::Iterator(Node<T> *_iter) : iter(_iter) {}

template <typename T> T &List<T>::Iterator::operator*() const {
  return iter->data;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
  Iterator temp = *this;
  iter = iter->next;
  return temp;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
  iter = iter->next;
  return *this;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator &_iter) const {
  return iter != _iter.iter;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator &_iter) const {
  return !(iter != _iter.iter);
}

template <typename T> typename List<T>::Iterator List<T>::begin() const {
  return Iterator(head);
}

template <typename T> typename List<T>::Iterator List<T>::end() const {
  return Iterator(nullptr);
}

#endif // NODE_HPP