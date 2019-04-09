/*
    OUTPUTS: 3
    - payload: bool heater
    - payload: current temp
    - payload: target temp
    
    INPUT:
    - topic: setTarget
    - topic: setCurrent
    - topic: setWindow
*/
const hysteresis = 0.2;

if (msg.topic === 'setTarget') {
    context.set('target', msg.payload);
}
if (msg.topic === 'setCurrent') {
    context.set('current', msg.payload);
}
if (msg.topic === 'setWindow') {
    context.set('win', msg.payload);
}

const target = context.get('target');
const current = context.get('current') || 20;
const win = context.get('win') !== false;

// Heater off when window is open
if (!win) {
    return [
        {payload: false},
        {payload: current},
        {payload: target}
    ];
}

// Heater off
if (current > target + hysteresis) {
    return [
        {payload: false},
        {payload: current},
        {payload: target}
    ];
}

// Heater on
if (current < target - hysteresis) {
    return [
        {payload: true},
        {payload: current},
        {payload: target}
    ];
}

return [null, {payload: current}, {payload: target}];
