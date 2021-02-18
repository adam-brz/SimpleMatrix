#if !defined(AXIS_H)
#define AXIS_H

template <typename T>
class Vector;

template <typename T = double>
class Axis
{
public:
    static const Vector<T> X() {
        return {1, 0, 0};
    }

    static const Vector<T> Y() {
        return {0, 1, 0};
    }

    static const Vector<T> Z() {
        return {0, 0, 1};
    }
};

#endif // AXIS_H