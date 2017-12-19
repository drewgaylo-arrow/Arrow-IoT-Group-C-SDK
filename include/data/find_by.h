#if !defined(ACN_SDK_C_FIND_BY_H_)
#define ACN_SDK_C_FIND_BY_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <data/property.h>
#include <data/linkedlist.h>
#include <stdarg.h>

enum FindBy {
  f_userHid = 0,
  f_uid,
  f_type,
  f_gatewayHid,
  f_createdBefore,
  f_createdAfter,
  f_updatedBefore,
  f_updatedAfter,
  f_enabled,
  f_page,
  f_size,
  createdDateFrom,
  createdDateTo,
  sortField,
  sortDirection,
  statuses,
  systemNames,
  // telemetry
  fromTimestamp,
  toTimestamp,
  telemetryNames,
  FindBy_count
};

typedef struct _find_by {
  int key;
  property_t value;
  linked_list_head_node;
} find_by_t;

#define find_by(x, y)       (find_by_t){ .key=x, .value=p_stack(y), .node={NULL} }
#define find_by_const(x, y) (find_by_t){ .key=x, .value=p_const(y), .node={NULL} }
#define find_by_heap(x, y)  (find_by_t){ .key=x, .value=p_heap(y), .node={NULL} }

const char *get_find_by_name(int num);
int find_by_validate_key(find_by_t *fb);

#define find_by_collect(params, n) \
  do { \
    va_list args; \
    va_start(args, n); \
    int i = 0; \
    for (i=0; i < n; i++) { \
      find_by_t *tmp = (find_by_t *)malloc(sizeof(find_by_t)); \
      *tmp = va_arg(args, find_by_t); \
      linked_list_add_node_last(params, find_by_t, tmp); \
    } \
    va_end(args); \
  } while(0)

#define find_by_to_property(fb) p_const(get_find_by_name((fb)->key))

#define find_by_for_each(tmp, params) \
    for_each_node(tmp, params, find_by_t) \
    if ( find_by_validate_key(tmp) == 0 ) \

// FIXME if value is property, rm p_stack

#if defined(__cplusplus)
}
#endif

#endif  // ACN_SDK_C_FIND_BY_H_
