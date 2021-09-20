import React, { Component } from "react";
import PacketBuilder from '../services/packetBuilder';
import BitBuilder from '../services/bitBuilder';
import external from "../json/external.json"

const PacketBuild = new PacketBuilder();
const BitBuild = new BitBuilder();

var LightBarPatterns = [
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]]
];

var LightBarBrightness = [
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]]
];

var LightBarConfigs = [
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]]
];

var cutOffs = [
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]],
    [[],[],[],[],[],[],[],[],[],[]]
];

var previousButton = [];
var previousRelay = [];
// var turnActive = false;
// var previousVehicle = [];
// var turnTimeOut;

export class Configs extends Component {
    constructor(props) {
        super(props);
        this.state = {
            external: external,
            buttonColors: [
                'default', 'default', 'default', 'default', 
                'default', 'default', 'default', 'default', 
                'default', 'default', 'default', 'default', 
                'default', 'default', 'default', 'default',
                'default', 'default', 'default', 'default',
                'default', 'default'
            ],
            IotStates : {"Siren": "Off", "Lights": "Off" }
        }
    }

    static addCutOffs(array) {
        for (var i = 0; i < array.length; i++) {
            for (let j = 0; j < array[i].length; j++) {
                for (let k = 0; k < array[i][j].length; k++) {
                    if (array[i][j][k] === 'cutOff') {
                        LightBarConfigs[i][j][k] = 'cutOff';
                    }
                }
            }
        }
    }

    static getDerivedStateFromProps(props, current_state) {

        var localCopyProps = JSON.parse(JSON.stringify(props.parentState));
        var configPropStates = props.configStates;
        var multiFunctions = localCopyProps.multiFunction;
        var brightness = localCopyProps.brightness;
        var buttonStates = localCopyProps.buttonStates;
        var screenBrightness = localCopyProps.screenBrightness;
        var powerState = localCopyProps.powerState;
        var speakerEnable = localCopyProps.speakerEnable;
        
        var buttonColors = configPropStates.ButtonBackgroundColor;
        var multiColors1 = configPropStates.MultiButtonBackgroundColor1;
        var multiColors2 = configPropStates.MultiButtonBackgroundColor2;
        var multiColors3 = configPropStates.MultiButtonBackgroundColor3;

        // var setBrightness = localCopyProps.setBrightness;
        var multiFunction = localCopyProps.multiFunction;
        var relaySelect = localCopyProps.relaySelect;
        var vehicleInputs = props.vehicleInputs;

        var currentVehicleSelection = localCopyProps.

        LightBarPatterns = [
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]]
        ];
        
        LightBarBrightness = [
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]]
        ];
        
        LightBarConfigs = [
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]]
        ];

        cutOffs = [
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]],
            [[],[],[],[],[],[],[],[],[],[]]
        ];
        // var vehicleStates = props.vehicleStates;

        // console.log("This is the active input: " + localCopyProps.activeInput);

        current_state.IotStates["Lights"] = "Off";

        // SETS BUTTON COLORS
        for (let color = 0; color < multiFunctions.length; color++) {

            if (multiFunctions[color] === 1) {
                if (multiColors1[color] !== 'default') {
                    current_state.buttonColors[color] = multiColors1[color];
                }
            }
            else if (multiFunctions[color] === 2) {
                if (multiColors2[color] !== 'default') {
                    current_state.buttonColors[color] = multiColors2[color];
                }
            }
            else if (multiFunctions[color] === 3) {
                if (multiColors3[color] !== 'default') {
                    current_state.buttonColors[color] = multiColors3[color];
                }
            }
            else {
                current_state.buttonColors[color] = buttonColors[color];
            }
        }

        // var lightBarConfig = [];
        var lightBarByte = [];
        var portBytes = [];
        var highLowByte = [];
        var ledConfigs = [];
        var SMZone = [];
        var dualDelay = 0;
        var radioReBroadcast = 0;
        var parkKill = 0;

        var lightBar = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
        var siren1 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
        var siren2 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
        var siren3 = [0, 0, 0, 0, 0, 0, 0, 0];
        var activePort = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
        var highLowActive = [0, 0, 0, 0, 0, 0, 0, 0];

        var lightBarPattern = '';

        // SENDS RELAY HIGH LOW PACKET DATA
        for (let active = 0; active < highLowActive.length; active++) {
            highLowActive[active] = configPropStates.inputOutputSettings[active].InputActivationLevel;
        }

        // console.log("THis is the vehicle data: " + JSON.stringify())
        // var vehicleSend = false;

        for (let input = 0; input < vehicleInputs.length; input++) {
            // console.log("These are the vehicle imputs", input);

            // if (vehicleInputs[input] !== -1) {

            var operator = configPropStates.vehicleOutputSettings[input].Function[0].Operator;
            var parameter = parseInt(configPropStates.vehicleOutputSettings[input].Function[0].Parameter, 10);

            let configsCondition;
            let patternCondition;
            let brightnessCondition;
            let vehicleConfigs = configPropStates.vehicleOutputSettings[input].Function[0];

            // DUAL DELAY RADIO BROADCAST OR PARKKILL
            if (operator === 'equals') {
                if (vehicleInputs[input] === parameter) {
                    if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.DualDelay === 1) {
                        dualDelay = 1;
                    }
                    if ((configPropStates.vehicleOutputSettings[input].Function[0].speaker.ReBroadcast & 1) === 1) {
                        radioReBroadcast = 1;
                    }
                    else if ((configPropStates.vehicleOutputSettings[input].Function[0].speaker.ReBroadcast & 2) === 2) {
                        parkKill = 1;
                    }
                }
            }
            else if (operator === 'lesser') {
                if (vehicleInputs[input] < parameter) {
                    if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.DualDelay === 1) {
                        dualDelay = 1;
                    }
                    if ((configPropStates.vehicleOutputSettings[input].Function[0].speaker.ReBroadcast & 1) === 1) {
                        radioReBroadcast = 1;
                    }
                    else if ((configPropStates.vehicleOutputSettings[input].Function[0].speaker.ReBroadcast & 2) === 2) {
                        parkKill = 1;
                    }
                }
            }  
            else if (operator === 'greater') {
                if (vehicleInputs[input] > parameter) {
                    if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.DualDelay === 1) {
                        dualDelay = 1;
                    }
                    if ((configPropStates.vehicleOutputSettings[input].Function[0].speaker.ReBroadcast & 1) === 1) {
                        radioReBroadcast = 1;
                    }
                    else if ((configPropStates.vehicleOutputSettings[input].Function[0].speaker.ReBroadcast & 2) === 2) {
                        parkKill = 1;
                    }
                }
            }

            // Active Lightbar configs
            for (let bar = 0; bar < lightBar.length; bar++) {

                if (operator === 'equals') {
                    if (vehicleInputs[input] === parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].LightBar[bar] === 1) {
                            lightBar[bar] = 1;
                        }
                    }
                }
                else if (operator === 'lesser') {
                    if (vehicleInputs[input] < parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].LightBar[bar] === 1) {
                            lightBar[bar] = 1;
                        }
                    }
                }  
                else if (operator === 'greater') {
                    if (vehicleInputs[input] > parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].LightBar[bar] === 1) {
                            lightBar[bar] = 1;
                        }
                    }
                }   
            }
            // Active siren configs
            for (let siren = 0; siren < siren1.length; siren++) {

                if (operator === 'equals') {
                    if (vehicleInputs[input] === parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.Speaker1[siren] === 1) {
                            siren1[siren] = 1;
                        }
                    }
                }
                else if (operator === 'lesser') {
                    if (vehicleInputs[input] < parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.Speaker1[siren] === 1) {
                            siren1[siren] = 1;
                        }
                    }
                }  
                else if (operator === 'greater') {
                    if (vehicleInputs[input] > parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.Speaker1[siren] === 1) {
                            siren1[siren] = 1;
                        } 
                    }
                }   
            }
            for (let siren = 0; siren < siren2.length; siren++) {
    
                if (operator === 'equals') {
                    if (vehicleInputs[input] === parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.Speaker2[siren] === 1) {
                            siren2[siren] = 1;
                        }
                    }
                }
                else if (operator === 'lesser') {
                    if (vehicleInputs[input] < parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.Speaker2[siren] === 1) {
                            siren2[siren] = 1;
                        }
                    }
                }  
                else if (operator === 'greater') {
                    if (vehicleInputs[input] > parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.Speaker2[siren] === 1) {
                            siren2[siren] = 1;
                        }
                    }
                }   
            }
            for (let siren = 0; siren < siren3.length; siren++) {
    
                if (operator === 'equals') {
                    if (vehicleInputs[input] === parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.Audio[siren] === 1) {
                            siren3[siren] = 1;
                        }
                    }
                }
                else if (operator === 'lesser') {
                    if (vehicleInputs[input] < parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.Audio[siren] === 1) {
                            siren3[siren] = 1;
                        }
                    }                      
                }  
                else if (operator === 'greater') {
                    if (vehicleInputs[input] > parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].speaker.Audio[siren] === 1) {
                            siren3[siren] = 1;
                        }                      
                    }     
                }
            }
            // Active Port configs
            for (let port = 0; port < activePort.length; port++) {
    
                if (operator === 'equals') {
                    if (vehicleInputs[input] === parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].ActivePorts[port] === 1) {
                            activePort[port] = 1;
                        }
                    }
                }
                else if (operator === 'lesser') {
                    if (vehicleInputs[input] < parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].ActivePorts[port] === 1) {
                            activePort[port] = 1;
                        }
                    }
                }  
                else if (operator === 'greater') {
                    if (vehicleInputs[input] > parameter) {
                        if (configPropStates.vehicleOutputSettings[input].Function[0].ActivePorts[port] === 1) {
                            activePort[port] = 1;
                        }
                    }
                }   
            }
            // Active Lightbar configs
            for (let bar = 0; bar < LightBarConfigs.length; bar++) {
            
                for (let config = 0; config < LightBarConfigs[bar].length; config++) {

                    configsCondition = vehicleConfigs.LightBarConfigs[bar][config].length > 0;

                    if (configsCondition) {
                        
                        if (operator === 'equals') {
                            lightBarPattern = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];

                            if (vehicleInputs[input] === parameter) {

                                LightBarConfigs[bar][config] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarConfigs[bar][config];

                                for (let c = 0; c < configPropStates.vehicleOutputSettings[input].Function[0].LightBarConfigs[bar][config].length; c++) {
                                    if (configPropStates.vehicleOutputSettings[input].Function[0].LightBarConfigs[bar][config][c] === 'cutOff') {
                                        cutOffs[bar][config][c] = 'cutOff';
                                    }
                                }
                                current_state.IotStates["Lights"] = "On";
                            }
                            else {
                                if (lightBarPattern === 'Brake Pop') {
                                    LightBarConfigs[bar][config] = [];
                                }
                            }
                        }
                        else if (operator === 'lesser') {
                            lightBarPattern = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];

                            if (vehicleInputs[input] < parameter) {
            
                                LightBarConfigs[bar][config] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarConfigs[bar][config];

                                for (let c = 0; c < configPropStates.vehicleOutputSettings[input].Function[0].LightBarConfigs[bar][config].length; c++) {
                                    if (configPropStates.vehicleOutputSettings[input].Function[0].LightBarConfigs[bar][config][c] === 'cutOff') {
                                        cutOffs[bar][config][c] = 'cutOff';
                                    }
                                }
                                current_state.IotStates["Lights"] = "On";
                            }
                            else {
                                if (lightBarPattern === 'Brake Pop') {
                                    LightBarConfigs[bar][config] = [];
                                }
                            }
                        }
                        else if (operator === 'greater') {
                            lightBarPattern = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];

                            if (vehicleInputs[input] > parameter) {

                                LightBarConfigs[bar][config] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarConfigs[bar][config];


                                for (let c = 0; c < configPropStates.vehicleOutputSettings[input].Function[0].LightBarConfigs[bar][config].length; c++) {
                                    if (configPropStates.vehicleOutputSettings[input].Function[0].LightBarConfigs[bar][config][c] === 'cutOff') {
                                        cutOffs[bar][config][c] = 'cutOff';
                                    }
                                }
                                current_state.IotStates["Lights"] = "On";
                            }
                            else {
                                if (lightBarPattern === 'Brake Pop') {
                                    LightBarConfigs[bar][config] = [];
                                }
                            }
                        }
                    }
                }
            }
            // Active Lightbar patterns
            for (let bar = 0; bar < LightBarPatterns.length; bar++) {

                for (let config = 0; config < LightBarPatterns[bar].length; config++) {

                    patternCondition = vehicleConfigs.LightBarPatterns[bar][config].length > 0;

                    if (patternCondition) {
                        if (operator === 'equals') {
                            if (vehicleInputs[input] === parameter) {
                                lightBarPattern = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];

                                // console.log("This is the lightbar patterns: " + configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config]);
                                if (bar === 2 || bar === 11) {
                                    for (let c = 0; c < configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config].length; c++) {
                                        if (configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config][c] !== 'deSelect') {
                                            LightBarPatterns[bar][config][c] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];
                                        }
                                    }
                                }
                                else {
                                    LightBarPatterns[bar][config] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];
                                }
                            }
                            else {
                                if (lightBarPattern === 'Brake Pop') {
                                    LightBarPatterns[bar][config] = [];
                                }
                            }
                        }
                        else if (operator === 'lesser') {
                            if (vehicleInputs[input] < parameter) {
                                lightBarPattern = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];

                                // console.log("This is the lightbar patterns: " + configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config]);
                                if (bar === 2 || bar === 11) {
                                    for (let c = 0; c < configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config].length; c++) {
                                        if (configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config][c] !== 'deSelect') {
                                            LightBarPatterns[bar][config][c] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];

                                        }
                                    }
                                }
                                else {
                                    LightBarPatterns[bar][config] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];
                                }
                            }
                            else {
                                if (lightBarPattern === 'Brake Pop') {
                                    LightBarPatterns[bar][config] = [];
                                }
                            }
                        }
                        else if (operator === 'greater') {
                            if (vehicleInputs[input] > parameter) {
                                lightBarPattern = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];

                                // console.log("This is the lightbar patterns: " + configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config]);
                                if (bar === 2 || bar === 11) {
                                    for (let c = 0; c < configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config].length; c++) {
                                        if (configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config][c] !== 'deSelect') {
                                            LightBarPatterns[bar][config][c] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];
                                        }
                                    }
                                }
                                else {
                                    LightBarPatterns[bar][config] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarPatterns[bar][config];

                                    // if (bar === 0 || bar === 1) {
                                    //     if (LightBarPatterns[bar][config] === 'Left Turn' || LightBarPatterns[bar][config] === 'Right Turn') {
                                    //         turnActive = true;
                                    //     }
                                    // }
                                }
                            }
                            else {
                                if (lightBarPattern === 'Brake Pop') {
                                    LightBarPatterns[bar][config] = [];
                                }
                            }
                        }
                    }
                    // if (bar === 0 || bar === 1) {
                    //     if (LightBarPatterns[bar][config] === 'Left Turn' || LightBarPatterns[bar][config] === 'Right Turn') {
                    //         turnActive = true;
                    //     }
                    // }
                }
            }
            // Active Lightbar brightness
            for (let bar = 0; bar < LightBarBrightness.length; bar++) {
            
                for (let config = 0; config < LightBarBrightness[bar].length; config++) {

                    brightnessCondition = vehicleConfigs.LightBarBrightness[bar][config].length > 0;

                    if (brightnessCondition) {
                        if (operator === 'equals') {
                            if (vehicleInputs[input] === parameter) {
                                if (bar === 2 || bar === 11) {
                                    for (let c = 0; c < configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config].length; c++) {
                                        if (configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config][c] !== 'deSelect') {
                                            LightBarBrightness[bar][config][c] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config];
                                        }
                                    }
                                }
                                else {
                                    LightBarBrightness[bar][config] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config];
                                }
                            }
                            // else {
                            //     LightBarBrightness[bar][config] = [];
                            // }
                        }
                        else if (operator === 'lesser') {
                            if (vehicleInputs[input] < parameter) {
                                if (bar === 2 || bar === 11) {
                                    for (let c = 0; c < configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config].length; c++) {
                                        if (configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config][c] !== 'deSelect') {
                                            LightBarBrightness[bar][config][c] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config];
                                        }
                                    }
                                }
                                else {
                                    LightBarBrightness[bar][config] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config];
                                }
                            }
                            // else {
                            //     LightBarBrightness[bar][config] = [];
                            // }
                        }
                        else if (operator === 'greater') {
                            if (vehicleInputs[input] > parameter) {
                                if (bar === 2 || bar === 11) {
                                    for (let c = 0; c < configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config].length; c++) {
                                        if (configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config][c] !== 'deSelect') {
                                            LightBarBrightness[bar][config][c] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config];
                                        }
                                    }
                                }
                                else {
                                    LightBarBrightness[bar][config] = configPropStates.vehicleOutputSettings[input].Function[0].LightBarBrightness[bar][config];
                                }
                            }
                            // else {
                            //     LightBarBrightness[bar][config] = [];
                            // }
                        }
                    }
                }
            }
            // }
        }

        for (let relay = 0; relay < relaySelect.length; relay++) {

            // let continueTurn;
            let configsCondition;
            let patternCondition;
            let brightnessCondition;

            if (relaySelect[relay] < 8) {
                // DUAL DELAY OR RADIO
                if (configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].speaker.DualDelay === 1) {
                    dualDelay = 1;
                }
                if ((configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].speaker.ReBroadcast & 1) === 1) {
                    radioReBroadcast = 1;
                }
                else if ((configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].speaker.ReBroadcast & 2) === 2) {
                    parkKill = 1;
                }
                
                // Active Lightbar configs
                var relayConfigs = configPropStates.inputOutputSettings[relaySelect[relay]].Function[0];

                for (let bar = 0; bar < lightBar.length; bar++) {
                    if (configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBar[bar] === 1) {
                        lightBar[bar] = 1;
                    }
                }
                // Active siren configs
                for (let siren = 0; siren < siren1.length; siren++) {
                    if (configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].speaker.Speaker1[siren] === 1) {
                        siren1[siren] = 1;
                    }
                }
                for (let siren = 0; siren < siren2.length; siren++) {
                    if (configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].speaker.Speaker2[siren] === 1) {
                        siren2[siren] = 1;
                    }
                }
                for (let siren = 0; siren < siren3.length; siren++) {
                    if (configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].speaker.Audio[siren] === 1) {
                        siren3[siren] = 1;
                    }
                }
                // Active Ports configs
                for (let port = 0; port < activePort.length; port++) {
                    if (configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].ActivePorts[port] === 1) {
                        activePort[port] = 1;
                    }
                }
                // Active Lightbar configs
                for (let bar = 0; bar < LightBarConfigs.length; bar++) {

                    for (let config = 0; config < LightBarConfigs[bar].length; config++) {

                        if (localCopyProps.activeInput === 'relay') {
                
                            configsCondition = relayConfigs.LightBarConfigs[bar][config].length > 0;
                        }
                        else {
                            configsCondition = relayConfigs.LightBarConfigs[bar][config].length > 0 && relayConfigs.LightBarConfigs[bar][config].length === 0;
                        }
                        
                        if (configsCondition) {
                            current_state.IotStates["Lights"] = "On";

                            LightBarConfigs[bar][config] = configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarConfigs[bar][config];

                            for (let c = 0; c < configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarConfigs[bar][config].length; c++) {
                                if (configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarConfigs[bar][config][c] === 'cutOff') {
                                    cutOffs[bar][config][c] = 'cutOff';
                                }
                            }
                            // console.log("This is the lightbar config: " + configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarConfigs[bar][config]);
                        }
                    }
                }

                // Active Lightbar patterns
                for (let bar = 0; bar < LightBarPatterns.length; bar++) {

                    for (let config = 0; config < LightBarPatterns[bar].length; config++) {

                        if (localCopyProps.activeInput === 'relay') {
                
                            patternCondition = relayConfigs.LightBarPatterns[bar][config].length > 0;
                        }
                        else {
                            patternCondition = relayConfigs.LightBarPatterns[bar][config].length > 0 && relayConfigs.LightBarPatterns[bar][config].length === 0;
                        }
                        
                        if (patternCondition) {
                            if (bar === 2 || bar === 11) {
                                for (let c = 0; c < configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarPatterns[bar][config].length; c++) {
                                    if (configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarPatterns[bar][config][c] !== 'deSelect') {
                                        LightBarPatterns[bar][config][c] = configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarPatterns[bar][config];
                                    }
                                }
                            }
                            else {
                                LightBarPatterns[bar][config] = configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarPatterns[bar][config];
                            }
                        }
                        // if (bar === 0 || bar === 1) {
                        //     if (LightBarPatterns[bar][config] === 'Left Turn' || LightBarPatterns[bar][config] === 'Right Turn') {
                        //         turnActive = true;
                        //     }
                        // }
                    }
                }
                // Active Lightbar brightness
                for (let bar = 0; bar < LightBarBrightness.length; bar++) {

                    for (let config = 0; config < LightBarBrightness[bar].length; config++) {

                        if (localCopyProps.activeInput === 'relay') {
                
                            brightnessCondition = relayConfigs.LightBarBrightness[bar][config].length > 0;
                        }
                        else {
                            brightnessCondition = relayConfigs.LightBarBrightness[bar][config].length > 0 && relayConfigs.LightBarBrightness[bar][config].length === 0;
                        }
                        
                        if (brightnessCondition) {
                            if (bar === 2 || bar === 11) {
                                for (let c = 0; c < configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarBrightness[bar][config].length; c++) {
                                    if (configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarBrightness[bar][config][c] !== 'deSelect') {
                                        LightBarBrightness[bar][config][c] = configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarBrightness[bar][config];
                                    }
                                }
                            }
                            else {
                                LightBarBrightness[bar][config] = configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarBrightness[bar][config];
                            }
                            // console.log("This is the lightbar brightness: " + configPropStates.inputOutputSettings[relaySelect[relay]].Function[0].LightBarBrightness[bar][config]);
                        }
                    }
                }
            }
            else if (previousRelay.length > 0){
                
                // DETERMINES WHAT BUTTON WAS DESELECTED
                let difference = previousRelay.filter(x => !relaySelect.includes(x));

                // console.log("THis is the button / pre button:", difference[0]);
                if (difference[0] !== undefined) {
                    for (let bar = 0; bar < LightBarConfigs.length; bar++) {
                        for (let config = 0; config < LightBarConfigs[bar].length; config++) {
                            // console.log("Give me each length please: ", JSON.stringify(configPropStates.buttonOutputSettings[difference[0]].Function[multiFunction[difference[0]]].LightBarConfigs[bar][config]))
                            if (configPropStates.inputOutputSettings[difference[0]].Function[0].LightBarConfigs[bar][config].length > 0) {
                            
                                try {
                                    LightBarConfigs[bar][config] = [];
                                    LightBarBrightness[bar][config] = [];
                                    LightBarPatterns[bar][config] = [];
                                }
                                catch(e) {
                                    console.log("Caught error", e.message);
                                }
                            }
                        }
                    }
                }
            }
            if (JSON.stringify(previousRelay) !== JSON.stringify(relaySelect)) {
                previousRelay[relay] = relaySelect[relay];
            }
        }

        for (let button = 0; button < buttonStates.length; button++) {

            // let continueTurn;
            let configsCondition;
            let patternCondition;
            let brightnessCondition;
            let buttonConfigs = configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]];
            
            if (buttonStates[button] < 22) {

                // DUAL DELAY OR RADIO
                if (configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].speaker.DualDelay === 1) {
                    dualDelay = 1;
                }
                if ((configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].speaker.ReBroadcast & 1) === 1) {
                    radioReBroadcast = 1;
                }
                else if ((configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].speaker.ReBroadcast & 2) === 2) {
                    parkKill = 1;
                }

                // Active Lightbar configs
                for (let bar = 0; bar < lightBar.length; bar++) {
                    if (configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBar[bar] === 1) {
                        lightBar[bar] = 1;
                    }
                }
                // Active siren configs
                for (let siren = 0; siren < siren1.length; siren++) {
                    if (configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].speaker.Speaker1[siren] === 1) {
                        siren1[siren] = 1;
                    }
                }
                for (let siren = 0; siren < siren2.length; siren++) {
                    if (configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].speaker.Speaker2[siren] === 1) {
                        siren2[siren] = 1;
                    }
                }
                for (let siren = 0; siren < siren3.length; siren++) {
                    if (configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].speaker.Audio[siren] === 1) {
                        siren3[siren] = 1;
                    }
                }
                // Active Ports configs
                for (let port = 0; port < activePort.length; port++) {
                    if (configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].ActivePorts[port] === 1) {
                        activePort[port] = 1;
                    }
                }
                // Active Lightbar configs
                for (let bar = 0; bar < LightBarConfigs.length; bar++) {

                    for (let config = 0; config < LightBarConfigs[bar].length; config++) {

                        if (localCopyProps.activeInput === 'button') {
                
                            configsCondition = buttonConfigs.LightBarConfigs[bar][config].length > 0 && buttonConfigs.LightBarConfigs[bar][config].filter(x => x !== 'deSelect').length > 0;
                        }
                        else {
                            configsCondition = buttonConfigs.LightBarConfigs[bar][config].length > 0 && buttonConfigs.LightBarConfigs[bar][config].length === 0;
                        }
                        
                        if (configsCondition) {
                            current_state.IotStates["Lights"] = "On";
                            // console.log("This is the lightbar config: " + configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarConfigs[bar][config]);
                            for (let c = 0; c < configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarConfigs[bar][config].length; c++) {

                                if (configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarConfigs[bar][config][c] !== 'deSelect') {

                                    if (configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarConfigs[bar][config][c] === 'cutOff') {
                                        cutOffs[bar][config][c] = 'cutOff';
                                    }
                                    LightBarConfigs[bar][config][c] = configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarConfigs[bar][config][c];
                                }
                            }
                        }
                    }
                }
                // Active Lightbar patterns
                for (let bar = 0; bar < LightBarPatterns.length; bar++) {

                    for (let config = 0; config < LightBarPatterns[bar].length; config++) {

                        if (localCopyProps.activeInput === 'button') {
                
                            patternCondition = buttonConfigs.LightBarPatterns[bar][config].length > 0;
                        }
                        else {
                            patternCondition = buttonConfigs.LightBarPatterns[bar][config].length > 0 && buttonConfigs.LightBarPatterns[bar][config].length === 0;
                        }
                        
                        if (patternCondition) {
                            if (bar === 2 || bar === 11) {
                                for (let c = 0; c < configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarConfigs[bar][config].length; c++) {

                                    let qssmValue = configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarConfigs[bar][config][c];
                                    
                                    if (qssmValue !== 'deSelect' && qssmValue !== null) {
                                        LightBarPatterns[bar][config][c] = configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarPatterns[bar][config];
                                    }
                                }
                            }
                            else {
                                LightBarPatterns[bar][config] = configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarPatterns[bar][config];
                            }
                        }
                    }
                }
                // Active Lightbar brightness
                for (let bar = 0; bar < LightBarBrightness.length; bar++) {

                    for (let config = 0; config < LightBarBrightness[bar].length; config++) {

                        if (localCopyProps.activeInput === 'button') {
                
                            brightnessCondition = buttonConfigs.LightBarBrightness[bar][config].length > 0;
                        }
                        else {
                            brightnessCondition = buttonConfigs.LightBarBrightness[bar][config].length > 0 && buttonConfigs.LightBarBrightness[bar][config].length === 0;
                        }
                        
                        if (brightnessCondition) {
                            if (bar === 2 || bar === 11) {
                                for (let c = 0; c < configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarConfigs[bar][config].length; c++) {

                                    let qssmValue = configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarConfigs[bar][config][c];

                                    if (qssmValue !== 'deSelect' && qssmValue !== null) {
                                        LightBarBrightness[bar][config][c] = configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarBrightness[bar][config];
                                    }
                                }
                            }
                            else {
                                LightBarBrightness[bar][config] = configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[buttonStates[button]]].LightBarBrightness[bar][config];
                            }
                            // console.log("This is the lightbar brightness: " + configPropStates.buttonOutputSettings[buttonStates[button]].Function[multiFunction[button]].LightBarBrightness[bar][config]);
                        }
                    }
                }
            }
            else if (previousButton.length > 0){
                
                // DETERMINES WHAT BUTTON WAS DESELECTED
                let difference = previousButton.filter(x => !buttonStates.includes(x));

                // console.log("THis is the button / pre button:", difference[0]);
                if (difference[0] !== undefined) {
                    for (let bar = 0; bar < LightBarConfigs.length; bar++) {
                        for (let config = 0; config < LightBarConfigs[bar].length; config++) {
                            // for (let c = 0; c < configPropStates.buttonOutputSettings[difference[0]].Function[multiFunction[difference[0]]].LightBarConfigs[bar][config].length; c++) {
                                // LightBarConfigs[bar][config][c] = 0;
                            // console.log("Give me each length please: ", JSON.stringify(configPropStates.buttonOutputSettings[difference[0]].Function[multiFunction[difference[0]]].LightBarConfigs[bar][config]))
                            if (configPropStates.buttonOutputSettings[difference[0]].Function[multiFunction[difference[0]]].LightBarConfigs[bar][config].length > 0) {
                            
                                try {
                                    LightBarConfigs[bar][config] = [];
                                    LightBarBrightness[bar][config] = [];
                                    LightBarPatterns[bar][config] = [];
                                }
                                catch(e) {
                                    console.log("Caught error", e.message);
                                }
                            }
                        }
                    }
                }
            }

            // console.log("THis is the p[reviousB", JSON.stringify(previousButton))
            if (JSON.stringify( previousButton) !== JSON.stringify(buttonStates)) {
                previousButton[button] = buttonStates[button];
            }
        }

        if (localCopyProps.handsFreeState === 1) {
            siren1[0] = 1;
            siren2[0] = 1;
        }
        else if (localCopyProps.handsFreeState === 2) {
            siren1[1] = 1;
            siren2[1] = 1;
        }
        else if (localCopyProps.handsFreeState === 3) {
            siren1[3] = 1;
            siren2[3] = 1;
        }

        if (localCopyProps.output32Active) {
            activePort[31] = 1;
        }

        portBytes = BitBuild.byteArray(activePort);
        lightBarByte = BitBuild.lightBar(lightBar);
        highLowByte = BitBuild.byteArray(highLowActive);

        PacketBuild.siren1(siren1);
        PacketBuild.siren2(siren2);
        PacketBuild.siren3(siren3);
        PacketBuild.activePorts(portBytes);
        PacketBuild.lightBar(lightBarByte);
        PacketBuild.highLow(highLowByte);

        PacketBuild.powerState(powerState);
        PacketBuild.speakerEnable(speakerEnable);
        PacketBuild.screenBrightness(screenBrightness);
        PacketBuild.buttonColor(current_state.buttonColors, brightness);

        PacketBuild.dualDelay(dualDelay);
        PacketBuild.radioReBroadcast(radioReBroadcast);

        // CLEARS OUT ALL SIREN/AUDIO
        if (parkKill === 1) {
            PacketBuild.parkKill();
        }

        var ledPacket = PacketBuild.createPacket();

        if (localCopyProps.demoPattern) {
            ledConfigs[0] = [
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],"demo"],
                [[],[],[],[],[],[],[],[],[],["demo","demo","demo","demo","demo","demo","demo","demo","demo","demo","demo","demo","demo","demo","demo","demo"]],
                [[],[],[],[],[],[],[],[],[],"demo"],
                [[],[],[],[],[],[],[],[],[],"demo"],
                [[],[],[],[],[],[],[],[],[],"demo"],
                [[],[],[],[],[],[],[],[],[],"demo"],
                [[],[],[],[],[],[],[],[],[],"demo"],
                [[],[],[],[],[],[],[],[],[],"demo"],
                [[],[],[],[],[],[],[],[],[],"demo"],
                [[],[],[],[],[],[],[],[],[],"demo"],
                [[],[],[],[],[],[],[],[],[],["demo","demo","demo","demo","demo","demo"]]
            ];
            ledConfigs[1] = [
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],[]]
            ];
            ledConfigs[2] = [
                [[],[],[],[],[],[],[],[],[],[]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]],
                [[],[],[],[],[],[],[],[],[],["rbaw","rbaw","rbaw","rbaw","rbaw","rbaw"]]
            ];
        }
        else {

            // ADD ALL ACTIVE EVENT CUTOFFS
            // console.log("These are the configs before", JSON.stringify(LightBarConfigs))
            Configs.addCutOffs(cutOffs);
            // console.log("These are the configs after", JSON.stringify(LightBarConfigs))

            ledConfigs[0] = LightBarPatterns;
            ledConfigs[1] = LightBarBrightness;
            ledConfigs[2] = LightBarConfigs;
        }
        // SETS SURFACE MOUNT ZONES
        if (localCopyProps.surfaceZones) {
            SMZone[0] = localCopyProps.SmZoneState;
            SMZone[1] = true;
            SMZone[2] = localCopyProps.SMOPacket;
            ledConfigs[3] = SMZone;
        }
        else {
            SMZone[0] = 0;
            SMZone[1] = false;
            ledConfigs[3] = SMZone;
        }

        // REMOVE TURN CONFIGS IF FORNT OR REAR CONFIGS PRESENT
        // for (let bar = 0; bar < LightBarConfigs.length; bar++) {
        //     if ((LightBarConfigs[bar][2].length || LightBarConfigs[bar][3].length) && (LightBarConfigs[bar][6].length || LightBarConfigs[bar][7].length)) {
        //         try {
        //             LightBarConfigs[bar][6] = [];
        //             LightBarBrightness[bar][6] = [];
        //             LightBarPatterns[bar][6] = [];

        //             LightBarConfigs[bar][7] = [];
        //             LightBarBrightness[bar][7] = [];
        //             LightBarPatterns[bar][7] = [];
        //         }
        //         catch(e) {
        //             console.log("Caught error", e.message);
        //         }
        //     }
        // }

        // CHECK SIRENS ACTIVE
        if (siren1.filter(x => x === 1).length > 0  || siren2.filter(x => x === 1).length > 0 || siren3.filter(x => x === 1).length > 0) {
            current_state.IotStates["Siren"] = "On";
        }
        else {
            current_state.IotStates["Siren"] = "Off";
        }
        // CHECK LIGHTS ACTIVE
        if (lightBar.filter(x => x === 1).length > 0) {
            current_state.IotStates["Lights"] = "On";
        }

        props.setConfigState(ledPacket, ledConfigs, current_state.IotStates);

        return current_state;
    }

    render() {

        if (this.props.debugData !== '') {
            return (
                <div>
                    Debug Data: {this.props.debugData}
                </div>
            )
        }
        else {
            return (
                <div>
                </div>
            );
        }
    }
}