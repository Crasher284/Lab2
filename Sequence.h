//
// Created by admin on 10.04.2025.
//

#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

template <typename T>
class Sequence{
public:

    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;
    virtual Sequence<T>* getSubsequence(int startIndex, int endIndex) = 0;
    virtual int getLength() = 0;

    virtual Sequence<T>* append(T item) = 0;
    virtual Sequence<T>* prepend(T item) = 0;
    virtual Sequence<T>* insertAt(T item, int index) = 0;
    virtual Sequence<T>* concat(Sequence <T> *list) = 0;
    virtual void print(std::ostream& os) const = 0;

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
    seq.print(os);
    return os;
}

#endif //LAB2_SEQUENCE_H
