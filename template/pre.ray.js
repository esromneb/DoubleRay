// This file (pre.ray.js)
// gets appended to the top of ray.js
////////////////////////////////////////

Module['onCustomMessage'] = (x) => {
  console.log('worker got msg: ' + JSON.stringify(x.data));
  if(x.data.userData && x.data.userData.type) {
    Module['dispatchCustomMessageType'](x.data.userData);
  } else {
    console.log('worker DROPPED: ' + JSON.stringify(x.data));
  }
}


Module['dispatchCustomMessageType'] = (x) => {
  console.log('in dispatchCustomMessageType' + JSON.stringify(x));

  switch(x.type) {
    case 'call': {
        // handle void void case
        if( x.fn && x.rt ) {
          const boundFn = Module.cwrap(x.fn, 'void');
          boundFn();
        } else {
          console.log('dispatchCustomMessageType switch CALL DROPPED: ' + JSON.stringify(x));
        }
      break;
    }
    default: {
      console.log('dispatchCustomMessageType DROPPED: ' + JSON.stringify(x));
    }
  }
}
////////////////////////////////////////
// end of pre.ray.js