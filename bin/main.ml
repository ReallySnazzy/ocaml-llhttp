let empty_data_cb name = fun data -> Printf.printf "Data callback %s with %s\n" name data; 0
let empty_cb name = fun () -> Printf.printf "No data callback %s\n" name; 0

let example () =
  let parser = Ocaml_llhttp.Llhttp.init HTTP_REQUEST in
  let () = Ocaml_llhttp.Llhttp.callback parser "on_message_begin" @@ empty_cb "on_message_begin" in
  let () = Ocaml_llhttp.Llhttp.data_callback parser "on_protocol" @@ empty_data_cb "on_protocol" in
  let http_data = "GET /path HTTP/1.1\r\nHost: example.com\r\n\r\n" in
  match Ocaml_llhttp.Llhttp.execute parser http_data with
  | 0 -> print_endline "Parsing successful"
  | code -> Printf.printf "Parsing failed with error code: %d\n" code

let () = example ()
