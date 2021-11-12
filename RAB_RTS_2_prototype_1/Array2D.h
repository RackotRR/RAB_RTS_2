#pragma once
#include <utility> 
#include <cassert>

// легковесный двумерный массив фиксированного размера на куче
template <typename T>
class Array2D { 
private:
	size_t sizeX{};
	size_t sizeY{};
	T* data{ nullptr };

	// запрет на копирование
	auto operator=(Array2D&) = delete;
	Array2D(Array2D&) = delete;
public:
	Array2D(size_t sizeX, size_t sizeY, T initialValue = T{})
		:
		sizeX{ sizeX },
		sizeY{ sizeY },
		data{ new T[sizeX * sizeY]{ initialValue } }
	{}

	// можно перемещать
	Array2D(Array2D&& other) noexcept {
		swap(other);
	}
	Array2D& operator=(Array2D&& other) noexcept {
		swap(other);
		return *this;
	} 
	~Array2D() {
		delete[] data;
	}

	// заполнить весь массив одним значением
	void Fill(T value) {
		size_t maxI{ sizeX * sizeY };
		for (size_t i{}; i < maxI; i++) {
			data[i] = value;
		}
	}
	 
	// доступна индексация через ()
	const T& operator() (size_t i, size_t j) const {
		assert(i < sizeX && j < sizeY); 

		return data[i + sizeX * j];
	}
	T& operator() (size_t i, size_t j) {
		assert(i < sizeX && j < sizeY);

		return data[i + sizeX * j];
	}
	 
	size_t SizeX() const {
		return sizeX;
	}
	size_t SizeY() const {
		return sizeY;
	}

	void swap(Array2D& other) noexcept {
		std::swap(sizeX, other.sizeX);
		std::swap(sizeY, other.sizeY);
		std::swap(data, other.data);
	}
}; 

template<typename T>
void swap(Array2D<T>& first, Array2D<T>& second) noexcept {
	first.swap(second);
}