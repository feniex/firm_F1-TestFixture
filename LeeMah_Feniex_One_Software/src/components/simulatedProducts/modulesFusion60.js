import React, { Component } from "react";
import './../../css/simulatedProducts.css';

var visiblityFalse = { display: "none" };
var visiblityTrue = { height: "15px", width:"35px", background:"rgb(180, 180, 180,1)" , border: '1px solid black', borderRadius: '3px'};

// var triBarRed = { background: "linear-gradient(to right, red, blue, yellow)" };
// SINGLE COLOR STYLES
var barRed100 = { height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px', background: "rgb(255, 0, 0,1)"};
var barBlue100 = {height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px',  background: "rgb(0, 0, 255,1)"};
var barAmber100 = { height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px', background: "rgb(255, 255, 0,1)"};
var barWhite100 = {height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px',  background: "rgb(255, 255, 255,1)"};

var barRed50 = { height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px', background: "rgb(255, 0, 0)", opacity: "0.65" };
var barBlue50 = {height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px',  background: "rgb(0, 0, 255)", opacity: "0.65" };
var barAmber50 = { height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px', background: "rgb(255, 255, 0)", opacity: "0.65" };
var barWhite50 = {height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px',  background: "rgb(255, 255, 255)", opacity: "0.65" };

var barRed10 = { height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px', background: "rgb(255, 0, 0)", opacity: "0.3" };
var barBlue10 = {height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px',  background: "rgb(0, 0, 255)", opacity: "0.3" };
var barAmber10 = { height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px', background: "rgb(255, 255, 0)", opacity: "0.3" };
var barWhite10 = {height: "15px", width:"35px" , border: '1px solid black', borderRadius: '3px',  background: "rgb(255, 255, 255)", opacity: "0.3" };

var thirtyXLookUp = [1,2,3,4,5,6,7,8,9,10,11,12,30,13,29,14,28,15,27,26,25,24,23,22,21,20,19,18,17,16];

var tempBuffer = 0;

export class ModulesFusion60 extends Component {

    constructor(props) {
        super(props);
        this.state = {
            frontStyles : [visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue,visiblityTrue, visiblityTrue, visiblityTrue,
                           visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue,visiblityTrue, visiblityTrue, visiblityTrue,
                           visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue, visiblityTrue,visiblityTrue, visiblityTrue, visiblityTrue ]
        }
    }

    static getDerivedStateFromProps(props, current_state) {
        var startOfThirtyX = 3;
        tempBuffer = JSON.parse(props.frameBufferProps);
        //console.log(tempBuffer);
        for(var i = startOfThirtyX; i<30+startOfThirtyX; i++)
        {
            //console.log(tempBuffer[i]);
            if((tempBuffer[i]&0x03) === 0x03)
            {
                //console.log("Blue");
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barBlue100;
            }
            else if((tempBuffer[i]&0x03) === 0x02)
            {
                //console.log("Blue 50");
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barBlue50;
            }
            else if((tempBuffer[i]&0x03) === 0x01)
            {
                //console.log("Blue 10");
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barBlue10;
            }
            else if((tempBuffer[i]&0x0C) === 0x0C)
            {
                //console.log("Blue");
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barRed100;
            }
            else if((tempBuffer[i]&0x0C) === 0x08)
            {
                //console.log("Blue");
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barRed50;
            }
            else if((tempBuffer[i]&0x0C) === 0x04)
            {
                //console.log("Blue");
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barRed10;
            }
            else if((tempBuffer[i]&0x30) === 0x30)
            {
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barAmber100;
            }
            else if((tempBuffer[i]&0x30) === 0x20)
            {
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barAmber50;
            }
            else if((tempBuffer[i]&0x30) === 0x10)
            {
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barAmber10;
            }
            else if((tempBuffer[i]&0xC0) === 0xC0)
            {
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barWhite100;
            }
            else if((tempBuffer[i]&0xC0) === 0x80)
            {
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barWhite50;
            }
            else if((tempBuffer[i]&0xC0) === 0x40)
            {
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = barWhite10;
            }
            else
            {
                current_state.frontStyles[thirtyXLookUp[i-startOfThirtyX]-1] = visiblityTrue;
            }
        }
        //console.log(current_state.frontStyles);
        return current_state;
    }

    render() {
        return (
            <div className="quantum60">
                <div className="quantum0" style={this.state.frontStyles[0]}>
                </div>
                <div className="quantum1" style={this.state.frontStyles[1]}>
                </div>
                <div className="quantum2" style={this.state.frontStyles[2]}>
                </div>
                <div className="quantum3" style={this.state.frontStyles[3]}>
                </div>
                <div className="quantum4" style={this.state.frontStyles[4]}>
                </div>
                <div className="quantum5" style={this.state.frontStyles[5]}>
                </div>
                <div className="quantum6" style={this.state.frontStyles[6]}>
                </div>
                <div className="quantum7" style={this.state.frontStyles[7]}>
                </div>
                <div className="quantum8" style={this.state.frontStyles[8]}>
                </div>
                <div className="quantum9" style={this.state.frontStyles[9]}>
                </div>
                <div className="quantum10" style={this.state.frontStyles[10]}>
                </div>
                <div className="quantum11" style={this.state.frontStyles[11]}>
                </div>
                <div className="quantum12" style={this.state.frontStyles[12]}>
                </div>
                <div className="quantum13" style={this.state.frontStyles[13]}>
                </div>
                <div className="quantum14" style={this.state.frontStyles[14]}>
                </div>
                <div className="quantum15" style={this.state.frontStyles[15]}>
                </div>
                <div className="quantum16" style={this.state.frontStyles[16]}>
                </div>
                <div className="quantum17" style={this.state.frontStyles[17]}>
                </div>
                <div className="quantum18" style={this.state.frontStyles[18]}>
                </div>
                <div className="quantum19" style={this.state.frontStyles[19]}>
                </div>
                <div className="quantum20" style={this.state.frontStyles[20]}>
                </div>
                <div className="quantum21" style={this.state.frontStyles[21]}>
                </div>
                <div className="quantum22" style={this.state.frontStyles[22]}>
                </div>
                <div className="quantum23" style={this.state.frontStyles[23]}>
                </div>
                <div className="quantum24" style={this.state.frontStyles[24]}>
                </div>
                <div className="quantum25" style={this.state.frontStyles[25]}>
                </div>
                <div className="quantum26" style={this.state.frontStyles[26]}>
                </div>
                <div className="quantum27" style={this.state.frontStyles[27]}>
                </div>
                <div className="quantum28" style={this.state.frontStyles[28]}>
                </div>
                <div className="quantum29" style={this.state.frontStyles[29]}>
                </div>
            </div>
        );
    }
}