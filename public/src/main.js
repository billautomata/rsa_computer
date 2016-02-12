console.log(Date.now())
console.log('lol')

var d3 = require('d3')
var parent = d3.select('body').append('div').attr('class', 'container')

var p = 409
var q = 983
var n = p * q
var phi = (p - 1) * (q - 1)
var e = 5

var d = 320525

var panel_P = draw_number_as_leds(p, 'P')
var panel_Q = draw_number_as_leds(q, 'Q')
var panel_N = draw_number_as_leds(n, 'N')
var panel_PHI = draw_number_as_leds(phi, 'PHI')
var panel_E = draw_number_as_leds(e, 'E')

function draw_number_as_leds (v, msg) {
  var n_bits = 16
  var h = 24
  var w = (2 + n_bits) * h
  var svg = parent.append('div').append('svg')
  svg.attr('width', w).attr('height', h).style('outline', '1px solid rgba(0,0,0,0.1)')

  var leds = []
  for (var i = 0; i < n_bits; i++) {
    leds.push(svg.append('circle').attr('cx', (1.5 * h) + (i * h)).attr('cy', h * 0.5).attr('r', h * 0.5).attr('fill', 'rgba(255,0,0,0.1)'))
  }

  // draw empty bits
  // fill bits
  update(v)

  function update (v) {
    leds.forEach(function (l) {
      l.attr('fill', 'rgba(255,0,0,0.1)')
    })
    var bits = v.toString(2)

    var led_index = leds.length - 1
    for (i = bits.length - 1; i >= 0; i--) {
      if (bits[i] === '0') {
        leds[led_index].attr('fill', 'rgba(255,0,0,0.1)')
      } else {
        leds[led_index].attr('fill', 'rgba(255,0,0,1)')
      }
      led_index--
      if (led_index < 0) {
        i = -1
      }
    }
  }
  return update
}
