//
// Created by Oruqimaru on 7/4/2019.
//

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

#include <cassert>
#include <cstring>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "utils/macros.hpp"

namespace husky {
    namespace base {

        class BinStream {
        public:
            BinStream();
            explicit BinStream(size_t sz);
            explicit BinStream(const std::vector<char>& v);
            explicit BinStream(std::vector<char>&& v);
            BinStream(const char* src, size_t sz);
            BinStream(const BinStream& stream);
            BinStream(BinStream&& stream);
            virtual ~BinStream();

            BinStream& operator=(BinStream&& stream);

            size_t hash();
            void clear();
            void purge();
            void resize(size_t size);
            void seek(size_t pos);

            void append(const BinStream& m);
            void push_back_bytes(const char* src, size_t sz);
            virtual void* pop_front_bytes(size_t sz);
            virtual size_t size() const { return buffer_.size() - front_; }

            /// Note that this method just returns the pointer pointing to the very
            /// beginning of the buffer_, and doesn't care about how much data have
            /// been read.
            inline char* get_buffer() { return &buffer_[0]; }
            inline const std::vector<char>& get_buffer_vector() { return buffer_; }
            inline const char* get_remained_buffer() const { return (&buffer_[0]) + front_; }
            inline std::string to_string() const { return std::string(buffer_.begin() + front_, buffer_.end()); }

        protected:
            std::vector<char> buffer_;

        private:
            size_t front_;
        };

        template <typename T>
        class has_serialize {
        private:
            template <typename U>
            static constexpr auto check(int) ->
            typename std::is_same<decltype(std::declval<U>().serialize(*(new BinStream))), BinStream&>::type;

            template <typename>
            static constexpr std::false_type check(...);

            typedef decltype(check<T>(0)) type;

        public:
            static constexpr bool value = type::value;
        };

        template <typename T>
        class has_deserialize {
        private:
            template <typename U>
            static constexpr auto check(int) ->
            typename std::is_same<decltype(std::declval<U>().deserialize(*(new BinStream))), BinStream&>::type;

            template <typename>
            static constexpr std::false_type check(...);

            typedef decltype(check<T>(0)) type;

        public:
            static constexpr bool value = type::value;
        };

        template <typename InputT>
        typename std::enable_if<has_serialize<InputT>::value, BinStream>::type& operator<<(BinStream& stream, const InputT& x) {
            x.serialize(stream);
            return stream;
        }

        template <typename OutputT>
        typename std::enable_if<has_deserialize<OutputT>::value, BinStream>::type& operator>>(BinStream& stream, OutputT& x) {
            x.deserialize(stream);
            return stream;
        }

        template <typename InputT>
        typename std::enable_if<!has_serialize<InputT>::value, BinStream>::type& operator<<(BinStream& stream,
                                                                                            const InputT& x) {
            static_assert(IS_TRIVIALLY_COPYABLE(InputT), "For non trivially copyable type, serialization functions are needed");
            stream.push_back_bytes((char*) &x, sizeof(InputT));
            return stream;
        }

        template <typename OutputT>
        typename std::enable_if<!has_deserialize<OutputT>::value, BinStream>::type& operator>>(BinStream& stream, OutputT& x) {
            static_assert(IS_TRIVIALLY_COPYABLE(OutputT),
                          "For non trivially copyable type, serialization functions are needed");
            x = *(OutputT*) (stream.pop_front_bytes(sizeof(OutputT)));
            return stream;
        }

        template <typename InputT>
        BinStream& operator<<(BinStream& stream, const std::vector<InputT>& v) {
            size_t len = v.size();
            stream << len;
            for (int i = 0; i < v.size(); ++i)
                stream << v[i];
            return stream;
        }

        template <typename OutputT>
        BinStream& operator>>(BinStream& stream, std::vector<OutputT>& v) {
            size_t len;
            stream >> len;
            v.clear();
            v.resize(len);
            for (int i = 0; i < v.size(); ++i)
                stream >> v[i];
            return stream;
        }

        template <typename K, typename V>
        BinStream& operator<<(BinStream& stream, const std::map<K, V>& map) {
            size_t len = map.size();
            stream << len;
            for (auto& elem : map)
                stream << elem;
            return stream;
        }

        template <typename K, typename V>
        BinStream& operator>>(BinStream& stream, std::map<K, V>& map) {
            size_t len;
            stream >> len;
            map.clear();
            for (int i = 0; i < len; i++) {
                std::pair<K, V> elem;
                stream >> elem;
                map.insert(elem);
            }
            return stream;
        }

        template <typename K, typename V>
        BinStream& operator<<(BinStream& stream, const std::unordered_map<K, V>& unordered_map) {
            size_t len = unordered_map.size();
            stream << len;
            for (auto& elem : unordered_map)
                stream << elem;
            return stream;
        }

        template <typename K, typename V>
        BinStream& operator>>(BinStream& stream, std::unordered_map<K, V>& unordered_map) {
            size_t len;
            stream >> len;
            unordered_map.clear();
            for (int i = 0; i < len; i++) {
                std::pair<K, V> elem;
                stream >> elem;
                unordered_map.insert(elem);
            }
            return stream;
        }

        template <typename T>
        BinStream& operator<<(BinStream& stream, const std::shared_ptr<T>& ptr) {
            stream << *ptr;
            return stream;
        }

        template <typename T>
        BinStream& operator>>(BinStream& stream, std::shared_ptr<T>& ptr) {
            T tmp;
            stream >> tmp;
            ptr.reset(new T);
            *ptr = tmp;
            return stream;
        }

        template <typename T>
        BinStream& operator<<(BinStream& stream, const std::unique_ptr<T>& ptr) {
            stream << *ptr;
            return stream;
        }

        template <typename T>
        BinStream& operator>>(BinStream& stream, std::unique_ptr<T>& ptr) {
            T tmp;
            stream >> tmp;
            ptr.reset(new T);
            *ptr = tmp;
            return stream;
        }

        template <typename InputT>
        BinStream& operator<<(BinStream& stream, const std::basic_string<InputT>& v) {
            size_t len = v.size();
            stream << len;
            for (auto& elem : v)
                stream << elem;
            return stream;
        }

        template <typename OutputT>
        BinStream& operator>>(BinStream& stream, std::basic_string<OutputT>& v) {
            size_t len;
            stream >> len;
            v.clear();
            try {
                v.resize(len);
            } catch (std::exception e) {
                assert(false);
            }
            for (auto& elem : v)
                stream >> elem;
            return stream;
        }

        template <typename FirstT, typename SecondT>
        BinStream& operator<<(BinStream& stream, const std::pair<FirstT, SecondT>& p) {
            stream << p.first << p.second;
            return stream;
        }

        template <typename FirstT, typename SecondT>
        BinStream& operator>>(BinStream& stream, std::pair<FirstT, SecondT>& p) {
            stream >> p.first >> p.second;
            return stream;
        }

        BinStream& operator<<(BinStream& stream, const BinStream& bin);
        BinStream& operator>>(BinStream& stream, BinStream& bin);

        BinStream& operator<<(BinStream& stream, const std::string& x);
        BinStream& operator>>(BinStream& stream, std::string& x);

        BinStream& operator<<(BinStream& stream, const std::vector<bool>& v);
        BinStream& operator>>(BinStream& stream, std::vector<bool>& v);

        template <typename Value>
        Value deser(BinStream& in) {
            Value v;
            in >> v;
            return v;
        }

        BinStream::BinStream() : front_(0) {}

        BinStream::BinStream(size_t sz) : front_(0) { buffer_.resize(sz); }

        BinStream::BinStream(const char* src, size_t sz) : front_(0) { push_back_bytes(src, sz); }

        BinStream::BinStream(const std::vector<char>& v) : front_(0), buffer_(v) {}

        BinStream::BinStream(std::vector<char>&& v) : front_(0), buffer_(std::move(v)) {}

        BinStream::BinStream(const BinStream& stream) {
            front_ = stream.front_;
            buffer_ = stream.buffer_;
        }

        BinStream::BinStream(BinStream&& stream) : front_(stream.front_), buffer_(std::move(stream.buffer_)) {
            stream.front_ = 0;
        }

        BinStream& BinStream::operator=(BinStream&& stream) {
            front_ = stream.front_;
            buffer_ = std::move(stream.buffer_);
            stream.front_ = 0;
            return *this;
        }

        size_t BinStream::hash() {
            size_t ret = 0;
            for (auto& i : buffer_)
                ret += i;
            return ret;
        }

        void BinStream::clear() {
            buffer_.clear();
            front_ = 0;
        }

        void BinStream::purge() {
            std::vector<char> tmp;
            buffer_.swap(tmp);
            front_ = 0;
        }

        void BinStream::resize(size_t size) {
            buffer_.resize(size);
            front_ = 0;
        }

        void BinStream::seek(size_t pos) { front_ = pos; }

        void BinStream::push_back_bytes(const char* src, size_t sz) {
            buffer_.insert(buffer_.end(), (const char*) src, (const char*) src + sz);
        }

        void* BinStream::pop_front_bytes(size_t sz) {
            assert(front_ <= buffer_.size());
            void* ret = &buffer_[front_];
            front_ += sz;
            return ret;
        }

        void BinStream::append(const BinStream& stream) { push_back_bytes(stream.get_remained_buffer(), stream.size()); }

        BinStream& operator<<(BinStream& stream, const BinStream& bin) {
            stream << bin.size();
            stream.push_back_bytes(bin.get_remained_buffer(), bin.size());
            return stream;
        }

        BinStream& operator>>(BinStream& stream, BinStream& bin) {
            size_t len;
            stream >> len;
            bin.resize(len);
            for (char* i = bin.get_buffer(); len--; i++)
                stream >> *i;
            return stream;
        }

        BinStream& operator<<(BinStream& stream, const std::string& x) {
            stream << x.size();
            stream.push_back_bytes(x.data(), x.length());
            return stream;
        }

        BinStream& operator>>(BinStream& stream, std::string& x) {
            size_t len;
            stream >> len;
            std::string s(reinterpret_cast<char*>(stream.pop_front_bytes(len)), len);
            x.swap(s);
            return stream;
        }

        BinStream& operator<<(BinStream& stream, const std::vector<bool>& v) {
            size_t len = v.size();
            stream << len;
            for (int i = 0; i < v.size(); ++i)
                stream << static_cast<bool>(v[i]);
            return stream;
        }

        BinStream& operator>>(BinStream& stream, std::vector<bool>& v) {
            size_t len;
            stream >> len;
            v.clear();
            v.resize(len);
            bool bool_tmp;
            for (int i = 0; i < v.size(); ++i) {
                stream >> bool_tmp;
                v[i] = bool_tmp;
            }
            return stream;
        }

        BinStream::~BinStream() {}



    }  // namespace base
}  // namespace husky
