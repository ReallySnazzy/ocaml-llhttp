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

(** Set callbacks *)
val callback : llhttp_t -> string -> (unit -> int) -> unit

(** Set data callbacks *)
val data_callback : llhttp_t -> string -> (string -> int) -> unit
