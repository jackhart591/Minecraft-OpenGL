#pragma once

#define Vector2 Vector<int, 2>
#define Vector3 Vector<int, 3>

template <typename T, size_t N>
class Vector {
private:
	T elems[N];

public:
	// Constructors
	Vector() {
		for (size_t i = 0; i < N; i++) {
			elems[i] = T();
		}
	}

	Vector(std::initializer_list<T> values) {
		size_t i = 0;
		for (const auto& value : values) {
			elems[i++] = value;
			if (i >= N) break;
		}
	}
	
	// Operator overloads
	Vector<T, N> operator+(const Vector& other) const {
		Vector result;
		for (size_t i = 0; i < N; i++) {
			result.elems[i] = elems[i] + other.elems[i];
		}

		return result;
	}

	const T& operator[](size_t index) const {
		if (index < N) {
			return elements[index];
		}
		else {
			// Handle out-of-bounds access appropriately, e.g., throw an exception
			throw std::out_of_range("Index out of bounds");
		}
	}

	T& operator[](size_t index) {
		if (index < N) {
			return elems[index];
		}
		else {
			// Handle out-of-bounds access appropriately, e.g., throw an exception
			throw std::out_of_range("Index out of bounds");
		}
	}

	T sum() const {
		T result = T();
		for (size_t i = 0; i < N; i++) {
			result += elems[i];
		}

		return result;
	}
	
	// Comparitive operators
	bool operator<(const Vector& other) const {
		return sum() < other.sum();
	}

	bool operator<=(const Vector& other) const {
		return sum() <= other.sum();
	}

	bool operator>(const Vector& other) const {
		return sum() > other.sum();
	}

	bool operator>=(const Vector& other) const {
		return sum() >= other.sum();
	}

	bool operator==(const Vector& other) const {
		for (int i = 0; i < N; i++) {
			if (this->elems[i] != other->elems[i]) {
				return false;
			}
		}
		
		return true;
	}

	bool operator!=(const Vector& other) const {
		for (int i = 0; i < N; i++) {
			if (this->elems[i] != other->elems[i]) {
				return true;
			}
		}

		return false;
	}

	// Accessors for x, y, z
	const T& x() const { return elems[0]; }
	T& x() { return elems[0]; }

	const T& y() const { return elems[1]; }
	T& y() { return elems[1]; }

	const T& z() const { return elems[2]; }
	T& z() { return elems[2]; }
};
