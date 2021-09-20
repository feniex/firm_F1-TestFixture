import React, { Component } from "react";
import './../css/components.css';

const { ipcRenderer } = window.require('electron');

const visible = { display: "block" };
const notVisible = { display: "none" };

var redBoxFail = {    
    backgroundColor: 'red',
    width:'200px',
    height:'50px',
    border:'1px',
    marginTop: '10px',
    textAlign: 'center',
    fontWeight: 'bold'}
var greenBoxPass = {    
    backgroundColor: 'green',
    width:'200px',
    height:'50px',
    border:'1px',
    marginTop: '10px',
    textAlign: 'center',
    fontWeight: 'bold'}

export class Components extends Component {
    constructor(props) {
        super(props);
        this.state = {
           testType : [notVisible, notVisible,notVisible,notVisible,notVisible],
           controllerState : [redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail, redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail,redBoxFail]
        }
        ipcRenderer.send("check-usb");
    }
    
    componentDidMount() {
        ipcRenderer.on('send-F1-diagnostics', (e, arg) => { this.parseDiagnosticData(e, arg) });
    }

    componentWillUnmount() {
        ipcRenderer.removeAllListeners('send-F1-diagnostics', (e, arg) => { this.parseDiagnosticData(e, arg) });
        ipcRenderer.removeAllListeners("check-usb");
    }

    // static getDerivedStateFromProps(props, current_state) {
    // }

    parseDiagnosticData(e, arg)
    {
        var localState = JSON.parse(JSON.stringify(this.state));

        //console.log(arg);
        if(arg[0] === 126)
        {
            if(arg[1] === 'C'.charCodeAt(0))
            {
                for(var i = 0; i<7; i++)
                {
                    localState.testType[0] = visible;
                    localState.testType[1] = notVisible;
                    localState.testType[2] = notVisible;
                    localState.testType[3] = notVisible;
                    localState.testType[4] = notVisible;
                    if(arg[i+2] === 'P'.charCodeAt(0))
                    {
                        localState.controllerState[i] = greenBoxPass;
                    }
                    else
                    {
                        localState.controllerState[i] = redBoxFail;
                    }
                }
            }
            else if(arg[1] === 'R'.charCodeAt(0))
            {
                localState.testType[0] = notVisible;
                localState.testType[1] = visible;
                localState.testType[2] = notVisible;
                localState.testType[3] = notVisible;
                localState.testType[4] = notVisible;
                for(i = 0; i<10; i++)
                {
                    if(arg[i+2] === 'P'.charCodeAt(0))
                    {
                        localState.controllerState[i] = greenBoxPass;
                    }
                    else
                    {
                        localState.controllerState[i] = redBoxFail;
                    }
                }
            }
            else if(arg[1] === 'S'.charCodeAt(0))
            {
                localState.testType[0] = notVisible;
                localState.testType[1] = notVisible;
                localState.testType[2] = visible;
                localState.testType[3] = notVisible;
                localState.testType[4] = notVisible;
                for(i = 0; i<11; i++)
                {
                    if(arg[i+2] === 'P'.charCodeAt(0))
                    {
                        localState.controllerState[i] = greenBoxPass;
                    }
                    else
                    {
                        localState.controllerState[i] = redBoxFail;
                    }
                }
            }
            else if(arg[1] === 'c'.charCodeAt(0))
            {
                localState.testType[0] = notVisible;
                localState.testType[1] = notVisible;
                localState.testType[2] = notVisible;
                localState.testType[3] = visible;
                localState.testType[4] = notVisible;
                for(i = 0; i<8; i++)
                {
                    if(arg[i+2] === 'P'.charCodeAt(0))
                    {
                        localState.controllerState[i] = greenBoxPass;
                    }
                    else
                    {
                        localState.controllerState[i] = redBoxFail;
                    }
                }
            }
            else if(arg[1] === 'r'.charCodeAt(0))
            {
                localState.testType[0] = notVisible;
                localState.testType[1] = notVisible;
                localState.testType[2] = notVisible;
                localState.testType[3] = notVisible;
                localState.testType[4] = visible;
                for(i = 0; i<14; i++)
                {
                    if(arg[i+2] === 'P'.charCodeAt(0))
                    {
                        localState.controllerState[i] = greenBoxPass;
                    }
                    else
                    {
                        localState.controllerState[i] = redBoxFail;
                    }
                }
            }
        }
        this.setState(localState);

    }

    componentDidUpdate() {

    }

    render() {
        return (
            <div>
                {/* 7 To Display  */}
                <div className="controllerTest"  style={this.state.testType[0]}>
                    {/* <div className="indicatorController1" style={this.state.controllerState[0]}>Initialize Test</div> */}
                    <div className="indicatorController1" style={this.state.controllerState[1]}>Confirm Bootup</div>
                    <div className="indicatorController1" style={this.state.controllerState[2]}>Push Buttons</div>
                    <div className="indicatorController1" style={this.state.controllerState[3]}>OBDII</div>
                    <div className="indicatorController1" style={this.state.controllerState[4]}>Quad Stream</div>
                    <div className="indicatorController1" style={this.state.controllerState[5]}>LED RGB - 3 Step Manual</div>
                    {/* <div className="indicatorController1" style={this.state.controllerState[6]}>Full Pass</div> */}
                </div>

                {/* 10 To Display  */}
                <div className="relayTest" style={this.state.testType[1]}>
                    {/* <div className="indicatorController1" style={this.state.controllerState[0]}>Initialize Test</div> */}
                    <div className="indicatorController1" style={this.state.controllerState[1]}>Siren Enable</div>
                    <div className="indicatorController1" style={this.state.controllerState[2]}>Outpus</div>
                    <div className="indicatorController1" style={this.state.controllerState[3]}>Datalink</div>
                    <div className="indicatorController1" style={this.state.controllerState[4]}>Quad</div>
                    <div className="indicatorController1" style={this.state.controllerState[5]}>Siren Uart</div>
                    <div className="indicatorController1" style={this.state.controllerState[6]}>Inputs</div>
                    <div className="indicatorController1" style={this.state.controllerState[7]}>Vbatt</div>
                    <div className="indicatorController1" style={this.state.controllerState[8]}>Block Currents</div>
                    {/* <div className="indicatorController1" style={this.state.controllerState[9]}>Full Pass</div> */}
                </div>

                {/* 11 To Display  */}
                <div className="sirenTest" style={this.state.testType[2]}>
                    {/* <div className="indicatorController1" style={this.state.controllerState[0]}>Initialize Test</div> */}
                    {/* <div className="indicatorController1" style={this.state.controllerState[1]}>Uart Rx</div> */}
                    <div className="indicatorController1" style={this.state.controllerState[2]}>Uart Tx</div>
                    <div className="indicatorController1" style={this.state.controllerState[3]}>Amp 1</div>
                    <div className="indicatorController1" style={this.state.controllerState[4]}>Amp 2</div>
                    {/* <div className="indicatorController1" style={this.state.controllerState[5]}>Radio Rebroadcast</div>
                    <div className="indicatorController1" style={this.state.controllerState[6]}>Mic</div>
                    <div className="indicatorController1" style={this.state.controllerState[7]}>Audio Stream</div>
                    <div className="indicatorController1" style={this.state.controllerState[8]}>Flash</div> */}
                    <div className="indicatorController1" style={this.state.controllerState[9]}>Overload</div>
                    {/* <div className="indicatorController1" style={this.state.controllerState[10]}>Full Pass</div> */}
                </div>

                {/* 8 To Display  */}
                <div className="completeControllerTest" style={this.state.testType[3]}>
                    {/* <div className="indicatorController1" style={this.state.controllerState[0]}>Initialize Test</div> */}
                    <div className="indicatorController1" style={this.state.controllerState[1]}>Confirm Bootup</div>
                    {/* <div className="indicatorController1" style={this.state.controllerState[2]}>Config File</div> */}
                    <div className="indicatorController1" style={this.state.controllerState[3]}>Test Powermodes</div>
                    <div className="indicatorController1" style={this.state.controllerState[4]}>OBDII</div>
                    <div className="indicatorController1" style={this.state.controllerState[5]}>Push Buttons</div>
                    <div className="indicatorController1" style={this.state.controllerState[6]}>Quad Strean</div>
                    {/* <div className="indicatorController1" style={this.state.controllerState[7]}>Full Pass</div> */}
                </div>

                {/* 14 To Display  */}
                <div className="completeRelaySirenTest" style={this.state.testType[4]}>
                    {/* <div className="indicatorController1" style={this.state.controllerState[0]}>Initialize Test</div> */}
                    <div className="indicatorController1" style={this.state.controllerState[1]}>Outputs</div>
                    <div className="indicatorController1" style={this.state.controllerState[2]}>Datalink</div>
                    <div className="indicatorController1" style={this.state.controllerState[3]}>Quad</div>
                    <div className="indicatorController1" style={this.state.controllerState[4]}>Inputs</div>
                    <div className="indicatorController1" style={this.state.controllerState[5]}>Vbatt</div>
                    <div className="indicatorController1" style={this.state.controllerState[6]}>Block Current</div>
                    <div className="indicatorController1" style={this.state.controllerState[7]}>Amp 1</div>
                    <div className="indicatorController1" style={this.state.controllerState[8]}>Amp 2</div>
                    <div className="indicatorController1" style={this.state.controllerState[9]}>Radio Rebroadcast</div>
                    <div className="indicatorController1" style={this.state.controllerState[10]}>Mic</div>
                    <div className="indicatorController1" style={this.state.controllerState[11]}>Flash</div>
                    <div className="indicatorController1" style={this.state.controllerState[12]}>GPS</div>
                    {/* <div className="indicatorController1" style={this.state.controllerState[12]}>Full Pass</div> */}
                </div>
            </div>
        );
    }
}
