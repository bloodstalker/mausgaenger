function demo1(address) {
  var page = require("webpage").create()
  page.open(address).then(function(status){
    if (status == "success") {
      console.log("the title of the page is :" + page.title)
    } else {
      console.log("sorry. somebody fucked something up.")
    }
    page.close()
    slimer.exit()
  })
}

function demo2(address) {
  var page = require("webpage").create()
  page.onConsoleMessage = function(msg) {console.log(msg)}
  page.open(address, function(status) {
    var mainTitle = page.evaluate(function() {
      console.log("message from the webpage")
      return document.querySelector("h1").textContent
    })
    console.log("first title of the page is" + mainTitle)
    slimer.exit()
    })
}

function screenshot(address, destination) {
  var page = require("webpage").create()
  page.open(address, function(status){
    page.viewportSize = {width:1024, height:768}
    page.render(destination)
    slimer.exit()
  })
}

function mouse() {
  process.argv.forEach(function(val, index, array) {console.log(index + ":" + val)})
  const ffi = require("./node-ffi/lib/ffi")
  const ref = require("ref")
  const sudo = require("sudo-js")
  const fs = require("fs")
  var f_contents = fs.readFileSync("./data.json")
  var j_contents = JSON.parse(f_contents)
  sudo.setPassword(j_contents.password)
  var command_watch = ["./mausgaenger", "--event-id", "6", "--out", "./out", "--outb", "./outb"]
  var command_dupe = ["./mausgaenger", "6", "./out", "./outb"]
  sudo.exec(command_watch, function(err, pid, result){console.log(result)})
}

mouse()
