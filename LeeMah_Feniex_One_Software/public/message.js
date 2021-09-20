// var awsIot = require('aws-iot-device-sdk');

// var controlAddress;

// process.on('message', (arg) => {
//     controlAddress = arg;
//     console.log("Address: ", controlAddress);
// });

// var device = awsIot.device({
//     keyPath: '/opt/external-resources/Feniex_Controllers.private.key',
//     certPath: '/opt/external-resources/Feniex_Controllers.cert.pem',
//     caPath: '/opt/external-resources/root-CA.crt',
//     clientId: 'basicPubSub',
//     host: 'a2mmua2sxz1lo6-ats.iot.us-east-1.amazonaws.com'
// });

// //
// // Device is an instance returned by mqtt.Client(), see mqtt.js for full
// // documentation.
// //
// device.on('connect', function() {
//     console.log('connect');
//     device.subscribe('controller/FeniexF1/MsgBox/185680b6df37');
//     // device.subscribe('controller/FeniexF1/MsgBox/' + controllerAddress + '');
//     device.publish('controller/FeniexF1/MsgBox/185680b6df37', JSON.stringify({ test_data: 3}));
// });

// device.on('message', function(topic, payload) {
//     console.log('message', topic, payload.toString());
// });