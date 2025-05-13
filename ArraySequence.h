//
// Created by admin on 10.04.2025.
//

#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

template <typename T> class MutableArraySequence;
template <typename T> class ImmutableArraySequence;

template <typename T>
class ArraySequence : public Sequence<T>{
public:
    ArraySequence(T* items, int count){
        data = new DynamicArray(items, count);
        size = data->getSize();
    }

    ArraySequence(){
        data = new DynamicArray<T>(1);
        size = 0;
    }

    explicit ArraySequence(DynamicArray<T> &array){
        data = new DynamicArray(array);
        size = data->getSize();
    }

    explicit ArraySequence(Sequence<T> &array){
        size = array.getLength();
        data = new DynamicArray<T>(size);
        for(int i=0;i<size;i++){
            data->set(i, array.get(i));
        }
    }

    T getFirst() override{
        if(size==0){
            throw std::out_of_range("That ArraySequence is empty; there are no first element.");
        }
        return data->get(0);
    }

    T getLast() override{
        if(size==0){
            throw std::out_of_range("That ArraySequence is empty; there are no last element.");
        }
        return data->get(size-1);
    }

    T get(int index) override{
        if(index<0 || index>=size){
            throw std::out_of_range("Used index cannot be interpreted as index of ArraySequence.");
        }
        return data->get(index);
    }

    Sequence<T>* getSubsequence(int startIndex, int endIndex) override{
        if(startIndex<0 || startIndex>=size || endIndex<0 || endIndex>=size || startIndex>endIndex){
            throw std::out_of_range("Used indexes or their combination are invalid for ArraySequence.");
        }
        auto* out = new DynamicArray<T>(endIndex-startIndex+1);
        for(int i=startIndex;i<=endIndex;i++){
            (*out)[i - startIndex] = data->get(i);
        }
        return new MutableArraySequence<T>(*out);
    }

    int getLength() override{
        return size;
    }

    Sequence<T>* append(T item) override{
        ArraySequence<T>* out = instance();
        if(data->getSize()==size){
            out->data->resize(size*2);
        }
        out->data->set(size, item);
        out->size++;
        return out;
    }

    Sequence<T>* prepend(T item) override{
        ArraySequence<T>* out = instance();
        if(data->getSize()==size){
            out->data->resize(size*2);
        }
        for(int i=size-1;i>=0;i--){
            out->data->set(i+1, data->get(i));
        }
        out->data->set(0, item);
        out->size++;
        return out;
    }

    Sequence<T>* insertAt(T item, int index) override{
        ArraySequence<T>* out = instance();
        if(data->getSize()==size){
            out->data->resize(size*2);
        }
        for(int i=size-1;i>=index;i--){
            out->data->set(i+1, data->get(i));
        }
        out->data->set(index, item);
        out->size++;
        return out;
    }

    Sequence<T>* concat(Sequence<T> *list) override{
        ArraySequence<T>* out = instance();
        out->data->resize(size + list->getLength());
        for(int i=size;i<size+list->getLength();i++){
            out->data->set(i, list->get(i-size));
        }
        out->size = size+list->getLength();
        return out;
    }

    Sequence<T>** split(bool(*select)(T), int& count) override{
        count = 1;
        for(int i=0;i<data->getSize();i++){
            if(select(data->get(i))){
                count++;
            }
        }
        Sequence<T>** split = new Sequence<T>*[count];
        for (int i = 0; i < count; i++) {
            split[i] = new MutableArraySequence<T>();
        }
        int cnt = 0;
        split[0] = new MutableArraySequence<T>;
        for (int i = 0; i < data->getSize(); i++) {
            if (select(data->get(i))) {
                cnt++;
            } else {
                split[cnt]->append(data->get(i));
            }
        }

        Sequence<T>** out = new Sequence<T>*[count];
        for (int i = 0; i < count; i++) {
            out[i] = split[i];
        }
        delete[] split;

        return out;
    }

    void print(std::ostream& os) const override{
        os << *data;
    }

    T& operator[](int index){
        ArraySequence<T> out = instance();
        return out.data[index];
    }

    const T& operator[](int index) const{
        ArraySequence<T> out = instance();
        return out.data[index];
    }

    ArraySequence<T>& operator=(const Sequence<T> &other){
        if(this != &other){
            delete data;
            data = new DynamicArray<T>(other.getLength());
            size = other.getLength();
            for(int i=0;i<other.getLength();i++){
                data->set(i, other.get(i));
            }
        }
    }

    friend std::ostream& operator << (std::ostream &os, const ArraySequence<T> &array){
        array.print(os);
        return os;
    }

private:
    DynamicArray<T> *data;
    int size;

    virtual ArraySequence<T>* instance() = 0;
};

template <typename T>
class MutableArraySequence : public ArraySequence<T>{
public:
    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}

    MutableArraySequence() : ArraySequence<T>() {}

    explicit MutableArraySequence(DynamicArray<T> &array) : ArraySequence<T>(array) {}

    explicit MutableArraySequence(Sequence<T> &array) : ArraySequence<T>(array) {}
private:
    ArraySequence<T>* instance() override {
        return this;
    }
};

template <typename T>
class ImmutableArraySequence : public ArraySequence<T>{
public:
    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}

    ImmutableArraySequence() : ArraySequence<T>() {}

    explicit ImmutableArraySequence(DynamicArray<T> &array) : ArraySequence<T>(array) {}

    explicit ImmutableArraySequence(Sequence<T> &array) : ArraySequence<T>(array) {}
private:
    ArraySequence<T>* instance() override {
        ArraySequence<T>* out = this;
        return out;
    }
};

#endif //LAB2_ARRAYSEQUENCE_H
