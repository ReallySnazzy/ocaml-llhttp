(** llhttp bindings for OCaml *)

type parser_type = HTTP_REQUEST | HTTP_RESPONSE | HTTP_BOTH
type llhttp_t
type llhttp_settings_t

(** Initialize a parser *)
val init : parser_type -> llhttp_t

(** Parse HTTP data *)
val execute : llhttp_t -> string -> int

(** Reset parser *)
val reset : llhttp_t -> unit

(** Get error code *)
val get_errno : llhttp_t -> int

(* Unit callbacks *)
val on_message_begin : llhttp_t -> (unit -> int) -> unit 
val on_headers_complete : llhttp_t -> (unit -> int) -> unit 
val on_message_complete : llhttp_t -> (unit -> int) -> unit 
val on_protocol_complete : llhttp_t -> (unit -> int) -> unit 
val on_url_complete : llhttp_t -> (unit -> int) -> unit 
val on_status_complete : llhttp_t -> (unit -> int) -> unit 
val on_method_complete : llhttp_t -> (unit -> int) -> unit 
val on_version_complete : llhttp_t -> (unit -> int) -> unit 
val on_header_field_complete : llhttp_t -> (unit -> int) -> unit 
val on_header_value_complete : llhttp_t -> (unit -> int) -> unit 
val on_chunk_extension_name_complete : llhttp_t -> (unit -> int) -> unit 
val on_chunk_extension_value_complete : llhttp_t -> (unit -> int) -> unit 
val on_chunk_header : llhttp_t -> (unit -> int) -> unit 
val on_chunk_complete : llhttp_t -> (unit -> int) -> unit 
val on_reset : llhttp_t -> (unit -> int) -> unit 

(* Data callbacks *)
val on_protocol : llhttp_t -> (string -> int) -> unit 
val on_url : llhttp_t -> (string -> int) -> unit 
val on_status : llhttp_t -> (string -> int) -> unit 
val on_method : llhttp_t -> (string -> int) -> unit 
val on_version : llhttp_t -> (string -> int) -> unit 
val on_header_field : llhttp_t -> (string -> int) -> unit 
val on_header_value : llhttp_t -> (string -> int) -> unit 
val on_chunk_extension_name : llhttp_t -> (string -> int) -> unit 
val on_chunk_extension_value : llhttp_t -> (string -> int) -> unit 
val on_body : llhttp_t -> (string -> int) -> unit 
