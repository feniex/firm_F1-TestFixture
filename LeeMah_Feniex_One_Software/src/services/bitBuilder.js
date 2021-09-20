export default class BitBuilder {

    constructor() {

        this.byteArray1 = ['0', '0', '0', '0', '0', '0', '0', '0'];
        this.byteArray2 = ['0', '0', '0', '0', '0', '0', '0', '0'];
        this.byteArray3 = ['0', '0', '0', '0', '0', '0', '0', '0'];
        this.byteArray4 = ['0', '0', '0', '0', '0', '0', '0', '0'];

        this.byte55Array = ['1', '0', '0', '0', '0', '0', '0', '0'];
        this.byte56Array = ['1', '0', '0', '0', '0', '0', '0', '0'];
        this.byte57Array = ['1', '0', '1', '1', '1', '1', '1', '1'];
    }

    byteArray(selection) {

        var byte1 = '';
        var byte2 = '';
        var byte3 = '';
        var byte4 = '';
        var bitValue = '';

        for (var bit = 0; bit < selection.length; bit++) {
            bitValue = selection[bit].toString();

            if (bit < 8) {
                this.byteArray1[7 - bit] = bitValue;
            }
            else if (bit > 7 && bit < 16) {
                this.byteArray2[15 - bit] = bitValue;
            }
            else if (bit > 15 && bit < 24) {
                this.byteArray3[23 - bit] = bitValue;
            }
            else if (bit < 32) {
                this.byteArray4[31 - bit] = bitValue;
            }
        }

        byte1 = this.byteArray1[0] + this.byteArray1[1] + this.byteArray1[2] + this.byteArray1[3] + 
        this.byteArray1[4] + this.byteArray1[5] + this.byteArray1[6] + this.byteArray1[7];

        byte2 = this.byteArray2[0] + this.byteArray2[1] + this.byteArray2[2] + this.byteArray2[3] + 
        this.byteArray2[4] + this.byteArray2[5] + this.byteArray2[6] + this.byteArray2[7];

        byte3 = this.byteArray3[0] + this.byteArray3[1] + this.byteArray3[2] + this.byteArray3[3] + 
        this.byteArray3[4] + this.byteArray3[5] + this.byteArray3[6] + this.byteArray3[7];

        byte4 = this.byteArray4[0] + this.byteArray4[1] + this.byteArray4[2] + this.byteArray4[3] + 
        this.byteArray4[4] + this.byteArray4[5] + this.byteArray4[6] + this.byteArray4[7];

        byte1 = parseInt(byte1, 2).toString(16);
        byte2 = parseInt(byte2, 2).toString(16);
        byte3 = parseInt(byte3, 2).toString(16);
        byte4 = parseInt(byte4, 2).toString(16);

        byte1 = parseInt(byte1, 16);
        byte2 = parseInt(byte2, 16);
        byte3 = parseInt(byte3, 16);
        byte4 = parseInt(byte4, 16);

        return [byte1, byte2, byte3, byte4];
    }

    lightBar(selection) {

        var barValue = '';
        var byte55 = '';
        var byte56 = '';
        var byte57 = '';

        for (var bit = 0; bit < selection.length; bit++) {

            barValue = selection[bit].toString();

            switch(bit) {
                case 0:
                    this.byte56Array[1] = barValue;
                    break;
                case 1:
                    this.byte56Array[2] = barValue;
                    break;
                case 2:
                    this.byte55Array[1] = barValue;
                    break;
                case 3:
                    this.byte55Array[2] = barValue;
                    break;
                case 4:
                    this.byte55Array[3] = barValue;
                    break;
                case 5:
                    this.byte55Array[4] = barValue;
                    break;
                case 6:
                    this.byte55Array[5] = barValue;
                    break;
                case 7:
                    this.byte55Array[6] = barValue;
                    break;
                case 8:
                    this.byte55Array[7] = barValue;
                    break;
                case 9:
                    this.byte56Array[3] = barValue;
                    break;
                case 10:
                    this.byte56Array[4] = barValue;
                    break;
                case 11:
                    this.byte56Array[5] = barValue;
                    break;
                case 12:
                    this.byte56Array[6] = barValue;
                    break;
                case 13:
                    this.byte56Array[7] = barValue;
                    break;
                case 14:
                    this.byte57Array[1] = barValue;
                    break;
                default:
            }
        }
 
        byte55 = this.byte55Array[0] + this.byte55Array[1] + this.byte55Array[2] + this.byte55Array[3] + 
                this.byte55Array[4] + this.byte55Array[5] + this.byte55Array[6] + this.byte55Array[7];

        byte56 = this.byte56Array[0] + this.byte56Array[1] + this.byte56Array[2] + this.byte56Array[3] + 
                this.byte56Array[4] + this.byte56Array[5] + this.byte56Array[6] + this.byte56Array[7];

        byte57 = this.byte57Array[0] + this.byte57Array[1] + this.byte57Array[2] + this.byte57Array[3] + 
                this.byte57Array[4] + this.byte57Array[5] + this.byte57Array[6] + this.byte57Array[7];

        byte55 = parseInt(byte55, 2).toString(16);
        byte56 = parseInt(byte56, 2).toString(16);
        byte57 = parseInt(byte57, 2).toString(16);

        byte55 = parseInt(byte55, 16);
        byte56 = parseInt(byte56, 16);
        byte57 = parseInt(byte57, 16);

        return [byte55, byte56, byte57];
    }
}