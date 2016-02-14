var d3 = require('d3')
var draw_number_as_leds = require('./draw_numbers_as_leds.js')

module.exports = function () {
  var parent = d3.select('body').append('div').attr('class', 'container').append('div').attr('class', 'col-md-6')
  parent.append('h3').attr('class', 'text-center').html('RSA Computer Simulator')

  var howto = parent.append('h5').attr('class', 'col-md-12 text-center')
  howto.html('Select P and Q values.  Ensure they are prime.<br>Choose a plaintext value.<br>All of these numbers should be integers or it does not work.')

  // append inputs that change p and q
  var parent_input = parent.append('div').attr('class', 'col-md-12').style('margin-bottom', '10px')
  var parent_p = parent_input.append('div').attr('class', 'col-md-6 text-center')
  parent_p.append('h4').html('P')
  var input_p = parent_p.append('input').attr('class', 'col-md-12')

  var parent_q = parent_input.append('div').attr('class', 'col-md-6 text-center')
  parent_q.append('h4').html('Q')
  var input_q = parent_q.append('input').attr('class', 'col-md-12')

  var parent_plaintext = parent_input.append('div').attr('class', 'col-md-12 text-center')
  parent_plaintext.append('h4').html('plaintext')
  var input_plaintext = parent_plaintext.append('input').attr('class', 'col-md-12')

  var p = 47
  var q = 53
  var PT = 30
  var iteration_speed = 500

  input_p.attr('value', p)
  input_q.attr('value', q)
  input_plaintext.attr('value', PT)

  input_p.on('keyup', function () {
    if (d3.event.keyCode === 13) {
      console.log(d3.event)
      var v = Number(d3.select(this).property('value'))
      if (p !== v) {
        p = v
        console.log(v, isNaN(v))
        panel_P(v)
        reset_panel_state()
      }
    }
  })
  input_q.on('keyup', function () {
    if (d3.event.keyCode === 13) {
      var v = Number(d3.select(this).property('value'))
      if (q !== v) {
        q = v
        console.log(v, isNaN(v))
        panel_Q(v)
        reset_panel_state()
      }
    }
  })
  input_plaintext.on('keyup', function () {
    if (d3.event.keyCode === 13) {
      var v = Number(d3.select(this).property('value'))
      if (PT !== v) {
        PT = v
        console.log(v, isNaN(v))
        panel_PT(v)
        reset_panel_state()
      }
    }
  })

  function reset_panel_state () {
    d_setup_complete = decrypt_setup_complete = encrypt_setup_complete = e_setup_complete = false
    n_dirty = phi_dirty = e_dirty = d_dirty = encrypt_dirty = decrypt_dirty = true
    status_plaintext_greater_than_n.html('')
    status_decrypt_encrypt_checker.html('')
    iteration_speed = 500
    panel_P(p)
    panel_Q(q)
    panel_N(0)
    panel_PHI(0)
    panel_E(0)
    panel_D(0)
    panel_NT(0)
    panel_R(0)
    panel_NR(0)
    panel_QUOT(0)
    panel_tmp(0)
    panel_PT(PT)
    panel_encrypt_eprime(0)
    panel_CT(0)
    panel_decrypt_eprime(0)
    panel_decrypted_PT(0)
    setTimeout(global_tick, iteration_speed)
  }

  var n_dirty = true
  var n = 0

  var phi_dirty = true
  var phi = 0

  var e_dirty = true
  var e_setup_complete = false
  var e_prime_pick_index = 0
  var e = 0

  var d_dirty = true
  var d_setup_complete = false
  var D, nt, r, nr, quot, tmp

  // encrypt / decrypt
  var encrypt_dirty = true
  var encrypt_setup_complete = false
  var CT, e_prime

  var decrypt_dirty = true
  var decrypt_setup_complete = false
  var DPT, _e_prime

  var panel_P = draw_number_as_leds(p, 'P', parent)
  var panel_Q = draw_number_as_leds(q, 'Q', parent)
  var panel_N = draw_number_as_leds(n, 'N', parent)
  var panel_PHI = draw_number_as_leds(phi, 'PHI', parent)
  var panel_E = draw_number_as_leds(e, 'E', parent)
  var panel_D = draw_number_as_leds(0, 'D', parent)
  var panel_NT = draw_number_as_leds(0, 'NT', parent)
  var panel_R = draw_number_as_leds(0, 'R', parent)
  var panel_NR = draw_number_as_leds(0, 'NR', parent)
  var panel_QUOT = draw_number_as_leds(0, 'QUOT', parent)
  var panel_tmp = draw_number_as_leds(0, 'TMP', parent)

  // encrypt
  var panel_PT = draw_number_as_leds(PT, 'PT', parent)
  var panel_encrypt_eprime = draw_number_as_leds(0, "e'", parent)
  var panel_CT = draw_number_as_leds(0, 'CT', parent)

  // decrypt
  var panel_decrypt_eprime = draw_number_as_leds(0, "e'2", parent)
  var panel_decrypted_PT = draw_number_as_leds(0, 'DPT', parent)

  // status variables
  var status_parent = parent.append('div').attr('class', 'col-md-12')
  var status_current_state = status_parent.append('h2').attr('class', 'text-center').html('none')
  var status_plaintext_greater_than_n = status_parent.append('h4').attr('class', 'text-center').html('')
  var status_decrypt_encrypt_checker = status_parent.append('h4').attr('class', 'text-center').html('')

  // tick stuff
  window.interval_step = 0
  setTimeout(global_tick, iteration_speed)
  function global_tick () {
    // console.log('interval_step', interval_step)
    window.interval_step++
    if (n_dirty) {
      status_current_state.html('key generation (intial steps)')
      n = p * q
      panel_N(n)
      n_dirty = false
      console.log('setting N', n)
      if (n < PT) {
        status_plaintext_greater_than_n.html('warning key too small for message size, decrease message size or increase key length with larger P and Q values')
      }
      return setTimeout(global_tick, iteration_speed)
    }
    if (phi_dirty) {
      phi = (p - 1) * (q - 1)
      panel_PHI(phi)
      phi_dirty = false
      console.log('setting PHI', phi)
      return setTimeout(global_tick, iteration_speed)
    }
    if (e_dirty) {
      // pick the next prime in the list
      //
      if (!e_setup_complete) {
        e_prime_pick_index = 0
        e_setup_complete = true
      }
      var primes_array = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139]
      e = primes_array[e_prime_pick_index]
      panel_E(e)
      e_prime_pick_index++

      if (phi % e !== 0) {
        console.log('setting e', e)
        e_dirty = false
      }
      return setTimeout(global_tick, iteration_speed)
    }
    if (d_dirty) {
      status_current_state.html('calculating private key')
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
        if (nr !== 0) {
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
          if (r > 1) { return -1 }
          if (D < 0) { D += phi }
          panel_R(r)
          panel_D(D)
          console.log('setting D', D)
          d_dirty = false
        }
      }
      return setTimeout(global_tick, iteration_speed)
    }
    if (encrypt_dirty) {
      status_current_state.html('encrypting')
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
      return setTimeout(global_tick, iteration_speed)
    }
    if (decrypt_dirty) {
      iteration_speed = 0
      status_current_state.html('decrypting')
      if (decrypt_setup_complete === false) {
        DPT = 1
        panel_decrypted_PT(DPT)
        _e_prime = 0
        panel_decrypt_eprime(_e_prime)
        decrypt_setup_complete = true
      } else {
        // perform iterative calcs
        var n_calcs = Math.ceil(D / 100)
        while (n_calcs--) {
          if (_e_prime < D) {
            _e_prime += 1
            status_current_state.html('DECRYPTING: ' + (100.0 * (_e_prime / D)).toFixed(0) + '%')
            DPT = DPT * CT
            DPT = DPT % n
          } else {
            console.log('setting decrypted plaintext', DPT)
            decrypt_dirty = false
            status_current_state.html('done decrypting')
            if (DPT !== PT) {
              status_decrypt_encrypt_checker.html('<p>plaintext & decrypted plaintext mismatch</p><p>Do you have prime P and Q values? Is your plaintext message larger than your key size?</p><p>' + [DPT, '!==', PT].join(' ') + '</p>')
            } else {
              status_decrypt_encrypt_checker.html('<p>plaintext & decrypted plaintext match</p><p>' + [DPT, '===', PT].join(' ') + '</p>')
            }
          }
        }

        panel_decrypt_eprime(_e_prime)
        panel_decrypted_PT(DPT)
      }
      return setTimeout(global_tick, iteration_speed)
    }
  }
}
