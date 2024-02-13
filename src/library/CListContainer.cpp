#include <cstddef>
#include <iostream>
#include <sstream>

/**
 * @brief конструктор
*/
template <typename T>
CListContainer<T>::CListContainer() : m_size(0) {
  m_values = new T[m_size];
}

/**
 * @brief конструктор
 * @param size размер массива
*/
template <typename T>
CListContainer<T>::CListContainer(size_t size) : m_size(size) {
  m_values = new T[m_size];
}

/**
 * @brief деструктор
*/
template <typename T>
CListContainer<T>::~CListContainer() {
  delete[] m_values;
}

/**
 * @brief добавить в конец массива
*/
template <typename T>
void CListContainer<T>::push_back(const T &value) {
  T *new_values = new T[m_size+1];
  for (size_t i = 0; i < m_size; i++) {
    new_values[i] = m_values[i];
  }
  new_values[m_size] = value;
  delete[] m_values;
  m_values = new_values;
  m_size++;
}

/**
 * @brief вставка заданного элемента в контейнер по заданному индексу
*/
template <typename T>
void CListContainer<T>::insert(int pos, const T &value) {
  if ((pos < 0) || (pos >= static_cast<int>(m_size))) {
    exit(0);
  } else {
    for (int i = static_cast<int>(m_size); i >= pos; i--) {
      m_values[i + 1] = m_values[i];
    }
    m_values[pos] = value;
    m_size++;
  }
  
}

/**
 * @brief удаление заданного элемента контейнера
*/
template <typename T>
void CListContainer<T>::erase(int pos) {
  if ((pos < 0) || (pos > static_cast<int>(m_size))) {
    exit(0);
  } else {
    for (int i = pos; i < static_cast<int>(m_size); i++) {
      m_values[i] = m_values[i + 1];
    }
  }
  m_size--;
}

/**
 * @brief размер контейнера
*/
template <typename T>
size_t CListContainer<T>::get_size() const {
  
  return static_cast<int>(m_size);
}

/**
 * @brief перегрузка оператора []
*/
template <typename T>
T CListContainer<T>::operator[](int pos) {
    if ((pos < 0) || (pos > static_cast<int>(m_size))) {
      exit(0);
    } else {
      return m_values[pos];
    }
}

/**
 * @brief печать массива
*/
template <typename T>
void CListContainer<T>::print() const {

  for (size_t i = 0; i < m_size; i++) {
    std::cout << m_values[i] << " ";
  }

  std::cout << std::endl;
}

/**
 * @brief проверка массива
*/
template <typename T>
void CListContainer<T>::check_size(int pos) {
  if (pos > static_cast<int>(m_size)) {
    T *new_values = new T[pos];
    for (int i = 0; i < pos; i++) {
      new_values[i] = m_values[i];
    }
    delete[] m_values;
    m_values = new_values;
    m_size = pos;
  }

  if (pos < static_cast<int>(m_size)) {
    T *new_values = new T[m_size + 1];
    for (int i = 0; i < static_cast<int>(m_size); i++) {
      new_values[i] = m_values[i];
    }
    delete[] m_values;
    m_values = new_values;
    m_size++; 
  }
}