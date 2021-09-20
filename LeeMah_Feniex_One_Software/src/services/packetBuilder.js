export default class PacketBuilder {

    constructor(button) {

        this.ledDataPacket = [
            126 , 73 , 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
            0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
            0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
            0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
            0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
            0 , 255 ,0, 0, 126 , 51 , 0 , 0 , 0 , 13 , 
            10 , 126 , 83 , 0 , 0 , 0 , 13 , 10 , 126 , 80 ,
            0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 13 , 10
        ];

        this.button = button;
    }

    calculateChecksum() {

        var checkSum = 0;

        // Removes old checksum values;
        if (this.ledDataPacket.length > 81) {
            this.ledDataPacket = this.ledDataPacket.slice(0, 81);
        }

        for (let i = 2; i < 81; i++) {
            checkSum ^= this.ledDataPacket[i];
        }
        return checkSum;
    }

    calculateRelayChecksum() {

        var relayCheckSum = 0;

        // Removes old checksum values;
        if (this.ledDataPacket.length > 84) {
            this.ledDataPacket = this.ledDataPacket.slice(0, 84);
        }

        for (let i = 71; i < 81; i++) {
            relayCheckSum ^= this.ledDataPacket[i];
        }
        return relayCheckSum;
    }

    createPacket() {

        var checkSum = 0;
        var checkRelaySum = 0;

        checkSum = this.calculateChecksum();
        checkRelaySum = this.calculateRelayChecksum();

        if (checkSum > 0) {
            this.ledDataPacket.push(checkSum, 13, 10);
        }
        if (checkRelaySum > 0) {
            this.ledDataPacket.push(checkRelaySum, 13, 10);
        }
        return this.ledDataPacket;
    }

    dualDelay(dualDelay) {
        this.ledDataPacket[66] = dualDelay;
    }

    radioReBroadcast(radioReBroadcast) {
        this.ledDataPacket[77] = radioReBroadcast;
    }

    parkKill() {
        this.ledDataPacket[66] = 0;
        this.ledDataPacket[77] = 0;
        this.ledDataPacket[64] = 0;
        this.ledDataPacket[65] = 0;
    }

    highLow(highLowActive) {
        this.ledDataPacket[75] = highLowActive[0];
    }

    activePorts(selection) {
        this.ledDataPacket[71] = selection[0];
        this.ledDataPacket[72] = selection[1];
        this.ledDataPacket[73] = selection[2];
        this.ledDataPacket[74] = selection[3];
    }

    siren1(sirenSelection) {

        this.ledDataPacket[64] = 0;

        for (var bit = 0; bit < sirenSelection.length; bit++) {
    
            if (sirenSelection[bit] === 1){
                if (bit === 13) {
                    this.ledDataPacket[64] = 22;
                }
                else {
                    this.ledDataPacket[64] = bit + 1;
                }
            }
        }
    }

    siren2(sirenSelection) {

        this.ledDataPacket[65] = 0;

        for (var bit = 0; bit < sirenSelection.length; bit++) {
            if (sirenSelection[bit] === 1) {
                if (bit === 13) {
                    this.ledDataPacket[65] = 22;
                }
                else {
                    this.ledDataPacket[65] = bit + 1;
                }
            }
        }
    }

    siren3(sirenSelection) {

        for (var bit = 0; bit < sirenSelection.length; bit++) {
            if (sirenSelection[bit] === 1){
                this.ledDataPacket[64] = bit + 14;
                this.ledDataPacket[65] = bit + 14;
            }
        }
    }

    lightBar(lightbarBytes) {

        if (lightbarBytes.length > 0) {
            this.ledDataPacket[57] = lightbarBytes[0];
            this.ledDataPacket[58] = lightbarBytes[1];
            this.ledDataPacket[59] = lightbarBytes[2];
        }
        else {
            this.ledDataPacket[57] = 0;
            this.ledDataPacket[58] = 0;
            this.ledDataPacket[59] = 0;
        }
    }

    screenBrightness(brightness) {
        this.ledDataPacket[52] = brightness;
    }

    speakerEnable(speakerEnable) {
        this.ledDataPacket[53] = speakerEnable;
    }

    powerState(powerState) {
        this.ledDataPacket[54] = powerState;
        this.ledDataPacket[76] = powerState;
    }

    buttonColor(buttonColors, brightness) {

        var buttonIndex = 50;

        for (let buttonColor = 0; buttonColor < buttonColors.length; buttonColor++) {

            var buttonSelect = buttonIndex - (3 * (buttonColor + 1));
            
            if (buttonColor < 16) {
                this.setColor(buttonSelect, buttonColors[buttonColor], brightness[buttonColor]);
            }
        }
    }

    setColor(button, color, brightness) {

        switch(color) {
            case "default":
                this.ledDataPacket[button] = 0;
                this.ledDataPacket[button + 1] = brightness;
                this.ledDataPacket[button + 2] = brightness;
                break;
            case 'Red':
                this.ledDataPacket[button] = brightness;
                this.ledDataPacket[button + 1] = 0;
                this.ledDataPacket[button + 2] = 0;
                break;
            case 'Green':
                this.ledDataPacket[button] = 0;
                this.ledDataPacket[button + 1] = brightness;
                this.ledDataPacket[button + 2] = 0;
                break;
            case "Yellow":
                this.ledDataPacket[button] = brightness;
                this.ledDataPacket[button + 1] = brightness;
                this.ledDataPacket[button + 2] = 0;
                break;
            case 'Blue':
                this.ledDataPacket[button] = 0;
                this.ledDataPacket[button + 1] = 0;
                this.ledDataPacket[button + 2] = brightness;
                break;
            case "Purple":
                this.ledDataPacket[button] = brightness;
                this.ledDataPacket[button + 1] = 0;
                this.ledDataPacket[button + 2] = brightness;
                break;
            case "White":
                this.ledDataPacket[button] = brightness;
                this.ledDataPacket[button + 1] = brightness;
                this.ledDataPacket[button + 2] = brightness;
                break;
            default:
        }
    }
}