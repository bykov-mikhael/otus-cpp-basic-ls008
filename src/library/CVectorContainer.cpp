#include <sstream>
#include <string>

template<typename T>
CVectorContainer<T>::CVectorContainer()
    : head(nullptr)
    , m_size(0) {
}

template<typename T>
CVectorContainer<T>::~CVectorContainer() {
  Node *current = head;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }
  head = nullptr;
  m_size = 0;
}

template<typename T>
void CVectorContainer<T>::push_back(const T &value) {
  Node *new_node = new Node(value);
  if (head == nullptr) {
    head = new_node;
  } else {
    Node *temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = new_node;
  }
  m_size++;
}

template<typename T>
void CVectorContainer<T>::insert(int pos, const T &value) {
  if (pos < 0 || static_cast<size_t>(pos) >= m_size) {
    exit(0);
  }
  Node *new_node = new Node(value);
  if (pos == 0) {
    new_node->next = head;
    head = new_node;
  } else {
    Node *temp = head;
    for (int i = 0; i < pos - 1; i++) {
      temp = temp->next;
    }
    new_node->next = temp->next;
    temp->next = new_node;
  }
  m_size++;
}

template<typename T>
void CVectorContainer<T>::erase(int pos) {
  if (pos< 0 || static_cast<size_t>(pos) >= m_size) {
    exit(0);
  }
  Node *temp = head;
  if (pos == 0) {
    head = temp->next;
    delete temp;
  } else {
    for (int i = 0; i < pos - 1; i++) {
      temp = temp->next;
    }
    Node *to_delete = temp->next;
    temp->next = to_delete->next;
    delete to_delete;
  }
  m_size--;
}

template<typename T>
size_t CVectorContainer<T>::get_size() const {
  return m_size;
}

template<typename T>
T CVectorContainer<T>::operator[](int index) {
  if (index < 0 || static_cast<size_t>(index) >= m_size) {
    exit(0);
  }
  Node *temp = head;
  for (int i = 0; i < index; i++) {
    temp = temp->next;
  }
  return temp->data;
}

template<typename T>
void CVectorContainer<T>::print() const {
  Node *temp = head;
  while (temp != nullptr) {
    std::cout << temp->data << " ";
    temp = temp->next;
  }
  std::cout << std::endl;
}