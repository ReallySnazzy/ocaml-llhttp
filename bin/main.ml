let empty_data_cb name = fun data -> Printf.printf "Data callback %s with %s\n" name data; 0
let empty_cb name = fun () -> Printf.printf "No data callback %s\n" name; 0


let example () =
  let parser = Llhttp.init HTTP_REQUEST in

  Llhttp.on_message_begin parser @@ empty_cb "on_message_begin";
  Llhttp.on_headers_complete parser @@ empty_cb "on_headers_complete";
  Llhttp.on_message_complete parser @@ empty_cb "on_message_complete";
  Llhttp.on_protocol_complete parser @@ empty_cb "on_protocol_complete";
  Llhttp.on_url_complete parser @@ empty_cb "on_url_complete";
  Llhttp.on_status_complete parser @@ empty_cb "on_status_complete";
  Llhttp.on_method_complete parser @@ empty_cb "on_method_complete";
  Llhttp.on_version_complete parser @@ empty_cb "on_version_complete";
  Llhttp.on_header_field_complete parser @@ empty_cb "on_header_field_complete";
  Llhttp.on_header_value_complete parser @@ empty_cb "on_header_value_complete";
  Llhttp.on_chunk_extension_name_complete parser @@ empty_cb "on_chunk_extension_name_complete";
  Llhttp.on_chunk_extension_value_complete parser @@ empty_cb "on_chunk_extension_value_complete";
  Llhttp.on_chunk_header parser @@ empty_cb "on_chunk_header";
  Llhttp.on_chunk_complete parser @@ empty_cb "on_chunk_complete";
  Llhttp.on_reset parser @@ empty_cb "on_reset";


  Llhttp.on_protocol parser @@ empty_data_cb "on_protocol";
  Llhttp.on_url parser @@ empty_data_cb "on_url";
  Llhttp.on_status parser @@ empty_data_cb "on_status";
  Llhttp.on_method parser @@ empty_data_cb "on_method";
  Llhttp.on_version parser @@ empty_data_cb "on_version";
  Llhttp.on_header_field parser @@ empty_data_cb "on_header_field";
  Llhttp.on_header_value parser @@ empty_data_cb "on_header_value";
  Llhttp.on_chunk_extension_name parser @@ empty_data_cb "on_chunk_extension_name";
  Llhttp.on_chunk_extension_value parser @@ empty_data_cb "on_chunk_extension_value";
  Llhttp.on_body parser @@ empty_data_cb "on_body";

  let http_data = "GET /path HTTP/1.1\r\nHost: example.com\r\n\r\n" in
  match Llhttp.execute parser http_data with
  | 0 -> print_endline "Parsing successful"
  | code -> Printf.printf "Parsing failed with error code: %d\n" code

let () = example ()
