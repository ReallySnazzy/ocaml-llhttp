(* llhttp types *)
type llhttp_t
type llhttp_settings_t

type parser_type = HTTP_REQUEST | HTTP_RESPONSE | HTTP_BOTH

let parser_type_to_int = function
  | HTTP_REQUEST -> 0
  | HTTP_RESPONSE -> 1
  | HTTP_BOTH -> 2

external create_llhttp : unit -> llhttp_t = "stub_create_llhttp"
external create_llhttp_settings : unit -> llhttp_settings_t = "stub_create_llhttp_settings"

(* Your functions, now as external *)
external llhttp_init : llhttp_t -> int -> llhttp_settings_t -> unit = "stub_llhttp_init"
external llhttp_execute : llhttp_t -> string -> int = "stub_llhttp_execute"
external llhttp_reset : llhttp_t -> unit = "stub_llhttp_reset"
external llhttp_get_errno : llhttp_t -> int = "stub_llhttp_get_errno"

let init parser_type =
  let parser = create_llhttp () in
  let settings = create_llhttp_settings () in
  llhttp_init parser (parser_type_to_int parser_type) settings;
  parser

(* Parse HTTP data *)
let execute parser data =
  llhttp_execute parser data

(* Reset parser *)
let reset parser =
  llhttp_reset parser

(* Get error code *)
let get_errno parser =
  llhttp_get_errno parser

(* Unit callbacks *)
external on_message_begin : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_message_begin"
external on_headers_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_headers_complete"
external on_message_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_message_complete"
external on_protocol_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_protocol_complete"
external on_url_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_url_complete"
external on_status_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_status_complete"
external on_method_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_method_complete"
external on_version_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_version_complete"
external on_header_field_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_header_field_complete"
external on_header_value_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_header_value_complete"
external on_chunk_extension_name_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_chunk_extension_name_complete"
external on_chunk_extension_value_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_chunk_extension_value_complete"
external on_chunk_header : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_chunk_header"
external on_chunk_complete : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_chunk_complete"
external on_reset : llhttp_t -> (unit -> int) -> unit = "stub_llhttp_on_reset"

(* Data callbacks *)
external on_protocol : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_protocol"
external on_url : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_url"
external on_status : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_status"
external on_method : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_method"
external on_version : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_version"
external on_header_field : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_header_field"
external on_header_value : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_header_value"
external on_chunk_extension_name : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_chunk_extension_name"
external on_chunk_extension_value : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_chunk_extension_value"
external on_body : llhttp_t -> (string -> int) -> unit = "stub_llhttp_on_body"
