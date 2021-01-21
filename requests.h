#include "rational.h"

template<typename T>
class node_operations {
public:
    int type;

    virtual int get_type() { return type; }

    virtual int get_index_i() { return 0; };

    virtual T get_val() { return 0; };

    virtual int get_index_j() { return 0;};
};

template<typename T>
class multiplication : public node_operations<T> {
public:
    int i;
    T val;

    int get_type() override { return node_operations<T>::type; }

    multiplication(int type_, int i_, T val_) {
        node_operations<T>::type = type_;
        i = i_;
        val = val_;
    }

    int get_index_i() override {
        return i;
    }

    T get_val() override {
        return val;
    }
};

template<typename T>
class swap_i_j : public node_operations<T> {
public:
    int i;
    int j;

    int get_type() override { return node_operations<T>::type; }

    swap_i_j(int type_, int i_, int j_) {
        node_operations<T>::type = type_;
        i = i_;
        j = j_;
    }

    int get_index_i() override {
        return i;
    }

    int get_index_j() override {
        return j;
    }
};

template<typename T>
class div_i_val : public node_operations<T> {
public:
    int i;
    T val;

    int get_type() override { return node_operations<T>::type; }

    div_i_val(int type_, int i_, T val_) {
        node_operations<T>::type = type_;
        i = i_;
        val = val_;
    }

    int get_index_i() override {
        return i;
    }

    T get_val() override {
        return val;
    }
};

template<typename T>
class plus_i_j_val : public node_operations<T> {
public:
    int i;
    int j;
    T val;

    int get_type() override { return node_operations<T>::type; }

    plus_i_j_val(int type_, int i_, int j_, T val_) {
        node_operations<T>::type = type_;
        i = i_;
        j = j_;
        val = val_;
    }

    int get_index_i() override {
        return i;
    }

    int get_index_j() override {
        return j;
    }

    T get_val() override {
        return val;
    }
};
