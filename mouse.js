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


//demo1("http://slimerjs.org")
//demo2("http://slimerjs.org")
//screenshot("http://slimerjs.org")
//screenshot("https://www.ticketmaster.nl/event/official-awakenings-festival-afterparty-tickets/223573?language=en-us", "./screenshot.png")
