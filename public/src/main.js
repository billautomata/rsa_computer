console.log(Date.now())
console.log('lol')

var d3 = require('d3')
var parent = d3.select('body').append('div').attr('class', 'container')

var p = 409
var q = 983

p = 19
q = 73

var n_dirty = true
var n = 0

var phi_dirty = true
var phi = 0

var e_dirty = true
var e_prime_pick_index = 0
var e = 0

var d_dirty = true
var d_setup_complete = false
var D,nt,r,nr,quot,tmp

// encrypt / decrypt
var encrypt_dirty = true
var encrypt_setup_complete = false
var PT,CT,e_prime
PT = 30

var decrypt_dirty = true
var decrypt_setup_complete = false
var _PT, DPT, _e_prime

// tick stuff
var interval_step = 0
setInterval(global_tick, 0)
function global_tick () {
  // console.log('interval_step', interval_step)
  interval_step++
  if (n_dirty) {
    console.log('setting N')
    n = p * q
    panel_N(n)
    n_dirty = false
    return
  }
  if (phi_dirty) {
    phi = (p - 1) * (q - 1)
    panel_PHI(phi)
    phi_dirty = false
    console.log('setting PHI', phi)
    return
  }
  if (e_dirty) {
    // pick the next prime in the list
    //
    var primes_array = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 47, 53, 59, 61, 67, 71, 73]
    e = primes_array[e_prime_pick_index]
    panel_E(e)
    e_prime_pick_index++

    if (phi % e !== 0) {
      console.log('setting e', e)
      e_dirty = false
    }
    return
  }
  if (d_dirty) {
    if (!d_setup_complete) {
      D = 0
      nt = 1
      r = phi
      nr = e % phi

      // correct values to acceptable input range
      if (phi < 0) {
        phi = -phi
      }
      if (e < 0) {
        e = phi - (-e % phi)
      }
      d_setup_complete = true
    } else {
      if (nr != 0) {
        quot = (r / nr) | 0
        tmp = nt
        nt = D - quot * nt
        D = tmp
        tmp = nr
        nr = r - quot * nr
        r = tmp

        panel_NT(nt)
        panel_R(r)
        panel_NR(nr)
        panel_tmp(tmp)
        panel_QUOT(quot)
        panel_D(D)
      } else {
        if (r > 1) { return -1; }
        if (D < 0) { D += phi; }
        panel_R(r)
        panel_D(D)
        console.log('setting D', D)
        d_dirty = false
      }
    }
    return
  }
  if (encrypt_dirty) {
    if (encrypt_setup_complete === false) {
      CT = 1
      panel_CT(CT)
      e_prime = 0
      panel_encrypt_eprime(e_prime)
      encrypt_setup_complete = true
    } else {
      // perform iterative calcs
      if (e_prime < e) {
        e_prime += 1
        CT = CT * PT
        CT = CT % n
      } else {
        console.log('setting ciphertext', CT)
        encrypt_dirty = false
      }
      panel_encrypt_eprime(e_prime)
      panel_CT(CT)
    }
    return
  }
  if (decrypt_dirty) {
    if (decrypt_setup_complete === false) {
      DPT = 1
      panel_decrypted_PT(DPT)
      _e_prime = 0
      panel_decrypt_eprime(_e_prime)
      decrypt_setup_complete = true
    } else {
      // perform iterative calcs
      if (_e_prime < D) {
        _e_prime += 1
        DPT = DPT * CT
        DPT = DPT % n
      } else {
        console.log('setting decrypted plaintext', DPT)
        decrypt_dirty = false
      }
      panel_decrypt_eprime(_e_prime)
      panel_decrypted_PT(DPT)
    }
    return
  }
}

// var d = 320525

var panel_P = draw_number_as_leds(p, 'P')
var panel_Q = draw_number_as_leds(q, 'Q')
var panel_N = draw_number_as_leds(n, 'N')
var panel_PHI = draw_number_as_leds(phi, 'PHI')
var panel_E = draw_number_as_leds(e, 'E')
var panel_D = draw_number_as_leds(0, 'D')
var panel_NT = draw_number_as_leds(0, 'NT')
var panel_R = draw_number_as_leds(0, 'R')
var panel_NR = draw_number_as_leds(0, 'NR')
var panel_QUOT = draw_number_as_leds(0, 'QUOT')
var panel_tmp = draw_number_as_leds(0, 'TMP')

// encrypt
var panel_PT = draw_number_as_leds(PT, 'PT')
var panel_encrypt_eprime = draw_number_as_leds(0, "e'")
var panel_CT = draw_number_as_leds(0, 'CT')

// decrypt
var panel_decrypt_eprime = draw_number_as_leds(0, "e'2")
var panel_decrypted_PT = draw_number_as_leds(0, 'DPT')

//
function modular_exponentiation (cipher_text, exponent, publickey) {
  c = 1
  e_prime = 0 // our counter variable
  while(e_prime < exponent){
    e_prime = e_prime + 1
    if (e_prime % 2) {
      P1OUT = BIT0
    } else {
      P1OUT = BIT6
    }
    c = c * cipher_text
    c = c % publickey
  }
  // c is the plaintext
  P1OUT = 0
  return c
}
//

function modular_multiplicative_inverse (E, PHI) {
  var D = 0
  var nt = 1
  var r = PHI
  var nr = E % PHI

  // correct values to acceptable input range
  if (PHI < 0) {
    PHI = -PHI
  }
  if (E < 0) {
    E = PHI - (-E % PHI)
  }

  // perform operations to calculate the MMI
  var quot
  var tmp
  while (nr != 0) {
    quot = (r / nr) | 0
    tmp = nt
    nt = D - quot * nt
    D = tmp
    tmp = nr
    nr = r - quot * nr
    r = tmp

    panel_NT(nt)
    panel_R(r)
    panel_NR(nr)
    panel_tmp(tmp)
    panel_QUOT(quot)
    panel_D(D)
  }
  if (r > 1) { return -1; }
  if (D < 0) { D += PHI; }
  panel_R(r)
  panel_D(D)
  return D
}

function draw_number_as_leds (v, msg) {
  var n_bits = 14
  var h = 24
  var w = (3 + n_bits) * h
  var svg = parent.append('div').append('svg')
  svg.attr('width', w).attr('height', h).style('outline', '1px solid rgba(0,0,0,0.1)')
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
