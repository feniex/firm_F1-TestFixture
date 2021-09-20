import React, { Component } from "react";
import { JsonToTable } from "react-json-to-table";
import './../css/components.css';
import './../css/info.css';

const ampImage = require(`../images/warning.png`);

const buttonSet = { backgroundImage: 'linear-gradient(#034b3b, #034b3b)', border: '2px solid #72e2ca' };
const buttonActive = { backgroundImage: 'linear-gradient(#034b3b, #034b3b)', border: '2px solid #065745' };

const visibilityTrue = { display: "block" };
const visibilityFalse = { display: "none" };
const ampWhite = { color: "white" };
const ampRed = { color: "red" };

const startPressed = { backgroundImage: 'linear-gradient(#034b3b, #034b3b)', border: '2px solid #065745' };

var setActiveBeep = true;

export class Info extends Component {
    constructor(props) {
        super(props);
        this.state = {
            // buttons: buttonData,
            buttonColors: [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet],
            buttonColors2: [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet],
            tab: 'sys',
            run: true,
            macAddress: '',
            voltage: 0,
            threeSenser: 0,
            fiveSenser: 0,
            speaker1Curr: 0,
            speaker2Curr: 0,
            batterVoltage: 0,
            relay1OutputCurrent: 0,
            relay2OutputCurrent: 0,
            relay3OutputCurrent: 0,
            relay4OutputCurrent: 0,
            currentOverage: [ampWhite, ampWhite, ampWhite, ampWhite],
            ampOverageImg: [visibilityFalse, visibilityFalse, visibilityFalse, visibilityFalse],
            hideInfo: visibilityTrue,
            hideInfo2: visibilityTrue,
            hideOBD: visibilityFalse,
            surfaceZoneStart: false,
            surfaceZoneStart2: false,
            surfaceZoneDisplay: [visibilityTrue, visibilityFalse],
            surfaceZoneDisplay2: [visibilityTrue, visibilityFalse],
            obdData: {},
            showInfo: [visibilityTrue, visibilityFalse]
        };
        this.myChangeHandler = this.myChangeHandler.bind(this);       
    }

    static getDerivedStateFromProps(props, current_state) {

        current_state.batterVoltage = props.parentState.versions[0] / 10;
        current_state.relay1OutputCurrent = props.parentState.versions[12] / 10;
        current_state.relay2OutputCurrent = props.parentState.versions[13] / 10;
        current_state.relay3OutputCurrent = props.parentState.versions[14] / 10;
        current_state.relay4OutputCurrent = props.parentState.versions[15] / 10;

        // current_state.relay1OutputCurrent = 13;
        // current_state.relay2OutputCurrent = 13;
        // current_state.relay3OutputCurrent = 13;
        // current_state.relay4OutputCurren = 13;

        if (current_state.relay1OutputCurrent > 12) {
            current_state.currentOverage[0] = ampRed;
            current_state.ampOverageImg[0] = visibilityTrue;
        }
        else {
            current_state.currentOverage[0] = ampWhite;
            current_state.ampOverageImg[0] = visibilityFalse;
        }

        if (current_state.relay2OutputCurrent > 12) {
            current_state.currentOverage[1] = ampRed;
            current_state.ampOverageImg[1] = visibilityTrue;
        }
        else {
            current_state.currentOverage[1] = ampWhite;
            current_state.ampOverageImg[1] = visibilityFalse;
        }

        if (current_state.relay3OutputCurrent > 12) {
            current_state.currentOverage[2] = ampRed;
            current_state.ampOverageImg[2] = visibilityTrue;
        }
        else {
            current_state.currentOverage[2] = ampWhite;
            current_state.ampOverageImg[2] = visibilityFalse;
        }

        if (current_state.relay4OutputCurrent > 12) {
            current_state.currentOverage[3] = ampRed;
            current_state.ampOverageImg[3] = visibilityTrue;
        }
        else {
            current_state.currentOverage[3] = ampWhite;
            current_state.ampOverageImg[3] = visibilityFalse;
        }

        // SETS DEFAULT ACTIVE BEEP BUTTON / MUST USE JS SINCE VALUE COMES IN TO LATE FROM ELECTRON FILE READ TO SET A defaultChecked ATTRIBUTE
        // UsING checked ATTRIBURE LOCKS CHKED STATE WITH VARIABLE VALURE WHEN USING onChange input event
        if (props.parentState.brightsSet === 1 && setActiveBeep) {
            setActiveBeep = false;
            if (props.parentState.activeBeep === 1) {
                document.getElementById("ABChecked").checked = true;
            }
            else {
                document.getElementById("ABChecked").checked = false;
            }
        }

        // SHOWS QSM ZONE
        if (props.parentState.showInfo12) {
            current_state.showInfo[0] = visibilityFalse;
            current_state.showInfo[1] = visibilityTrue;
        }
        else {
            // current_state.showInfo[0] = visibilityFalse;
            // current_state.showInfo[1] = visibilityTrue;
            current_state.showInfo[0] = visibilityTrue;
            current_state.showInfo[1] = visibilityFalse;
        }

        // SHOWS OBD LOG INFO
        if (props.parentState.showOBD) {
            current_state.hideOBD = visibilityTrue;
        }
        else {
            current_state.hideOBD = visibilityFalse;
        }

        // SHOWS OBD LOG DATA AS TABLE DATA
        try {
            current_state.obdData = JSON.parse(props.parentState.obdData);
        } catch (e) {
            ;
        }

        // HIDES SET ZONES WHEN ANY BUTTON IS PRESSED AND surfaceZones IS SET TO FALSE
        if (props.parentState.surfaceZones === false && (current_state.hideInfo.display === visibilityFalse.display || current_state.hideInfo2.display === visibilityFalse.display)) {
            
            current_state.surfaceZoneStart = false;
            current_state.surfaceZoneStart2 = false;

            current_state.buttonColors = [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet];
            current_state.buttonColors2 = [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet];

            current_state.hideInfo2 = visibilityTrue;
            current_state.hideInfo = visibilityTrue;

            current_state.surfaceZoneDisplay[0] = visibilityTrue;
            current_state.surfaceZoneDisplay[1] = visibilityFalse;

            current_state.surfaceZoneDisplay2[0] = visibilityTrue;
            current_state.surfaceZoneDisplay2[1] = visibilityFalse;
        }
        
        return current_state;
    }

    // componentDidUpdate() {
    //     var info2 = document.querySelector('.zoneInfo');
    //     var rect = info2.getBoundingClientRect();
    //     var infoBlock;

    //     document.addEventListener('scroll', function () {

    //         infoBlock = 
    //             rect.top >= 0 &&
    //             rect.right >= 0 &&
    //             rect.bottom <= (window.innerHeight || document.documentElement.clientHeight) &&
    //             rect.right <= (window.innerWidth || document.documentElement.clientWidth)
    //         ;

    //         if (infoBlock) {
    //             console.log("Info 2 is visible");
    //             // window.scrollTo(0, 0);
    //         }
    //         else {
    //             console.log("Info 2 is not visible");
    //         }
    //     });
    // }

    scrollToId(elementId) {
        let element = document.getElementById(elementId);
        element.scrollIntoView();
    }

    myChangeHandler(event) {

        var activeBeep = event.target.checked;
        this.props.updateActiveBeep(activeBeep);
    }

    buttonSelected(button) {

        var localState = JSON.parse(JSON.stringify(this.state));

        localState.buttonColors = [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet];

        localState.buttonColors[button] = buttonActive;

        this.setState(localState, () => { this.props.setSurfaceZones(localState) });
    }

    buttonSelected2(button) {

        var localState = JSON.parse(JSON.stringify(this.state));

        localState.buttonColors2 = [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet];

        localState.buttonColors2[button] = buttonActive;

        this.setState(localState, () => { this.props.setSurfaceZones2(localState) });
    }

    startStopZones(zone) {

        var localState = JSON.parse(JSON.stringify(this.state));

        if (zone === 'start') {
            localState.surfaceZoneStart = true;
            localState.surfaceZoneDisplay[0] = startPressed;
            
            setTimeout(function() {
                localState.surfaceZoneDisplay[0] = visibilityFalse;
                localState.surfaceZoneDisplay[1] = visibilityTrue;
                localState.hideInfo = visibilityFalse;
                this.setState(localState, () => { this.props.setSurfaceZones(localState) });
            }.bind(this), 2000);

            localState.surfaceZoneDisplay2[0] = visibilityTrue;
            localState.surfaceZoneDisplay2[1] = visibilityFalse;
            localState.hideInfo2 = visibilityTrue;
            localState.buttonColors2 = [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet];
        }
        else {
            localState.surfaceZoneStart = false;
            localState.buttonColors = [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet];
            localState.surfaceZoneDisplay[0] = visibilityTrue;
            localState.surfaceZoneDisplay[1] = visibilityFalse;
            localState.hideInfo = visibilityTrue;
        }
        this.setState(localState, () => { this.props.setSurfaceZones(localState) });
    }

    startStopZones2(zone) {

        var localState = JSON.parse(JSON.stringify(this.state));

        if (zone === 'start') {
            localState.surfaceZoneStart2 = true;
            localState.surfaceZoneDisplay2[0] = startPressed;
            
            setTimeout(function() {
                localState.surfaceZoneDisplay2[0] = visibilityFalse;
                localState.surfaceZoneDisplay2[1] = visibilityTrue;
                localState.hideInfo2 = visibilityFalse;
                this.setState(localState, () => { this.props.setSurfaceZones2(localState) });
            }.bind(this), 2000);

            localState.surfaceZoneDisplay[0] = visibilityTrue;
            localState.surfaceZoneDisplay[1] = visibilityFalse;
            localState.hideInfo = visibilityTrue;
            localState.buttonColors = [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet];

        }
        else {
            localState.surfaceZoneStart2 = false;
            localState.buttonColors2 = [buttonSet, buttonSet, buttonSet, buttonSet, buttonSet, buttonSet];
            localState.surfaceZoneDisplay2[0] = visibilityTrue;
            localState.surfaceZoneDisplay2[1] = visibilityFalse;
            localState.hideInfo2 = visibilityTrue;
        }
        this.setState(localState, () => { this.props.setSurfaceZones2(localState) });
    }

    render() {
        return (
            <div id="infoContainer">
                <div id="info" style={this.state.showInfo[0]}>
                    {/* <button type="button" id="sysButton" onClick={() => { this.scrollToId('sysInfo'); }}>SYSTEM INFORMATION</button>
                    <button type="button" id="vehButton" onClick={() => { this.scrollToId('vehInfo'); }}>VEHICAL INFORMATION</button> */}

                    <h4>SYSTEM INFORMATION</h4>
                    <table id="sysInfo">
                        <tbody>
                            <tr id="notification" className="row2 hidden">
                                <td className="labelInfo">Update Available</td>
                                <td id="RV2"><button id="restart-button" onClick={(e) => this.props.restartApp()}>Update Now</button></td>
                            </tr>
                            <tr className="row2">
                                <td className="labelInfo">Active Beep</td>
                                <td id="RV2">
                                    <form id="active-beep">
                                        <span>Off</span>

                                        <label className="switch">
                                            <input
                                                id="ABChecked"
                                                className='checkbox'
                                                type='checkbox'
                                                name='activeButton'
                                                onChange={this.myChangeHandler}
                                                // onClick={this.myChangeHandler}
                                            />
                                            <span className="slider round"></span>
                                        </label>
        
                                        <span>On</span>
                                    </form>
                                </td>
                            </tr>
                            <tr className="row2">
                                <td className="labelInfo">Controller ID</td>
                                <td id="RV2">{this.props.macAddress}</td>
                            </tr>
                            <tr className="row2">
                                <td className="labelInfo">Battery Voltage</td>
                                <td id="RV2">{this.state.batterVoltage} V</td>
                            </tr>
                            <tr className="row4">
                                <td className="labelInfo">Software Version</td>
                                <td className="DeviceVersionStatusText">{this.props.parentState.packageJson.version} Beta</td>
                            </tr>
                            <tr className="row5">
                                <td className="labelInfo">Controller Firmware Version</td>
                                <td className="FV2">{this.props.parentState.versions[3]}.{this.props.parentState.versions[4]}.{this.props.parentState.versions[5]}</td>
                            </tr>
                            <tr className="row5">
                                <td className="labelInfo">Relay Firmware Version</td>
                                <td className="FV2">{this.props.parentState.versions[9]}.{this.props.parentState.versions[10]}.{this.props.parentState.versions[11]}</td>
                            </tr>
                            <tr className="row5">
                                <td className="labelInfo">Siren Firmware Version</td>
                                <td className="FV2">{this.props.parentState.versions[6]}.{this.props.parentState.versions[7]}.{this.props.parentState.versions[8]}</td>
                            </tr>
                            <tr className="row6">
                                <td className="labelInfo">Total System Hours</td>
                                <td className="TSH2"></td>
                            </tr>
                            <tr className="row9">
                                <td className="labelInfo">Speaker 1 Over Current</td>
                                <td className="TSH2">{this.props.parentState.versions[1]}</td>
                            </tr>
                            <tr className="row10">
                                <td className="labelInfo">Speaker 2 Over Current</td>
                                <td className="TSH2">{this.props.parentState.versions[2]}</td>
                            </tr>
                            <tr style={this.state.currentOverage[0]} className="row10">
                                <td className="labelInfo">Relay 1 Output Current</td>
                                <td className="TSH2">{this.state.relay1OutputCurrent} A <img id="ampImage" style={this.state.ampOverageImg[0]} src={ampImage} alt="img" /></td>
                            </tr>
                            <tr style={this.state.currentOverage[1]} className="row10">
                                <td className="labelInfo">Relay 2 Output Current</td>
                                <td className="TSH2">{this.state.relay2OutputCurrent} A <img id="ampImage" style={this.state.ampOverageImg[1]} src={ampImage} alt="img" /></td>
                            </tr>
                            <tr style={this.state.currentOverage[2]} className="row10">
                                <td className="labelInfo">Relay 3 Output Current</td>
                                <td className="TSH2">{this.state.relay3OutputCurrent} A <img id="ampImage" style={this.state.ampOverageImg[2]} src={ampImage} alt="img" /></td>
                            </tr>
                            <tr style={this.state.currentOverage[3]} className="row10">
                                <td className="labelInfo">Relay 4 Output Current</td>
                                <td className="TSH2">{this.state.relay4OutputCurrent} A <img id="ampImage" style={this.state.ampOverageImg[3]} src={ampImage} alt="img" /></td>
                            </tr>
                        </tbody>
                    </table>
                    <h4>VEHICAL INFORMATION</h4>
                    <table id="vehInfo">
                        <tbody>
                            <tr className="table2">
                                <td className="RV">GPS Time</td>
                                <td className="RV2">{this.props.geoData[3]}</td>
                            </tr>
                            <tr className="table2">
                                <td className="RV">GPS Loci</td>
                                <td className="RV2">lat: {this.props.geoData[0]} <br /> long: {this.props.geoData[1]}</td>
                            </tr>
                            <tr className="table3">
                                <td className="RC">Speed</td>
                                <td className="RC2">{this.props.geoData[2]} mph</td>
                            </tr>
                        </tbody>
                    </table>
                    <a id="infoBack" className="backButton" onClick={(e) => { this.props.updateScreen('home') }}>BACK</a>
                </div>
                <div id="info2" className="zoneInfo" style={this.state.showInfo[1]}>
                    <h4>QSSM ZONE SELECTION</h4>

                    <div className="startStopButton" style={this.state.surfaceZoneDisplay[0]} onClick={(e) => { this.startStopZones('start') }}>START</div>
                    <div className="startStopButton" id="stopButton" style={this.state.surfaceZoneDisplay[1]} onClick={(e) => { this.startStopZones('stop') }}>STOP</div>

                    <div id="hideInfo" style={this.state.hideInfo}></div>
                    <div className="infoButtons" id="topZone">
                        <div className='infoLeft' style={this.state.buttonColors[0]} onClick={(button) => this.buttonSelected(0) }>
                            <p>1</p>
                        </div>
                        <div className='infoLeft' id="SMbutton1" style={this.state.buttonColors[1]} onClick={(button) => this.buttonSelected(1) }>
                            <p>2</p>
                        </div>
                        <div className='infoLeft' id="SMbutton2" style={this.state.buttonColors[2]} onClick={(button) => this.buttonSelected(2) }>
                            <p>3</p>
                        </div>
                        <div className='infoLeft' id="SMbutton3" style={this.state.buttonColors[3]} onClick={(button) => this.buttonSelected(3) }>
                            <p>4</p>
                        </div>
                        <div className='infoRight' id="SMbutton4" style={this.state.buttonColors[4]} onClick={(button) => this.buttonSelected(4) }>
                            <p>5</p>
                        </div>
                        <div className='infoRight' id="SMbutton5" style={this.state.buttonColors[5]} onClick={(button) => this.buttonSelected(5) }>
                            <p>6</p>
                        </div>
                        <div className='infoRight' id="SMbutton6" style={this.state.buttonColors[6]} onClick={(button) => this.buttonSelected(6) }>
                            <p>7</p>
                        </div>
                        <div className='infoRight' id="SMbutton7" style={this.state.buttonColors[7]} onClick={(button) => this.buttonSelected(7) }>
                            <p>8</p>
                        </div>
                        <div className='infoLeft2' id="SMbutton8" style={this.state.buttonColors[8]} onClick={(button) => this.buttonSelected(8) }>
                            <p>9</p>
                        </div>
                        <div className='infoLeft2' id="SMbutton9" style={this.state.buttonColors[9]} onClick={(button) => this.buttonSelected(9) }>
                            <p>10</p>
                        </div>
                        <div className='infoLeft2' id="SMbutton10" style={this.state.buttonColors[10]} onClick={(button) => this.buttonSelected(10) }>
                            <p>11</p>
                        </div>
                        <div className='infoLeft2' id="SMbutton11" style={this.state.buttonColors[11]} onClick={(button) => this.buttonSelected(11) }>
                            <p>12</p>
                        </div>
                        <div className='infoRight' id="SMbutton12" style={this.state.buttonColors[12]} onClick={(button) => this.buttonSelected(12) }>
                            <p>13</p>
                        </div>
                        <div className='infoRight' id="SMbutton13" style={this.state.buttonColors[13]} onClick={(button) => this.buttonSelected(13) }>
                            <p>14</p>
                        </div>
                        <div className='infoRight' id="SMbutton14" style={this.state.buttonColors[14]} onClick={(button) => this.buttonSelected(14) }>
                            <p>15</p>
                        </div>
                        <div className='infoRight' id="SMbutton15" style={this.state.buttonColors[15]} onClick={(button) => this.buttonSelected(15) }>
                            <p>16</p>
                        </div>
                    </div>
   
                    <h4>SPOILER ZONE SELECTION</h4>

                    <div className="startStopButton" style={this.state.surfaceZoneDisplay2[0]} onClick={(e) => { this.startStopZones2('start') }}>START</div>
                    <div className="startStopButton" id="stopButton2" style={this.state.surfaceZoneDisplay2[1]} onClick={(e) => { this.startStopZones2('stop') }}>STOP</div>

                    <div id="hideInfo2" style={this.state.hideInfo2}></div>
                    <div className="infoButtons" id="bottomZone">
                        <div className='infoLeft' style={this.state.buttonColors2[0]} onClick={(button) => this.buttonSelected2(0) }>
                            <p>1</p>
                        </div>
                        <div className='infoLeft' id="SMbutton1" style={this.state.buttonColors2[1]} onClick={(button) => this.buttonSelected2(1) }>
                            <p>2</p>
                        </div>
                        <div className='infoLeft' id="SMbutton2" style={this.state.buttonColors2[2]} onClick={(button) => this.buttonSelected2(2) }>
                            <p>3</p>
                        </div>
                        <div className='infoLeft' id="SMbutton3" style={this.state.buttonColors2[3]} onClick={(button) => this.buttonSelected2(3) }>
                            <p>4</p>
                        </div>
                        <div className='infoRight' id="SMbutton4" style={this.state.buttonColors2[4]} onClick={(button) => this.buttonSelected2(4) }>
                            <p>5</p>
                        </div>
                        <div className='infoRight' id="SMbutton5" style={this.state.buttonColors2[5]} onClick={(button) => this.buttonSelected2(5) }>
                            <p>6</p>
                        </div>
                    </div>
                    <div id="obdData" style={this.state.hideOBD}>
                        <JsonToTable json={this.state.obdData} />
                    </div>
                </div>
            </div>
        );
    }
}