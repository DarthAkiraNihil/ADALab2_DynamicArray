//
// Created by EgrZver on 06.11.2026.
//

#ifndef ADALAB2_DYNAMICARRAY_TESTCLASSES_H
#define ADALAB2_DYNAMICARRAY_TESTCLASSES_H

struct Podman {
    int podman_id;
    int pod_id;
    long cluster_id;
    bool is_running;
    int children[2];
};

class SimpleMovableClass {
    private:
        int* just_data;
        int size;
        std::string data_name;

    public:
        SimpleMovableClass(const int size, const std::string& data_name) {
            this->data_name = data_name;
            this->size = size;
            this->just_data = new int[size];
            for (int i = 0; i < size; i++) {
                this->just_data[i] = i;
            }
        }

        SimpleMovableClass(const SimpleMovableClass& other) {
            this->data_name = other.data_name;
            this->size = other.size;
            this->just_data = new int[size];
            for (int i = 0; i < size; i++) {
                this->just_data[i] = other.just_data[i];
            }
        }

        SimpleMovableClass& operator=(const SimpleMovableClass& other) {
            if (this == &other) {
                return *this;
            }

            this->data_name = other.data_name;
            this->size = other.size;
            this->just_data = new int[size];
            for (int i = 0; i < size; i++) {
                this->just_data[i] = other.just_data[i];
            }

            return *this;
        }

        SimpleMovableClass(SimpleMovableClass&& other) noexcept {
            this->data_name = other.data_name;
            this->size = other.size;
            this->just_data = other.just_data;
            other.just_data = nullptr;
            other.size = 0;
            other.data_name = "";
        }

        SimpleMovableClass& operator=(SimpleMovableClass&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            this->data_name = other.data_name;
            this->size = other.size;
            this->just_data = other.just_data;
            other.just_data = nullptr;
            other.size = 0;
            other.data_name = "";

            return *this;
        }

        ~SimpleMovableClass() {
            delete[] this->just_data;
        }

        [[nodiscard]] int get_size() const {
            return this->size;
        }

        int* get_just_data() const {
            return this->just_data;
        }

        [[nodiscard]] std::string get_data_name() const {
            return this->data_name;
        }

        bool operator==(const SimpleMovableClass& other) const {
            if (this == &other) {
                return true;
            }

            if (this->size != other.size) {
                return false;
            }

            for (int i = 0; i < this->size; i++) {
                if (this->just_data[i] != other.just_data[i]) {
                    return false;
                }
            }

            return this->data_name == other.data_name;
        }
};

class UnmovableClass {
    private:
        int* just_data;
        int size;
        std::string data_name;

    public:
        UnmovableClass(const int size, const std::string& data_name) {
            this->data_name = data_name;
            this->size = size;
            this->just_data = new int[size];
            for (int i = 0; i < size; i++) {
                this->just_data[i] = i;
            }
        }

        UnmovableClass(const UnmovableClass& other) {
            this->data_name = other.data_name;
            this->size = other.size;
            this->just_data = new int[size];
            for (int i = 0; i < size; i++) {
                this->just_data[i] = other.just_data[i];
            }
        }

        UnmovableClass& operator=(const UnmovableClass& other) {
            if (this == &other) {
                return *this;
            }

            this->data_name = other.data_name;
            this->size = other.size;
            this->just_data = new int[size];
            for (int i = 0; i < size; i++) {
                this->just_data[i] = other.just_data[i];
            }

            return *this;
        }

        ~UnmovableClass() {
            delete[] this->just_data;
        }

        [[nodiscard]] int get_size() const {
            return this->size;
        }

        int* get_just_data() const {
            return this->just_data;
        }

        [[nodiscard]] std::string get_data_name() const {
            return this->data_name;
        }

        bool operator==(const UnmovableClass& other) const {
            if (this == &other) {
                return true;
            }

            if (this->size != other.size) {
                return false;
            }

            for (int i = 0; i < this->size; i++) {
                if (this->just_data[i] != other.just_data[i]) {
                    return false;
                }
            }

            return this->data_name == other.data_name;
        }
};

#endif // ADALAB2_DYNAMICARRAY_TESTCLASSES_H
