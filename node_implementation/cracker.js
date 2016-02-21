var bignum = require('bignum')

module.exports = function(publickey){

  var _t = Date.now().valueOf()
  var crack_index = bignum(2);
  var privatekey;
  var key = publickey

  function start(){

    if(key.generator.powm(crack_index, key.prime).eq(key.publickey)){
      privatekey = bignum(crack_index)
      console.log('cracked!')
      console.log(privatekey.toString())
      console.log('after',(Date.now().valueOf()-_t)/1000,'seconds')
    } else {
      crack_index = crack_index.add(1)
      if(crack_index.mod(10000).toNumber()===0){
        console.log(crack_index.toString())
      }
      process.nextTick(start)
    }
  }

  return {
    start: start
  }
  
}
