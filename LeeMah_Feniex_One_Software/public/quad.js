var lightbar = require("./QuadProducts/lightbar.js");
var NanoTimer = require('nanotimer');
var fs = require('fs');

var deBug = false;
var constant = require("./QuadProducts/CommonQuadResources.js");

var lightBarBuffer = new lightbar(0,0);

var previousConfigs = [];
var previousSurfaceZone;
var quadBrightness = [];
var updatedFrameBuffer = [];
var updatedFrameBrightness = [];
var quadPatterns = [];
var quadMods = [];

var OFF = constant.OFF;
// var start;

var timerId;
var masterCounter = 0;
var runCount = 0;
var timerObject  = new NanoTimer();
var SMtimerObject  = new NanoTimer();
var SMZonetimerObject = new NanoTimer();

var onPower = true;
// var end9 = 0;

var surfaceZone;
var SMActive;
var QuadActive = true;

var SMZoneFrameBuffer = [
  0x7E, 0x59,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,
  0x0D,0x0A
];

var SMZoneNumFrameBuffer = [
  0x7E, 0x4F,
  22,
  0x0D,0x0A
];

var frameBuffer = [
    0x7E,0x4C,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,
    0x0D,0x0A, 0x7E, 0x59,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,OFF,OFF,
    0x0D,0x0A
];

var frameBrightness = [
  0x7E,0x4C,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,
  0x0D,0x0A, 0x7E, 0x59,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,
  0x0D,0x0A
];

var frameSelect = [
  0x7E,0x4C,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,
  0x0D,0x0A, 0x7E, 0x59,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
  OFF,OFF,OFF,
  0x0D,0x0A
];

var flbSet = false;
var tenXSet = false;
var firstTwo = true;

var sendZonePacket = false;
var clearPatternsOnStartup = true;

const SerialPort = require("serialport");
const { Console } = require("console");
const obd_serial_port = new SerialPort("/dev/ttymxc2", { baudRate: 460800, autoOpen: false });
// const obd_serial_port = new SerialPort("/dev/ttyUSB2", { baudRate: 115200, autoOpen: false });

const OBDReadline = SerialPort.parsers.Readline;
const obd_parser = new OBDReadline({ delimiter: Buffer.from([13, 10]), encoding: 'hex' });

setTimeout(function() {
  // OBD/QUAD SERIAL PORT CONNECT WAIT FOR APP TO LANCH FIRST
  obd_serial_port.open(function (err) {
    if (err) {
        return consoleLogger("Error opening obd port: ", err.message);
    }
    else {
      consoleLogger("Successfully connected obd", '');
    }
  });

  obd_serial_port.pipe(obd_parser);

  obd_parser.on('data', function (data) {
    // console.log("OBD Data send: ", JSON.stringify(obdTempBuffer[1]));
    process.send(data);
  });
}, 3000);

function readyQuantumPacket() {
  
  if (onPower) {

    if(masterCounter % 2 === 0) {  //Send Serial Packet Every 20 Milliseconds
    
      let readyFrameBuffer = [];

      // let start1 = new Date().getTime();
      // let start4 = new Date().getTime();

      lightBarBuffer.addSSFrameBuffer(updatedFrameBuffer, updatedFrameBrightness, quadPatterns, quadMods);

      readyFrameBuffer = lightBarBuffer.startPatterns();

      // {
      // console.log("This is the ready frame buffer packet:", JSON.stringify(readyFrameBuffer));
      //   let start5 = new Date().getTime();
      //   let returnTime = start5 - start4;
      //   let timeToIssue = new Date().getTime();

      //   let end1 = new Date().getTime();
      //   let timeToIssue1 = end1 - start;

      //   if (returnTime > 1) {
      //     console.log('Ready front flash execution time:', returnTime, timeToIssue1);
      //   }
      // });


      process.send(readyFrameBuffer);
      // let start2 = new Date().getTime();

      obd_serial_port.write(Buffer.from(readyFrameBuffer), function(err) {
        if (err) {
          return console.log('Error on readyFrameBuffer write: ', err.message)
        }
      
        // let start3 = new Date().getTime();
        // let writeEecuteTime = start3 - start2;
        
        // if (writeEecuteTime > 1) {
      
        //   let end = new Date().getTime();
        //   let timeToIssue = end - start;
      
        //   console.log('Write buffer execution time:', writeEecuteTime, timeToIssue);
        // }
      });
    }
    lightBarBuffer.updatePatterns();
  
    masterCounter++;
  
    if(masterCounter === 99) {
      masterCounter = 0;
    }
  }
}


function sendSMZPacket() {
  // console.log("This is the surface zone packet: ", JSON.stringify(SMZoneFrameBuffer));
  obd_serial_port.write(Buffer.from(SMZoneFrameBuffer), function(err) {
    if(err) {
      console.log("obd_serial_port SMZoneFrameBuffer error:", err.message);
    }
  });
}

function sendSMZNumPacket() {
  // console.log("This is the surface zone number packet: ", JSON.stringify(SMZoneNumFrameBuffer));
  obd_serial_port.write(Buffer.from(SMZoneNumFrameBuffer), function(err) {
    if(err) {
      console.log("obd_serial_port SMZoneNumFrameBuffer error:", err.message);
    }
  });
}

process.on('message', (barConfigs) => {

  onPower = barConfigs[4];
  // let start3 = new Date().getTime();

  // onPower = true;

  if (onPower) {
    // let previousNotEmpty = configsExist(previousConfigs);
    // let isNotEmpty = configsExist(barConfigs);
    surfaceZone = barConfigs[3][0];
    SMActive = barConfigs[3][1];
    sendZonePacket = barConfigs[3][2];

    // SETS SURFACE ZONE
    // console.log("Surface zone log fun", SMActive, sendZonePacket);

    if (SMActive) {
      if (sendZonePacket) {
        timerObject.clearInterval();
        SMZonetimerObject.clearInterval();
        SMtimerObject.clearInterval();
        SMZonetimerObject.setInterval(sendSMZNumPacket, '', '100m');
  
        setTimeout(function(){
          sendZonePacket = false;
          SMZonetimerObject.clearInterval();
          SMtimerObject.clearInterval();
          SMtimerObject.setInterval(sendSMZPacket, '', '100m');
        }, 2000);
      }

      if (surfaceZone !== previousSurfaceZone) {
        // SMZoneFrameBuffer[10] = surfaceZone;
        // SWITCH TO 22 ZONES
        SMZoneFrameBuffer[24] = surfaceZone;
      }
    }
    else {
      SMtimerObject.clearInterval();
      SMZonetimerObject.clearInterval();
      sendZonePacket = false;
    }

    if (JSON.stringify(previousConfigs) !== JSON.stringify(barConfigs) && previousConfigs.length > 0 && !SMActive) {

      flbSet = false;
      tenXSet = false;
      
      let frameFull = configsExist(barConfigs[0]);

      // CLEAR FRAME BUFFERS
      for (let b = 0; b < frameBuffer.length; b++) {
        updatedFrameBuffer[b] = frameBuffer[b];
      }

      for (let b = 0; b < frameBrightness.length; b++) {
        updatedFrameBrightness[b] = frameBrightness[b];
      }

      for (let b = 0; b < frameSelect.length; b++) {
        quadPatterns[b] = frameSelect[b];
        quadMods[b] = frameSelect[b];
      }

      var quadPattern = barConfigs[0];
      var quadBrightness = barConfigs[1];
      var quadConfigs = barConfigs[2];

      var checkPattern;
      var checkCutOff;
      var patternSubChange;
      var checkSubCutOff;

      if (clearPatternsOnStartup) {
        clearPatternsOnStartup = false;
        lightBarBuffer.clearPattern();
      }

      if (!frameFull) {
        lightBarBuffer.clearPattern();
      }

      timerObject.clearInterval();

      for (let bar = 0; bar < quadConfigs.length; bar++) {

        for (let mode = 0; mode < quadConfigs[bar].length; mode++) {

          if (quadConfigs[bar][mode].length > 0) {

            let pattern = quadPattern[bar][mode];
            let colors = quadConfigs[bar][mode];
            let brightness = quadBrightness[bar][mode];
        
            let barPatternParams = setPattern(pattern, bar);

            setBufferConfigs(bar, colors, barPatternParams, mode, brightness);
          }
        }
      }
      timerObject.setInterval(readyQuantumPacket, '', '10m');

      // COMPARES PATTERN ADDITION FOR ALL BARS TO DETERMINE PATTERN CLEAR
      for(let p = 0; p < barConfigs[2].length; p++) {

        for(let n = 0; n < barConfigs[2][p].length; n++) {
          // console.log("Open up hope for school", barConfigs[2][p][n].length, previousConfigs[2][p][n].length)
          for (let a = 0; a < barConfigs[2][p][n].length; a++) {

            // console.log("THis is the changing pattern", JSON.stringify(barConfigs[2][p][n]), JSON.stringify(previousConfigs[2][p][n]))
            // HANDLES PATTERN ON EVENT
            if (barConfigs[2][p][n][a] !== previousConfigs[2][p][n][a] && (barConfigs[2][p][n][a] !== null && previousConfigs[2][p][n][a] !== null)) {

              if (p === 2 || p === 11) {
                checkPattern = barConfigs[0][p][n][a];
                checkCutOff = barConfigs[2][p][n][a];
                // console.log("Monkey horse qssm", barConfigs[0][p][n][a]);
              }
              else {
                checkPattern = barConfigs[0][p][n];
                checkCutOff = barConfigs[2][p][n][a];
                // console.log("Monkey horse", barConfigs[0][p][n]);
              }
              a = 1000;
              
              if (checkPattern === 'Attack' || checkPattern === 'Cluster' || checkPattern === 'Cluster-Mix' || checkPattern === 'Combo-Single' || checkPattern === 'Combo-Triple'
              || checkPattern === 'Half-Half-Single' || checkPattern === 'Half-Half-Triple' || checkPattern === 'One-One-Single' || checkPattern === 'One-One-Triple' || checkPattern === 'Two-Two-Single'
              || checkPattern === 'Two-Two-Triple' || checkPattern === 'All-On-Single' || checkPattern === 'All-On-Triple' || checkPattern === 'End-Corner' || checkPattern === 'Left-Slow'
              || checkPattern === 'Left-Fast' || checkPattern === 'Left-Combo' || checkPattern === 'Right-Slow' || checkPattern === 'Right-Fast' || checkPattern === 'Right-Combo'
              || checkPattern === 'Center-Out-Slow' || checkPattern === 'Center-Out-Fast' || checkPattern === 'Center-Out-Combo' || checkPattern === 'Left-Fast' || checkPattern === 'All-On-Triple'
              || checkPattern === 'Half-Half-Single' || checkPattern === 'Half-Half-Triple' || checkPattern === 'Vehicle-Park' || checkPattern === 'Brake Pop') {

                lightBarBuffer.clearPattern();
                lightBarBuffer.startQuadPattern(quadPatterns, quadMods, updatedFrameBuffer);
              }
              else if (checkPattern === 'Left Turn' || checkPattern === 'Right Turn' || checkPattern === 'Standard On' || checkPattern === 'Passenger' || checkPattern === 'Driver' || checkPattern === 'flood' || checkCutOff === 'cutOff') {

                lightBarBuffer.clearQssmSteady();
              }
            }
          }
          // HANDLES PATTERN OFF EVENT
          if (previousConfigs[2][p][n].length > barConfigs[2][p][n].length && barConfigs[2][p][n].length === 0) {
            for (let a = 0; a < previousConfigs[2][p][n].length; a++) {

              // console.log("THis is the changing pattern", JSON.stringify(previousConfigs[2][p][n][a]))

              if (previousConfigs[2][p][n][a] !== null) {
                if (p === 2 || p === 11) {

                  patternSubChange = previousConfigs[0][p][n][a];

                  if (previousConfigs[2][p][n][a] === 'cutOff') {
                    checkSubCutOff = previousConfigs[2][p][n][a];
                  }
                  // console.log("Monkey horse qssm 587", patternSubChange);
                  a = 1000;
                }
                else if ( previousConfigs[0][p][n] !== null) {
                  patternSubChange = previousConfigs[0][p][n];

                  if (previousConfigs[2][p][n][a] === 'cutOff') {
                    checkSubCutOff = previousConfigs[2][p][n][a];
                  }
                  // console.log("Monkey horse 587", patternSubChange);
                  a = 1000;
                }
              }
              
              if (patternSubChange === 'Attack' || patternSubChange === 'Cluster' || patternSubChange === 'Cluster-Mix' || patternSubChange === 'Combo-Single' || patternSubChange === 'Combo-Triple'
              || patternSubChange === 'Half-Half-Single' || patternSubChange === 'Half-Half-Triple' || patternSubChange === 'One-One-Single' || patternSubChange === 'One-One-Triple' || patternSubChange === 'Two-Two-Single'
              || patternSubChange === 'Two-Two-Triple' || patternSubChange === 'All-On-Single' || patternSubChange === 'All-On-Triple' || patternSubChange === 'End-Corner' || patternSubChange === 'Left-Slow'
              || patternSubChange === 'Left-Fast' || patternSubChange === 'Left-Combo' || patternSubChange === 'Right-Slow' || patternSubChange === 'Right-Fast' || patternSubChange === 'Right-Combo'
              || patternSubChange === 'Center-Out-Slow' || patternSubChange === 'Center-Out-Fast' || patternSubChange === 'Center-Out-Combo' || patternSubChange === 'Left-Fast' || patternSubChange === 'All-On-Triple'
              || patternSubChange === 'Half-Half-Single' || patternSubChange === 'Half-Half-Triple' || patternSubChange === 'Vehicle-Park' || patternSubChange === 'Brake Pop') {

                lightBarBuffer.clearPattern();
                lightBarBuffer.startQuadPattern(quadPatterns, quadMods, updatedFrameBuffer);
              }
              else if (patternSubChange === 'Left Turn' || patternSubChange === 'Right Turn' || patternSubChange === 'Standard On' || patternSubChange === 'Passenger' || patternSubChange === 'Driver' || patternSubChange === 'flood' || checkSubCutOff === 'cutOff') {

                lightBarBuffer.clearQssmSteady();
                lightBarBuffer.clearPattern();
                lightBarBuffer.startQuadPattern(quadPatterns, quadMods, updatedFrameBuffer);
              }
            }
          }
        }
      }
    }
    previousSurfaceZone = surfaceZone;
    previousConfigs = barConfigs;
  }
});

function setPattern(quadPat, bar) {
  // SET BAR CONFIGS AND PATTERNS
  var patternParams = [];

  // SETS DEFAULT PATTERN FOR NO PATTERNS (I.E CUTOFF)
  if (quadPat.length === 0) {
    if (bar === 2 || bar === 11) {

      patternParams = [[], []];
      
      for (let p = 0; p < 22; p++) {
        patternParams[0][p] = 0;
        patternParams[1][p] = 7;
      }
    }
    else {
      patternParams[0] = 27;
      patternParams[1] = 0;
    }
  }
  else {
    if (quadPat.constructor === Array) {

      patternParams = [[], []];
  
      for (let p = 0; p < quadPat.length; p++) {
        if (quadPat[p] === 'Attack') {
          patternParams[0][p] = 0;
          patternParams[1][p] = 7;
        }
        else if (quadPat[p] === 'Brake Pop') {
          patternParams[0][p] = 28;
          patternParams[1][p] = 0;
        }
        else if (quadPat[p] === 'flood') {
          patternParams[0][p] = 27;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Cluster') {
          patternParams[0][p] = 1;
          patternParams[1][p] = 2;
        }
        else if (quadPat === 'Cluster-Mix') {              
          patternParams[0][p] = 2;
          patternParams[1][p] = 2;
        }
        else if (quadPat === 'Combo-Single') {
          patternParams[0][p] = 3;
          patternParams[1][p] = 4;
        }
        else if (quadPat === 'Combo-Triple') {
          patternParams[0][p] = 4;
          patternParams[1][p] = 10;
        }
        else if (quadPat === 'Half-Half-Single') {
          patternParams[0][p] = 6;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Half-Half-Triple') {
          patternParams[0][p] = 7;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'One-One-Single') {
          patternParams[0][p] = 8;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'One-One-Triple') {
          patternParams[0][p] = 9;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Two-Two-Single') {
          patternParams[0][p] = 10;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Two-Two-Triple') {
          patternParams[0][p] = 11;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'All-On-Single') {
          patternParams[0][p] = 12;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'All-On-Triple') {
          patternParams[0][p] = 13;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'End-Corner') {
          patternParams[0][p] = 14;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Left-Slow') {
          patternParams[0][p] = 15;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Left-Fast') {
          patternParams[0][p] = 16;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Left-Combo') {
          patternParams[0][p] = 17;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Right-Slow') {
          patternParams[0][p] = 18;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Right-Fast') {
          patternParams[0][p] = 19;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Right-Combo') {
          patternParams[0][p] = 20;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Center-Out-Slow') {
          patternParams[0][p] = 21;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Center-Out-Fast') {
          patternParams[0][p] = 22;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Center-Out-Combo') {
          patternParams[0][p] = 23;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Standard On') {
          patternParams[0][p] = 24;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Driver') {
          patternParams[0][p] = 27;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Left Turn') {
          patternParams[0][p] = 25;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Passenger') {
          patternParams[0][p] = 27;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Right Turn') {
          patternParams[0][p] = 26;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'flood') {
          patternParams[0][p] = 27;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Brake Pop') {
          patternParams[0][p] = 28;
          patternParams[1][p] = 0;
        }
        else if (quadPat === 'Vehicle-Park') {
          patternParams[0][p] = 29;
          patternParams[1][p] = 4;
        }
        else if (quadPat === 'demo') {
          patternParams[0][p] = 39;
          patternParams[1][p] = 0;
        }
        else {
          patternParams[0][p] = 27;
          patternParams[1][p] = 0;
        }
      }
    }
    else {
      if (quadPat === 'Attack') {
        patternParams[0] = 0;
        patternParams[1] = 7;
      }
      else if (quadPat === 'Cluster') {
        patternParams[0] = 1;
        patternParams[1] = 2;
      }
      else if (quadPat === 'Cluster-Mix') {              
        patternParams[0] = 2;
        patternParams[1] = 2;
      }
      else if (quadPat === 'Combo-Single') {
        patternParams[0] = 3;
        patternParams[1] = 4;
      }
      else if (quadPat === 'Combo-Triple') {
        patternParams[0] = 4;
        patternParams[1] = 10;
      }
      else if (quadPat === 'Half-Half-Single') {
        patternParams[0] = 6;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Half-Half-Triple') {
        patternParams[0] = 7;
        patternParams[1] = 0;
      }
      else if (quadPat === 'One-One-Single') {
        patternParams[0] = 8;
        patternParams[1] = 0;
      }
      else if (quadPat === 'One-One-Triple') {
        patternParams[0] = 9;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Two-Two-Single') {
        patternParams[0] = 10;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Two-Two-Triple') {
        patternParams[0] = 11;
        patternParams[1] = 0;
      }
      else if (quadPat === 'All-On-Single') {
        patternParams[0] = 12;
        patternParams[1] = 0;
      }
      else if (quadPat === 'All-On-Triple') {
        patternParams[0] = 13;
        patternParams[1] = 0;
      }
      else if (quadPat === 'End-Corner') {
        patternParams[0] = 14;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Left-Slow') {
        patternParams[0] = 15;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Left-Fast') {
        patternParams[0] = 16;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Left-Combo') {
        patternParams[0] = 17;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Right-Slow') {
        patternParams[0] = 18;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Right-Fast') {
        patternParams[0] = 19;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Right-Combo') {
        patternParams[0] = 20;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Center-Out-Slow') {
        patternParams[0] = 21;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Center-Out-Fast') {
        patternParams[0] = 22;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Center-Out-Combo') {
        patternParams[0] = 23;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Standard On') {
        patternParams[0] = 24;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Driver') {
        patternParams[0] = 27;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Left Turn') {
        patternParams[0] = 25;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Passenger') {
        patternParams[0] = 27;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Right Turn') {
        patternParams[0] = 26;
        patternParams[1] = 0;
      }
      else if (quadPat === 'flood') {
        patternParams[0] = 27;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Brake Pop') {
        patternParams[0] = 28;
        patternParams[1] = 0;
      }
      else if (quadPat === 'Vehicle-Park') {
        patternParams[0] = 29;
        patternParams[1] = 4;
      }
      else if (quadPat === 'demo') {
        patternParams[0] = 39;
        patternParams[1] = 0;
      }
      else {
        patternParams[0] = 27;
        patternParams[1] = 0;
      }
    }
  }
  return patternParams;
}

function setBufferConfigs(bar, colors, patternParams, mode, brightness) {
  // ALLOWS FLB 49 CONFIGS TO BE HANDLED BY FLB 60 LOGIC
  if (bar === 0) {
    colors.splice(1, 0, 'deSelect');
    colors.splice(12, 0, 'deSelect');
    colors.splice(16, 0, 'deSelect');
    colors.splice(27, 0, 'deSelect');
  }
  for (let config = 0; config < colors.length; config++) {
    // 49/60 BARS
    if (bar === 0 || bar === 1) {
      if (colors[config] !== null && colors[config] !== 'deSelect' && colors[config] !== 'blank') {
        // ADD CUT OFF TO BUFFER ARRAY
        if (mode === 4) {
          if (config === 0) {
  
            quadPatterns[15] = patternParams[0];
            quadMods[15] = patternParams[1];
            updatedFrameBuffer[15] = colors[config];
            updatedFrameBrightness[15] = brightness;
          }
          else if (config === 13) {
  
            quadPatterns[16] = patternParams[0];
            quadMods[16] = patternParams[1];
            updatedFrameBuffer[16] = colors[config];
            updatedFrameBrightness[16] = brightness;
          }
          else if (config === 29) {
  
            quadPatterns[17] = patternParams[0];
            quadMods[17] = patternParams[1];
            updatedFrameBuffer[17] = colors[config];
            updatedFrameBrightness[17] = brightness;
          }
          else if (config === 14) {
  
            quadPatterns[18] = patternParams[0];
            quadMods[18] = patternParams[1];
            updatedFrameBuffer[18] = colors[config];
            updatedFrameBrightness[18] = brightness;
          }
          else if (config < 15) {
  
            quadPatterns[config + 2] = patternParams[0];
            quadMods[config + 2] = patternParams[1];
            updatedFrameBuffer[config + 2] = colors[config];
            updatedFrameBrightness[config + 2] = brightness;
          }
  
          else if (config === 28) {
  
            quadPatterns[19] = patternParams[0];
            quadMods[19] = patternParams[1];
            updatedFrameBuffer[19] = colors[config];
            updatedFrameBrightness[19] = brightness;
          }
          else if (config === 15) {
  
            quadPatterns[20] = patternParams[0];
            quadMods[20] = patternParams[1];
            updatedFrameBuffer[20] = colors[config];
            updatedFrameBrightness[20] = brightness;
          }
          else if (config === 16) {
  
            quadPatterns[32] = patternParams[0];
            quadMods[32] = patternParams[1];
            updatedFrameBuffer[32] = colors[config];
            updatedFrameBrightness[32] = brightness;
          }
          else if (config === 17) {
  
            quadPatterns[31] = patternParams[0];
            quadMods[31] = patternParams[1];
            updatedFrameBuffer[31] = colors[config];
            updatedFrameBrightness[31] = brightness;
          }
          else if (config === 18) {
  
            quadPatterns[30] = patternParams[0];
            quadMods[30] = patternParams[1];
            updatedFrameBuffer[30] = colors[config];
            updatedFrameBrightness[30] = brightness;
          }
          else if (config === 19) {
  
            quadPatterns[29] = patternParams[0];
            quadMods[29] = patternParams[1];
            updatedFrameBuffer[29] = colors[config];
            updatedFrameBrightness[29] = brightness;
          }
          else if (config === 20) {
  
            quadPatterns[28] = patternParams[0];
            quadMods[28] = patternParams[1];
            updatedFrameBuffer[28] = colors[config];
            updatedFrameBrightness[28] = brightness;
          }
          else if (config === 21) {
  
            quadPatterns[27] = patternParams[0];
            quadMods[27] = patternParams[1];
            updatedFrameBuffer[27] = colors[config];
            updatedFrameBrightness[27] = brightness;
          }
          else if (config === 22) {
  
            quadPatterns[26] = patternParams[0];
            quadMods[26] = patternParams[1];
            updatedFrameBuffer[26] = colors[config];
            updatedFrameBrightness[26] = brightness;
          }
          else if (config === 23) {
  
            quadPatterns[25] = patternParams[0];
            quadMods[25] = patternParams[1];
            updatedFrameBuffer[25] = colors[config];
            updatedFrameBrightness[25] = brightness;
          }
          else if (config === 24) {
  
            quadPatterns[24] = patternParams[0];
            quadMods[24] = patternParams[1];
            updatedFrameBuffer[24] = colors[config];
            updatedFrameBrightness[24] = brightness;
          }
          else if (config === 25) {
  
            quadPatterns[23] = patternParams[0];
            quadMods[23] = patternParams[1];
            updatedFrameBuffer[23] = colors[config];
            updatedFrameBrightness[23] = brightness;
          }
          else if (config === 26) {
  
            quadPatterns[22] = patternParams[0];
            quadMods[22] = patternParams[1];
            updatedFrameBuffer[22] = colors[config];
            updatedFrameBrightness[22] = brightness;
          }
          else if (config === 27) {
  
            quadPatterns[21] = patternParams[0];
            quadMods[21] = patternParams[1];
            updatedFrameBuffer[21] = colors[config];
            updatedFrameBrightness[21] = brightness;
          }
          else if (config === 28) {
  
            quadPatterns[19] = patternParams[0];
            quadMods[19] = patternParams[1];
            updatedFrameBuffer[19] = colors[config];
            updatedFrameBrightness[19] = brightness;
          }
          else if (config === 29) {
  
            quadPatterns[17] = patternParams[0];
            quadMods[17] = patternParams[1];
            
            updatedFrameBuffer[17] = colors[config];
            updatedFrameBrightness[17] = brightness;
          } 
        }
        // TAIL CRUISE / DRIVER & LEFT TURN
        if (mode === 0 || mode === 6) {
          if (config > 0 && config < 7) {

            quadPatterns[config + 2] = patternParams[0];
            quadMods[config + 2] = patternParams[1];
            updatedFrameBuffer[config + 2] = colors[config];
            updatedFrameBrightness[config + 2] = brightness;
          }
          else if (config === 0) {

            quadPatterns[15] = patternParams[0];
            quadMods[15] = patternParams[1];
            updatedFrameBuffer[15] = colors[config];
            updatedFrameBrightness[15] = brightness;
          }
          else if (config === 22) {

            quadPatterns[26] = patternParams[0];
            quadMods[26] = patternParams[1];
            updatedFrameBuffer[26] = colors[config];
            updatedFrameBrightness[26] = brightness;
          }
          else if (config === 23) {

            quadPatterns[25] = patternParams[0];
            quadMods[25] = patternParams[1];
            updatedFrameBuffer[25] = colors[config];
            updatedFrameBrightness[25] = brightness;
          }
          else if (config === 24) {

            quadPatterns[24] = patternParams[0];
            quadMods[24] = patternParams[1];
            updatedFrameBuffer[24] = colors[config];
            updatedFrameBrightness[24] = brightness;
          }
          else if (config === 25) {

            quadPatterns[23] = patternParams[0];
            quadMods[23] = patternParams[1];
            updatedFrameBuffer[23] = colors[config];
            updatedFrameBrightness[23] = brightness;
          }
          else if (config === 26) {

            quadPatterns[22] = patternParams[0];
            quadMods[22] = patternParams[1];
            updatedFrameBuffer[22] = colors[config];
            updatedFrameBrightness[22] = brightness;
          }
          else if (config === 27) {

            quadPatterns[21] = patternParams[0];
            quadMods[21] = patternParams[1];
            updatedFrameBuffer[21] = colors[config];
            updatedFrameBrightness[21] = brightness;
          }
          else if (config === 28) {

            quadPatterns[19] = patternParams[0];
            quadMods[19] = patternParams[1];
            updatedFrameBuffer[19] = colors[config];
            updatedFrameBrightness[19] = brightness;
          }
          else if (config === 29) {

            quadPatterns[17] = patternParams[0];
            quadMods[17] = patternParams[1];
            updatedFrameBuffer[17] = colors[config];
            updatedFrameBrightness[17] = brightness;
          }
        }
        // TAIL CRUISE / PASSENGER & RIGHT TURN
        if (mode === 1 || mode === 7) {
          if (config > 6 && config < 13) {

            quadPatterns[config + 2] = patternParams[0];
            quadMods[config + 2] = patternParams[1];
            updatedFrameBuffer[config + 2] = colors[config];
            updatedFrameBrightness[config + 2] = brightness;
          }
          else if (config === 13) {

            quadPatterns[16] = patternParams[0];
            quadMods[16] = patternParams[1];
            updatedFrameBuffer[16] = colors[config];
            updatedFrameBrightness[16] = brightness;
          }
          else if (config === 14) {

            quadPatterns[18] = patternParams[0];
            quadMods[18] = patternParams[1];
            updatedFrameBuffer[18] = colors[config];
            updatedFrameBrightness[18] = brightness;
          }
          else if (config === 15) {

            quadPatterns[20] = patternParams[0];
            quadMods[20] = patternParams[1];
            updatedFrameBuffer[20] = colors[config];
            updatedFrameBrightness[20] = brightness;
          }
          else if (config === 16) {

            quadPatterns[32] = patternParams[0];
            quadMods[32] = patternParams[1];
            updatedFrameBuffer[32] = colors[config];
            updatedFrameBrightness[32] = brightness;
          }
          else if (config === 17) {

              quadPatterns[31] = patternParams[0];
              quadMods[31] = patternParams[1];
              updatedFrameBuffer[31] = colors[config];
              updatedFrameBrightness[31] = brightness;
          }
          else if (config === 18) {

            quadPatterns[30] = patternParams[0];
            quadMods[30] = patternParams[1];
            updatedFrameBuffer[30] = colors[config];
            updatedFrameBrightness[30] = brightness;
          }
          else if (config === 19) {

            quadPatterns[29] = patternParams[0];
            quadMods[29] = patternParams[1];
            updatedFrameBuffer[29] = colors[config];
            updatedFrameBrightness[29] = brightness;
          }
          else if (config === 20) {

            quadPatterns[28] = patternParams[0];
            quadMods[28] = patternParams[1];
            updatedFrameBuffer[28] = colors[config];
            updatedFrameBrightness[28] = brightness;
          }
          else if (config === 21) {

            quadPatterns[27] = patternParams[0];
            quadMods[27] = patternParams[1];
            updatedFrameBuffer[27] = colors[config];
            updatedFrameBrightness[27] = brightness;
          }
        }
        // FRONT / FLOOD / CUT OFF
        if (mode === 9) {
          if (config === 0) {

            quadPatterns[15] = patternParams[0];
            quadMods[15] = patternParams[1];
            updatedFrameBuffer[15] = colors[config];
            updatedFrameBrightness[15] = brightness;
          }
          else if (config === 13) {

            quadPatterns[16] = patternParams[0];
            quadMods[16] = patternParams[1];
            updatedFrameBuffer[16] = colors[config];
            updatedFrameBrightness[16] = brightness;
          }
          else if (config === 29) {

            quadPatterns[17] = patternParams[0];
            quadMods[17] = patternParams[1];
            updatedFrameBuffer[17] = colors[config];
            updatedFrameBrightness[17] = brightness;
          }
          else if (config === 14) {

            quadPatterns[18] = patternParams[0];
            quadMods[18] = patternParams[1];
            updatedFrameBuffer[18] = colors[config];
            updatedFrameBrightness[18] = brightness;
          }
          else if (config < 15) {

            quadPatterns[config + 2] = patternParams[0];
            quadMods[config + 2] = patternParams[1];
            updatedFrameBuffer[config + 2] = colors[config];
            updatedFrameBrightness[config + 2] = brightness;
          }
        }
        // REAR / FLOOD  / CUT OFF / BRAKE
        if (mode === 9 || mode === 8) {
          if (config === 28) {

            quadPatterns[19] = patternParams[0];
            quadMods[19] = patternParams[1];
            updatedFrameBuffer[19] = colors[config];
            updatedFrameBrightness[19] = brightness;
          }
          else if (config === 15) {

            quadPatterns[20] = patternParams[0];
            quadMods[20] = patternParams[1];
            updatedFrameBuffer[20] = colors[config];
            updatedFrameBrightness[20] = brightness;
          }
          else if (config === 16) {

            quadPatterns[32] = patternParams[0];
            quadMods[32] = patternParams[1];
            updatedFrameBuffer[32] = colors[config];
            updatedFrameBrightness[32] = brightness;
          }
          else if (config === 17) {

            quadPatterns[31] = patternParams[0];
            quadMods[31] = patternParams[1];
            updatedFrameBuffer[31] = colors[config];
            updatedFrameBrightness[31] = brightness;
          }
          else if (config === 18) {

            quadPatterns[30] = patternParams[0];
            quadMods[30] = patternParams[1];
            updatedFrameBuffer[30] = colors[config];
            updatedFrameBrightness[30] = brightness;
          }
          else if (config === 19) {

            quadPatterns[29] = patternParams[0];
            quadMods[29] = patternParams[1];
            updatedFrameBuffer[29] = colors[config];
            updatedFrameBrightness[29] = brightness;
          }
          else if (config === 20) {

            quadPatterns[28] = patternParams[0];
            quadMods[28] = patternParams[1];
            updatedFrameBuffer[28] = colors[config];
            updatedFrameBrightness[28] = brightness;
          }
          else if (config === 21) {

            quadPatterns[27] = patternParams[0];
            quadMods[27] = patternParams[1];
            updatedFrameBuffer[27] = colors[config];
            updatedFrameBrightness[27] = brightness;
          }
          else if (config === 22) {

            quadPatterns[26] = patternParams[0];
            quadMods[26] = patternParams[1];
            updatedFrameBuffer[26] = colors[config];
            updatedFrameBrightness[26] = brightness;
          }
          else if (config === 23) {
  
            quadPatterns[25] = patternParams[0];
            quadMods[25] = patternParams[1];
            updatedFrameBuffer[25] = colors[config];
            updatedFrameBrightness[25] = brightness;
          }
          else if (config === 24) {

            quadPatterns[24] = patternParams[0];
            quadMods[24] = patternParams[1];
            updatedFrameBuffer[24] = colors[config];
            updatedFrameBrightness[24] = brightness;
          }
          else if (config === 25) {

            quadPatterns[23] = patternParams[0];
            quadMods[23] = patternParams[1];
            updatedFrameBuffer[23] = colors[config];
            updatedFrameBrightness[23] = brightness;
          }
          else if (config === 26) {

            quadPatterns[22] = patternParams[0];
            quadMods[22] = patternParams[1];
            updatedFrameBuffer[22] = colors[config];
            updatedFrameBrightness[22] = brightness;
          }
          else if (config === 27) {

            quadPatterns[21] = patternParams[0];
            quadMods[21] = patternParams[1];
            updatedFrameBuffer[21] = colors[config];
            updatedFrameBrightness[21] = brightness;
          }
          else if (config === 28) {

            quadPatterns[19] = patternParams[0];
            quadMods[19] = patternParams[1];
            updatedFrameBuffer[19] = colors[config];
            updatedFrameBrightness[19] = brightness;
          }
          else if (config === 29) {
 
            quadPatterns[17] = patternParams[0];
            quadMods[17] = patternParams[1];
            updatedFrameBuffer[17] = colors[config];
            updatedFrameBrightness[17] = brightness;
          } 
        }
        // FRONT FLASHING
        if (mode === 2) {
          if (config === 0) {

            quadPatterns[15] = patternParams[0];
            quadMods[15] = patternParams[1];
            updatedFrameBuffer[15] = colors[config];
            updatedFrameBrightness[15] = brightness;
          }
          else if (config === 13) {

            quadPatterns[16] = patternParams[0];
            quadMods[16] = patternParams[1];
            updatedFrameBuffer[16] = colors[config];
            updatedFrameBrightness[16] = brightness;
          }
          else if (config === 29) {

            quadPatterns[17] = patternParams[0];
            quadMods[17] = patternParams[1];
            updatedFrameBuffer[17] = colors[config];
            updatedFrameBrightness[17] = brightness;
          }
          else if (config === 14) {

            quadPatterns[18] = patternParams[0];
            quadMods[18] = patternParams[1];
            updatedFrameBuffer[18] = colors[config];
            updatedFrameBrightness[18] = brightness;
          }
          else if (config < 15) {

            quadPatterns[config + 2] = patternParams[0];
            quadMods[config + 2] = patternParams[1];
            updatedFrameBuffer[config + 2] = colors[config];
            updatedFrameBrightness[config + 2] = brightness;
          }
        }
        // REAR FLASHING
        if (mode === 3) {
          if (config === 28) {

            quadPatterns[19] = patternParams[0];
            quadMods[19] = patternParams[1];
            updatedFrameBuffer[19] = colors[config];
            updatedFrameBrightness[19] = brightness;
          }
          else if (config === 15) {

            quadPatterns[20] = patternParams[0];
            quadMods[20] = patternParams[1];
            updatedFrameBuffer[20] = colors[config];
            updatedFrameBrightness[20] = brightness;
          }
          else if (config === 16) {

            quadPatterns[32] = patternParams[0];
            quadMods[32] = patternParams[1];
            updatedFrameBuffer[32] = colors[config];
            updatedFrameBrightness[32] = brightness;
          }
          else if (config === 17) {

            quadPatterns[31] = patternParams[0];
            quadMods[31] = patternParams[1];
            updatedFrameBuffer[31] = colors[config];
            updatedFrameBrightness[31] = brightness;
          }
          else if (config === 18) {

            quadPatterns[30] = patternParams[0];
            quadMods[30] = patternParams[1];
            updatedFrameBuffer[30] = colors[config];
            updatedFrameBrightness[30] = brightness;
          }
          else if (config === 19) {

            quadPatterns[29] = patternParams[0];
            quadMods[29] = patternParams[1];
            updatedFrameBuffer[29] = colors[config];
            updatedFrameBrightness[29] = brightness;
          }
          else if (config === 20) {

            quadPatterns[28] = patternParams[0];
            quadMods[28] = patternParams[1];
            updatedFrameBuffer[28] = colors[config];
            updatedFrameBrightness[28] = brightness;
          }
          else if (config === 21) {

            quadPatterns[27] = patternParams[0];
            quadMods[27] = patternParams[1];
            updatedFrameBuffer[27] = colors[config];
            updatedFrameBrightness[27] = brightness;
          }
          else if (config === 22) {

            quadPatterns[26] = patternParams[0];
            quadMods[26] = patternParams[1];
            updatedFrameBuffer[26] = colors[config];
            updatedFrameBrightness[26] = brightness;
          }
          else if (config === 23) {

            quadPatterns[25] = patternParams[0];
            quadMods[25] = patternParams[1];
            updatedFrameBuffer[25] = colors[config];
            updatedFrameBrightness[25] = brightness;
          }
          else if (config === 24) {

            quadPatterns[24] = patternParams[0];
            quadMods[24] = patternParams[1];
            updatedFrameBuffer[24] = colors[config];
            updatedFrameBrightness[24] = brightness;
          }
          else if (config === 25) {

            quadPatterns[23] = patternParams[0];
            quadMods[23] = patternParams[1];
            updatedFrameBuffer[23] = colors[config];
            updatedFrameBrightness[23] = brightness;
          }
          else if (config === 26) {

            quadPatterns[22] = patternParams[0];
            quadMods[22] = patternParams[1];
            updatedFrameBuffer[22] = colors[config];
            updatedFrameBrightness[22] = brightness;
          }
          else if (config === 27) {

            quadPatterns[21] = patternParams[0];
            quadMods[21] = patternParams[1];
            updatedFrameBuffer[21] = colors[config];
            updatedFrameBrightness[21] = brightness;
          }
          else if (config === 28) {

            quadPatterns[19] = patternParams[0];
            quadMods[19] = patternParams[1];
            updatedFrameBuffer[19] = colors[config];
            updatedFrameBrightness[19] = brightness;
          }
          else if (config === 29) {

            quadPatterns[17] = patternParams[0];
            quadMods[17] = patternParams[1];
            updatedFrameBuffer[17] = colors[config];
            updatedFrameBrightness[17] = brightness;
          } 
        }
        // ARROW DIRECTION
        if (mode === 5) {
          doubleCount = 0;
          if (config === 16) {

            quadPatterns[32] = patternParams[0];
            quadMods[32] = patternParams[1];
            updatedFrameBuffer[32] = colors[config];
            updatedFrameBrightness[32] = brightness;
          }
          else if (config === 17) {

            quadPatterns[31] = patternParams[0];
            quadMods[31] = patternParams[1];
            updatedFrameBuffer[31] = colors[config];
            updatedFrameBrightness[31] = brightness;
          }
          else if (config === 18) {

            quadPatterns[30] = patternParams[0];
            quadMods[30] = patternParams[1];
            updatedFrameBuffer[30] = colors[config];
            updatedFrameBrightness[30] = brightness;
          }
          else if (config === 19) {

            quadPatterns[29] = patternParams[0];
            quadMods[29] = patternParams[1];
            updatedFrameBuffer[29] = colors[config];
            updatedFrameBrightness[29] = brightness;
          }
          else if (config === 20) {

            quadPatterns[28] = patternParams[0];
            quadMods[28] = patternParams[1];
            updatedFrameBuffer[28] = colors[config];
            updatedFrameBrightness[28] = brightness;
          }
          else if (config === 21) {

            quadPatterns[27] = patternParams[0];
            quadMods[27] = patternParams[1];
            updatedFrameBuffer[27] = colors[config];
            updatedFrameBrightness[27] = brightness;
          }
          else if (config === 22) {

            quadPatterns[26] = patternParams[0];
            quadMods[26] = patternParams[1];
            updatedFrameBuffer[26] = colors[config];
            updatedFrameBrightness[26] = brightness;
          }
          else if (config === 23) {

            quadPatterns[25] = patternParams[0];
            quadMods[25] = patternParams[1];
            updatedFrameBuffer[25] = colors[config];
            updatedFrameBrightness[25] = brightness;
          }
          else if (config === 24) {

            quadPatterns[24] = patternParams[0];
            quadMods[24] = patternParams[1];
            updatedFrameBuffer[24] = colors[config];
            updatedFrameBrightness[24] = brightness;
          }
          else if (config === 25) {

            quadPatterns[23] = patternParams[0];
            quadMods[23] = patternParams[1];          
            updatedFrameBuffer[23] = colors[config];
            updatedFrameBrightness[23] = brightness;
          }
          else if (config === 26) {

            quadPatterns[22] = patternParams[0];
            quadMods[22] = patternParams[1];
            updatedFrameBuffer[22] = colors[config];
            updatedFrameBrightness[22] = brightness;
          }
          else if (config === 27) {

            quadPatterns[21] = patternParams[0];
            quadMods[21] = patternParams[1];
            updatedFrameBuffer[21] = colors[config];
            updatedFrameBrightness[21] = brightness;
          }
        }
      }
    }
    // 10X BARS
    // SURFACE MOUNT
    if (bar === 2 && colors[config] !== 'select' && colors[config] !== null) {
      // console.log("This is the QssmSelect: ", QssmSelect);
      if (config >= 0 && config < 16) {

        if (colors[config] !== 'deSelect') {
          quadPatterns[config + 117] = patternParams[0][config];
          quadMods[config + 117] = patternParams[1][config];
          updatedFrameBuffer[config + 117] = colors[config];
          updatedFrameBrightness[config + 117] = brightness[config];
        }
      }
    }
    // FRONT INTERIOR LB
    if (bar === 3 && colors[config] !== 'blank' && colors[config] !== 'select' && colors[config] !== null) {

      if (config >= 0 && config < 8) {

        quadPatterns[config + 44] = patternParams[0];
        quadMods[config + 44] = patternParams[1];
        updatedFrameBuffer[config + 44] = colors[config];
        updatedFrameBrightness[config + 44] = brightness;
      }
    }
    // REAR INTERIOR LB
    if (bar === 4 && colors[config] !== 'blank' && colors[config] !== 'select' && colors[config] !== null) {

      if (config >= 0 && config < 8 && colors[config] !== 'blank') {

        quadPatterns[config + 74] = patternParams[0];
        quadMods[config + 74] = patternParams[1];
        updatedFrameBuffer[config + 74] = colors[config];
        updatedFrameBrightness[config + 74] = brightness;
      }
    }
    // LEFT ROCKER PANEL
    if (bar === 5 && colors[config] !== 'blank' && colors[config] !== 'select' && colors[config] !== null) {

      if (config >= 0 && config < 8) {

        quadPatterns[config + 84] = patternParams[0];
        quadMods[config + 84] = patternParams[1];
        updatedFrameBuffer[config + 84] = colors[config];
        updatedFrameBrightness[config + 84] = brightness;
      }
    }
    // 400 10X
    if (bar === 6 && colors[config] !== 'blank' && colors[config] !== 'select' && colors[config] !== null) {

      if (config >= 0 && config < 4) {

        quadPatterns[config + 36] = patternParams[0];
        quadMods[config + 36] = patternParams[1];
        updatedFrameBuffer[config + 36] = colors[config];
        updatedFrameBrightness[config + 36] = brightness;
      }
    }
    // 600 10X
    if (bar === 7 && colors[config] !== 'blank' && colors[config] !== 'select' && colors[config] !== null) {

      if (config >= 0 && config < 6) {

        quadPatterns[config + 55] = patternParams[0];
        quadMods[config + 55] = patternParams[1];
        updatedFrameBuffer[config + 55] = colors[config];
        updatedFrameBrightness[config + 55] = brightness;
      }
    }
    // 800 10X
    if (bar === 8 && colors[config] !== 'blank' && colors[config] !== 'select' && colors[config] !== null) {

      if (config >= 0 && config < 8) {

        quadPatterns[config + 64] = patternParams[0];
        quadMods[config + 64] = patternParams[1];
        updatedFrameBuffer[config + 64] = colors[config];
        updatedFrameBrightness[config + 64] = brightness;
      }
    }
    // ARROW BOARD
    if (bar === 9 && colors[config] !== 'blank' && colors[config] !== 'select' && colors[config] !== null) {

      if (config >= 0 && config < 10) {

        quadPatterns[config + 103] = patternParams[0];
        quadMods[config + 103] = patternParams[1];
        updatedFrameBuffer[config + 103] = colors[config];
        updatedFrameBrightness[config + 103] = brightness;
      }
    }
    // ROCKER RIGHT
    if (bar === 10 && colors[config] !== 'blank' && colors[config] !== 'select' && colors[config] !== null) {

      if (config >= 0 && config < 8) {

        quadPatterns[config + 94] = patternParams[0];
        quadMods[config + 94] = patternParams[1];
        updatedFrameBuffer[config + 94] = colors[config];
        updatedFrameBrightness[config + 94] = brightness;
      }
    }
    // SPOILER MOUNT
    if (bar === 11 && colors[config] !== 'blank' && colors[config] !== 'select' && colors[config] !== null) {
      if (config >= 0 && config < 6) {

        if (colors[config] !== 'deSelect') {
          quadPatterns[config + 133] = patternParams[0][config];
          quadMods[config + 133] = patternParams[1][config];
          updatedFrameBuffer[config + 133] = colors[config];
          updatedFrameBrightness[config + 133] = brightness[config];
        }
      }
    }
  }
}

function configsExist(array) {
  for (var i = 0; i < array.length; i++) {
    for (let j = 0; j < array[i].length; j++)
      for (let k = 0; k < array[i][j].length; k++) {
        if (array[i][j][k] !== null) {
          if (array[i][j][k].length > 0) {
            return true;
          }
        }
      }
  }
  return false;
}

function consoleLogger(message, log) {
  if (deBug) {
    console.log(message, log);
  }
}