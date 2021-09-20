import React, { Component } from "react";
// import LinesEllipsis from 'react-lines-ellipsis'
// import Slider from 'rc-slider';

import './../css/components.css';
import './../css/messages.css';

// const oneImg = require(`../images/Group40.png`);
// const down = require(`../images/Minus-icon.svg`);
// const up = require(`../images/Plus-icon.svg`);

var strEllips = 30;

const visiblityTrue = { display: "block" };
const visiblityFalse = { display: "none" };
var d = new Date();

// var prevButtonValue;
// var screenCounter = 0;

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

export class Messages extends Component {
    constructor(props) {
        super(props);
        this.state = {
            dotVisibility: [visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse],
            messageVisibility: [visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse, visiblityFalse],
            inboxVisibility: visiblityTrue,
            messageTimes: ['10/4', '10/4', '10/4', '10/4', '10/4', '10/4', '10/4', '10/4', '10/4', '10/4'],
            messageListings: ['', '', '', '', '', '', '', '', '', '']
            // buttons: buttonData,
        };
    }

    static getDerivedStateFromProps(props, current_state) {

        current_state.inboxVisibility = visiblityTrue;

        for (let d = 0; d <current_state.dotVisibility.length; d++) {

            if (props.parentState.messages[d].Messages.length > 0 && props.parentState.messages[d].Messages !== 'm3$$4g3C134r') {

                current_state.messageVisibility[d] = visiblityTrue;
                current_state.inboxVisibility = visiblityFalse;

                let viewTime = props.parentState.messages[d]['Time'];

                if (viewTime !== undefined && viewTime.length > 15) {
                    current_state.messageTimes[d] = Messages.setDateTime(viewTime);
                }
                // ADDS ELLIPSIS TO STRING
                current_state.messageListings[d] = Messages.setEllipsis(props.parentState.messages[d].Messages);
            }
            else {
                current_state.messageVisibility[d] = visiblityFalse;
            }

            // SHOWS DOTS FOR NEW MESSAGES
            try {
                if (props.parentState.messages[d]['New'] === true) {
                    current_state.dotVisibility[d] = visiblityTrue;
                }
                else {
                    current_state.dotVisibility[d] = visiblityFalse;
                }
            }
            catch(e) {
                ;
            }
        }
        return current_state;    
    }

    static setEllipsis(str) {
        return (str.length > strEllips) ? str.substr(0, strEllips - 1) + '. . .' : str;
    }

    static setDateTime(time) {

        let dateTime = time;
        var monthNames = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
        let viewTime; 

        let year =  dateTime.split(' ')[3];
        let monthDay = dateTime.split(', ')[1];
        let month = monthDay.split(' ')[0];
        let dayNum = monthDay.split(' ')[1];

        let dayTime = dateTime.split(' ')[4];
        let dayTime1 = dayTime.split(':')[0];
        let dayTime2 = dayTime.split(':')[0];
        let amPm = dateTime.split(' ')[5];
    
        dayTime = dayTime1 + ':' + dayTime2;
    
        let currentMonth = d.getMonth();
        let currentYear = d.getFullYear();
        let currentDay = d.getDate();
    
        for(let m = 0; m < monthNames.length; m++) {
          if (currentMonth === m) {
            currentMonth = monthNames[m];
          }
        }
    
        if (currentMonth == month && currentDay == dayNum && currentYear == year) {
          viewTime = dayTime + ' ' + amPm;
          strEllips = 30;
        }
        else {
          for(let m = 0; m < monthNames.length; m++) {
            if (month === monthNames[m]) {
              viewTime = m + '/' + dayNum;
            }
          }
          strEllips = 35;
        }
        return viewTime;
    }

    render() {
        return (
            <div id="messageList">
                <h3 style={this.state.inboxVisibility}>Inbox Empty</h3>
                <ul id="messageListing">
                    <li style={this.state.messageVisibility[0]} onClick={(e, count) => { this.props.updateScreen('message', 0) }}>
                        <span style={this.state.dotVisibility[0]} className="dot"></span>
                        {this.state.messageListings[0]}
                        <span>{this.state.messageTimes[0]}</span>
                    </li>
                    <li style={this.state.messageVisibility[1]} onClick={(e, count) => { this.props.updateScreen('message', 1) }}>
                        <span style={this.state.dotVisibility[1]} className="dot"></span>
                        {this.state.messageListings[1]}
                        <span>{this.state.messageTimes[1]}</span>
                    </li>
                    <li style={this.state.messageVisibility[2]} onClick={(e, count) => { this.props.updateScreen('message', 2) }}>
                        <span style={this.state.dotVisibility[2]} className="dot"></span>
                        {this.state.messageListings[2]}
                        <span>{this.state.messageTimes[2]}</span>
                    </li>
                    <li style={this.state.messageVisibility[3]} onClick={(e, count) => { this.props.updateScreen('message', 3) }}>
                        <span style={this.state.dotVisibility[3]} className="dot"></span>
                        {this.state.messageListings[3]}
                        <span>{this.state.messageTimes[3]}</span>
                    </li>
                    <li style={this.state.messageVisibility[4]} onClick={(e, count) => { this.props.updateScreen('message', 4) }}>
                        <span style={this.state.dotVisibility[4]} className="dot"></span>
                        {this.state.messageListings[4]}
                        <span>{this.state.messageTimes[4]}</span>
                    </li>
                    <li style={this.state.messageVisibility[5]} onClick={(e, count) => { this.props.updateScreen('message', 5) }}>
                        <span style={this.state.dotVisibility[5]} className="dot"></span>
                        {this.state.messageListings[5]}
                        <span>{this.state.messageTimes[5]}</span>
                    </li>
                    <li style={this.state.messageVisibility[6]} onClick={(e, count) => { this.props.updateScreen('message', 6) }}>
                        <span style={this.state.dotVisibility[6]} className="dot"></span>
                        {this.state.messageListings[6]}
                        <span>{this.state.messageTimes[6]}</span>
                    </li>
                    <li style={this.state.messageVisibility[7]} onClick={(e, count) => { this.props.updateScreen('message', 7) }}>
                        <span style={this.state.dotVisibility[7]} className="dot"></span>
                        {this.state.messageListings[7]}
                        <span>{this.state.messageTimes[7]}</span>
                    </li>
                    <li style={this.state.messageVisibility[8]} onClick={(e, count) => { this.props.updateScreen('message', 8) }}>
                        <span style={this.state.dotVisibility[8]} className="dot"></span>
                        {this.state.messageListings[8]}
                        <span>{this.state.messageTimes[8]}</span>
                    </li>
                    <li style={this.state.messageVisibility[9]} onClick={(e, count) => { this.props.updateScreen('message', 9) }}>
                        <span style={this.state.dotVisibility[9]} className="dot"></span>
                        {this.state.messageListings[9]}
                        <span>{this.state.messageTimes[9]}</span>
                    </li>
                </ul>
                <a className="backButton" onClick={(e) => { this.props.updateScreen('home') }}>BACK</a>
                <br /><br />
            </div>
        );
    }
}