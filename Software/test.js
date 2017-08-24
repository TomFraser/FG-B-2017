
// function calculateTheoreticalOrbit(){
//     for(let i = 0; i < 12; i++){
//         var angleIn = i*30;
//         // console.log("Angle: " + angleIn)
//         if(angleIn <= 301 || angleIn >= 59){
//             //-50cos3x+50 (Maybe) [Confirmed]
//             // Serial.println(angleIn < 180 ? (-50*cos(3*angleIn)+50) : -(-50*cos(3*angleIn)+50));
//              console.log(angleIn < 180 ? (-50*Math.cos(3*angleIn)+50) : -(-50*Math.cos(3*angleIn)+50));
//         }else{
//             let tsop = angleIn/30;
//             let frontalChange = tsop < 6 ? (tsop) : (12 - tsop);
//             console.log(tsop < 6 ? (constrain(angleIn + 20 * frontalChange, 0.00, 270)) : (constrain(angleIn - 20 * frontalChange, 90.00, 360)));
//         }
//     }
// }
//
// calculateTheoreticalOrbit();
//

// console.log(360-(-50*Math.cos(2*(300*(Math.PI/180)))+50))

function calcOrbit(){
    let angToRad = 0.01745329251
    for(let i = 0; i < 24; i++){
        let tsopAngle = i*15
        if(tsopAngle <= 60 || tsopAngle >= 300){ //Front
            // return angleIn < 180 ? angleIn +((0.5 * cos(2*(angleIn*angToRad))+0.5) * 90) : angleIn + ((0.5 * cos(2*((360 * angToRad) - angleIn*angToRad))+0.5) * 90);
            console.log(tsopAngle < 180 ? ((-0.5 * Math.cos(3*(tsopAngle * angToRad))+0.5) * (tsopAngle + 90)) : 360 - ((-0.5 * Math.cos(3*(tsopAngle*angToRad))+0.5) * (360-tsopAngle + 90)))
            //---> Final C++ Line // return angleIn < 180 ? ((-0.5 * cos(2*(angleIn * angToRad)) + 0.5) * (angleIn + 90)) : ((-0.5 * cos(2*(angleIn * angToRad)) + 0.5) * (angleIn - 90));
        }else{
            console.log(tsopAngle < 180 ? (tsopAngle + 90) : (tsopAngle - 90))
        }
    }
}

calcOrbit()
