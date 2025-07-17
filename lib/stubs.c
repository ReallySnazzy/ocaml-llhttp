#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <string.h>
#include "vend/llhttp.h"  // Your llhttp header

// Callbacks

typedef struct {
  value on_message_begin;
  value on_headers_complete;
  value on_message_complete;
  value on_protocol_complete;
  value on_url_complete;
  value on_status_complete;
  value on_method_complete;
  value on_version_complete;
  value on_header_field_complete;
  value on_header_value_complete;
  value on_chunk_extension_name_complete;
  value on_chunk_extension_value_complete;
  value on_chunk_header;
  value on_chunk_complete;
  value on_reset;
  value on_protocol;
  value on_url;
  value on_status;
  value on_method;
  value on_version;
  value on_header_field;
  value on_header_value;
  value on_chunk_extension_name;
  value on_chunk_extension_value;
  value on_body;
} callbacks_t;

static void finalize_callbacks(callbacks_t *data) {
  if (Is_block(data->on_message_begin)) caml_remove_global_root(&data->on_message_begin);
  if (Is_block(data->on_headers_complete)) caml_remove_global_root(&data->on_headers_complete);
  if (Is_block(data->on_message_complete)) caml_remove_global_root(&data->on_message_complete);
  if (Is_block(data->on_protocol_complete)) caml_remove_global_root(&data->on_protocol_complete);
  if (Is_block(data->on_url_complete)) caml_remove_global_root(&data->on_url_complete);
  if (Is_block(data->on_status_complete)) caml_remove_global_root(&data->on_status_complete);
  if (Is_block(data->on_method_complete)) caml_remove_global_root(&data->on_method_complete);
  if (Is_block(data->on_version_complete)) caml_remove_global_root(&data->on_version_complete);
  if (Is_block(data->on_header_field_complete)) caml_remove_global_root(&data->on_header_field_complete);
  if (Is_block(data->on_header_value_complete)) caml_remove_global_root(&data->on_header_value_complete);
  if (Is_block(data->on_chunk_extension_name_complete)) caml_remove_global_root(&data->on_chunk_extension_name_complete);
  if (Is_block(data->on_chunk_extension_value_complete)) caml_remove_global_root(&data->on_chunk_extension_value_complete);
  if (Is_block(data->on_chunk_header)) caml_remove_global_root(&data->on_chunk_header);
  if (Is_block(data->on_chunk_complete)) caml_remove_global_root(&data->on_chunk_complete);
  if (Is_block(data->on_reset)) caml_remove_global_root(&data->on_reset);
  if (Is_block(data->on_protocol)) caml_remove_global_root(&data->on_protocol);
  if (Is_block(data->on_url)) caml_remove_global_root(&data->on_url);
  if (Is_block(data->on_status)) caml_remove_global_root(&data->on_status);
  if (Is_block(data->on_method)) caml_remove_global_root(&data->on_method);
  if (Is_block(data->on_version)) caml_remove_global_root(&data->on_version);
  if (Is_block(data->on_header_field)) caml_remove_global_root(&data->on_header_field);
  if (Is_block(data->on_header_value)) caml_remove_global_root(&data->on_header_value);
  if (Is_block(data->on_chunk_extension_name)) caml_remove_global_root(&data->on_chunk_extension_name);
  if (Is_block(data->on_chunk_extension_value)) caml_remove_global_root(&data->on_chunk_extension_value);
  if (Is_block(data->on_body)) caml_remove_global_root(&data->on_body);
}

static void init_callbacks(callbacks_t *data) {
  data->on_message_begin = Val_unit;
  data->on_headers_complete = Val_unit;
  data->on_message_complete = Val_unit;
  data->on_protocol_complete = Val_unit;
  data->on_url_complete = Val_unit;
  data->on_status_complete = Val_unit;
  data->on_method_complete = Val_unit;
  data->on_version_complete = Val_unit;
  data->on_header_field_complete = Val_unit;
  data->on_header_value_complete = Val_unit;
  data->on_chunk_extension_name_complete = Val_unit;
  data->on_chunk_extension_value_complete = Val_unit;
  data->on_chunk_header = Val_unit;
  data->on_chunk_complete = Val_unit;
  data->on_reset = Val_unit;
  data->on_protocol = Val_unit;
  data->on_url = Val_unit;
  data->on_status = Val_unit;
  data->on_method = Val_unit;
  data->on_version = Val_unit;
  data->on_header_field = Val_unit;
  data->on_header_value = Val_unit;
  data->on_chunk_extension_name = Val_unit;
  data->on_chunk_extension_value = Val_unit;
  data->on_body = Val_unit;
}

/////////////////////// llhttp_t exposure

// Finalizer for llhttp_t
static void finalize_llhttp(value v) {
  llhttp_t *d = (llhttp_t *)Data_custom_val(v);
  finalize_callbacks((callbacks_t*)d->data);
  free((callbacks_t*)d->data);
}

static struct custom_operations llhttp_custom_ops = {
  "llhttp_t",
  finalize_llhttp,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
  custom_fixed_length_default
};

CAMLprim value stub_create_llhttp(value unit) {
  CAMLparam1(unit);

  value block = caml_alloc_custom(&llhttp_custom_ops, sizeof(llhttp_t), 0, 1);
  llhttp_t *d = (llhttp_t *)Data_custom_val(block);
  d->data = malloc(sizeof(callbacks_t));
  if (d->data == NULL) caml_failwith("malloc failed");
  init_callbacks(d->data);

  CAMLreturn(block);
}

///////////////// Callbacks to settings glue
static int llhttp_invoke_on_message_begin(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_message_begin;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_headers_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_headers_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_message_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_message_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_protocol_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_protocol_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_url_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_url_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_status_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_status_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_method_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_method_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_version_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_version_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_header_field_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_header_field_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_header_value_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_header_value_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_chunk_extension_name_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_chunk_extension_name_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_chunk_extension_value_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_chunk_extension_value_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_chunk_header(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_chunk_header;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_chunk_complete(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_chunk_complete;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}
static int llhttp_invoke_on_reset(llhttp_t *parser) {
  value cb = ((callbacks_t*)parser->data)->on_reset;
  if (cb == Val_unit) return 0;
  value res = caml_callback(cb, Val_unit);
  return Int_val(res);
}

static int llhttp_invoke_on_protocol(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_protocol;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}
static int llhttp_invoke_on_url(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_url;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}
static int llhttp_invoke_on_status(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_status;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}
static int llhttp_invoke_on_method(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_method;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}
static int llhttp_invoke_on_version(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_version;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}
static int llhttp_invoke_on_header_field(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_header_field;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}
static int llhttp_invoke_on_header_value(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_header_value;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}
static int llhttp_invoke_on_chunk_extension_name(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_chunk_extension_name;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}
static int llhttp_invoke_on_chunk_extension_value(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_chunk_extension_value;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}
static int llhttp_invoke_on_body(llhttp_t *parser, const char *data, size_t len) {
  value cb = ((callbacks_t*)parser->data)->on_body;
  if (cb == Val_unit) return 0;
  char buf[len + 1];
  strncpy(buf, data, len);
  buf[len] = '\0';
  value vdata = caml_copy_string(buf);
  value res = caml_callback(cb, vdata);
  return Int_val(res);
}

//////////////// llhttp_settings_t exposure

static struct custom_operations llhttp_settings_custom_ops = {
  "llhttp_settings_t",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
  custom_fixed_length_default
};

CAMLprim value stub_create_llhttp_settings(value unit) {
  CAMLparam1(unit);

  value block = caml_alloc_custom(&llhttp_settings_custom_ops, sizeof(llhttp_settings_t), 0, 1);
  llhttp_settings_t *d = (llhttp_settings_t *)Data_custom_val(block);

  d->on_message_begin = llhttp_invoke_on_message_begin;
  d->on_headers_complete = llhttp_invoke_on_headers_complete;
  d->on_message_complete = llhttp_invoke_on_message_complete;
  d->on_protocol_complete = llhttp_invoke_on_protocol_complete;
  d->on_url_complete = llhttp_invoke_on_url_complete;
  d->on_status_complete = llhttp_invoke_on_status_complete;
  d->on_method_complete = llhttp_invoke_on_method_complete;
  d->on_version_complete = llhttp_invoke_on_version_complete;
  d->on_header_field_complete = llhttp_invoke_on_header_field_complete;
  d->on_header_value_complete = llhttp_invoke_on_header_value_complete;
  d->on_chunk_extension_name_complete = llhttp_invoke_on_chunk_extension_name_complete;
  d->on_chunk_extension_value_complete = llhttp_invoke_on_chunk_extension_value_complete;
  d->on_chunk_header = llhttp_invoke_on_chunk_header;
  d->on_chunk_complete = llhttp_invoke_on_chunk_complete;
  d->on_reset = llhttp_invoke_on_reset;
  d->on_protocol = llhttp_invoke_on_protocol;
  d->on_url = llhttp_invoke_on_url;
  d->on_status = llhttp_invoke_on_status;
  d->on_method = llhttp_invoke_on_method;
  d->on_version = llhttp_invoke_on_version;
  d->on_header_field = llhttp_invoke_on_header_field;
  d->on_header_value = llhttp_invoke_on_header_value;
  d->on_chunk_extension_name = llhttp_invoke_on_chunk_extension_name;
  d->on_chunk_extension_value = llhttp_invoke_on_chunk_extension_value;
  d->on_body = llhttp_invoke_on_body;

  CAMLreturn(block);
}

//////////////////// STUBS ////////////////////////////

static void caml_llhttp_realloc(value *callback, value new_callback) {
  if (Is_block(*callback)) {
    caml_remove_global_root(callback);
  }
  *callback = new_callback;
  caml_register_global_root(callback);
}

CAMLprim value stub_llhttp_on_message_begin (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_message_begin, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_headers_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_headers_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_message_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_message_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_protocol_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_protocol_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_url_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_url_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_status_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_status_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_method_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_method_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_version_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_version_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_header_field_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_header_field_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_header_value_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_header_value_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_chunk_extension_name_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_chunk_extension_name_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_chunk_extension_value_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_chunk_extension_value_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_chunk_header (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_chunk_header, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_chunk_complete (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_chunk_complete, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_reset (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_reset, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_protocol (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_protocol, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_url (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_url, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_status (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_status, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_method (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_method, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_version (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_version, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_header_field (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_header_field, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_header_value (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_header_value, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_chunk_extension_name (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_chunk_extension_name, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_chunk_extension_value (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_chunk_extension_value, v_callback); 

  CAMLreturn(Val_unit);
}

CAMLprim value stub_llhttp_on_body (value v_parser, value v_callback) {
  CAMLparam2(v_parser, v_callback);

  llhttp_t *parser = (llhttp_t*)Data_custom_val(v_parser);
  callbacks_t *callbacks = (callbacks_t*)parser->data;
  caml_llhttp_realloc(&((callbacks_t*)parser->data)->on_body, v_callback); 

  CAMLreturn(Val_unit);
}

// llhttp_init (sets up context for callbacks)
CAMLprim value stub_llhttp_init(value v_parser, value v_type, value v_settings) {
  CAMLparam3(v_parser, v_type, v_settings);

  llhttp_t *d = (llhttp_t *)Data_custom_val(v_parser);
  llhttp_settings_t *sd = (llhttp_settings_t *)Data_custom_val(v_settings);
  int type = Int_val(v_type);
  void* callbacks = d->data;
  llhttp_init(d, type, sd);
  d->data = callbacks;

  CAMLreturn(Val_unit);
}

// llhttp_execute
CAMLprim value stub_llhttp_execute(value v_parser, value v_data) {
  CAMLparam2(v_parser, v_data);

  llhttp_t *d = (llhttp_t *)Data_custom_val(v_parser);
  const char *data = String_val(v_data);
  size_t len = strlen(data);
  llhttp_errno_t res = llhttp_execute(d, data, len);
  CAMLreturn(Val_int(res));
}

// llhttp_reset
CAMLprim value stub_llhttp_reset(value v_parser) {
  CAMLparam1(v_parser);
  
  llhttp_t *d = (llhttp_t *)Data_custom_val(v_parser);
  llhttp_reset(d);

  CAMLreturn(Val_unit);
}

// llhttp_get_errno
CAMLprim value stub_llhttp_get_errno(value v_parser) {
  CAMLparam1(v_parser);

  llhttp_t *d = (llhttp_t *)Data_custom_val(v_parser);
  llhttp_errno_t err = llhttp_get_errno(d);

  CAMLreturn(Val_int(err));
}

// llhttp_settings_init
CAMLprim value stub_llhttp_settings_init(value v_settings) {
  CAMLparam1(v_settings);

  llhttp_settings_t *d = (llhttp_settings_t *)Data_custom_val(v_settings);
  llhttp_settings_init(d);

  CAMLreturn(Val_unit);
}


