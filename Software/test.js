
function calculateTheoreticalOrbit(){
    for(let i = 0; i < 12; i++){
        var angleIn = i*30;
        // console.log("Angle: " + angleIn)
        if(angleIn <= 301 || angleIn >= 59){
            //-50cos3x+50 (Maybe) [Confirmed]
            // Serial.println(angleIn < 180 ? (-50*cos(3*angleIn)+50) : -(-50*cos(3*angleIn)+50));
             console.log(angleIn < 180 ? (-50*Math.cos(3*angleIn)+50) : -(-50*Math.cos(3*angleIn)+50));
        }else{
            let tsop = angleIn/30;
            let frontalChange = tsop < 6 ? (tsop) : (12 - tsop);
            console.log(tsop < 6 ? (constrain(angleIn + 20 * frontalChange, 0.00, 270)) : (constrain(angleIn - 20 * frontalChange, 90.00, 360)));
        }
    }
}

calculateTheoreticalOrbit();
//ahhhhhhhhhH
