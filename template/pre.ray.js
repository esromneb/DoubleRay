// This file (pre.ray.js)
// gets appended to the top of ray.js
////////////////////////////////////////

Module["onCustomMessage"] = (x) => {
  console.log('wworker got msg: ' + JSON.stringify(x.data));
}

////////////////////////////////////////
// end of pre.ray.js