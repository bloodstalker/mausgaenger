function mouse() {
  const fs = require("fs")
  const buf = fs.readFileSync("./mausgaenger.wasm")
  //const lib_mouse = WebAssembly.instantiate(new Uint8Array(buf)).exports
  const lib_mouse = WebAssembly.instantiate()
  lib_mouse.mouse()
}

mouse()
