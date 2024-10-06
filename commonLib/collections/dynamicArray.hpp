#pragma once

#include<random>

namespace Collections {
template<class T> using imutableArray = T const * const;
template<class T> using imutableArray2D = T const * const * const;

template<class T>
class DynamicArray {
public:
    inline static T* newArray(int size);
    inline static T* newArray(int size, const T& value);
    inline static T** newArray2D(int size1D, int size2D);
    inline static T** newArray2D(int size1D, int size2D, const T& value);
    inline static void deleteArray(T* array);
    inline static void deleteArray2D(T** array, int size1D);
    inline static void safetyDeleteArray(T* array);
    inline static void safetyDeleteArray2D(T** array, int size1D);

    inline static void copy(imutableArray<T> srcArray, T* distArray, int size);
    inline static void copy2D(imutableArray2D<T> srcArray, T** distArray, int size1D, int size2D);
    inline static void fill(T* array, int size, const T& value);
    inline static void fill2D(T** array, int size1D, int size2D, const T& value);
    inline static void shaffle(T* array, int size, std::mt19937 randEngine);

private:
    DynamicArray() = delete;
}; 

template<class T>
inline T* DynamicArray<T>::newArray(int size) {
    return new T[size];
}

template<class T>
inline T* DynamicArray<T>::newArray(int size, const T& value) {
    T* array = new T[size];
    for(int i = 0; i < size; ++i) array[i] = value;
    return array;
}

template<class T>
inline T** DynamicArray<T>::newArray2D(int size1D, int size2D) {
    T** array = new T*[size1D];
    for(int i = 0; i < size1D; ++i) array[i] = new T[size2D];
    return array;
}

template<class T>
inline T** DynamicArray<T>::newArray2D(int size1D, int size2D, const T& value) {
    T** array = newArray2D(size1D, size2D);
    for(int i = 0; i < size1D; ++i) {
        for(int j = 0; j < size2D; ++j) {
            array[i][j] = value;
        }
    }
    return array;
}

template<class T>
inline void DynamicArray<T>::deleteArray(T* array) {
    delete[] array;
}

template<class T>
inline void DynamicArray<T>::deleteArray2D(T** array, int size1D) {
    for(int i = 0; i < size1D; ++i) {
        delete[] array[i];
    }
    delete[] array;
}

template<class T>
inline void DynamicArray<T>::safetyDeleteArray(T* array) {
    if(array == nullptr) return;
    delete[] array;
    array = nullptr;
}

template<class T>
inline void DynamicArray<T>::safetyDeleteArray2D(T** array, int size1D) {
    if(array == nullptr) return;
    
    for(int i = 0; i < size1D; ++i) {
        if(array[i] == nullptr) continue;
        delete[] array[i];
    }
    delete[] array;
}

template<class T>
inline void DynamicArray<T>::copy(imutableArray<T> srcArray, T* distArray, int size) {
    for(int i = 0; i < size; ++i) distArray[i] = srcArray[i];
}

template<class T>
inline void DynamicArray<T>::copy2D(imutableArray2D<T> srcArray, T** distArray, int size1D, int size2D) {
    for(int i = 0; i < size1D; ++i) {
        for(int j = 0; j < size2D; ++j) {
            distArray[i][j] = srcArray[i][j];
        }
    }
}

template<class T>
inline void DynamicArray<T>::fill(T* array, int size, const T& value) {
    for(int i = 0; i < size; ++i)
        array[i] = value;
}

template<class T>
inline void DynamicArray<T>::fill2D(T** array, int size1D, int size2D, const T& value) {
    for(int i = 0; i < size1D; ++i) {
        for(int j = 0; j < size2D; ++j) {
            array[i][j] = value;
        }
    }
}

template<class T>
inline void DynamicArray<T>::shaffle(T* array, int size, std::mt19937 randEngine) {
    for(int end = size; end >= 1; --end) {
        int rand = randEngine() % end;
        int tail = end - 1;
        
        int temp = array[tail];
        array[tail] = array[rand];
        array[rand] = temp;
    }
}
}