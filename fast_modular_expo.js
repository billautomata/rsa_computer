fast_modular_expo(5,117,19)
fast_modular_expo(44336,17143,60491)

function fast_modular_expo(a,b,c){

  console.log(a,'^',b,' % ',c)

  // convert b to binary
  var binary_b = b.toString(2)
  console.log('b in binary', binary_b)
  console.log('there are ', binary_b.length, ' significant bits.')
  console.log('calculate the values of (2^n) from zero to ', binary_b.length-1)

  // build a lookup table of values to use in the next step
  var pow_two_mod_c = []
  for(var i = 0; i < binary_b.length; i++){
    if(i == 0){
      pow_two_mod_c.push(Math.pow(a,Math.pow(2,i)) % c)
    } else {
      var pval = pow_two_mod_c[i-1]
      pow_two_mod_c.push((pval*pval) % c)
    }
  }
  console.log(pow_two_mod_c)

  console.log('binary reverse', binary_b.split('').reverse().join(''))
  var running_value = 1
  binary_b.split('').reverse().forEach(function(bit,idx){
    if(Number(bit) === 1){
      running_value *= pow_two_mod_c[idx]
      running_value = running_value % c
      console.log(running_value)
    }
  })
  // var result = running_value % c
  console.log('result',running_value)

}
