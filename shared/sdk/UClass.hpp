#pragma once

#include "UObject.hpp"

namespace sdk {
class UClass;
class UStruct;
class FField;

class UField : public UObject {
public:
    static UClass* static_class();
    static void update_offsets();


protected:
    static inline bool s_attempted_update_offsets{false};

    friend class UStruct;
};

class UStruct : public UField {
public:
    static UClass* static_class();
    static void update_offsets();

    UStruct* get_super_struct() const {
        return *(UStruct**)((uintptr_t)this + s_super_struct_offset);
    }
    
    FField* get_children() const {
        return *(FField**)((uintptr_t)this + s_children_offset);
    }

    bool is_a(UStruct* other) const {
        for (auto super = this; super != nullptr; super = super->get_super_struct()) {
            if (super == other) {
                return true;
            }
        }

        return false;
    }

protected:
    static inline bool s_attempted_update_offsets{false};
    static inline uint32_t s_super_struct_offset{0x40}; // not correct always, we bruteforce it later
    static inline uint32_t s_children_offset{0x48}; // not correct always, we bruteforce it later
    static inline uint32_t s_properties_size_offset{0x50}; // not correct always, we bruteforce it later

    friend class UField;
};

class UClass : public UStruct {
public:
    static UClass* static_class();
    static void update_offsets();

    UObject* get_class_default_object() const {
        return *(UObject**)((uintptr_t)this + s_default_object_offset);
    }

protected:
    static inline bool s_attempted_update_offsets{false};
    static inline uint32_t s_default_object_offset{0x118}; // not correct always, we bruteforce it later
};

class UScriptStruct : public UStruct {
public:
    struct StructOps {
        virtual ~StructOps() {};

        int32_t size;
        int32_t alignment;
    };

    static UClass* static_class();
    static void update_offsets();

    StructOps* get_struct_ops() const {
        return *(StructOps**)((uintptr_t)this + s_struct_ops_offset);
    }

    int32_t get_struct_size() const {
        const auto ops = get_struct_ops();
        if (ops == nullptr) {
            return 0;
        }

        return ops->size;
    }

protected:
    static inline bool s_attempted_update_offsets{false};
    static inline uint32_t s_struct_ops_offset{0xB8}; // not correct always, we bruteforce it later
};
}