import React, { Component } from "react";
import Slider from 'rc-slider';

import './../css/components.css';
import './../css/brightness.css';

// const oneImg = require(`../images/Group40.png`);
const down = require(`../images/Minus-icon.svg`);
const up = require(`../images/Plus-icon.svg`);

var prevButtonValue;
var screenCounter = 0;

// const sliderStyle = { width: 400, margin: 50 };
// const Handle = Slider.Handle;

// const handle = (props) => {
//     const { value, dragging, index, ...restProps } = props;
//     return (
//       <Tooltip
//         prefixCls="rc-slider-tooltip"
//         overlay={value}
//         visible={dragging}
//         placement="top"
//         key={index}
//       >
//         <Handle value={value} {...restProps} />
//       </Tooltip>
//     );
// };

export class Brightness extends Component {
    constructor(props) {
        super(props);
        this.state = {
            // buttons: buttonData,
            screenValue: 50,
            buttonValue: 1,
            volumeValue: 100
        };
    }

    static getDerivedStateFromProps(props, current_state) {

        current_state.screenValue = props.parentState.screenBrightness;
        current_state.volumeValue = props.parentState.volumeBrightness;
        current_state.buttonValue = props.parentState.setBrightness;

        return current_state;
    }

    screenSliderChange = screenValue => {
        // console.log("Brightness value: " + screenValue);
        this.setState({ screenValue:  screenValue});

        this.props.updateBrightness('screen', screenValue);
    };

    volumeSliderChange = volumeValue => {
        // console.log("Brightness value: " + screenValue);
        this.setState({ volumeValue:  volumeValue});

        this.props.updateBrightness('volume', volumeValue);
    };

    buttonSliderChange = buttonValue => {
        // console.log("Brightness2 value: " + buttonValue);

        // console.log("Brightness2 previous value: " + prevButtonValue);

        if (prevButtonValue < buttonValue) {
            if (buttonValue === 5) {
                if (screenCounter < 5) {
                    buttonValue = 1;
                    screenCounter++;
                }
                else {
                    screenCounter = 0;
                }
            }
        }
        else if (prevButtonValue > buttonValue) {
            if (buttonValue === 0) {
                if (screenCounter < 5) {
                    buttonValue = 1;
                    screenCounter++;
                }
                else {
                    buttonValue = 0;
                    screenCounter = 0;
                }
            }
        }

        prevButtonValue = buttonValue;

        this.setState({ buttonValue: buttonValue });



        this.props.updateBrightness('button', buttonValue);
    };

    ScreenBrightness(value) {
        
        let screen = this.state.screenValue;

        if (value === 1) {
            if (screen !== 100) {
                screen += 10
                // this.setState({ screenValue: screen });
            }
            else if (screen > 100) {
                screen = 100;
            }
        } else {
            if (screen !== 0) {
                screen -= 10
            }
        }
        this.setState({ screenValue: screen });
        this.props.updateBrightness('screen', screen);
    }

    VolumeBrightness(value) {
        
        let volume = this.state.volumeValue;

        if (value === 1) {
            if (volume !== 100) {
                volume += 5
                this.setState({ volumeValue: volume });
            }
        } else {
            if (volume !== 0) {
                volume -= 5
            }
        }
        this.setState({ volumeValue: volume });
        this.props.updateBrightness('volume', volume);
    }
    
    ButtonBrightness(value) {
        
        let button = this.state.buttonValue;

        if (value === 1) {
            // if (button === 0)
            if (button === 0) {
                button = 1;
            }
            else if (button === 26) {
                button = 30;
            }
            else if (button < 30) {
                button += 5;
            }
        } else {
            if (button > 1) {
                button -= 5
            }
            else if (button === 1) {
                button = 0;
            }
        }
        this.setState({ buttonValue: button });
        this.props.updateBrightness('button', button);
    }

    render() {
        return (
            <div>
                <div id="brightness">
                    <p id="screenText">Screen</p>

                    <button type="button" className="minusBtn" onClick={(e) => { this.ScreenBrightness(0); }}>
                        <img className="minus" src={down} alt="img" />
                    </button>

                    <Slider min={0} max={100} step={10} defaultValue={50} value={this.state.screenValue} onChange={this.screenSliderChange}
                        railStyle={{
                            height: 2
                        }}
                        handleStyle={{
                            height: 17,
                            width: 17,
                            marginTop: -9,
                            backgroundColor: "white",
                            border: 0
                        }}
                        trackStyle={{
                            background: "none"
                        }}
                    />

                    <button type="button" className="plusBtn" onClick={(e) => { this.ScreenBrightness(1); }}>
                        <img className="plus" src={up} alt="img" />
                    </button>

                    <p id="buttonsText">Buttons</p>

                    <button type="button" className="minusBtn" onClick={(e) => { this.ButtonBrightness(0); }}>
                        <img className="minus" src={down} alt="img" />
                    </button>

                    <Slider min={0} max={30} step={5} defaultValue={1} value={this.state.buttonValue} onChange={this.buttonSliderChange}
                        railStyle={{
                            height: 2
                        }}
                        handleStyle={{
                            height: 17,
                            width: 17,
                            marginTop: -9,
                            backgroundColor: "white",
                            border: 0
                        }}
                        trackStyle={{
                            background: "none"
                        }}
                    />

                    <button type="button" className="plusBtn" onClick={(e) => { this.ButtonBrightness(1); }}>
                        <img className="plus" src={up} alt="img" />
                    </button>

                    <p id="volumeText">Button Volume</p>

                    <button type="button" className="minusBtn" onClick={(e) => { this.VolumeBrightness(0); }}>
                        <img className="minus" src={down} alt="img" />
                    </button>

                    <Slider min={0} max={100} step={5} defaultValue={1} value={this.state.volumeValue} onChange={this.volumeSliderChange}
                        railStyle={{
                            height: 2
                        }}
                        handleStyle={{
                            height: 17,
                            width: 17,
                            marginTop: -9,
                            backgroundColor: "white",
                            border: 0
                        }}
                        trackStyle={{
                            background: "none"
                        }}
                    />

                    <button type="button" className="plusBtn" onClick={(e) => { this.VolumeBrightness(1); }}>
                        <img className="plus" src={up} alt="img" />
                    </button>

                    <a className="backButton" onClick={(e) => { this.props.updateScreen('home') }}>BACK</a>
                </div>
            </div>
        );
    }
}