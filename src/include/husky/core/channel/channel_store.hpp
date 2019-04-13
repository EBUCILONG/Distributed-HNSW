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

#include <string>

#include "core/channel/channel_store_base.hpp"
#include "core/context.hpp"
#include "core/objlist.hpp"

namespace husky {

class ChannelStore : public ChannelStoreBase {
   public:
    template <typename MsgT, typename DstObjT>
    static PushChannel<MsgT, DstObjT>& create_push_channel(ChannelSource& src_list, ObjList<DstObjT>& dst_list) {
        auto& ch = ChannelStoreBase::create_push_channel<MsgT>(src_list, dst_list);
        setup(ch);
        return ch;
    }

    template <typename MsgT, typename DstObjT>
    static PushChannel<MsgT, DstObjT>& create_push_channel(ChannelSource& src_list, ObjList<DstObjT>& dst_list,
                                                           const std::string& channel_name) {
        auto& ch = ChannelStoreBase::create_push_channel<MsgT>(src_list, dst_list, channel_name);
        setup(ch);
        return ch;
    }

    template <typename MsgT, typename CombineT, typename DstObjT>
    static PushCombinedChannel<MsgT, DstObjT, CombineT>& create_push_combined_channel(ChannelSource& src_list,
                                                                                      ObjList<DstObjT>& dst_list) {
        auto& ch = ChannelStoreBase::create_push_combined_channel<MsgT, CombineT>(src_list, dst_list);
        setup(ch);
        return ch;
    }

    template <typename MsgT, typename CombineT, typename DstObjT>
    static PushCombinedChannel<MsgT, DstObjT, CombineT>& create_push_combined_channel(ChannelSource& src_list,
                                                                                      ObjList<DstObjT>& dst_list,
                                                                                      const std::string& channel_name) {
        auto& ch = ChannelStoreBase::create_push_combined_channel<MsgT, CombineT>(src_list, dst_list, channel_name);
        setup(ch);
        return ch;
    }

    template <typename ObjT>
    static MigrateChannel<ObjT>& create_migrate_channel(ObjList<ObjT>& src_list, ObjList<ObjT>& dst_list) {
        auto& ch = ChannelStoreBase::create_migrate_channel<ObjT>(src_list, dst_list);
        setup(ch);
        return ch;
    }

    template <typename KeyT, typename MsgT>
    static BroadcastChannel<KeyT, MsgT>& create_broadcast_channel(ChannelSource& src_list) {
        auto& ch = ChannelStoreBase::create_broadcast_channel<KeyT, MsgT>(src_list);
        setup(ch);
        return ch;
    }

    template <typename MsgT, typename ObjT>
    static AsyncPushChannel<MsgT, ObjT>& create_async_push_channel(ObjList<ObjT>& obj_list) {
        auto& ch = ChannelStoreBase::create_async_push_channel<MsgT>(obj_list);
        setup(ch);
        return ch;
    }

    template <typename ObjT>
    static AsyncMigrateChannel<ObjT>& create_async_migrate_channel(ObjList<ObjT>& obj_list) {
        auto& ch = ChannelStoreBase::create_async_migrate_channel<ObjT>(obj_list);
        setup(ch);
        return ch;
    }

    static void setup(ChannelBase& ch) {
        ch.setup(Context::get_local_tid(), Context::get_global_tid(), Context::get_worker_info(),
                 Context::get_mailbox());
    }
};

}  // namespace husky
