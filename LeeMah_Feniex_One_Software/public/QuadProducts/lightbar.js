var constant = require("./CommonQuadResources.js");
const NtpTimeSync = require("ntp-time-sync").NtpTimeSync;
const timeSync = NtpTimeSync.getInstance();

var NanoTimer = require('nanotimer');
var patternSyncTime = new NanoTimer();

// var preTime;
var patternTimeInit = true;
var calibratePTC = true;
var startPatternTime;
var initCounter = 0;
var checkNetworkClock;
var ptc;

var ptcCheckAttack = {};
var ptcCheckCluster = {};
var ptcCheckClusterMix = {};
var ptcCheckCombo = {};
var ptcCheckComboTriple = {};

var ptcHalfHalfSingle = {};
var ptcHalfHalfTriple = {};
var ptcOneOneSingle = {};
var ptcOneOneTriple = {};

var ptcLeftSlow = {};
var ptcLeftFast = {};
var ptcLeftCombo = {};

var ptcRightSlow = {};
var ptcRightFast = {};
var ptcRightCombo = {};

var ptcCenterSlow = {};
var ptcCenterFast = {};
var ptcCenterCombo = {};

var ptcTwoTwoSingle = {};
var ptcTwoTwoTriple = {};
var ptcAllOnSingle = {};
var ptcAllOnTriple = {};

var ptcEndCorner = {};
var ptcVehiclePark = {};

var initQssmSync = true;
var initSpoilerSync = true;

var ptcCheckCalQssm;
var ptcCheckCalSpoiler;
var ptcCheckCalSurface;
var ptcCheckCalFront;
var ptcCheckCalRear;
var ptcCheckCalArrow;
var ptcCheckCalRockerRight;
var ptcCheckCal800;
var ptcCheckCal600;
var ptcCheckCal400;
var ptcCheckCalRockerLeft;
var ptcCheckCalInnerRear;
var ptcCheckCalInner;

var comboOfFlashPatterns = constant.comboOfFlashPatterns;
var comboPatternTiming = constant.comboPatternTiming;

var END = constant.END;
var RED = constant.RED;
var BLUE = constant.BLUE;
var WHITE = constant.WHITE;
var AMBER = constant.AMBER;
var OFF = constant.OFF;

var previousBuffer = [
    0x7E,0x4C,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,
    0x0D,0x0A, 0x7E, 0x59,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,
    0x0D,0x0A
];

var quadColorLength = [
    0x7E,0x4C,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,
    0x0D,0x0A, 0x7E, 0x59,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,
    0x0D,0x0A
];

var newColorQuad = [
    0x7E,0x4C,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,
    0x0D,0x0A, 0x7E, 0x59,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,
    0x0D,0x0A
];

// var barColor = 0;
var quadColor = [
    0x7E,0x4C,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,
    0x0D,0x0A, 0x7E, 0x59,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,
    0x0D,0x0A
];

var firstquadColor = [
    0x7E,0x4C,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,
    0x0D,0x0A, 0x7E, 0x59,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,
    0x0D,0x0A
];

var patModQuad = [
    0x7E,0x4C,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,
    0x0D,0x0A, 0x7E, 0x59,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,
    0x0D,0x0A
];

var colorLength = 1;
var buffColor = 0;

var configColors = false;
var allowTurn = false;
var allowSteadyOn = false;
var setQuadPatternColors = false;
var setQuadPatternColors = false;
var set10xColors = false;

var noFlashPatterns = [];

// var start4;

var FIFTY_PERCENT_BRIGHT = constant.FIFTY_PERCENT_BRIGHT;
var TEN_PERCENT_BRIGHT = constant.TEN_PERCENT_BRIGHT;

var framePattern = [
    0x7E,0x4C,
    OFF,0,1,2,3,4,5,6,7,8,
    9,10,11,12,13,14,15,16,17,18,
    19,20,21,22,23,24,25,26,27,28,
    29,OFF,OFF,OFF,22,23,24,25,OFF,OFF,
    OFF,OFF,20,21,22,23,24,25,26,27,
    OFF,OFF,OFF,21,22,23,24,25,26,OFF,
    OFF,OFF,20,21,22,23,24,25,26,27,
    OFF,OFF,20,21,22,23,24,25,26,27,
    OFF,OFF,20,21,22,23,24,25,26,27,
    OFF,OFF,20,21,22,23,24,25,26,27,
    OFF,19,20,21,22,23,24,25,26,27,
    28,
    0x0D,0x0A, 0x7E, 0x59,
    14,12,0,1,2,3,4,5,6,7,
    8,9,10,11,13,15,3,4,5,6,
    7,8,OFF,
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

var brightness = [
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

var activeframeBuffer = [
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
var nextFrameBuffers = [
    [
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
    ], 
    [
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
    ], 
    [
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
    ], 
    [
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
    ]
];

var previousFrameBuffer = [
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

function lightbar(frontflashpattern, rearflashpattern)
{

    var trackTimerQuad = [
        0x7E,0x4C,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,
        0x0D,0x0A, 0x7E, 0x59,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,
        0x0D,0x0A
    ];

    var quantumPatternEnabled = [
        0x7E,0x4C,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,
        0x0D,0x0A, 0x7E, 0x59,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,false,false,false,false,false,false,false,
        false,false,false,
        0x0D,0x0A
    ];

    var trackComboPatternQuadFrame = [
        0x7E,0x4C,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,
        0x0D,0x0A, 0x7E, 0x59,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,
        0x0D,0x0A
    ];

    var quadFlashPattern = [
        0x7E,0x4C,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,
        0x0D,0x0A, 0x7E, 0x59,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,
        0x0D,0x0A
    ];

    // var otherRearPattern;
    // var otherRearMod = 0;

    function patternTimeCount() {
        ptc++
        // console.log ("This is the Pattern count", ptc);
    }

    function setPatternTimer() {

        if (patternTimeInit) {

            let time1 = new Date();
            let time2 = time1.getTime();
            let time3 = Math.round(time2 * .1);
            
            ptc = time3;

            if (ptc > 162569318340) {
                patternTimeInit = false;
                clearInterval(checkNetworkClock);
                patternSyncTime.clearInterval();
                patternSyncTime.setInterval(patternTimeCount, '', '10m'); 
            }
        }
    }

    // 117

    function quantumPattern() {

        for (let p = 0; p < quantumPatternEnabled.length; p++) {

            if(quantumPatternEnabled[p] === true) {
                trackTimerQuad[p]++;

                if(trackTimerQuad[p] > comboPatternTiming[quadFlashPattern[p]][trackComboPatternQuadFrame[p]] && comboPatternTiming[quadFlashPattern[p]][trackComboPatternQuadFrame[p]] !== 0) {
                    trackComboPatternQuadFrame[p]++;
                    trackTimerQuad[p] = 0;

                    if (comboOfFlashPatterns[quadFlashPattern[p]][trackComboPatternQuadFrame[p]] === END || trackComboPatternQuadFrame[p] % patModQuad[p] === 0) {

                        if (quadColorLength[p] > 1) {
                            // CATCH ERROR IF NEXT NEW COLOR FAME BUFFER NOT SET
                            try {   
                    
                                if (nextFrameBuffers[newColorQuad[p]][p] !== OFF) {

                                    activeframeBuffer[p] = nextFrameBuffers[newColorQuad[p]][p];
                                    quadColor[p] = nextFrameBuffers[newColorQuad[p]][p];
                                }
                    
                                newColorQuad[p]++;

                                if (newColorQuad[p] === quadColorLength[p]) {
                                    newColorQuad[p] = 0; 
                                }
                            }
                            catch(err) {
                                console.log("Next rear frame contains no length")
                            }
                        }
                        if (comboOfFlashPatterns[quadFlashPattern[p]][trackComboPatternQuadFrame[p]] === END) {
                            trackComboPatternQuadFrame[p] = 0;
                        }
                    }
                }
            }
        }
    }

    function continueCalibrate(pattern, barPattern, interval) {

        // patternSyncTime.clearInterval();
        if (barPattern === 'qssm') {
            initQssmSync = true;
            ptcCheckCalQssm = setTimeout(function() {
                // console.log("Welcome to the qssm callibrate", pattern, patModQuad);
                setStartPattern('startQuadPattern1', pattern);
            }, interval);
        }
        else if (barPattern === 'spoiler') {
            initSpoilerSync = true;
            ptcCheckCalSpoiler = setTimeout(function() {
                // console.log("Welcome to the qssm callibrate", pattern, patModSpoiler);
                setStartPattern('startQuadPattern17', pattern);
            }, interval);
        }
        else if (barPattern === 'rear') {
            ptcCheckCalRear = setTimeout(function() {
                // console.log("Welcome to the rear callibrate", pattern, patModRear);
                setStartPattern('startRearPattern', pattern);
            }, interval);
        }
        else if (barPattern === 'front') {
            ptcCheckCalFront = setTimeout(function() {  
                // console.log("Welcome to the front callibrate", pattern, patModFront);
                setStartPattern('startFrontPattern', pattern);
            }, interval);
        }
        else if (barPattern === 'arrow') {
            ptcCheckCalArrow = setTimeout(function() {  
                // console.log("Welcome to the arrow callibrate", pattern, patModArrow);
                setStartPattern('startArrowPattern', pattern);
            }, interval);
        }
        else if (barPattern === 'rockerRight') {
            ptcCheckCalRockerRight= setTimeout(function() {  
                // console.log("Welcome to the rockerRight callibrate", pattern, patModRockerRight);
                setStartPattern('startRockerRightPattern', pattern);
            }, interval);
        }
        else if (barPattern === 'fusion800') {
            ptcCheckCal800 = setTimeout(function() {  
                // console.log("Welcome to the fusion800 callibrate", pattern, patMod800);
                setStartPattern('start800Pattern', pattern);
            }, interval);
        }
        else if (barPattern === 'fusion600') {
            ptcCheckCal600 = setTimeout(function() {  
                // console.log("Welcome to the fusion600 callibrate", pattern, patMod600);
                setStartPattern('start600Pattern', pattern);
            }, interval);
        }
        else if (barPattern === 'fusion400') {
            ptcCheckCal400 = setTimeout(function() {  
                // console.log("Welcome to the fusion400 callibrate", pattern, patMod400);
                setStartPattern('start400Pattern', pattern);
            }, interval);
        }
        else if (barPattern === 'rockerLeft') {
            ptcCheckCalRockerLeft = setTimeout(function() {  
                // console.log("Welcome to the rockerLeft callibrate", pattern, patModRockerLeft);
                setStartPattern('startRockerLeftPattern', pattern);
            }, interval);
        }
        else if (barPattern === 'innerRear') {
            ptcCheckCalInnerRear = setTimeout(function() {  
                // console.log("Welcome to the innerRear callibrate", pattern, patModInnerRear);
                setStartPattern('startInnerRearPattern', pattern);
            }, interval);
        }
        else if (barPattern === 'innerFront') {
            ptcCheckCalInner = setTimeout(function() {  
                // console.log("Welcome to the innerFront callibrate", pattern, patModInner);
                setStartPattern('startInnerPattern', pattern);
            }, interval);
        }
    }

    function syncPattern(pattern, barPattern) {

        setPatternTimer();

        // INTERVAL TO RECHECK PTC WITH INTERNAL CLOCK EVERY 5 MINUTES
        if(calibratePTC) {
            calibratePTC = false;

            setInterval(function() {

                patternTimeInit = true;

                let time1 = new Date();
                let time2 = time1.getTime();
                let time3 = Math.round(time2 * .1);
                ptc = time3;

                if (ptc > 162569318340) {
                    // console.log("Networtk ptc calibration");
                    setPatternTimer();
                }
            }, 300000)

            // CONTINUES TO CHECK TO CALIBRATE UNTILL NTP IS SET AFTER LIGHT PATTERN
            checkNetworkClock = setInterval(function() {

                let time1 = new Date();
                let time2 = time1.getTime();
                let time3 = Math.round(time2 * .1);
                ptc = time3;

                if (ptc > 162569318340) {
                    // console.log("Networtk clock is calibrated");
                    setPatternTimer();
                }
                else {
                    // console.log("Networtk clock is NOT calibrated");
                }
            }, 10000)            
        }

        // ATTACK
        if (pattern === 0) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcCheckAttack[barSync]);

            ptcCheckAttack[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 1000 === 0) {
                    console.log("Attack pattern synced", ptc)
                    clearInterval(ptcCheckAttack[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 9600);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // CLUSTER
        else if (pattern === 1) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcCheckCluster[barSync]);

            ptcCheckCluster[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 336 === 0) {
                    clearInterval(ptcCheckCluster[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 2800);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // CLUSTER MIX NOT IN USE
        else if (pattern === 2) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcCheckClusterMix[barSync]);

            ptcCheckClusterMix[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 217 === 0) {
                    clearInterval(ptcCheckClusterMix[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 1800);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // COMBO SINGLE
        else if (pattern === 3) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcCheckCombo[barSync]);

            ptcCheckCombo[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 336 === 0) {
                    clearInterval(ptcCheckCombo[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 2800);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // COMBO TRIPLE
        else if (pattern === 4) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcCheckComboTriple[barSync]);

            ptcCheckComboTriple[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 686 === 0) {
                    clearInterval(ptcCheckComboTriple[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 6360);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // HALF HALF SINGLE
        else if (pattern === 6) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcHalfHalfSingle[barSync]);

            ptcHalfHalfSingle[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 220 === 0) {
                    clearInterval(ptcHalfHalfSingle[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 1800);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // HALF HALF TRIPLE
        else if (pattern === 7) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcHalfHalfTriple[barSync]);

            ptcHalfHalfTriple[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 960 === 0) {
                    clearInterval(ptcHalfHalfTriple[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 9100);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // ONE ONE SINGLE
        else if (pattern === 8) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcOneOneSingle[barSync]);

            ptcOneOneSingle[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 420 === 0) {
                    clearInterval(ptcOneOneSingle[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 3800);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // ONE ONE TRIPLE
        else if (pattern === 9) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcOneOneTriple[barSync]);

            ptcOneOneTriple[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 900 === 0) {
                    clearInterval(ptcOneOneTriple[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 8600);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // TWO TWO SINGLE
        else if (pattern === 10) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcTwoTwoSingle[barSync]);

            ptcTwoTwoSingle[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 420 === 0) {
                    clearInterval(ptcTwoTwoSingle[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 3800);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // TWO TWO TRIPLE
        else if (pattern === 11) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcTwoTwoTriple[barSync]);

            ptcTwoTwoTriple[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 900 === 0) {
                    clearInterval(ptcTwoTwoTriple[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 8600);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // ALL ON SINGLE
        else if (pattern === 12) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcAllOnSingle[barSync]);

            ptcAllOnSingle[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 420 === 0) {
                    clearInterval(ptcAllOnSingle[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 3800);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // ALL ON TRIPLE
        else if (pattern === 13) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcAllOnTriple[barSync]);

            ptcAllOnTriple[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 670 === 0) {
                    clearInterval(ptcAllOnTriple[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 6300);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // END CORNER
        else if (pattern === 14) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcEndCorner[barSync]);

            ptcEndCorner[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 420 === 0) {
                    clearInterval(ptcEndCorner[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 3800);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // LEFT SLOW ** pattern time varies from 4030 to 4090
        else if (pattern === 15) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcLeftSlow[barSync]);

            ptcLeftSlow[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 403 === 0) {
                    clearInterval(ptcLeftSlow[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 3630);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // LEFT FAST
        else if (pattern === 16) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcLeftFast[barSync]);

            ptcLeftFast[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 143 === 0) {
                    clearInterval(ptcLeftFast[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 1030);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // LEFT COMBO
        else if (pattern === 17) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcLeftCombo[barSync]);

            ptcLeftCombo[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 900 === 0) {
                    clearInterval(ptcLeftCombo[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 8600);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // RIGHT SLOW
        else if (pattern === 18) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcRightSlow[barSync]);

            ptcRightSlow[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 403 === 0) {
                    clearInterval(ptcRightSlow[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 3630);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // RIGHT FAST
        else if (pattern === 19) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcRightFast[barSync]);

            ptcRightFast[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 143 === 0) {
                    clearInterval(ptcRightFast[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 1030);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // RIGHT COMBO
        else if (pattern === 20) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcRightCombo[barSync]);

            ptcRightCombo[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 1000 === 0) {
                    clearInterval(ptcRightCombo[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 8600);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // CENTER OUT SLOW ** Issue with crashing
        else if (pattern === 21) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcCenterSlow[barSync]);

            ptcCenterSlow[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 217 === 0) {
                    clearInterval(ptcCenterSlow[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 1770);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // CENTER OUT FAST
        else if (pattern === 22) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcCenterFast[barSync]);

            ptcCenterFast[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 770 === 0) {
                    clearInterval(ptcCenterFast[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 7300);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // CENTER OUT COMBO
        else if (pattern === 23) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcCenterCombo[barSync]);

            ptcCenterCombo[barSync] = setInterval(function() {
                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 294 === 0) {
                    // console.log("Braking into the rear arrow", calBarPattern);
                    clearInterval(ptcCenterCombo[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 2300);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
        // VEHICLE PARK
        else if (pattern === 29) {

            let barSync = "" + barPattern + "";
            clearInterval(ptcVehiclePark[barSync]);

            ptcVehiclePark[barSync] = setInterval(function() {

                let calPattern = pattern;
                let calBarPattern = barPattern;
                let clearBarSync = "" + barPattern + "";

                if (ptc % 336 === 0) {
                    // console.log("Braking into the rear arrow", calBarPattern);
                    clearInterval(ptcVehiclePark[clearBarSync]);
                    continueCalibrate(calPattern, calBarPattern, 2800);
                    resetBarPatterns(barPattern, ptc);
                }
            }, 10);
        }
    }

    function resetBarPatterns(barToSync, ptc) {

        newColorQuad = [
            0x7E,0x4C,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,
            0x0D,0x0A, 0x7E, 0x59,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,
            0x0D,0x0A
        ];

        trackTimerQuad = [
            0x7E,0x4C,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,
            0x0D,0x0A, 0x7E, 0x59,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,
            0x0D,0x0A
        ];

        trackComboPatternQuadFrame = [
            0x7E,0x4C,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,
            0x0D,0x0A, 0x7E, 0x59,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,
            0x0D,0x0A
        ];
        quadColor = firstquadColor;
    }

    function setStartPattern(barPattern, pattern) {

        if (barPattern === 'startQssmPattern') {

            if (initQssmSync) {
                initQssmSync = false;
                syncPattern(pattern, 'qssm');
            }
        }
        else if (barPattern === 'startSurfacePattern') {

            if (initSpoilerSync) {
                initSpoilerSync = false;
                syncPattern(pattern, 'spoiler');
            }
        }
        // 10X PRODUCTS
        else if (barPattern === 'startArrowPattern') {
            syncPattern(pattern, 'arrow');
        }
        else if (barPattern === 'startRockerRightPattern') {
            syncPattern(pattern, 'rockerRight');
        }
        else if (barPattern === 'start800Pattern') {
            syncPattern(pattern, 'fusion800');
        }
        else if (barPattern === 'start600Pattern') {
            syncPattern(pattern, 'fusion600');
        }
        else if (barPattern === 'start400Pattern') {
            syncPattern(pattern, 'fusion400');
        }
        else if (barPattern === 'startRockerLeftPattern') {
            syncPattern(pattern, 'rockerLeft');
        }
        else if (barPattern === 'startInnerRearPattern') {
            syncPattern(pattern, 'innerRear');
        }
        else if (barPattern === 'startInnerPattern') {
            syncPattern(pattern, 'innerFront');
        }
        // FLB BARS
        else if (barPattern === 'startFrontPattern') {

            // console.log("Start front pattern sync", pattern)
            // start4 = new Date().getTime();
            // console.log("CALL THE FRPONT PATTERN")

            syncPattern(pattern, 'front');
        }
        else if (barPattern === 'startRearPattern') {

            // start4 = new Date().getTime();
            // console.log("CALL THE REAR PATTERN")

            syncPattern(pattern, 'rear');
        }
    }

    this.updatePatterns = function()
    {
        quantumPattern();
    }

    this.startQuadPattern = function(patterns, modulus, updatedFrameBuffer)
    {
        // console.log("WHat is the shitt!!", JSON.stringify(updatedFrameBuffer))
        // console.log("WHat is the shitt!! 2", JSON.stringify(patterns))
        // console.log("WHat is the shitt!! 3", JSON.stringify(modulus))
        let syncFront = true;
        let syncRear = true;
        let sync400 = true;
        let sync600 = true;
        let sync800 = true;
        let syncQssm = true;
        let syncInner = true;
        let syncArrow = true;
        let syncSurface = true;
        let syncRearInner = true;
        let syncRockerLeft = true;
        let syncRockerRight = true;
        let patternToSync = '';

        for (let byte = 0; byte < updatedFrameBuffer.length; byte++) {
            if (patterns[byte] < 24 || patterns[byte] > 27) {
                if (updatedFrameBuffer[byte] !== OFF && ((byte > 2 && byte < 113) || (byte > 116 && byte < 140))) {

                    quantumPatternEnabled[byte] = true;
                    trackTimerQuad[byte] = 0;
                    trackComboPatternQuadFrame[byte] = 0;
                    newColorQuad[byte] = 1;
                    patModQuad[byte] = modulus[byte];
                    quadFlashPattern[byte] = patterns[byte];

                    // START PATTERN SYNCINGS
                    if (quantumPatternEnabled[byte] === true && ((byte > 2 && byte < 18) || (byte > 14 && byte < 19))) {
                        patternToSync = 'startFrontPattern';
                        if (syncFront) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            syncFront = false;
                        }
                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 18 && byte < 33)) {
                        patternToSync = 'startRearPattern';
                        if (syncRear) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            syncRear = false;
                        }                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 35 && byte < 40)) {
                        patternToSync = 'start400Pattern';
                        if (sync400) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            sync400 = false;
                        }                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 43 && byte < 52)) {
                        patternToSync = 'startInnerPattern';
                        if (syncInner) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            syncInner = false;
                        }                    
                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 54 && byte < 61)) {
                        patternToSync = 'start600Pattern';
                        if (sync600) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            sync600 = false;
                        }                    
                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 63 && byte < 72)) {
                        patternToSync = 'start800Pattern';
                        if (sync800) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            sync800 = false;
                        }                    
                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 73 && byte < 82)) {
                        patternToSync = 'startInnerRearPattern';
                        if (syncRearInner) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            syncRearInner = false;
                        }                    
                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 83 && byte < 92)) {
                        patternToSync = 'startRockerLeftPattern';
                        if (syncRockerLeft) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            syncRockerLeft = false;
                        }                    
                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 93 && byte < 102)) {
                        patternToSync = 'startRockerRightPattern';
                        if (syncRockerRight) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            syncRockerRight = false;
                        }                    
                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 104 && byte < 113)) {
                        patternToSync = 'startArrowPattern';
                        if (syncArrow) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            syncArrow = false;
                        }                    
                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 116 && byte < 133)) {
                        patternToSync = 'startQssmPattern';
                        if (syncQssm) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            syncQssm = false;
                        }                    
                    }
                    else if (quantumPatternEnabled[byte] === true && (byte > 132 && byte < 139)) {
                        patternToSync = 'startSurfacePattern';
                        if (syncSurface) {
                            setStartPattern(patternToSync, quadFlashPattern[byte]);
                            syncSurface = false;
                        }                    
                    }
                }
            }
            else if (updatedFrameBuffer[byte] !== OFF && ((byte > 2 && byte < 113) || (byte > 116 && byte < 140))) {
                patModQuad[byte] = modulus[byte];
                quadFlashPattern[byte] = patterns[byte];
            }
        }
    }

    this.clearQssmSteady = function() {
        setQuadColors = true;
    }

    this.clearPattern = function()
    {

        // RESET COLOR VARIABLES
        configColors = true;

        setQuadColors = true;
        setQuadPatternColors = true;
        // set10xColors = true;
        // RESET PATTERN SYNC VARIABLES
        patternSyncTime.clearInterval();
        patternTimeInit = true;

        initQssmSync = true;
        initSpoilerSync = true;

        // otherRearPattern;
        // otherRearMod = 0;

        // CLEAR ALL PATTERN SYNC INTERVALS
        for (var key in ptcCheckAttack) {
            clearInterval(ptcCheckAttack[key]);
        }
        for (var key in ptcCheckCluster) {
            clearInterval(ptcCheckCluster[key]);
        }
        for (var key in ptcCheckClusterMix) {
            clearInterval(ptcCheckClusterMix[key]);
        }
        for (var key in ptcCheckCombo) {
            clearInterval(ptcCheckCombo[key]);
        }
        for (var key in ptcCheckComboTriple) {
            clearInterval(ptcCheckComboTriple[key]);
        }
        for (var key in ptcHalfHalfSingle) {
            clearInterval(ptcHalfHalfSingle[key]);
        }
        for (var key in ptcHalfHalfTriple) {
            clearInterval(ptcHalfHalfTriple[key]);
        }
        for (var key in ptcOneOneSingle) {
            clearInterval(ptcOneOneSingle[key]);
        }
        for (var key in ptcOneOneTriple) {
            clearInterval(ptcOneOneTriple[key]);
        }
        for (var key in ptcLeftSlow) {
            clearInterval(ptcLeftSlow[key]);
        }
        for (var key in ptcLeftFast) {
            clearInterval(ptcLeftFast[key]);
        }
        for (var key in ptcLeftCombo) {
            clearInterval(ptcLeftCombo[key]);
        }
        for (var key in ptcRightSlow) {
            clearInterval(ptcRightSlow[key]);
        }
        for (var key in ptcRightFast) {
            clearInterval(ptcRightFast[key]);
        }
        for (var key in ptcRightCombo) {
            clearInterval(ptcRightCombo[key]);
        }
        for (var key in ptcCenterSlow) {
            clearInterval(ptcCenterSlow[key]);
        }
        for (var key in ptcCenterFast) {
            clearInterval(ptcCenterFast[key]);
        }
        for (var key in ptcCenterCombo) {
            clearInterval(ptcCenterCombo[key]);
        }
        for (var key in ptcTwoTwoSingle) {
            clearInterval(ptcTwoTwoSingle[key]);
        }
        for (var key in ptcTwoTwoTriple) {
            clearInterval(ptcTwoTwoTriple[key]);
        }
        for (var key in ptcAllOnSingle) {
            clearInterval(ptcAllOnSingle[key]);
        }
        for (var key in ptcAllOnTriple) {
            clearInterval(ptcAllOnTriple[key]);
        }
        for (var key in ptcEndCorner) {
            clearInterval(ptcEndCorner[key]);
        }
        for (var key in ptcVehiclePark) {
            clearInterval(ptcVehiclePark[key]);
        }
        
        clearTimeout(ptcCheckCalQssm);
        clearTimeout(ptcCheckCalSpoiler);
        clearTimeout(ptcCheckCalFront);
        clearTimeout(ptcCheckCalRear);
        clearTimeout(ptcCheckCalArrow);
        clearTimeout(ptcCheckCalRockerRight);
        clearTimeout(ptcCheckCal800);
        clearTimeout(ptcCheckCal600);
        clearTimeout(ptcCheckCal400);
        clearTimeout(ptcCheckCalRockerLeft);
        clearTimeout(ptcCheckCalInnerRear);
        clearTimeout(ptcCheckCalInner);       

        quadColor = [
            0x7E,0x4C,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,
            0x0D,0x0A, 0x7E, 0x59,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,
            0x0D,0x0A
        ];

        trackComboPatternQuadFrame = [
            0x7E,0x4C,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,
            0x0D,0x0A, 0x7E, 0x59,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,
            0x0D,0x0A
        ];

        quantumPatternEnabled = [
            0x7E,0x4C,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,
            0x0D,0x0A, 0x7E, 0x59,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,false,false,false,false,false,false,false,
            false,false,false,
            0x0D,0x0A
        ];
    }

    function valueToColor(color, brightness) {

        let bufferColor;

        if (color === 'r') {
            if (brightness === '10%') {
                bufferColor = RED & TEN_PERCENT_BRIGHT;
            }
            else if (brightness === '50%') {
                bufferColor = RED & FIFTY_PERCENT_BRIGHT;
            }
            else if (brightness === '100%') {
                bufferColor = RED;
            }
            else {
                bufferColor = RED;
            }
        }
        else if (color === 'b') {

            if (brightness === '10%') {
                bufferColor = BLUE & TEN_PERCENT_BRIGHT;
            }
            else if (brightness === '50%') {
                bufferColor = BLUE & FIFTY_PERCENT_BRIGHT;
            }
            else if (brightness === '100%') {
                bufferColor = BLUE;
            }
            else {
                bufferColor = BLUE;
            }
        }
        else if (color === 'a') {

            if (brightness === '10%') {
                bufferColor = AMBER & TEN_PERCENT_BRIGHT;
            }
            else if (brightness === '50%') {
                bufferColor = AMBER & FIFTY_PERCENT_BRIGHT;
            }
            else if (brightness === '100%') {
                bufferColor = AMBER;
            }
            else {
                bufferColor = AMBER;
            }
        }
        else if (color === 'w') {

            if (brightness === '10%') {
                bufferColor = WHITE & TEN_PERCENT_BRIGHT;
            }
            else if (brightness === '50%') {
                bufferColor = WHITE & FIFTY_PERCENT_BRIGHT;
            }
            else if (brightness === '100%') {
                bufferColor = WHITE;
            }
            else {
                bufferColor = WHITE;
            }
        }
        return bufferColor;
    }

    function setBufferColor(color) {

        // console.log("This is the color: ", frameBuffer[color])
        if (frameBuffer[color].length < 5) {

            if (frameBuffer[color].length === 1 && frameBuffer[color] !== 0) {
            // if (frameBuffer[color].length === 1) {
                buffColor = 0;
                colorLength = 1;

                let color1 = valueToColor(frameBuffer[color], brightness[color]);

                activeframeBuffer[color] = color1;
                nextFrameBuffers[0][color] = color1;

                buffColor = color1;
            }
            else if (frameBuffer[color].length === 2) {
                buffColor = 0;
                colorLength = 2;

                let color2 = valueToColor(frameBuffer[color].substr(0, 1), brightness[color]);

                nextFrameBuffers[0][color] = color2;
                nextFrameBuffers[1][color] = valueToColor(frameBuffer[color].substr(1, 1), brightness[color]);
                activeframeBuffer[color] = color2;
                buffColor = color2;
            }
            else if (frameBuffer[color].length === 3) {
                buffColor = 0;
                colorLength = 3;

                let color3 = valueToColor(frameBuffer[color].substr(0, 1), brightness[color]);

                nextFrameBuffers[0][color] = color3;
                nextFrameBuffers[1][color] = valueToColor(frameBuffer[color].substr(1, 1), brightness[color]);
                nextFrameBuffers[2][color] = valueToColor(frameBuffer[color].substr(2, 1), brightness[color]);
                activeframeBuffer[color] = color3;
                buffColor = color3;
            }
            else if (frameBuffer[color].length === 4) {
                buffColor = 0;
                colorLength = 4;

                let color4 = valueToColor(frameBuffer[color].substr(0, 1), brightness[color]);

                nextFrameBuffers[0][color] = color4;
                nextFrameBuffers[1][color] = valueToColor(frameBuffer[color].substr(1, 1), brightness[color]);
                nextFrameBuffers[2][color] = valueToColor(frameBuffer[color].substr(2, 1), brightness[color]);
                nextFrameBuffers[3][color] = valueToColor(frameBuffer[color].substr(3, 1), brightness[color]);
                activeframeBuffer[color] = color4;
                buffColor = color4;
            }
        }
        else {
            activeframeBuffer[color] = frameBuffer[color];
            nextFrameBuffers[0][color] = frameBuffer[color];
            nextFrameBuffers[1][color] = frameBuffer[color];
            nextFrameBuffers[2][color] = frameBuffer[color];
            nextFrameBuffers[3][color] = frameBuffer[color];
        }
        return [buffColor, colorLength];
    }

    function clearColors(color) {
        activeframeBuffer[color] = OFF;
        nextFrameBuffers[0][color] = OFF;
        nextFrameBuffers[1][color] = OFF;
        nextFrameBuffers[2][color] = OFF;
        nextFrameBuffers[3][color] = OFF;
    }

    this.addSSFrameBuffer = function(frameBuff, bright, patterns, modulus) {

        frameBuffer = frameBuff;
        brightness = bright;

        if (setQuadColors) {

            for (let color = 0; color < frameBuffer.length; color++) {

                if (patterns[color] === 24 || patterns[color] === 25 || patterns[color] === 26 || patterns[color] === 27) {

                    let setQuadColor = setBufferColor(color);

                    quadFlashPattern[color] = patterns[color];
                    newColorQuad[color] = 1;
                    quadColor[color] = setQuadColor[0];
                    firstquadColor[color] = quadColor[color];
                    quadColorLength[color] = setQuadColor[1];
                    trackComboPatternQuadFrame[color] = 0;
                }
                else {
                    if (setQuadPatternColors) {
                        if ((color > 2 && color < 113) || (color > 116 && color < 140)) {

                            let setQuadColor = setBufferColor(color);

                            newColorQuad[color] = 1;
                            quadColor[color] = setQuadColor[0];
                            firstquadColor[color] = quadColor[color];
                            quadColorLength[color] = setQuadColor[1];
                            quadFlashPattern[color] = patterns[color];
                            patModQuad[color] = modulus[color];
                            trackComboPatternQuadFrame[color] = 0;
                            quantumPatternEnabled[color] = true;
                            trackTimerQuad[color] = 0;
                        }
                    }
                }
            }
            setQuadColors = false;
            setQuadPatternColors = false;
        }

        for (let color = 0; color < frameBuffer.length; color++) {
            if (frameBuffer[color] === 'cutOff' || frameBuffer[color] === 0) {
                clearColors(color);
            }
        }
    }

    this.startPatterns = function() {

        for (let p = 0; p < quantumPatternEnabled.length; p++) {
            
            if (quantumPatternEnabled[p] === true) {

                if (quadFlashPattern[p] === 29) {
            
                    let color10 = quadColor[p] & TEN_PERCENT_BRIGHT;
                    let color50 = quadColor[p] & FIFTY_PERCENT_BRIGHT;

                    if (comboOfFlashPatterns[quadFlashPattern[p]][trackComboPatternQuadFrame[p]][framePattern[p]] === OFF) {
                        activeframeBuffer[p] = color10;
                    }
                    else {
                        if (nextFrameBuffers[0][p] !== OFF){
                            activeframeBuffer[p] = color50;
                        }
                    }
                }
                else {
                    // console.log("What is this!!! 1",  quadFlashPattern[p], p)
                    // console.log("What is this!!! 2",  trackComboPatternQuadFrame[p], p)
                    // console.log("What is this!!! 3",  JSON.stringify(quantumPatternEnabled.length))
                    // console.log("What is this!!! 4",  JSON.stringify(framePattern.length))

                    if (comboOfFlashPatterns[quadFlashPattern[p]][trackComboPatternQuadFrame[p]][framePattern[p]] === OFF) {
                        activeframeBuffer[p] = comboOfFlashPatterns[quadFlashPattern[p]][trackComboPatternQuadFrame[p]][framePattern[p]];
                    }
                    else {
                        if (nextFrameBuffers[0][p] !== OFF) {
                            activeframeBuffer[p] = quadColor[p];
                        }
                    }
                }
            }
        }
        return activeframeBuffer;
    }
}
module.exports = lightbar;