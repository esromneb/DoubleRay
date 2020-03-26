// This file (pre.ray.js)
// gets appended to the top of ray.js
////////////////////////////////////////

Module["onCustomMessage"] = (x) => {
  console.log('worker got msg: ' + JSON.stringify(x));
}

////////////////////////////////////////
// end of pre.ray.js