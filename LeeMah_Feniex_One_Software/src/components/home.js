import React, { Component } from "react";
import './../css/components.css';
import './../css/home.css';
import './../css/home2.css';

const light = require(`../images/Amp-icon.svg`);
// const temp = require(`../images/Temperature-icon.svg`);
const batt = require(`../images/Battery-icon.svg`);
const car = require(`../images/Car-icon.svg`);

const visiblityTrue = { display: "block" };
const visiblityFalse = { display: "none" };

const buttonSet = { backgroundImage: 'linear-gradient(#034b3b, #034b3b)', border: '2px solid #72e2ca' };
const buttonActive = { backgroundImage: 'linear-gradient(#034b3b, #034b3b)', border: '2px solid #065745' };

const Red = { backgroundImage: 'linear-gradient(red, red)', border: '2px solid red' };
const Blue = { backgroundImage: 'linear-gradient(blue, blue)', border: '2px solid blue' };
const Green = { backgroundImage: 'linear-gradient(green, green)', border: '2px solid green' };
const Purple = { backgroundImage: 'linear-gradient(purple, purple)', border: '2px solid purple' };
const Yellow = { backgroundImage: 'linear-gradient(yellow, yellow)', border: '2px solid yellow' };
const White = { backgroundImage: 'linear-gradient(white, white)', border: '2px solid white' };

// const background = { background: '#000000', height: '240px' };

var relay1OutputCurrent;
var relay2OutputCurrent;
var relay3OutputCurrent;
var relay4OutputCurrent;

var previousScroll;
var toggle;
var home = 1;
var setHome = true;

var buttonCounter = [1, 1, 1];
var previousButton;
var buttonEnabled = true;
// var allowMomentary = false;

var buttonTimer = [];
var buttonTime = [];
var buttonTimeout = [];
var setTime;

export class Home extends Component {
    constructor(props) {
        super(props);
        this.state = {
            buttonColors: [buttonSet, buttonSet, buttonSet],
            multiFunction: [0, 0, 0],
            brightness: [1, 1, 1],
            playing: false,
            activeplay: false,
            batterVoltage: 0,
            relayCurrent: 0,
            hideHome: [visiblityTrue, visiblityFalse, visiblityTrue, visiblityFalse, visiblityTrue, visiblityFalse]
        }
        // this.handleScroll = this.handleScroll.bind(this);
    }

    componentDidUpdate() {
        let homeScreen = this.props.parentState.homeScreen;
        var homeElmnt;

        if (homeScreen !== 0 && setHome) {
            if (homeScreen === 1) {
                homeElmnt = document.getElementById("home");
                homeElmnt.scrollIntoView();
            }
            else {
                homeElmnt = document.getElementById("home2");
                homeElmnt.scrollIntoView();
            }
            setHome = false;
        }
    }

    static getDerivedStateFromProps(props, current_state) {

        var configPropStates = props.configStates;

        current_state.batterVoltage = props.parentState.versions[0] / 10;

        relay1OutputCurrent = props.parentState.versions[12] / 10;
        relay2OutputCurrent = props.parentState.versions[13] / 10;
        relay3OutputCurrent = props.parentState.versions[14] / 10;
        relay4OutputCurrent = props.parentState.versions[15] / 10;

        if (Number.isFinite(relay1OutputCurrent) && Number.isFinite(relay2OutputCurrent) && Number.isFinite(relay3OutputCurrent) && Number.isFinite(relay4OutputCurrent)) {
            current_state.relayCurrent = (relay1OutputCurrent + relay2OutputCurrent + relay3OutputCurrent + relay4OutputCurrent);
        }

        if (props.parentState.buttonEnabled === false) {
            current_state.buttonColors = [buttonSet, buttonSet, buttonSet];
            buttonCounter = [1, 1, 1];
            buttonEnabled = false;
        }
        else {
            buttonEnabled = true;
        }

        if (configPropStates.buttonOutputSettings[16].ButtonType === "Momentary"){
            current_state.hideHome[0] = visiblityFalse;
            current_state.hideHome[1] = visiblityTrue;
        }
        else {
            current_state.hideHome[0] = visiblityTrue;
            current_state.hideHome[1] = visiblityFalse;
        }

        if (configPropStates.buttonOutputSettings[17].ButtonType === "Momentary"){
            current_state.hideHome[2] = visiblityFalse;
            current_state.hideHome[3] = visiblityTrue;
        }
        else {
            current_state.hideHome[2] = visiblityTrue;
            current_state.hideHome[3] = visiblityFalse;
        }

        if (configPropStates.buttonOutputSettings[18].ButtonType === "Momentary"){
            current_state.hideHome[4] = visiblityFalse;
            current_state.hideHome[5] = visiblityTrue;
        }
        else {
            current_state.hideHome[4] = visiblityTrue;
            current_state.hideHome[5] = visiblityFalse;
        }

        return current_state;
    }
    
    buttonSelected(event, buttonNumber, button) {

        var localState = JSON.parse(JSON.stringify(this.state));
        var setBrightness = this.props.parentState.setBrightness;

        var configPropStates = this.props.configStates;
        var timeOut = configPropStates.buttonOutputSettings[button].ButtonTimerValue;
        
        var buttonColors = configPropStates.ButtonBackgroundColor;
        var multiColors1 = configPropStates.MultiButtonBackgroundColor1;
        var multiColors2 = configPropStates.MultiButtonBackgroundColor2;
        var multiColors3 = configPropStates.MultiButtonBackgroundColor3;

        var brighter = 0;

        toggle = configPropStates.buttonOutputSettings[button].ButtonType

        if (setBrightness < 10) {
            brighter = 40;
        }
        else {
            brighter = 70;
        }

        if (event !== 'timeout') {
            setTime = true;
        }
        else {
            setTime = false;
        }

        if (buttonEnabled) {
    
            if (previousButton === buttonNumber) {
                if (configPropStates.buttonOutputSettings[button].NumberOfFunctions === 0 && buttonCounter[buttonNumber] === 2) {
                    buttonCounter[buttonNumber] = 5;
                }
                else if (configPropStates.buttonOutputSettings[button].NumberOfFunctions === 2 && buttonCounter[buttonNumber] === 3) {
                    buttonCounter[buttonNumber] = 5;
                }
                else if (configPropStates.buttonOutputSettings[button].NumberOfFunctions === 3 && buttonCounter[buttonNumber] === 4) {
                    buttonCounter[buttonNumber] = 5;
                }
            }
            else {
                if (JSON.stringify(localState.brightness[buttonNumber]) > setBrightness) {
                    buttonCounter[buttonNumber] = 5;
                }
                else {
                    buttonCounter[buttonNumber] = 1;
                }
            }
            // Sets multi config index for config interation
            if (buttonCounter[buttonNumber] === 1) {
                localState.brightness[buttonNumber] = (setBrightness + brighter);
                localState.buttonColors[buttonNumber] = setColor(buttonColors[button]);
            }
            else if (buttonCounter[buttonNumber] === 2) {
                localState.brightness[buttonNumber] = (setBrightness + brighter);
                localState.buttonColors[buttonNumber] = setColor(multiColors1[button]);
            }
            else if (buttonCounter[buttonNumber] === 3) {
                localState.brightness[buttonNumber] = (setBrightness + brighter);
                localState.buttonColors[buttonNumber] = setColor(multiColors2[button]);
            }
            else if (buttonCounter[buttonNumber] === 4) {
                localState.brightness[buttonNumber] = (setBrightness + brighter);
                localState.buttonColors[buttonNumber] = setColor(multiColors3[button]);
            }
            else if (buttonCounter[buttonNumber] === 5) {
                localState.brightness[buttonNumber] = setBrightness;
                localState.buttonColors[buttonNumber] = buttonSet;
                buttonCounter[buttonNumber] = 0;
            }
            // Handles button timeouts
            if (toggle === 'Timer') {
                for (let t = 0; t < buttonTimer.length; t++) {
    
                    if (buttonTimer[t] === buttonNumber) {
    
                        localState.buttonColors[buttonNumber] = buttonSet;
                        localState.brightness[buttonNumber] = setBrightness;
                        clearTimeout(buttonTimeout[t]);
                        buttonTimeout.splice(t, 1);
                        buttonTimer.splice(t, 1);
                        buttonTime.splice(t, 1);
                        setTime = false;
                    }
                }
                if (setTime) {
                    buttonTimer.push(buttonNumber);
                    buttonTime.push(timeOut);
                
                    for (let t = 0; t < buttonTimer.length; t++) {
                        if (buttonTimer[t] === buttonNumber) {
                            buttonTimeout[t] = setTimeout(function(){
                                localState = JSON.parse(JSON.stringify(this.state));
                                localState.buttonColors[buttonTimer[t]] = buttonSet;
                                localState.brightness[buttonTimer[t]] = setBrightness;
                                buttonCounter[buttonTimer[t]] = 2;
                                //  made switch to counter 2
                                // buttonCounter = 2;
                                buttonTimeout.splice(t, 1);
                                buttonTimer.splice(t, 1);
                                buttonTime.splice(t, 1);
                                this.buttonSelected('timeout', buttonNumber, buttonNumber + 16);
                                previousButton = buttonTimer[t];
                            }.bind(this), (buttonTime[t] * 1000));
                        }
                    }              
                }
            }
            buttonCounter[buttonNumber] = buttonCounter[buttonNumber] + 1;
            previousButton = buttonNumber;

            let ledButton = [];
            ledButton.push(button);

            this.props.handleInputData('', ledButton, this.props.relayPress, '', true);

            this.setState(localState);

            // if (event !== 'timeout') {
            //     this.setState(localState);
            // }
        }
    }

    momentaryButtons(buttonNumber, button) {

        var localState = JSON.parse(JSON.stringify(this.state));
        var configPropStates = this.props.configStates;

        toggle = configPropStates.buttonOutputSettings[button].ButtonType;

        if (toggle === 'Momentary') {

            localState.buttonColors[buttonNumber] = buttonSet;
            localState.brightness[buttonNumber] = 1;
            localState.playing = true;
            buttonCounter[buttonNumber] = 1;

            this.props.momentaryButtonData('', button);
            this.setState(localState);
        }
    }

    handleScroll(e) {
        let element = e.target

        if (element.scrollLeft < previousScroll) {
            this.props.handleScroll('left');
            home = 1;
        }
        else {
            this.props.handleScroll('right');
            home = 2;
        }
        previousScroll = element.scrollLeft;

        this.props.handleHome(home);
    }

    render() {
      
        return (
            <div onScroll={this.handleScroll.bind(this)} id="homeContainer">
                <div id="home">
                    <div id="car">
                        <img src={car} alt="img" />
                        <div className="sidebar">
                            <img id="battery" src={batt} alt="battery" />
                            <p id="voltage">{this.state.batterVoltage}<span>V</span></p>
                            {/* <p id="voltage">{this.state.voltage}<span>V</span></p> */}
                            {/* <img id="tempGauge" src={temp} alt="temperature" />
                            <p id="temp">{this.props.parentState.tempState}<span>{'\u2109'}</span></p> */}
                            <img id="lightning" src={light} alt="lightning" />
                            <p id="amp">{this.state.relayCurrent}<span>AMP</span></p>
                        </div>
                    </div>
                </div>
                <div id="home2">
                    <div id="homeButtons">

                        <div id="button0" style={{ ...this.state.hideHome[0], ...this.state.buttonColors[0] }} onClick={(e, button, buttonSleected) => this.buttonSelected('', 0, 16) }>
                            <p>{this.props.configStates.buttonOutputSettings[16].UserName}</p>
                        </div>
                        <div id="button0" style={{ ...this.state.hideHome[1], ...this.state.buttonColors[0] }}  onTouchStart={(e, button, buttonSleected) => this.buttonSelected('', 0, 16) } onTouchEnd={(e) => this.momentaryButtons(0, 16) }>
                            <p>{this.props.configStates.buttonOutputSettings[16].UserName}</p>
                        </div>

                        <div id="button1" style={{ ...this.state.hideHome[2], ...this.state.buttonColors[1] }}  onClick={(e, button, buttonSleected) => this.buttonSelected('', 1, 17) }>
                            <p>{this.props.configStates.buttonOutputSettings[17].UserName}</p>
                        </div>
                        <div id="button1" style={{ ...this.state.hideHome[3], ...this.state.buttonColors[1] }}  onTouchStart={(e, button, buttonSleected) => this.buttonSelected('', 1, 17) } onTouchEnd={(e) => this.momentaryButtons(1, 17) }>
                            <p>{this.props.configStates.buttonOutputSettings[17].UserName}</p>
                        </div>

                        <div id="button2" style={{ ...this.state.hideHome[4], ...this.state.buttonColors[2] }}  onClick={(e, button, buttonSleected) => this.buttonSelected('', 2, 18) }>
                            <p>{this.props.configStates.buttonOutputSettings[18].UserName}</p>
                        </div>
                        <div id="button2" style={{ ...this.state.hideHome[5], ...this.state.buttonColors[2] }}  onTouchStart={(e, button, buttonSleected) => this.buttonSelected('', 2, 18) } onTouchEnd={(e) => this.momentaryButtons(2, 18) }>
                            <p>{this.props.configStates.buttonOutputSettings[18].UserName}</p>
                        </div>

                    </div>
                </div>
            </div>
        );
    }
}

function setColor(colorString) {
    if (colorString === 'Red') {
        return Red;
    }
    else if (colorString === 'Red') {
        return Red;
    }
    else if (colorString === 'Green') {
        return Green;
    }
    else if (colorString === 'Blue') {
        return Blue;
    }
    else if (colorString === 'Yellow') {
        return Yellow;
    }
    else if (colorString === 'Purple') {
        return Purple;
    }
    else if (colorString === 'White') {
        return White;
    }
    else {
        return buttonActive;
    }
}