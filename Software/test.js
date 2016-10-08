
function log(){
    var angle = 21;
    var dirNum = 4;
    var angToRad = 0.01745329251;
    var radToAng = 57.2957795131;
    var array = [60, 180, 300];

    var newAngle = (Math.abs(Math.round(angle/(360*1/dirNum))))*(360*1/dirNum);

    var newNum = Math.cos(((array[0] + 90) * angToRad) - (newAngle * angToRad));

    console.log(newNum * 255);
}

log();
