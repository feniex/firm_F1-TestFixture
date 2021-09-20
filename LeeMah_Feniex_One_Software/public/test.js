const electron = require('electron');
const { app, ipcMain, BrowserWindow, ipcRenderer } = electron;
const path = require('path');
const url = require('url');
var fs = require('fs');
const SerialPort = require("serialport");
const Readline = SerialPort.parsers.Readline;
var serial_port = new SerialPort("/dev/ttyUSB0", { baudRate: 230400, autoOpen: false });
const parser = new Readline({ delimiter: Buffer.from([13, 10]), encoding: 'hex' });
serial_port.pipe(parser);
var Desktop_serial_port = new SerialPort("/dev/ttyUSB1", { baudRate: 115200, autoOpen: false });
var buf1;
var oldtempBuffer;
var fileName = './homeScreen.json';
var file = require(fileName);
var DevMode = true;

var configFile = DevMode ? require('./../extraResources/posts.json') : require('./../../extraResources/posts.json');

const isDev = require("electron-is-dev");

//var timeOutCommunicationTimer = setInterval(reconnectPSOCDevice, 10000);
//var timeOutCommunicationTimer2 = setInterval(reconnectDesktopDevice, 10000);

serial_port.open(function (err) {
  if (err) {
    //timeOutCommunicationTimer = setInterval(reconnectPSOCDevice, 5000);
    return console.log('Error opening controller port: ', err.message)
  }
  else {
    console.log("Successfully connected controller")
    //clearInterval(timeOutCommunicationTimer);
  }
})
Desktop_serial_port.open(function (err) {
  if (err) {
    //timeOutCommunicationTimer2 = setInterval(reconnectDesktopDevice, 5000);
    return console.log('Error opening Desktop port: ', err.message)
  }
  else {
    console.log("Successfully connected Desktop")
    //clearInterval(timeOutCommunicationTimer2);
  }
})

//checking connection with controller
//SerialPort.list(function (err, ports) {
 // ports.forEach(function (port) {
 //   console.log('port comName: ' + port.comName);
 //   console.log('port pnpID: ' + port.pnpId);
 //   console.log('port manufacturer: ' + port.manufacturer);
 //   if (port.manufacturer === "Cypress Semiconductor") {
 //     mainWindow.webContents.send('unmounted', 'alive');
 //   }
 // });
//});

let mainWindow;

function createWindow() {
  // Create the browser window.
  mainWindow = new BrowserWindow({
    width: 318,
    height: 240,
    frame: false,
    resizable: false,
    x: 0,
    y: 0,
    disableAutoHideCursor: true,
    show: false,
    transparent: false,
    webPreferences: {
      nodeIntegration: true
    }
  });


  // Use dot-notation to access nested properties
  //store.set('foo.bar', true); 
  //console.log(store.get('foo'));
  //=> {bar: true}

  //store.delete('unicorn');
  //console.log(store.get('unicorn'));
  //=> undefined
//console.log(configFile);


  mainWindow.once('ready-to-show', () => {
    mainWindow.show()
  })

  mainWindow.webContents.on('did-finish-load', () => {
    mainWindow.webContents.send('loadApp', configFile);
    mainWindow.webContents.setZoomFactor(1)
    mainWindow.webContents.setVisualZoomLevelLimits(1, 1)
    mainWindow.webContents.setLayoutZoomLevelLimits(0, 0)
    var state = file.carBtns;
    mainWindow.webContents.send('Screen', state);
  })


  // and load the index.html of the app.
  var startUrl;
  if (DevMode) {
    startUrl = (isDev ? 'http://localhost:3000' : `file://${path.join(__dirname, '../build/index.html')}`);
    mainWindow.webContents.openDevTools({ mode: "detach" });
  } else {
    startUrl = (`file://${path.join(__dirname, '../build/index.html')}`);
    //mainWindow.webContents.openDevTools({ mode: "detach" });
  }

  mainWindow.loadURL(startUrl);
  
  // Emitted when the window is closed.
  mainWindow.on('closed', function () {
    mainWindow = null
  })
}

app.disableHardwareAcceleration();

app.on('ready', createWindow);

// Quit when all windows are closed.
app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') {
    app.quit()
  }
});

app.on('activate', function () {
  if (mainWindow === null) {
    createWindow()
  }
});

app.on('ready', () => {
  
  // mainWindow.webContents.on('did-finish-load', () => {
  //   var child_process = require('child_process');
  //   var activePorts = child_process.execSync('nmcli -t -f NAME connection show --active').toString();
  //   mainWindow.webContents.send('wifi-connection', activePorts);
  //   //checking connection with controller
  //   SerialPort.list(function(err, ports) {
  //     ports.forEach(function(port) {
  //       console.log('port comName: ' + port.comName);
  //       if(port.manufacturer === "Cypress Semiconductor"){
  //         mainWindow.webContents.send('unmounted', 'alive');
  //       }
  //     });
  //   });
  // })
})

//switches states when clicked on a different tab
ipcMain.on('switch_tabs', (event, arg) => {
  mainWindow.webContents.send('tab-event2', arg);
})

ipcMain.on('manualSlideSwitch', (event, arg) => {
  if (arg === 7) {
    console.log('slideswitch is off');
  } else if (arg === 5) {
    console.log('slideswitch is MODE1');
  } else if (arg === 6) {
    console.log('slideswitch is MODE2');
  } else if (arg === 3) {
    console.log('slideswitch is MODE3');
  }
})

//send to firmware to turn on
ipcMain.on('packet-sending', (event, led16r, led16g, led16b, led15r, led15g, led15b, led14r, led14g, led14b, led13r, led13g, led13b, led12r,
  led12g, led12b, led11r, led11g, led11b, led10r, led10g, led10b, led9r, led9g, led9b, led8r, led8g, led8b, led7r, led7g, led7b, led6r, led6g, led6b,
  led5r, led5g, led5b, led4r, led4g, led4b, led3r, led3g, led3b, led2r, led2g, led2b, led1r, led1g, led1b, beep, lb1, lb2, lb3, sk1, sk2, dd,
  outputs1, outputs2, outputs3, outputs4, outputs5, screenBrightness) => {


  //fill in other outputs
  outputs5 += 63;
  var beep1 = 0;
  var beep2 = 0;
  beep = 'no';

  //press button - send beep
  if (beep === 'yes') {
    beep1 = 3;
    beep2 = 232;

    var checksum = led16r ^ led16g ^ led16b ^ led15r ^ led15g ^ led15b ^ led14r ^ led14g ^ led14b ^ led13r ^ led13g ^ led13b ^ led12r ^
      led12g ^ led12b ^ led11r ^ led11g ^ led11b ^ led10r ^ led10g ^ led10b ^ led9r ^ led9g ^ led9b ^ led8r ^ led8g ^ led8b ^ led7r ^ led7g ^
      led7b ^ led6r ^ led6g ^ led6b ^ led5r ^ led5g ^ led5b ^ led4r ^ led4g ^ led4b ^ led3r ^ led3g ^ led3b ^ led2r ^ led2g ^ led2b ^ led1r ^
      led1g ^ led1b ^ beep1 ^ beep2 ^ screenBrightness ^ 126 ^ 51 ^ lb1 ^ lb2 ^ lb3 ^ 13 ^ 10 ^ 126 ^ 83 ^ sk1 ^ sk2 ^ dd ^ 13 ^ 10 ^ 126 ^ 80 ^
      outputs1 ^ outputs2 ^ outputs3 ^ outputs4 ^ outputs5 ^ 0 ^ 13 ^ 10;

    serial_port.write(Buffer.from([126, 73, led16r, led16g, led16b, led15r, led15g, led15b, led14r, led14g, led14b, led13r, led13g, led13b, led12r,
      led12g, led12b, led11r, led11g, led11b, led10r, led10g, led10b, led9r, led9g, led9b, led8r, led8g, led8b, led7r, led7g, led7b, led6r, led6g, led6b,
      led5r, led5g, led5b, led4r, led4g, led4b, led3r, led3g, led3b, led2r, led2g, led2b, led1r, led1g, led1b, beep1, beep2, screenBrightness,
      126, 51, lb1, lb2, lb3, 13, 10, 126, 83, sk1, sk2, dd, 13, 10, 126, 80, outputs1, outputs2, outputs3, outputs4, outputs5, 0, 13, 10,
      checksum, 13, 10]));

    Desktop_serial_port.write(Buffer.from([126, 73, led16r, led16g, led16b, led15r, led15g, led15b, led14r, led14g, led14b, led13r, led13g, led13b, led12r,
      led12g, led12b, led11r, led11g, led11b, led10r, led10g, led10b, led9r, led9g, led9b, led8r, led8g, led8b, led7r, led7g, led7b, led6r, led6g, led6b,
      led5r, led5g, led5b, led4r, led4g, led4b, led3r, led3g, led3b, led2r, led2g, led2b, led1r, led1g, led1b, beep1, beep2, screenBrightness,
      126, 51, lb1, lb2, lb3, 13, 10, 126, 83, sk1, sk2, dd, 13, 10, 126, 80, outputs1, outputs2, outputs3, outputs4, outputs5, 0, 13, 10,
      checksum, 13, 10]));
  }
  //no press - no beep
  else {
    var checksum1 = led16r ^ led16g ^ led16b ^ led15r ^ led15g ^ led15b ^ led14r ^ led14g ^ led14b ^ led13r ^ led13g ^ led13b ^ led12r ^
      led12g ^ led12b ^ led11r ^ led11g ^ led11b ^ led10r ^ led10g ^ led10b ^ led9r ^ led9g ^ led9b ^ led8r ^ led8g ^ led8b ^ led7r ^ led7g ^
      led7b ^ led6r ^ led6g ^ led6b ^ led5r ^ led5g ^ led5b ^ led4r ^ led4g ^ led4b ^ led3r ^ led3g ^ led3b ^ led2r ^ led2g ^ led2b ^ led1r ^
      led1g ^ led1b ^ beep1 ^ beep2 ^ screenBrightness ^ 126 ^ 51 ^ lb1 ^ lb2 ^ lb3 ^ 13 ^ 10 ^ 126 ^ 83 ^ sk1 ^ sk2 ^ dd ^ 13 ^ 10 ^ 126 ^
      80 ^ outputs1 ^ outputs2 ^ outputs3 ^ outputs4 ^ outputs5 ^ 0 ^ 13 ^ 10;

    serial_port.write(Buffer.from([126, 73, led16r, led16g, led16b, led15r, led15g, led15b, led14r, led14g, led14b, led13r, led13g, led13b, led12r,
      led12g, led12b, led11r, led11g, led11b, led10r, led10g, led10b, led9r, led9g, led9b, led8r, led8g, led8b, led7r, led7g, led7b, led6r, led6g, led6b,
      led5r, led5g, led5b, led4r, led4g, led4b, led3r, led3g, led3b, led2r, led2g, led2b, led1r, led1g, led1b, beep1, beep2, screenBrightness,
      126, 51, lb1, lb2, lb3, 13, 10, 126, 83, sk1, sk2, dd, 13, 10, 126, 80, outputs1, outputs2, outputs3, outputs4, outputs5, 0, 13, 10,
      checksum1, 13, 10]));

    Desktop_serial_port.write(Buffer.from([126, 73, led16r, led16g, led16b, led15r, led15g, led15b, led14r, led14g, led14b, led13r, led13g, led13b, led12r,
      led12g, led12b, led11r, led11g, led11b, led10r, led10g, led10b, led9r, led9g, led9b, led8r, led8g, led8b, led7r, led7g, led7b, led6r, led6g, led6b,
      led5r, led5g, led5b, led4r, led4g, led4b, led3r, led3g, led3b, led2r, led2g, led2b, led1r, led1g, led1b, beep1, beep2, screenBrightness,
      126, 51, lb1, lb2, lb3, 13, 10, 126, 83, sk1, sk2, dd, 13, 10, 126, 80, outputs1, outputs2, outputs3, outputs4, outputs5, 0, 13, 10,
      checksum1, 13, 10]));
  }
})

ipcMain.on('unmount', (event, data) => {
  //console.log(data)
  //Desktop_serial_port.write(Buffer.from([126, 77, 1, data, 13, 10]));
})

///////////////////Send and Receive From PSOC///////////////////
parser.on('data', function (data) {
  var tempBuffer = Buffer.from(data, 'hex');
  //console.log(tempBuffer)
  var recivingNewPacket = new Uint8Array(1);
  recivingNewPacket[0] = parseInt(tempBuffer[1], 10);

  //console.log(recivingNewPacket[0])

  if (recivingNewPacket[0] === 71) {
    //console.log(tempBuffer)
    mainWindow.webContents.send('GPS-serialData', tempBuffer);
  }

  if (recivingNewPacket[0] === 68) {
    //console.log(tempBuffer)
    mainWindow.webContents.send('realy-serialData', tempBuffer);

    var recivingChecksum1 = new Uint8Array(1);
    var index12 = new Uint8Array(1);
    var index13 = new Uint8Array(1);
    var index14 = new Uint8Array(1);
    var index15 = new Uint8Array(1);
    var index16 = new Uint8Array(1);
    var index17 = new Uint8Array(1);
    var index18 = new Uint8Array(1);
    var index19 = new Uint8Array(1);
    var index110 = new Uint8Array(1);
    var index111 = new Uint8Array(1);
    var index112 = new Uint8Array(1);
    var index113 = new Uint8Array(1);
    var index114 = new Uint8Array(1);
    var index115 = new Uint8Array(1);
    var index116 = new Uint8Array(1);
    var index117 = new Uint8Array(1);
    var index118 = new Uint8Array(1);
    var index119 = new Uint8Array(1);
    var index120 = new Uint8Array(1);
    var index121 = new Uint8Array(1);
    var index122 = new Uint8Array(1);
    var index123 = new Uint8Array(1);
    var index124 = new Uint8Array(1);
    var index125 = new Uint8Array(1);
    var index126 = new Uint8Array(1);
    var index127 = new Uint8Array(1);
    var index128 = new Uint8Array(1);
    var index129 = new Uint8Array(1);
    var index130 = new Uint8Array(1);
    var index131 = new Uint8Array(1);
    var index132 = new Uint8Array(1);
    var index133 = new Uint8Array(1);
    var index134 = new Uint8Array(1);
    var index135 = new Uint8Array(1);
    var index136 = new Uint8Array(1);
    var index137 = new Uint8Array(1);
    var index138 = new Uint8Array(1);
    var index139 = new Uint8Array(1);
    var index140 = new Uint8Array(1);
    var index141 = new Uint8Array(1);
    var index142 = new Uint8Array(1);
    var index143 = new Uint8Array(1);
    var index144 = new Uint8Array(1);
    var index145 = new Uint8Array(1);
    var index146 = new Uint8Array(1);
    var index147 = new Uint8Array(1);
    var index148 = new Uint8Array(1);
    var index149 = new Uint8Array(1);
    var index150 = new Uint8Array(1);
    var index151 = new Uint8Array(1);
    var index152 = new Uint8Array(1);
    var index153 = new Uint8Array(1);
    var index154 = new Uint8Array(1);
    var index155 = new Uint8Array(1);
    var index156 = new Uint8Array(1);
    var index157 = new Uint8Array(1);
    var index158 = new Uint8Array(1);
    var index159 = new Uint8Array(1);
    var index160 = new Uint8Array(1);
    var index161 = new Uint8Array(1);
    var index162 = new Uint8Array(1);
    var index163 = new Uint8Array(1);
    var index164 = new Uint8Array(1);
    var index165 = new Uint8Array(1);
    var index166 = new Uint8Array(1);
    var index167 = new Uint8Array(1);
    var index168 = new Uint8Array(1);
    var index169 = new Uint8Array(1);
    var index170 = new Uint8Array(1);
    var index171 = new Uint8Array(1);
    var index172 = new Uint8Array(1);
    var index173 = new Uint8Array(1);
    var index174 = new Uint8Array(1);
    var index175 = new Uint8Array(1);
    var index176 = new Uint8Array(1);
    var index177 = new Uint8Array(1);
    var index178 = new Uint8Array(1);
    var index179 = new Uint8Array(1);
    var index180 = new Uint8Array(1);
    var index181 = new Uint8Array(1);
    var index182 = new Uint8Array(1);
    var index183 = new Uint8Array(1);
    var index184 = new Uint8Array(1);

    index12[0] = parseInt(tempBuffer[2], 10);
    index13[0] = parseInt(tempBuffer[3], 10);
    index14[0] = parseInt(tempBuffer[4], 10);
    index15[0] = parseInt(tempBuffer[5], 10);
    index16[0] = parseInt(tempBuffer[6], 10);
    index17[0] = parseInt(tempBuffer[7], 10);
    index18[0] = parseInt(tempBuffer[8], 10);
    index19[0] = parseInt(tempBuffer[9], 10);
    index110[0] = parseInt(tempBuffer[10], 10);
    index111[0] = parseInt(tempBuffer[11], 10);
    index112[0] = parseInt(tempBuffer[12], 10);
    index113[0] = parseInt(tempBuffer[13], 10);
    index114[0] = parseInt(tempBuffer[14], 10);
    index115[0] = parseInt(tempBuffer[15], 10);
    index116[0] = parseInt(tempBuffer[16], 10);
    index117[0] = parseInt(tempBuffer[17], 10);
    index118[0] = parseInt(tempBuffer[18], 10);
    index119[0] = parseInt(tempBuffer[19], 10);
    index120[0] = parseInt(tempBuffer[20], 10);
    index121[0] = parseInt(tempBuffer[21], 10);
    index122[0] = parseInt(tempBuffer[22], 10);
    index123[0] = parseInt(tempBuffer[23], 10);
    index124[0] = parseInt(tempBuffer[24], 10);
    index125[0] = parseInt(tempBuffer[25], 10);
    index126[0] = parseInt(tempBuffer[26], 10);
    index127[0] = parseInt(tempBuffer[27], 10);
    index128[0] = parseInt(tempBuffer[28], 10);
    index129[0] = parseInt(tempBuffer[29], 10);
    index130[0] = parseInt(tempBuffer[30], 10);
    index131[0] = parseInt(tempBuffer[31], 10);
    index132[0] = parseInt(tempBuffer[32], 10);
    index133[0] = parseInt(tempBuffer[33], 10);
    index134[0] = parseInt(tempBuffer[34], 10);
    index135[0] = parseInt(tempBuffer[35], 10);
    index136[0] = parseInt(tempBuffer[36], 10);
    index137[0] = parseInt(tempBuffer[37], 10);
    index138[0] = parseInt(tempBuffer[38], 10);
    index139[0] = parseInt(tempBuffer[39], 10);
    index140[0] = parseInt(tempBuffer[40], 10);
    index141[0] = parseInt(tempBuffer[41], 10);
    index142[0] = parseInt(tempBuffer[42], 10);
    index143[0] = parseInt(tempBuffer[43], 10);
    index144[0] = parseInt(tempBuffer[44], 10);
    index145[0] = parseInt(tempBuffer[45], 10);
    index146[0] = parseInt(tempBuffer[46], 10);
    index147[0] = parseInt(tempBuffer[47], 10);
    index148[0] = parseInt(tempBuffer[48], 10);
    index149[0] = parseInt(tempBuffer[49], 10);
    index150[0] = parseInt(tempBuffer[50], 10);
    index151[0] = parseInt(tempBuffer[51], 10);
    index152[0] = parseInt(tempBuffer[52], 10);
    index153[0] = parseInt(tempBuffer[53], 10);
    index154[0] = parseInt(tempBuffer[54], 10);
    index155[0] = parseInt(tempBuffer[55], 10);
    index156[0] = parseInt(tempBuffer[56], 10);
    index157[0] = parseInt(tempBuffer[57], 10);
    index158[0] = parseInt(tempBuffer[58], 10);
    index159[0] = parseInt(tempBuffer[59], 10);
    index160[0] = parseInt(tempBuffer[60], 10);
    index161[0] = parseInt(tempBuffer[61], 10);
    index162[0] = parseInt(tempBuffer[62], 10);
    index163[0] = parseInt(tempBuffer[63], 10);
    index164[0] = parseInt(tempBuffer[64], 10);
    index165[0] = parseInt(tempBuffer[65], 10);
    index166[0] = parseInt(tempBuffer[66], 10);
    index167[0] = parseInt(tempBuffer[67], 10);
    index168[0] = parseInt(tempBuffer[68], 10);
    index169[0] = parseInt(tempBuffer[69], 10);
    index170[0] = parseInt(tempBuffer[70], 10);
    index171[0] = parseInt(tempBuffer[71], 10);
    index172[0] = parseInt(tempBuffer[72], 10);
    index173[0] = parseInt(tempBuffer[73], 10);
    index174[0] = parseInt(tempBuffer[74], 10);
    index175[0] = parseInt(tempBuffer[75], 10);
    index176[0] = parseInt(tempBuffer[76], 10);
    index177[0] = parseInt(tempBuffer[77], 10);
    index178[0] = parseInt(tempBuffer[78], 10);
    index179[0] = parseInt(tempBuffer[79], 10);
    index180[0] = parseInt(tempBuffer[80], 10);
    index181[0] = parseInt(tempBuffer[81], 10);
    index182[0] = parseInt(tempBuffer[82], 10);
    index183[0] = parseInt(tempBuffer[83], 10);
    index184[0] = parseInt(tempBuffer[84], 10);
    recivingChecksum1[0] = parseInt(tempBuffer[85], 10);

    var comapreChecksum1 = index12[0] ^ index13[0] ^ index14[0] ^ index15[0] ^ index16[0] ^ index17[0] ^ index18[0] ^ index19[0] ^ index110[0] ^
      index111[0] ^ index112[0] ^ index113[0] ^ index114[0] ^ index115[0] ^ index116[0] ^ index117[0] ^ index118[0] ^ index119[0] ^ index120[0] ^
      index121[0] ^ index122[0] ^ index123[0] ^ index124[0] ^ index125[0] ^ index126[0] ^ index127[0] ^ index128[0] ^ index129[0] ^ index130[0] ^
      index131[0] ^ index132[0] ^ index133[0] ^ index134[0] ^ index135[0] ^ index136[0] ^ index137[0] ^ index138[0] ^ index139[0] ^ index140[0] ^
      index141[0] ^ index142[0] ^ index143[0] ^ index144[0] ^ index145[0] ^ index146[0] ^ index147[0] ^ index148[0] ^ index149[0] ^ index150[0] ^
      index151[0] ^ index152[0] ^ index153[0] ^ index154[0] ^ index155[0] ^ index156[0] ^ index157[0] ^ index158[0] ^ index159[0] ^ index160[0] ^
      index161[0] ^ index162[0] ^ index163[0] ^ index164[0] ^ index165[0] ^ index166[0] ^ index167[0] ^ index168[0] ^ index169[0] ^ index170[0] ^
      index171[0] ^ index172[0] ^ index173[0] ^ index174[0] ^ index175[0] ^ index176[0] ^ index177[0] ^ index178[0] ^ index179[0] ^ index180[0] ^
      index181[0] ^ index182[0] ^ index183[0] ^ index184[0];

    if (comapreChecksum1 === recivingChecksum1[0]) {
      //console.log(tempBuffer)
      mainWindow.webContents.send('realy-serialData', tempBuffer);
    }
    else {
      //mainWindow.webContents.send('detatchTest', tempBuffer);
      console.log('Relay Packet Dropped')
      console.log(tempBuffer)
      console.log(comapreChecksum1)
      console.log(recivingChecksum1[0])
    }
  }
  if (recivingNewPacket[0] === 73) {
    //mainWindow.webContents.send('detatchTest', tempBuffer);
    var recivingChecksum = new Uint8Array(1);
    var index2 = new Uint8Array(1);
    var index3 = new Uint8Array(1);
    var index4 = new Uint8Array(1);
    var index5 = new Uint8Array(1);
    var index6 = new Uint8Array(1);
    var index7 = new Uint8Array(1);
    var index8 = new Uint8Array(1);
    var index9 = new Uint8Array(1);
    var index10 = new Uint8Array(1);
    var index11 = new Uint8Array(1);
    var index12 = new Uint8Array(1);
    var index13 = new Uint8Array(1);
    var index14 = new Uint8Array(1);
    var index15 = new Uint8Array(1);
    var index16 = new Uint8Array(1);
    var index17 = new Uint8Array(1);
    var index18 = new Uint8Array(1);
    var index19 = new Uint8Array(1);
    var index20 = new Uint8Array(1);
    var index21 = new Uint8Array(1);
    var index22 = new Uint8Array(1);

    recivingChecksum[0] = parseInt(tempBuffer[23], 10);
    index2[0] = parseInt(tempBuffer[2], 10);
    index3[0] = parseInt(tempBuffer[3], 10);
    index4[0] = parseInt(tempBuffer[4], 10);
    index5[0] = parseInt(tempBuffer[5], 10);
    index6[0] = parseInt(tempBuffer[6], 10);
    index7[0] = parseInt(tempBuffer[7], 10);
    index8[0] = parseInt(tempBuffer[8], 10);
    index9[0] = parseInt(tempBuffer[9], 10);
    index10[0] = parseInt(tempBuffer[10], 10);
    index11[0] = parseInt(tempBuffer[11], 10);
    index12[0] = parseInt(tempBuffer[12], 10);
    index13[0] = parseInt(tempBuffer[13], 10);
    index14[0] = parseInt(tempBuffer[14], 10);
    index15[0] = parseInt(tempBuffer[15], 10);
    index16[0] = parseInt(tempBuffer[16], 10);
    index17[0] = parseInt(tempBuffer[17], 10);
    index18[0] = parseInt(tempBuffer[18], 10);
    index19[0] = parseInt(tempBuffer[19], 10);
    index20[0] = parseInt(tempBuffer[20], 10);
    index21[0] = parseInt(tempBuffer[21], 10);
    index22[0] = parseInt(tempBuffer[22], 10);

    var comapreChecksum = index2[0] ^ index3[0] ^ index4[0] ^ index5[0] ^ index6[0] ^ index7[0] ^ index8[0] ^ index9[0] ^ index10[0] ^
      index11[0] ^ index12[0] ^ index13[0] ^ index14[0] ^ index15[0] ^ index16[0] ^ index17[0] ^ index18[0] ^ index19[0] ^ index20[0] ^ index21[0] ^
      index22[0];

    if (buf1 !== recivingChecksum[0]) {
      if (comapreChecksum === recivingChecksum[0]) {
        //console.log(tempBuffer)
        //mainWindow.webContents.send('detatchTest', tempBuffer);
        mainWindow.webContents.send('asynchronous-serialData', tempBuffer);
      }
      else {
        //mainWindow.webContents.send('detatchTest', tempBuffer);
        console.log('Controller Packet Dropped')
        console.log(tempBuffer)
        console.log(comapreChecksum)
        console.log(recivingChecksum[0])
      }
      buf1 = recivingChecksum[0];
      oldtempBuffer = tempBuffer;
    }
  }
});

//reciving JSON file
Desktop_serial_port.on('data', function (data) {
  console.log(`Received ${data.length} bytes of data.`);
  console.log(data.toString());
  var BufferData = data.toString();
  movedata(BufferData);
});

//receving data in chuncks
//so appending all data to a file
var str = '';
function movedata(textFile) {
  str = str + textFile;
  //once file gets to the end, save
  //clear variable for the next file to be sent in and rewrite old states
  if (str.includes('}]}"end"')) {

    var str1 = JSON.stringify(str)
    var newData = str1.slice(0, - 8);
    newData = newData + '"';
    mainWindow.webContents.send('buttonstate', newData);
    var currentPath = 0;

    if (DevMode) {
    currentPath = path.join(app.getAppPath(), '/extraResources/posts.json');
    }
    else
    {
      currentPath = path.join(app.getAppPath(), '/../extraResources/posts.json');
    }

    mainWindow.webContents.send('consoleLogPath', currentPath);
    //console.log("Poooooooooooooooooooooooooooooooooooooooooooooooooooooooop" + currentPath);

    fs.writeFile(currentPath, newData, (err) => {
      if (err) throw err;
      console.log('The file has been saved!');
    });

    str = '';
    newData = '';
    console.log("the string is now empty: " + str + newData + " <--")
    mainWindow.webContents.send('asynchronous-serialData', oldtempBuffer);
  }
}

//write GPS to file
ipcMain.on('gps', (event, arg) => {
  //console.log(arg)
  //fs.appendFile(__dirname + '/../app/build/runGPS1.txt', arg, function (err) {
  //  if (err) return console.log(err);
    //console.log('The Location has been saved!');
  //});
})


ipcMain.on('updateJson', (event, arg) => {
  file.carBtns = arg;
  fs.writeFile(__dirname + '/homeScreen.json', JSON.stringify(file), function (err) {
    if (err) return console.log(err);
    console.log('writing');
  });
})


function reconnectPSOCDevice() {
  setTimeout(function () {
    if (serial_port.isOpen === false) {
      serial_port.open(
        function (err) {
          if (err) {
            return console.log('Error opening port: ', err.message)
          }
        })
    }
  }, 2000)
}

function reconnectDesktopDevice() {
  setTimeout(function () {
    if (Desktop_serial_port.isOpen === false) {
      Desktop_serial_port.open(function (err) {
        if (err) {
          return console.log('Error opening port: ', err.message)
        }
      })
    }
  }, 2000)
}