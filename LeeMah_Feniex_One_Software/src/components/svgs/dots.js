import React, { Component } from "react";
import './../../css/components.css';

export class Dots extends Component {
    constructor(props) {
        super(props);
        this.state = {

        };
    }

    // componentDidMount() {
    //     var element = document.getElementById("homeContainer");
    //     element.addEventListener('scroll', this.handleScroll);
    // }
    
    // componentWillUnmount() {
    //     var element = document.getElementById("homeContainer");
    //     element.removeEventListener('scroll', this.handleScroll);
    // }




    // componentDidUpdate() {

    //     var element = document.getElementById("homeContainer");

    //     console.log("THis is the elewment: " + element)

    //     element.addEventListener('scroll', function (event) {
    //         if(event.originalEvent.detail > 0 || event.originalEvent.wheelDeltaX < 0) { //alternative options for wheelData: wheelDeltaX & wheelDeltaY
    //             //scroll right
    //             console.log("RIGHT");
    //         } else {
    //             //scroll left
    //             console.log("LEFT");
    //         }
    //         //prevent page fom scrolling
    //         return false;
    //     });
    // }

    render() {
        return (
            <div id="dots">
                <svg xmlns="http://www.w3.org/2000/svg" width={this.props.dotSize[0]} height={this.props.dotSize[0]} viewBox="0 0 15.547 15.547" className="circle11">
                    <circle id="ellipse_156" data-name="Ellipse 156" cx="5.5" cy="5.5" r="5.5" transform="translate(0 8.045) rotate(-47)" fill={this.props.dotFill[0]} />
                </svg>
                <svg xmlns="http://www.w3.org/2000/svg" width={this.props.dotSize[1]} height={this.props.dotSize[1]} viewBox="0 0 15.547 15.547" className="circle21">
                    <circle id="ellipse_157" data-name="Ellipse 157" cx="5.5" cy="5.5" r="5.5" transform="translate(0 8.045) rotate(-47)" fill={this.props.dotFill[1]} />
                </svg>
            </div>
        );
    }
}