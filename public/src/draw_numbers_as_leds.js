module.exports = function draw_number_as_leds (v, msg, parent) {
  var n_bits = 20
  var h = 24
  var w = (3 + n_bits) * h
  var svg = parent.append('div').append('svg')
  svg.attr('viewBox', '0 0 ' + w + ' ' + h)
  svg.attr('preserveAspectRatio', 'xMidYMid')
  svg.attr('width', '100%').style('outline', '1px solid rgba(0,0,0,0.1)')

  svg.append('text').attr('x', w - 2).attr('y', h * 0.5).attr('dy', '0.66em').attr('text-anchor', 'end').text(msg).style('font-size', h * 0.5)

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
