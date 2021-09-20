import React, { Component } from "react";

export class Arrow extends Component {
    constructor(props) {
        super(props);
        this.state = {
        };
    }

    render() {
        return (
            <div id="arrow">
                <svg xmlns="http://www.w3.org/2000/svg" width="318" height="20" viewBox="0 0 192.741 9.364" className="arrow">
                    <defs>
                        <linearGradient id="left-right" x1="-100%" y1="0" x2="200%" y2="0" >
                            <stop offset="0" stopColor="white">
                                <animate attributeName="offset" values="0;0.1;0.2;0.7;" dur="1.7s" repeatCount="indefinite" />
                            </stop>
                            <stop offset="0.5" stopColor="red">
                                <animate attributeName="offset" values="0.2;0.5;0.7;" dur="1.7s" repeatCount="indefinite" />
                            </stop>
                            <stop offset="0" stopColor="red">
                                <animate attributeName="offset" values="0.1;0.3;0.7;0.9;" dur="1.7s" repeatCount="indefinite" />
                            </stop>
                            <stop offset="0.5" stopColor="white">
                                <animate attributeName="offset" values="0.3;0.5;0.7;1.1;" dur="1.7s" repeatCount="indefinite" />
                            </stop>
                        </linearGradient>

                        <linearGradient id="right-left" x1="200%" y1="0" x2="-100%" y2="0" >
                            <stop offset="0" stopColor="white">
                                <animate attributeName="offset" values="0;0.1;0.2;0.7;" dur="1.7s" repeatCount="indefinite" />
                            </stop>
                            <stop offset="0.5" stopColor="red">
                                <animate attributeName="offset" values="0.2;0.5;0.7;" dur="1.7s" repeatCount="indefinite" />
                            </stop>
                            <stop offset="0" stopColor="red">
                                <animate attributeName="offset" values="0.1;0.3;0.7;0.9;" dur="1.7s" repeatCount="indefinite" />
                            </stop>
                            <stop offset="0.5" stopColor="white">
                                <animate attributeName="offset" values="0.3;0.5;0.7;1.1;" dur="1.7s" repeatCount="indefinite" />
                            </stop>
                        </linearGradient>

                        <radialGradient id="center-out" cx="50%" cy="50%" r="155%">
                            <stop offset="-1" stopColor="white">
                                <animate attributeName="offset" from="-1" to="1" dur="2s" repeatCount="indefinite" />
                            </stop>
                            <stop offset="-0.25" stopColor="red">
                                <animate attributeName="offset" from="-0.25" to="1.25" dur="2s" repeatCount="indefinite" />
                            </stop>
                            <stop offset="0" stopColor="white">
                                <animate attributeName="offset" from="0" to="1.5" dur="2s" repeatCount="indefinite" />
                            </stop>
                        </radialGradient>

                        <pattern id="random" x="0" y="0" width=".25" height=".25" >
                            <rect x="0" y="0" width="10" height="10" fill="red">
                                <animate attributeName="fill" values="red;white;red" dur="1s" repeatCount="indefinite" />
                            </rect>
                            <rect x="10" y="0" width="10" height="10" fill="white">
                                <animate attributeName="fill" values="white;red;white" dur="2s" repeatCount="indefinite" />
                            </rect>
                            <rect x="20" y="0" width="10" height="10" fill="red">
                                <animate attributeName="fill" values="red;white;red" dur="1.5s" repeatCount="indefinite" />
                            </rect>
                            <rect x="30" y="0" width="10" height="10" fill="white">
                                <animate attributeName="fill" values="white;red;white" dur="1s" repeatCount="indefinite" />
                            </rect>
                            <rect x="40" y="0" width="10" height="10" fill="red">
                                <animate attributeName="fill" values="red;white;red" dur="1.5s" repeatCount="indefinite" />
                            </rect>
                        </pattern>
                    </defs>
                    <g id="Group_44" data-name="Group 44" transform="translate(-2.5 -18.376)">
                        <path id="Union_3" fill="white" data-name="Union 3" d="M570-39.772v-3.239H393.742v3.239a.5.5,0,0,1-.75.433L385.75-43.52a.5.5,0,0,1,0-.867l7.242-4.181a.5.5,0,0,1,.75.433v3.123H570v-3.123a.5.5,0,0,1,.75-.433l6.161,3.556H577v.052l.992.572a.5.5,0,0,1,0,.867l-7.242,4.181a.492.492,0,0,1-.249.068A.5.5,0,0,1,570-39.772Z" transform="translate(-383 67.011)" />
                    </g>
                </svg>
            </div>
        );
    }
}