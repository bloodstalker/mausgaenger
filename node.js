function mouse() {
  const fs = require("fs")
  const ffi = require("./node-ffi/lib/ffi")

  const buf = fs.readFileSync("./mausgaenger.wasm")
  var u_buf = new Uint8Array(buf)
  if (WebAssembly.validate(u_buf)) {
    console.log("wasm object valid.")
  } else {
    console.log("wasm object not valid.")
  }
  var mouse_module = new WebAssembly.Module(u_buf)

  var mouse_exports = WebAssembly.Module.exports(mouse_module)
  var mouse_imports = WebAssembly.Module.imports(mouse_module)
  var mouse_cs_sections = WebAssembly.Module.customSections(mouse_module)
  console.log(mouse_exports)

  //var mouse_instance = new WebAssembly.instantiate(mouse_module, importObject)
  //console.log(mouse_imports)
  //console.log(mouse_cs_sections)
}

mouse()
