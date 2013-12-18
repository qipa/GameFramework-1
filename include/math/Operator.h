#ifndef OPERATOR_H_2013_12_18
#define OPERATOR_H_2013_12_18

template <class L, class R>
class Plus {
    const L& l_; // 左辺値
    const R& r_; // 右辺値
public:
    Plus(const L& l, const R& r)
        : l_(l), r_(r) {}

    float operator[](std::size_t i) const
    {
        return l_[i] + r_[i];
    }
};

template <class L, class R>
class Minus {
    const L& l_; // 左辺値
    const R& r_; // 右辺値
public:
    Minus(const L& l, const R& r)
        : l_(l), r_(r) {}

    float operator[](std::size_t i) const
    {
        return l_[i] + r_[i];
    }
};


#endif
