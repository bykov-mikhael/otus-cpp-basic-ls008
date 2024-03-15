/**
 * Пользовательский код (вызывается из функции main) должен содержать следующий набор
 * действий с обоими контейнерами:
 * 1. создание объекта контейнера для хранения объектов типа int
 * 2. добавление в контейнер десяти элементов (0, 1 ... 9)
 * 3. вывод содержимого контейнера на экран ожидаемый результат: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
 * 4. вывод размера контейнера на экран ожидаемый результат: 10
 * 5. удаление третьего (по счёту), пятого и седьмого элементов
 * 6. вывод содержимого контейнера на экран ожидаемый результат: 0, 1, 3, 5, 7, 8, 9
 * 7. добавление элемента 10 в начало контейнера
 * 8. вывод содержимого контейнера на экран ожидаемый результат: 10, 0, 1, 3, 5, 7, 8, 9
 * 9. добавление элемента 20 в середину контейнера
 * 10. вывод содержимого контейнера на экран ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9
 * 11. добавление элемента 30 в конец контейнера
 * 12. вывод содержимого контейнера на экран ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30
 * 
 * Требования к минимальному интерфейсу:
 * - метод/ы (может быть несколько) добавления элементов в конец контейнера ( push_back )
 * - метод/ы вставки элементов в произвольную позицию ( insert )
 * - метод/ы удаления элементов из контейнера ( erase )
 * - метод получения текущего размера контейнера ( size )
 * - метод/ы получения доступа по индексу ( operator[] )
*/

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>


using namespace std;

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);
void count_words(std::istream& stream, Counter&);
void print_topk(std::ostream& stream, const Counter&, const size_t k);

Counter all_dicts;
mutex mx;

void add_maps(Counter& m1, Counter& m2)
{
    if (!m1.size()){
        m1 = m2;
        return;
    }
    for(auto it_m1 = m1.begin(), end_m1 = m1.end(),
             it_m2 = m2.begin(), end_m2 = m2.end();
             it_m1 != end_m1 ;)
    {
        if(it_m1 != end_m1 && it_m2 != end_m2) {
             if (it_m1->first == it_m2->first) it_m1->second += it_m2->second;
        }
        ++it_m1;
        ++it_m2;
    }
}

int count_chr(string name, vector<Counter>& cnts, mutex& mx)
{
    Counter freq_dict;
    std::ifstream input{name};
    if (!input.is_open()) {
        std::cerr << "Failed to open file " << name << '\n';
        return EXIT_FAILURE;
    }
    count_words(input, freq_dict);
    lock_guard lock(mx);
    cnts.emplace_back(freq_dict);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    vector<std::thread> counts_chr;
    vector<Counter> counts;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < argc; ++i) {
        counts_chr.emplace_back(count_chr, argv[i], ref(counts), ref(mx));
    }

    for (auto& i : counts_chr) {
        i.join();
    }

    while (counts.size()) {
        add_maps(all_dicts,counts.back());
        counts.pop_back();
    }

    print_topk(std::cout, all_dicts, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
}

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });    
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

     std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}