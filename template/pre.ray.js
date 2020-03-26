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

        // debug
        // const setScale = Module.cwrap('coutInt', 'void', ['number']);
        // setScale(101);
        // break;

        if ( x.fn && x.rt && x.at && x.av ) {
          console.log('in void, any case');
          // handle the void, any case
          const boundFn = Module.cwrap(x.fn, 'void', x.at);
          // const boundFn = Module.cwrap(x.fn, 'void', ['number']);
          boundFn(...x.av);
          // boundFn(99);
        } else if( x.fn && x.rt ) {
          // handle void, void case
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