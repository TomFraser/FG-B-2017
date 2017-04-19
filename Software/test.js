const fs = require('fs')

function log() {
    var angle = 90;
    var dirNum = 4;
    var angToRad = 0.01745329251;
    var radToAng = 57.2957795131;
    var array = [60, 180, 300];

    var newAngle = (Math.abs(Math.round(angle / (360 * 1 / dirNum)))) * (360 *
        1 / dirNum);

    var newNum = Math.cos(((array[0] + 90) * angToRad) - (newAngle * angToRad)); //Nice

    console.log(newNum * 255);
}

function run() {
    var dou = 79.91;
    var mega = Math.trunc(dou);

    console.log(mega);
}

function calulcateIfs(){
    for(let i = 0; i < 301; i++){

    }
}

function calculateTheoreticalOrbit(){
    var values = [0,0,0,0,0,0,0,0,0,0,0,0]
    /*
Dat C++ Tho

                int selectedTsop = angleIn/30;
                int inVar = angleIn <= 180.00 ? (selectedTsop) : (TSOP_NUM - selectedTsop);
                int variableRotate = angleIn <= 180.00 ? (TSOP_VARIABLE_ANGLE * inVar + 90) : (360 - TSOP_VARIABLE_ANGLE * inVar - 90);
                // int variableRotate = constrain(TSOP_VARIABLE_ANGLE * inVar, 0.00, angleIn < 180.00 ? (angleIn - TSOP_ORBIT_ANGLE) : (angleIn + TSOP_ORBIT_ANGLE));
                return variableRotate;
    */

    for(var i = 0; i <= 12; i++){
        var selectedTsop = i
        var angle = i * 30
        if(angle < 180){
            var inVar = selectedTsop
            var variableRotate = 18 * inVar + 90
        }else{
            var inVar = 12 - selectedTsop
            var variableRotate = 360 - 18 * inVar - 90
        }
        values[i] = variableRotate
    }
    console.log(values)
    //[ 90, 108, 126, 144, 162, 180, 198, 180, 198, 216, 234, 252, 270 ] Theoretical Values

}

calculateTheoreticalOrbit()

//ahhhhhhhhhH
