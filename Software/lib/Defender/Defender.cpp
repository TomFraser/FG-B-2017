#include <Defender.h>

bool Defender::init(){
    compass.init();
    delay(10);
    compass.calibrate();
}

Vect2D Defender::getPixy(int pixyIn){
    if(pixyIn != 0){ //Seeing the goal
        pixyData currentPixy = {pixy.blocks[0].x, pixy.blocks[0].y, pixy.blocks[0].width, pixy.blocks[0].height, (pixy.blocks[0].width/pixy.blocks[0].height)};
        if(currentPixy.blockX >= PIXY_CENTRE_X){
            Vect2D left = {270, (-1*(PIXY_CENTRE_X - currentPixy.blockX))}; //These are flipped from normal because the camera is facing backwards
            Serial.println(currentPixy.blockX);
            return left;
        }else if(currentPixy.blockX <= PIXY_CENTRE_X){
            Vect2D right = {90, (-1*(PIXY_CENTRE_X - currentPixy.blockX))}; //These are flipped from normal because the camera is facing backwards
            Serial.println(currentPixy.blockX);
            return right;
        }
    }
    return {65506, 0.00}; //The goal is gone, wtf (Probs go into attack mode?)
}

double Defender::aimBall(int angle){
    double currentDirection = (int)getCompass();
    // double angleToBall = angle < 180 ? /*(int)getCompass() -*/ angle : /*(int)getCompass() +*/ -(360-angle); //The ammount we need to rotate from current direction to meet the ball
    if(angle > 400){
        return (double)getCompass();
    }
    // return angleToBall; //Make it snappy (Same as compass correction variable)
    if(angle < 180){
        return angle;
    }else{
        return -(360-angle);
    }
}

Vect2D Defender::calcScale(int pixyIn){
    //Some pixy shit aye
    delay(10);
    if(pixyIn != 0){ //Seeing the goal
        pixyData currentPixy = {pixy.blocks[0].x, pixy.blocks[0].y, pixy.blocks[0].width, pixy.blocks[0].height, (pixy.blocks[0].width/pixy.blocks[0].height)};
        if(doneRead){
            firstRead = currentPixy;
            doneRead = false;
        }
        if(currentPixy.width > firstRead.width){ //Current Goal is bigger than initial
            //Move Forward
            Vect2D forward = {0, (currentPixy.width - firstRead.width)};
            return forward;
        }else if(currentPixy.width < firstRead.width){ //Current goal is smaller than initial
            //Move Backward
            Vect2D backward = {180, (currentPixy.width - firstRead.width)};
            return backward;
        }
    }else{
        return {65506, 0.00};
    }
}

Vector3D Defender::calcDirection(int angle){
    int pixyBlocks = pixy.getBlocks();
    if(pixyBlocks != 0){
        //get Y Data (forwards and backwards)
        Vect2D Y = calcScale(pixyBlocks);
        //get X Data (left and right)
        Vect2D X = getPixy(pixyBlocks);
        //get Rotation
        double rotation = aimBall(angle);//Fix
        //Move on a direction
        Vector3D direction = calcVector(X,Y,rotation);
        //x = direction, y = strength, z = rotation
        Vector3D finals = {direction.x, direction.y, direction.z}; //three vects
        return finals;
    }else{
        Serial.println("NO GOAL DIRECTION");
        return {65506, 0.00, 0.00};
    }
}

Vector3D Defender::calcVector(Vect2D X, Vect2D Y, double rotation){
    //Calc Hypot with a^2 + b^2 = c^2
    int vectorStrength = sqrt(pow(X.strength, 2) + pow(Y.strength, 2));
    double direction = atan2(-(X.strength), (Y.strength))*radToAng;
    // Serial.println(X.strength);
    // rotation = rotation*0.1;
    //This value should be a direction that the robot needs to move in to intercept the ball
    return {direction, vectorStrength, rotation}; //3 vects
}

double Defender::getCompassGlobal(){
    return getCompass();
}

double Defender::getCompass(){
    compass.update();
    return compass.getHeading();
}
