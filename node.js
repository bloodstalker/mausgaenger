function mouse() {
  const fs = require("fs")
  const buf = fs.readFileSync("./mausgaenger.wasm")
  const lib_mouse = Wasm.instantiateModule(new Uint8Array(buf)).exports
  lib.mouse()
}

mouse()
