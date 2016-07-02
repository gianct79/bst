#include <iostream>
#include <array>

template <class T, std::size_t N>
struct circular_buffer {

private:
    std::size_t r_ = 0;
    std::size_t w_ = 0;

    std::array<T, N> buffer_;

public:
    const T &read() {
        if (r_ == w_)
            throw std::logic_error("empty");

        return buffer_[r_++ % buffer_.size()];
    }

    void write(T const &v) {
        if ((w_ - r_) == buffer_.size())
            throw std::logic_error("full");

        buffer_[w_++ % buffer_.size()] = v;
    }
};


int main()
{
    circular_buffer<int, 4> buffer;

    buffer.write(1);
    buffer.write(2);
    buffer.write(3);
    buffer.write(4);

    std::cout << buffer.read() << '\n';
    std::cout << buffer.read() << '\n';

    buffer.write(5);
    buffer.write(6);

    std::cout << buffer.read() << '\n';
    std::cout << buffer.read() << '\n';

    buffer.write(7);
    buffer.write(8);

    std::cout << buffer.read() << '\n';
    std::cout << buffer.read() << '\n';

    return 0;
}
