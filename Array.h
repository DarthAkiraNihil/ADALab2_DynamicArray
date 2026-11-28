//
// Created by EgrZver on 29.10.2026.
//

#ifndef ADALAB2_DYNAMICARRAY_ARRAY_H
#define ADALAB2_DYNAMICARRAY_ARRAY_H

#include <algorithm>
#include <cstdlib>


inline constexpr int DEFAULT_CAPACITY = 16;
inline constexpr float EXTENSION_FACTOR = 1.6f;

template<typename T>
class Array final {

    public:
        class Iterator {
            public:
                Iterator(int start, int end, Array* data) {
                    this->current = start;
                    this->end = end;
                    this->data = data;
                }

                T& get() {
                    return (*this->data)[std::abs(this->current)];
                }

                void set(const T& value) {
                    (*this->data)[std::abs(this->current)] = value;
                }

                void next() {
                    if (this->hasNext()) {
                        ++this->current;
                    }
                }

                [[nodiscard]] bool hasNext() const {
                    return this->current < this->end;
                }

            private:
                int current;
                int end;
                Array* data;
        };

        class ConstIterator {
            public:
                ConstIterator(int start, int end, const Array* data) {
                    this->current = start;
                    this->end = end;
                    this->data = data;
                }

                const T& get() const {
                    return (*this->data)[std::abs(this->current)];
                }

                void next() {
                    if (this->hasNext()) {
                        ++this->current;
                    }
                }

                [[nodiscard]] bool hasNext() const {
                    return this->current < this->end;
                }

            private:
                int current;
                int end;
                const Array* data;
        };

        explicit Array() {
            this->capacity = DEFAULT_CAPACITY;
            this->count = 0;
            this->data = static_cast<T*>(std::malloc(DEFAULT_CAPACITY * sizeof(T)));
        }

        explicit Array(int capacity) {
            this->capacity = capacity;
            this->count = 0;
            this->data = static_cast<T*>(std::malloc(capacity * sizeof(T)));
        }

        Array(const Array& other) {
            this->capacity = other.capacity;
            this->count = other.count;
            this->data = static_cast<T*>(std::malloc(other.capacity * sizeof(T)));

            for (int i = 0; i < other.count; i++) {
                // fixed TODO: suspicious operation, possible copy invocation
                *(new (this->data + i) T(other.data[i]));
            }
        }

        Array(Array&& other) noexcept {
            this->capacity = other.capacity;
            this->count = other.count;
            this->data = std::move(other.data);

            other.count = 0;
            other.capacity = 0;
            other.data = nullptr;
        }

        ~Array() {
            if (this->data == nullptr) {
                return;
            }

            for (int i = 0; i < this->count; i++) {
                this->data[i].~T();
            }

            std::free(this->data);
        }

        Array& operator=(const Array& other) {
            Array copy{other};
            this->swap(copy);
            return *this;
        }

        Array& operator=(Array&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            for (int i = 0; i < this->count; i++) {
                this->data[i].~T();
            }

            std::free(this->data);

            this->data = other.data;
            this->count = other.count;
            this->capacity = other.capacity;

            other.data = nullptr;
            other.count = 0;
            other.capacity = 0;

            return *this;
        }

        void swap(Array& other) noexcept {
            std::swap(this->capacity, other.capacity);
            std::swap(this->count, other.count);
            std::swap(this->data, other.data);
        }

        int insert(const T& value) {
            return this->insert(this->count, value);
        }

        int insert(int index, const T& value) {
            if (this->count == this->capacity) {
                this->resize();
            }

            for (int i = this->count; i > index; --i) {
                if constexpr (std::is_move_constructible_v<T> && std::is_move_assignable_v<T>) {
                    *(new (this->data + i) T(std::move(*(this->data + i - 1))));
                } else {
                    *(new (this->data[i - 1]) T(data[i - 1]));
                    *(this->data + i - 1).~T();
                }
            }

            this->data[index] = *(new (this->data + index) T(value));
            ++this->count;
            return this->count;
        }

        void remove(const int index) {
            for (int i = index; i < this->count - 1; ++i) {
                (*(this->data + i)).~T();
                if constexpr (
                        std::is_move_constructible_v<T>
                    /*&&  std::is_move_assignable_v<T>*/) {
                    *(new (this->data + i) T(std::move(*(this->data + i + 1))));
                } else {

                    *(new (this->data + i) T(data[i + 1])); //
                    // TODO: desctructor of the previous, desctructors are called differently
                    // *(new (this->data[i - 1]) T(data[i + 1]));
                    // *(this->data + i + 1).~T();
                }
            }

            // don't forget the last element
            (*(this->data + this->count - 1)).~T();
            --this->count;
        }

        const T& operator[](int index) const {
            return this->data[index];
        }

        T& operator[](int index) {
            return this->data[index];
        }

        [[nodiscard]] int size() const {
            return this->count;
        }

        Iterator iterator() {
            return Iterator{0, this->count, this};
        }

        ConstIterator constIterator() const {
            return ConstIterator{0, this->count, this};
        }

        Iterator reverseIterator() {
            return Iterator{1 - this->count, 0, this};
        }

        ConstIterator reverseConstIterator() const {
            return ConstIterator{1 - this->count, 0, this};
        }

    private:
        int capacity;
        int count;
        T* data;

        void resize() {
            const int new_capacity = this->capacity * EXTENSION_FACTOR;
            T* new_data = static_cast<T*>(std::malloc(new_capacity * sizeof(T)));

            for (int i = 0; i < this->count; i++) {
                if constexpr (std::is_move_constructible_v<T>/* && std::is_move_assignable_v<T>*/) {
                    *(new (new_data + i) T(std::move(*(this->data + i))));
                } else {
                    // TODO: missed destructors
                    *(new (new_data + i) T(data[i])); // if we fail to copy in the middle, array is half-destroyed, which is bulls***
                }
            }

            for (int i = 0; i < this->count; i++) {
                (*(this->data + i)).~T();
            }

            std::free(this->data);
            this->capacity = new_capacity;
            this->data = new_data;
        }
};

#endif // ADALAB2_DYNAMICARRAY_ARRAY_H
