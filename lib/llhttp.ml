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

external callback : llhttp_t -> string -> (unit -> int) -> unit = "stub_llhttp_set_callback"
external data_callback : llhttp_t -> string -> (string -> int) -> unit = "stub_llhttp_set_callback"

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
