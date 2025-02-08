#ifndef DATA_BASE_H
#define DATA_BASE_H


#define GETSET(type, name) \
private: \
    type name; \
public: \
    type get_##name() const { return name; } \
    void set_##name(const type& value) { name = value; }

#define STR(R) #R
#define VER(R) STR(R)

#endif // DATA_BASE_H
