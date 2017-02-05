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

//ahhhhhhhhhH
