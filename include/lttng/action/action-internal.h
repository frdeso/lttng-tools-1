/*
 * Copyright (C) 2017 Jérémie Galarneau <jeremie.galarneau@efficios.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-only
 *
 */

#ifndef LTTNG_ACTION_INTERNAL_H
#define LTTNG_ACTION_INTERNAL_H

#include <lttng/action/action.h>
#include <lttng/lttng-error.h>
#include <common/macros.h>
#include <common/buffer-view.h>
#include <common/dynamic-buffer.h>
#include <common/dynamic-array.h>
#include <stdbool.h>
#include <sys/types.h>
#include <urcu/ref.h>

typedef bool (*action_validate_cb)(struct lttng_action *action);
typedef void (*action_destroy_cb)(struct lttng_action *action);
typedef int (*action_serialize_cb)(struct lttng_action *action,
		struct lttng_dynamic_buffer *buf);
typedef bool (*action_equal_cb)(const struct lttng_action *a,
		const struct lttng_action *b);
typedef ssize_t (*action_create_from_buffer_cb)(
		const struct lttng_buffer_view *view,
		struct lttng_action **action);

struct lttng_action {
	struct urcu_ref ref;
	enum lttng_action_type type;
	action_validate_cb validate;
	action_serialize_cb serialize;
	action_equal_cb equal;
	action_destroy_cb destroy;
};

struct lttng_action_comm {
	/* enum lttng_action_type */
	int8_t action_type;
} LTTNG_PACKED;

struct lttng_action_capture_bytecode_element
{
	struct lttng_event_expr *expression;
	struct lttng_bytecode *bytecode;
};

LTTNG_HIDDEN
void lttng_action_init(struct lttng_action *action,
		enum lttng_action_type type,
		action_validate_cb validate,
		action_serialize_cb serialize,
		action_equal_cb equal,
		action_destroy_cb destroy);

LTTNG_HIDDEN
bool lttng_action_validate(struct lttng_action *action);

LTTNG_HIDDEN
int lttng_action_serialize(struct lttng_action *action,
		struct lttng_dynamic_buffer *buf);

LTTNG_HIDDEN
ssize_t lttng_action_create_from_buffer(const struct lttng_buffer_view *view,
		struct lttng_action **action);

LTTNG_HIDDEN
enum lttng_action_type lttng_action_get_type_const(
		const struct lttng_action *action);

LTTNG_HIDDEN
bool lttng_action_is_equal(const struct lttng_action *a,
		const struct lttng_action *b);

LTTNG_HIDDEN
void lttng_action_get(struct lttng_action *action);

LTTNG_HIDDEN
void lttng_action_put(struct lttng_action *action);

LTTNG_HIDDEN
const char* lttng_action_type_string(enum lttng_action_type action_type);

LTTNG_HIDDEN
enum lttng_error_code lttng_action_generate_capture_descriptor_bytecode_set(
		struct lttng_action *action,
		struct lttng_dynamic_pointer_array *bytecode_set);

#endif /* LTTNG_ACTION_INTERNAL_H */
