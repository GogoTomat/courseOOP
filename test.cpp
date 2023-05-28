#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

// Класс, реализующий алгоритмы сортировки
class SortingAlgorithms {
public:
    // Сортировка пузырьком
    static void bubbleSort(std::vector<int>& arr, int& comparisons, int& swaps) {
        for (int i = 0; i < arr.size() - 1; i++) {
            for (int j = 0; j < arr.size() - i - 1; j++) {
                comparisons++;
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swaps++;
                }
            }
        }
    }
    
    // Сортировка выбором
    static void selectionSort(std::vector<int>& arr, int& comparisons, int& swaps) {
        for (int i = 0; i < arr.size() - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < arr.size(); j++) {
                comparisons++;
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            std::swap(arr[i], arr[min_idx]);
            swaps++;
        }
    }
    
    // Сортировка вставками
    static void insertionSort(std::vector<int>& arr, int& comparisons, int& swaps) {
        for (int i = 1; i < arr.size(); i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                comparisons++;
                arr[j + 1] = arr[j];
                swaps++;
                j--;
            }
            arr[j + 1] = key;
            swaps++;
        }
    }
};

// Класс, позволяющий исследовать различные алгоритмы сортировки
class SortingExperiment {
public:
    // Задание массива исходных данных для сортировки
    void setData(const std::vector<int>& data) {
        m_data = data;
    }
    
    // Генерация массива исходных данных с заданными характеристиками
    void generateData(int size, const std::string& distribution) {
        std::random_device rd;
        std::mt19937 gen(rd());
        if (distribution == "random") {
            // Заполнение случайными значениями
            std::uniform_int_distribution<> dis(1, 1000);//целые числа от 1 до 1000
            m_data.resize(size);
            for (int i = 0; i < size; i++) {
                m_data[i] = dis(gen);
            }
        } else if (distribution == "ascending") {
            // Заполнение упорядоченными значениями
            m_data.resize(size);
            for (int i = 0; i < size; i++) {
                m_data[i] = i + 1;
            }
        } else if (distribution == "descending") {
            // Заполнение обратно упорядоченными значениями
            m_data.resize(size);
            for (int i = 0; i < size; i++) {
                m_data[i] = size - i;
            }
        } else {
            std::cerr << "Unknown distribution: " << distribution << std::endl;
        }
    }
    
    // Определение количества сравнений и перестановок, выполненных в процессе сортировки массива
    void runSort(const std::string& algorithm) {
        int comparisons = 0;
        int swaps = 0;
        std::vector<int> arr = m_data;
        if (algorithm == "bubble") {
            SortingAlgorithms::bubbleSort(arr, comparisons, swaps);
        } else if (algorithm == "selection") {
            SortingAlgorithms::selectionSort(arr, comparisons, swaps);
        } else if (algorithm == "insertion") {
            SortingAlgorithms::insertionSort(arr, comparisons, swaps);
        } else {
            std::cerr << "Unknown algorithm: " << algorithm << std::endl;
            return;
        }
        // Вывод результатов
        std::cout << "Algorithm: " << algorithm << std::endl;
        std::cout << "Comparisons: " << comparisons << std::endl;
        std::cout << "Swaps: " << swaps << std::endl;
    }
    
    // Сравнение показателей различных алгоритмов, выполненных над идентичными массивами
    void compareAlgorithms(const std::vector<std::string>& algorithms) {
        std::cout << "Comparing algorithms: ";
        for (const auto& algorithm : algorithms) {
            std::cout << algorithm << " ";
        }
        std::cout << std::endl;
        for (const auto& algorithm : algorithms) {
            auto start_time = std::chrono::high_resolution_clock::now();
            runSort(algorithm);
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            std::cout << "Time taken by " << algorithm << ": " << duration.count() << " microseconds" << std::endl;
        }
    }
    
private:
    std::vector<int> m_data;
};

// Пример использования класса SortingExperiment
int main() {
    SortingExperiment experiment;
    
    // Генерация массива исходных данных
    experiment.generateData(1000, "random");
    
    // Задание массива исходных данных
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    experiment.setData(data);
    
    // Запуск сортировки выбранным алгоритмом
    experiment.runSort("bubble");
    
    // Сравнение показателей различных алгоритмов
    std::vector<std::string> algorithms = {"bubble", "selection", "insertion"};
    experiment.compareAlgorithms(algorithms);
    
    return 0;
}
