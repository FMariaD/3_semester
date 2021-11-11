#include<iostream>

template <typename T>
class Grid {
private:
    T *memory;
    size_t x_size, y_size;

public:
    Grid(size_t x_size, size_t y_size): x_size(x_size), y_size(y_size) {
        memory = new T[x_size * y_size];
    };

    T operator()(size_t x_idx, size_t y_idx) const {
        return memory[x_idx * y_size + y_idx];
    };
    T& operator()(size_t x_idx, size_t y_idx) {
        return memory[x_idx * y_size + y_idx];
    };

    size_t get_xsize() const {return x_size;};
    size_t get_ysize() const {return y_size;};

    Grid& operator=(T x) {
        for (int i = 0; i < x_size; i++) {
            for (int j = 0; j < y_size; j++) {
                memory[i * y_size + j] = x;
            }
        }
        return *this;
    };

    ~Grid() {delete[] memory;};

    template <typename Q>
    friend std::ostream& operator<<(std::ostream& os, Grid<Q> const& g);
    template <typename Q>
    friend std::istream& operator>>(std::istream& is, Grid<Q> & g);
};

template <typename P>
std::ostream& operator<<(std::ostream& os, Grid<P> const& G) {
    if ((G.get_xsize() == 0) && (G.get_ysize() == 0)) os << "Grid is empty";
    for (size_t i = 0; i < G.get_xsize(); i++) {
            for (size_t j = 0; j < G.get_ysize(); j++) {
                os << G(i, j) << " ";
            }
            os << "\n";
    }
    return os;
};

template <typename P>
std::istream& operator>>(std::istream& is, Grid<P>& G) {
    P x;
    for (size_t i = 0; i < G.x_size; i++) {
            for (size_t j = 0; j < G.y_size; j++) {
                is >> x;
                G.memory[i * G.y_size + j] = x;
            }
        }
    return is;
 };

int main()
{
    Grid<int> g(2, 3);
    g = 1;
    std::cout << g;
    g(1, 2) = 5;
    std::cout << g;
    std::cin >> g;
    std::cout << g;
    return 0;
}
