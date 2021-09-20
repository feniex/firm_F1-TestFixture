const electron = require('electron');
const { app, BrowserWindow } = electron;
const SerialPort = require("serialport");
const { ipcMain } = electron;
const url = require("url");
const path = require("path");
//const serial_port = new SerialPort("/dev/ttyUSB0", { baudRate: 230400, autoOpen: false });
var desktop_serial_port; //= new SerialPort("COM10", { baudRate: 115200, autoOpen: false });

const DesktopReadline = SerialPort.parsers.Readline;
const desktopParser = new DesktopReadline({ delimiter: Buffer.from([13, 10]), encoding: 'hex' });
let mainWindow;

var DevMode = false;

var portInterval;
var pollRate = 800;

var serialPortFound = false;
//var broadcastCount = 0;
//var checkBroadcast = 0;
var comName = '';
var comNameSplit = '';
var portConnected = false;

function createWindow() {
  // Create the browser window.ControllerSoftware
    mainWindow = new BrowserWindow({
      width: 225,
      height: 900,
      frame: true,
      resizable: true,
      x: 0,
      y: 0,
      disableAutoHideCursor: false,
      show: false,
      transparent: false,
      webPreferences: {
          nodeIntegration: true
      }
    });
}

var startUrl;

app.on('ready', function() {

  //try {
    createWindow();

    if (DevMode) {
      startUrl = 'http://localhost:3000';
      mainWindow.webContents.openDevTools({ mode: "detach" });
    } else {
      startUrl =
      process.env.ELECTRON_START_URL ||
      url.format({
        pathname: path.join(__dirname, "/../build/index.html"),
        protocol: "file:",
        slashes: true
      });
    }
    mainWindow.loadURL(startUrl);

    mainWindow.once('ready-to-show', () => {
      if(mainWindow!==null)
      {
        mainWindow.show();
      }  
    });

    mainWindow.on('closed', function () {
      mainWindow = null;
    });
 // }
  //catch(e) {
  //  console.log("Caught error reading outer.json using feniexGuest");
  //}
});

app.on('activate', function () {
  if (mainWindow === null) {
    
    createWindow();
  }
});

function openSerialPort() {
  desktop_serial_port.open(function (err) {
    if (err) {
       console.log("Open error: " + err.message);
      if (err.message === 'Port is opening') {
        ;
      }
      else if (err.message === 'Port is already open') {
        ;
         console.log("Port is already open");
      }
      else {
        serialPortFound = false;
      }
    }
    else {
      ;
       //console.log('Port Open');
    }
  });
}

function pollPort() 
{
  var manKey = '';
  try 
  {
    SerialPort.list((err, ports) => 
    {
      if (err) 
      {
        console.log("Error: " + err.message);
        return
      }
      else 
      {
        serialPortFound = false;
        portConnected = false;

        for (var p = 0; p < ports.length; p++) 
        {
          comName = ports[p].comName;

          if (process.platform === "darwin") 
          {
            comNameSplit = comName.split('-')[0];
            if (comNameSplit === '/dev/tty.usbserial') 
            {
              portConnected = true;
            }
          }
          else if (process.platform === "win32") 
          {
            comNameSplit = comName.substring(0, 3);
            if (comNameSplit === 'COM') 
            {
              portConnected = true;
            }
          }
          else if (process.platform === 'linux') 
          {
            comNameSplit = comName.split('B')[0];
            if (comNameSplit === 'ttyUS') 
            {
              portConnected = true;
            }
          }
          manKey = ports[p].manufacturer;
        }
          
          if (portConnected && manKey === 'FTDI') 
          {
             desktop_serial_port = new SerialPort(comName, { baudRate: 115200, autoOpen: false });
             desktop_serial_port.pipe(desktopParser);
              //console.log(comName);
              openSerialPort();
              clearInterval(portInterval);
              //setSerial = comName;
          }
      }
    })
  }
  catch (error) {
    console.error(error);
  }
}

ipcMain.on('check-usb', () => {

  clearInterval(portInterval);
  portInterval = setInterval(function () {
    pollPort();
  }, pollRate);
});

desktopParser.on('data', function (data) {
  var BufferData = data.toString();
  //console.log('Buffer data: ', BufferData);

  BufferData = Buffer.from(data, 'hex')
  //if(previousBufferData !== BufferData)
  //{
    mainWindow.webContents.send('send-F1-diagnostics', BufferData);
  //}

  //previousBufferData = BufferData;

       //desktop_serial_port.write(Buffer.from(sendloadData), function(err) {
        //mainWindow.webContents.send('showProgressBar', 'Programming');
});

