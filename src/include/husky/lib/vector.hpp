// Copyright 2016 Husky Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#define EIGEN_MATRIXBASE_PLUGIN "lib/eigen_matrix_base_plugin.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/Sparse"

#include "core/engine.hpp"

namespace husky {
namespace lib {

using Eigen::VectorXd;
using SparseVectorXd = Eigen::SparseVector<double>;

template <typename _Scalar, int _Flags = 0, typename _StorageIndex = int>
class InnerIterator;

template <typename XprType, int, typename>
class InnerIterator : public Eigen::InnerIterator<XprType> {
   protected:
    typedef typename Eigen::internal::traits<XprType>::Scalar Scalar;

   public:
    InnerIterator(const XprType& xpr, const Eigen::Index& outerId) : Eigen::InnerIterator<XprType>(xpr, outerId) {}
    EIGEN_STRONG_INLINE Scalar& valueRef() { return this->m_eval.coeffRef(this->row(), this->col()); }
};

template <typename _Scalar, int _Flags, typename _StorageIndex>
class InnerIterator<Eigen::SparseVector<_Scalar, _Flags, _StorageIndex>>
    : public Eigen::SparseVector<_Scalar, _Flags, _StorageIndex>::InnerIterator {
   protected:
    typedef Eigen::SparseVector<_Scalar> XprType;

   public:
    InnerIterator(const XprType& xpr, const Eigen::Index& outerId)
        : Eigen::SparseVector<_Scalar, _Flags, _StorageIndex>::InnerIterator(xpr, outerId) {}
};

template <typename T, typename U>
struct LabeledPoint {
    LabeledPoint() = default;
    LabeledPoint(T& x, U& y) : x(x), y(y) {}
    LabeledPoint(T&& x, U&& y) : x(std::move(x)), y(std::move(y)) {}

    T x;
    U y;

    friend husky::BinStream& operator<<(husky::BinStream& stream, const LabeledPoint<T, U>& b) {
        stream << b.x << b.y;
        return stream;
    }

    friend husky::BinStream& operator>>(husky::BinStream& stream, LabeledPoint<T, U>& b) {
        stream >> b.x >> b.y;
        return stream;
    }
};

}  // namespace lib

namespace base {

template <typename Scalar, int RowsAtCompileTime, int Options>
inline BinStream& operator<<(BinStream& stream, const Eigen::Matrix<Scalar, RowsAtCompileTime, Eigen::Dynamic, Options>& mat) {
    stream << (size_t)mat.cols();

    stream.push_back_bytes((const char*)mat.data(), mat.size() * sizeof(Scalar));

    return stream;
}

template <typename Scalar, int RowsAtCompileTime, int Options>
inline BinStream& operator>>(BinStream& stream, Eigen::Matrix<Scalar, RowsAtCompileTime, Eigen::Dynamic, Options>& mat) {
    size_t cols;
    stream >> cols;

    mat.resize(RowsAtCompileTime, cols);

    Scalar* data = (Scalar*)stream.pop_front_bytes(mat.size() * sizeof(Scalar));
    std::copy(data, data + mat.size(), mat.data());

    return stream;
}

template <typename Scalar, int ColsAtCompileTime, int Options>
inline BinStream& operator<<(BinStream& stream, const Eigen::Matrix<Scalar, Eigen::Dynamic, ColsAtCompileTime, Options>& mat) {
    stream << (size_t)mat.rows();

    stream.push_back_bytes((const char*)mat.data(), mat.size() * sizeof(Scalar));

    return stream;
}

template <typename Scalar, int ColsAtCompileTime, int Options>
inline BinStream& operator>>(BinStream& stream, Eigen::Matrix<Scalar, Eigen::Dynamic, ColsAtCompileTime, Options>& mat) {
    size_t rows;
    stream >> rows;

    mat.resize(rows, ColsAtCompileTime);

    Scalar* data = (Scalar*)stream.pop_front_bytes(mat.size() * sizeof(Scalar));
    std::copy(data, data + mat.size(), mat.data());

    return stream;
}

template <typename Scalar, int Options>
inline BinStream& operator<<(BinStream& stream, const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Options>& mat) {
    stream << (size_t)mat.rows() << (size_t)mat.cols();

    stream.push_back_bytes((const char*)mat.data(), mat.size() * sizeof(Scalar));

    return stream;
}

template <typename Scalar, int Options>
inline BinStream& operator>>(BinStream& stream, Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Options>& mat) {
    size_t rows, cols;
    stream >> rows >> cols;

    mat.resize(rows, cols);

    Scalar* data = (Scalar*)stream.pop_front_bytes(mat.size() * sizeof(Scalar));
    std::copy(data, data + mat.size(), mat.data());

    return stream;
}

template <typename _Scalar, int _Flags, typename _StorageIndex>
inline BinStream& operator<<(BinStream& stream, const Eigen::SparseVector<_Scalar, _Flags, _StorageIndex>& vec) {
    stream << (size_t)vec.rows() << (size_t)vec.nonZeros();

    stream.push_back_bytes((const char*)vec.innerIndexPtr(), vec.nonZeros() * sizeof(_StorageIndex));
    stream.push_back_bytes((const char*)vec.valuePtr(), vec.nonZeros() * sizeof(_Scalar));

    return stream;
}

template <typename _Scalar, int _Flags, typename _StorageIndex>
inline BinStream& operator>>(BinStream& stream, Eigen::SparseVector<_Scalar, _Flags, _StorageIndex>& vec) {
    size_t rows, non_zeros;
    stream >> rows >> non_zeros;

    vec.resize(rows);
    vec.reserve(non_zeros);
    vec.resizeNonZeros(non_zeros);

    _StorageIndex* idxs = (_StorageIndex*)stream.pop_front_bytes(non_zeros * sizeof(_StorageIndex));
    _Scalar* vals = (_Scalar*)stream.pop_front_bytes(non_zeros * sizeof(_Scalar));
    std::copy(idxs, idxs + non_zeros, vec.innerIndexPtr());
    std::copy(vals, vals + non_zeros, vec.valuePtr());

    return stream;
}

}  // namespace base

namespace lib {

template <typename T, bool is_sparse>
class Vector;

template <typename T>
using SparseVector = Vector<T, true>;

template <typename T>
using DenseVector = Vector<T, false>;

template <typename T>
struct FeaValPair {
    FeaValPair(int fea, T val) : fea(fea), val(val) {}
    // TODO(Kelvin): I want fea to be a const, but this will make operator=()
    // unavailable and break the use of STL containers
    int fea;
    T val;
};

template <typename T>
class Vector<T, false> {
   public:
    typedef typename std::vector<T>::iterator Iterator;
    typedef typename std::vector<T>::const_iterator ConstIterator;
    typedef typename std::vector<T>::iterator ValueIterator;
    typedef typename std::vector<T>::const_iterator ConstValueIterator;

    class FeaValIterator {
       public:
        explicit FeaValIterator(std::vector<T>& vec) : idx(0), vec(vec) {}
        FeaValIterator(std::vector<T>& vec, int idx) : idx(idx), vec(vec) {}

        FeaValPair<T&> operator*() { return FeaValPair<T&>(idx, vec[idx]); }

        FeaValIterator& operator++() {
            idx++;
            return *this;
        }

        FeaValIterator& operator--() {
            idx--;
            return *this;
        }

        FeaValIterator operator++(int) {
            FeaValIterator it(*this);
            idx++;
            return it;
        }

        FeaValIterator operator--(int) {
            FeaValIterator it(*this);
            idx--;
            return it;
        }

        bool operator==(const FeaValIterator& b) const { return idx == b.idx && &vec == &(b.vec); }

        bool operator!=(const FeaValIterator& b) const { return idx != b.idx || &vec != &(b.vec); }

       private:
        int idx;
        std::vector<T>& vec;
    };

    class ConstFeaValIterator {
       public:
        explicit ConstFeaValIterator(const std::vector<T>& vec) : idx(0), vec(vec) {}
        ConstFeaValIterator(const std::vector<T>& vec, int idx) : idx(idx), vec(vec) {}

        FeaValPair<const T&> operator*() const { return FeaValPair<const T&>(idx, vec[idx]); }

        ConstFeaValIterator& operator++() {
            idx++;
            return *this;
        }

        ConstFeaValIterator& operator--() {
            idx--;
            return *this;
        }

        ConstFeaValIterator operator++(int) {
            ConstFeaValIterator it(*this);
            idx++;
            return it;
        }

        ConstFeaValIterator operator--(int) {
            ConstFeaValIterator it(*this);
            idx--;
            return it;
        }

        bool operator==(const ConstFeaValIterator& b) const { return idx == b.idx && &vec == &(b.vec); }

        bool operator!=(const ConstFeaValIterator& b) const { return idx != b.idx || &vec != &(b.vec); }

       private:
        int idx;
        const std::vector<T>& vec;
    };

    Vector<T, false>() = default;

    Vector<T, false>(int feature_num) : feature_num(feature_num), vec(feature_num) {}

    Vector<T, false>(const SparseVector<T>& b) : feature_num(b.get_feature_num()), vec(b.get_feature_num()) {
        for (auto entry : b) {
            vec[entry.fea] = entry.val;
        }
    }

    Vector<T, false>(int feature_num, const T& val) : feature_num(feature_num), vec(feature_num, val) {}

    Vector<T, false>(int feature_num, T&& val) : feature_num(feature_num), vec(feature_num, val) {}

    inline int get_feature_num() const { return feature_num; }

    inline Iterator begin() { return vec.begin(); }

    inline ConstIterator begin() const { return vec.begin(); }

    inline Iterator end() { return vec.end(); }

    inline ConstIterator end() const { return vec.end(); }

    inline ValueIterator begin_value() { return vec.begin(); }

    inline ConstValueIterator begin_value() const { return vec.begin(); }

    inline ValueIterator end_value() { return vec.end(); }

    inline ConstValueIterator end_value() const { return vec.end(); }

    inline FeaValIterator begin_feaval() { return FeaValIterator(vec, 0); }

    inline ConstFeaValIterator begin_feaval() const { return ConstFeaValIterator(vec, 0); }

    inline FeaValIterator end_feaval() { return FeaValIterator(vec, feature_num); }

    inline ConstFeaValIterator end_feaval() const { return ConstFeaValIterator(vec, feature_num); }

    inline T& operator[](int idx) { return vec[idx]; }

    inline const T& operator[](int idx) const { return vec[idx]; }

    inline void sort_asc() {}

    inline void resize(int size) {
        vec.resize(size);
        feature_num = size;
    }

    inline void set(int idx, const T& val) { vec[idx] = val; }

    inline void set(int idx, T&& val) { vec[idx] = std::move(val); }

    DenseVector<T> operator-() const;

    DenseVector<T> operator*(T) const;
    DenseVector<T>& operator*=(T);
    DenseVector<T> scalar_multiple_with_intcpt(T) const;

    DenseVector<T> operator/(T) const;
    DenseVector<T>& operator/=(T);

    DenseVector<T> operator+(const DenseVector<T>&) const;
    DenseVector<T>& operator+=(const DenseVector<T>&);
    DenseVector<T> operator+(const SparseVector<T>&) const;
    DenseVector<T>& operator+=(const SparseVector<T>&);

    DenseVector<T> operator-(const DenseVector<T>&) const;
    DenseVector<T>& operator-=(const DenseVector<T>&);
    DenseVector<T> operator-(const SparseVector<T>&) const;
    DenseVector<T>& operator-=(const SparseVector<T>&);

    T dot(const DenseVector<T>&) const;
    T dot(const SparseVector<T>&) const;

    T dot_with_intcpt(const DenseVector<T>&) const;
    T dot_with_intcpt(const SparseVector<T>&) const;

    inline T sorted_dot(const DenseVector<T>& b) const { return dot(b); }
    inline T sorted_dot(const SparseVector<T>& b) const { return dot(b); }

    inline T sorted_dot_with_intcpt(const DenseVector<T>& b) const { return dot_with_intcpt(b); }
    inline T sorted_dot_with_intcpt(const SparseVector<T>& b) const { return dot_with_intcpt(b); }

    template <bool is_sparse>
    inline T euclid_dist(const Vector<T, is_sparse>& b) const {
        DenseVector<T> diff = *this - b;
        return std::sqrt(diff.dot(diff));
    }

    inline T sorted_euclid_dist(const DenseVector<T>& b) const { return euclid_dist(b); }
    T sorted_euclid_dist(const SparseVector<T>& b) const;

    friend husky::BinStream& operator<<(husky::BinStream& stream, const DenseVector<T>& b) {
        stream << b.feature_num;
        for (int i = 0; i < b.feature_num; i++) {
            stream << b.vec[i];
        }

        return stream;
    }

    friend husky::BinStream& operator>>(husky::BinStream& stream, DenseVector<T>& b) {
        stream >> b.feature_num;
        b.vec.resize(b.feature_num);

        for (int i = 0; i < b.feature_num; i++) {
            stream >> b.vec[i];
        }

        return stream;
    }

   private:
    std::vector<T> vec;
    int feature_num;
};

template <typename T>
class Vector<T, true> {
   public:
    typedef typename std::vector<FeaValPair<T>>::iterator Iterator;
    typedef typename std::vector<FeaValPair<T>>::const_iterator ConstIterator;
    typedef typename std::vector<FeaValPair<T>>::iterator FeaValIterator;
    typedef typename std::vector<FeaValPair<T>>::const_iterator ConstFeaValIterator;

    class ValueIterator {
       public:
        explicit ValueIterator(std::vector<FeaValPair<T>>& vec) : idx(0), vec(vec) {}
        ValueIterator(std::vector<FeaValPair<T>>& vec, int idx) : idx(idx), vec(vec) {}

        T& operator*() { return vec[idx].val; }

        T* operator->() { return &(vec[idx].val); }

        ValueIterator& operator++() {
            idx++;
            return *this;
        }

        ValueIterator& operator--() {
            idx--;
            return *this;
        }

        ValueIterator operator++(int) {
            ValueIterator it(*this);
            idx++;
            return it;
        }

        ValueIterator operator--(int) {
            ValueIterator it(*this);
            idx--;
            return it;
        }

        bool operator==(const ValueIterator& b) const { return idx == b.idx; }

        bool operator!=(const ValueIterator& b) const { return idx != b.idx; }

       private:
        int idx;
        std::vector<FeaValPair<T>>& vec;
    };

    class ConstValueIterator {
       public:
        explicit ConstValueIterator(const std::vector<FeaValPair<T>>& vec) : idx(0), vec(vec) {}
        ConstValueIterator(const std::vector<FeaValPair<T>>& vec, int idx) : idx(idx), vec(vec) {}

        const T& operator*() const { return vec[idx].val; }

        const T* operator->() const { return &(vec[idx].val); }

        ConstValueIterator& operator++() {
            idx++;
            return *this;
        }

        ConstValueIterator& operator--() {
            idx--;
            return *this;
        }

        ConstValueIterator operator++(int) {
            ConstValueIterator it(*this);
            idx++;
            return it;
        }

        ValueIterator operator--(int) {
            ConstValueIterator it(*this);
            idx--;
            return it;
        }

        bool operator==(const ConstValueIterator& b) const { return idx == b.idx; }

        bool operator!=(const ConstValueIterator& b) const { return idx != b.idx; }

       private:
        int idx;
        const std::vector<FeaValPair<T>>& vec;
    };

    Vector<T, true>() = default;

    Vector<T, true>(int feature_num) : feature_num(feature_num) {}

    inline int get_feature_num() const { return feature_num; }

    inline Iterator begin() { return vec.begin(); }

    inline ConstIterator begin() const { return vec.begin(); }

    inline Iterator end() { return vec.end(); }

    inline ConstIterator end() const { return vec.end(); }

    inline ValueIterator begin_value() { return ValueIterator(vec, 0); }

    inline ConstValueIterator begin_value() const { return ConstValueIterator(vec, 0); }

    inline ValueIterator end_value() { return ValueIterator(vec, vec.size()); }

    inline ConstValueIterator end_value() const { return ConstValueIterator(vec, vec.size()); }

    inline FeaValIterator begin_feaval() { return vec.begin(); }

    inline ConstFeaValIterator begin_feaval() const { return vec.begin(); }

    inline FeaValIterator end_feaval() { return vec.end(); }

    inline ConstFeaValIterator end_feaval() const { return vec.end(); }

    inline void sort_asc() {
        std::sort(vec.begin(), vec.end(), [](const FeaValPair<T>& a, const FeaValPair<T>& b) { return a.fea < b.fea; });
    }

    inline void resize(int size) { feature_num = size; }

    inline void set(int idx, const T& val) { vec.emplace_back(idx, val); }

    inline void set(int idx, T&& val) { vec.emplace_back(idx, std::move(val)); }

    SparseVector<T> operator-() const;

    SparseVector<T> operator*(T) const;
    SparseVector<T>& operator*=(T);
    SparseVector<T> scalar_multiple_with_intcpt(T) const;

    SparseVector<T> operator/(T) const;
    SparseVector<T>& operator/=(T);

    DenseVector<T> operator+(const SparseVector<T>& b) const;

    inline DenseVector<T> operator+(const DenseVector<T>& b) const { return b + *this; }

    DenseVector<T> operator-(const SparseVector<T>& b) const;
    DenseVector<T> operator-(const DenseVector<T>&) const;

    inline T dot(const DenseVector<T>& b) const { return b.dot(*this); }

    T dot_with_intcpt(const DenseVector<T>& b) const;

    // should be used only when sparse vectors are sorted ascendingly according to feature number
    inline T sorted_dot(const DenseVector<T>& b) const { return b.dot(*this); }
    T sorted_dot(const SparseVector<T>& b) const;

    T sorted_dot_with_intcpt(const DenseVector<T>& b) const;
    T sorted_dot_with_intcpt(const SparseVector<T>& b) const;

    inline T euclid_dist(const DenseVector<T>& b) const {
        DenseVector<T> diff = b - *this;
        return std::sqrt(diff.dot(diff));
    }

    inline T sorted_euclid_dist(const DenseVector<T>& b) const { return b.sorted_euclid_dist((*this)); }
    T sorted_euclid_dist(const SparseVector<T>& b) const;

    friend husky::BinStream& operator<<(husky::BinStream& stream, const SparseVector<T>& b) {
        stream << b.feature_num << b.vec.size();
        for (auto& entry : b.vec) {
            stream << entry.fea << entry.val;
        }

        return stream;
    }

    friend husky::BinStream& operator>>(husky::BinStream& stream, SparseVector<T>& b) {
        b.vec.clear();

        typename std::vector<FeaValPair<T>>::size_type num;
        stream >> b.feature_num >> num;

        int fea;
        T val;
        for (int i = 0; i < num; i++) {
            stream >> fea >> val;
            b.vec.emplace_back(fea, val);
        }

        return stream;
    }

   private:
    std::vector<FeaValPair<T>> vec;
    int feature_num;
};

template <typename T>
inline DenseVector<T> operator*(T c, const DenseVector<T>& a) {
    return a * c;
}

template <typename T>
inline SparseVector<T> operator*(T c, const SparseVector<T>& a) {
    return a * c;
}

#include "vector.tpp"

}  // namespace lib
}  // namespace husky
