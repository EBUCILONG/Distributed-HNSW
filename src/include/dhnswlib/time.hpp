
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

#include <chrono>

namespace dhnsw {
        inline long long get_current_time_milliseconds() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
                    .count();
        }

        inline long long get_current_time_nanoseconds() {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch())
                    .count();
        }

        class Timer{
        private:
            long long _last_time;
        public:
            Timer(){
                std::cout << "ddgdg" << std::endl;
                update_time();
                std::cout << "asdaoijsd" << std::endl;
            }

            void update_time(){
                _last_time = get_current_time();
            }

            virtual long long get_current_time() = 0;

            long long get_span(){
                return get_current_time() - _last_time;
            }

            long long span_and_update(){
                long long this_time = get_current_time();
                long long result = this_time - _last_time;
                _last_time = this_time;
                return result;
            }

            long long get_last_time(){
                return _last_time;
            }
        };

        class MiliTimer{
        private:
            long long _last_time;
        public:
            MiliTimer(){
                update_time();
            }

            long long get_current_time(){
                return get_current_time_milliseconds();
            }

            void update_time(){
                _last_time = get_current_time();
            }

            long long get_span(){
                return get_current_time() - _last_time;
            }

            long long span_and_update(){
                long long this_time = get_current_time();
                long long result = this_time - _last_time;
                _last_time = this_time;
                return result;
            }

            long long get_last_time(){
                return _last_time;
            }
        };

        class NanoTimer : public Timer{
        public:
            long long get_current_time(){
                return get_current_time_nanoseconds();
            }
        };
}  // namespace husky