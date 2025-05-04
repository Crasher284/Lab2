//
// Created by admin on 12.04.2025.
//

#ifndef LAB2_LISTSEQUENCE_H
#define LAB2_LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <typename T> class MutableListSequence;
template <typename T> class ImmutableListSequence;

template <typename T>
class ListSequence : public Sequence<T>{
public:
    ListSequence(T* items, int count){
        data = new LinkedList<T>(items, count);
    }

    ListSequence(){
        data = new LinkedList<T>;
    }

    explicit ListSequence(LinkedList<T> &list){
        data = new LinkedList<T>(list);
    }
    explicit ListSequence(Sequence<T> &array){
        data = new LinkedList<T>();
        for(int i=0;i<array.getLength();i++){
            data->append(array.get(i));
        }
    }

    T getFirst() override{
        return data->getFirst();
    }

    T getLast() override{
        return data->getLast();
    }

    T get(int index) override{
        return data->get(index);
    }

    Sequence<T>* getSubsequence(int startIndex, int endIndex) override{
        return new MutableListSequence(*(data->getSublist(startIndex, endIndex)));
    }

    int getLength() override{
        return data->getLength();
    }

    Sequence<T>* append(T item) override{
        ListSequence<T> *out = instance();
        out->data->append(item);
        return out;
    }

    Sequence<T>* prepend(T item) override{
        ListSequence<T> *out = instance();
        out->data->prepend(item);
        return out;
    }

    Sequence<T>* insertAt(T item, int index) override{
        ListSequence<T> *out = instance();
        out->data->insertAt(item, index);
        return out;
    }

    Sequence<T>* concat(Sequence<T> *list) override{
        ListSequence<T>* out = instance();
        auto* other = new MutableListSequence<T>(*list);
        out->data->concat(other->data);
        return out;
    }

    void print(std::ostream& os) const override{
        os << *data;
    }

    T& operator[](int index){
        return instance().data[index];
    }

    const T& operator[](int index) const{
        return instance().data[index];
    }

    friend std::ostream& operator << (std::ostream &os, const ListSequence<T> &list){
        list.print(os);
        return os;
    }

    ~ListSequence(){
        delete data;
    }

protected:
    LinkedList<T> *data;
private:
    virtual ListSequence<T>* instance() = 0;
};

template <typename T>
class MutableListSequence : public ListSequence<T>{
public:
    MutableListSequence(T* items, int count) : ListSequence<T>(items, count){}

    MutableListSequence() : ListSequence<T>(){}

    explicit MutableListSequence(LinkedList<T> &list) : ListSequence<T>(list){}

    explicit MutableListSequence(Sequence<T> &array) : ListSequence<T>(array){}
private:
    ListSequence<T>* instance() override{
        return this;
    }
};

template <typename T>
class ImmutableListSequence : public ListSequence<T>{
public:
    ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count){}

    ImmutableListSequence() : ListSequence<T>(){}

    explicit ImmutableListSequence(LinkedList<T> &list) : ListSequence<T>(list){}

    explicit ImmutableListSequence(Sequence<T> &array) : ListSequence<T>(array){}
private:
    ListSequence<T>* instance() override{
        auto *out = new ImmutableListSequence<T>(*this->data);
        return out;
    }
};

#endif //LAB2_LISTSEQUENCE_H
