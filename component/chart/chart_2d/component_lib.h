#ifndef DATA_COGNITIVE_LIB_H_20241216
#define DATA_COGNITIVE_LIB_H_20241216

#include "export_global.h"
#include "abstract_component.h"

extern "C"  DCOGNI_EXPORT bool create_lib(abstract_component** component);
extern "C"  DCOGNI_EXPORT bool release_lib(abstract_component** component);

#endif // DATA_COGNITIVE_LIB_H_20241216
