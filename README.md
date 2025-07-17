# OCaml bindings for llhttp

[llhttp](https://github.com/nodejs/llhttp/tree/main) is a performant HTTP parser used in [Node.js](https://nodejs.org/en)

## Intents

This project prefers vendoring and static linking so that this library can be used more seamlessly within the OCaml ecosystem.

The current goal is to get more of the functionality implemented into this binding, but more focus on performance might be done later. 

## Bug reports

Feel free to open an issue with any information you have. Any help addressing the issue would be appreciated.

## Contributing

Feel free to open a PR with any contributions you might have.

## Example

```ocaml
let empty_data_cb name = fun data -> Printf.printf "Data callback %s with %s\n" name data; 0
let empty_cb name = fun () -> Printf.printf "No data callback %s\n" name; 0

let () =
  let parser = Ocaml_llhttp.Llhttp.init HTTP_REQUEST in
  let () = Ocaml_llhttp.Llhttp.callback parser "on_message_begin" @@ empty_cb "on_message_begin" in
  let () = Ocaml_llhttp.Llhttp.data_callback parser "on_protocol" @@ empty_data_cb "on_protocol" in
  let http_data = "GET /path HTTP/1.1\r\nHost: example.com\r\n\r\n" in
  match Ocaml_llhttp.Llhttp.execute parser http_data with
  | 0 -> print_endline "Parsing successful"
  | code -> Printf.printf "Parsing failed with error code: %d\n" code
```

As you can see from this example, the binding is quite low level and is closely tied to llhttp with a few changes.

## llhttp 

This was forked from master of llhttp when the latest release was v9.3.0. 

### Updating llhttp

Assuming no changes to the interface, it is possible to plug in the latest version of llhttp using the following steps.

1. Clone llhttp to a local directory
2. Run `npm ci` followed by `make` from the llhttp directory
3. Copy the following files into `lib/vend` of the ocaml-llhttp project
    - llhttp/build/c/llhttp.c
    - llhttp/src/native/http.c
    - llhttp/src/native/api.c
    - llhttp/build/llhttp.h

## Docs

Currently the only real documentation is found in lib/llhttp.mli, but it would be nice to have more formal documentation. Examples and a function level reference would be ideal.
