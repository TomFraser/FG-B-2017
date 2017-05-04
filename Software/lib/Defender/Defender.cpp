#include <Defender.h>

bool Defender::init(){
    //Pixy
    if(pixy.getBlocks()){ //Seeing the goal
        pixyData initial = {pixy.blocks[0].x, pixy.blocks[0].y, pixy.blocks[0].width, pixy.blocks[0].height, (pixy.blocks[0].width/pixy.blocks[0].height)};
    }
    compass.init();
    delay(10);
    compass.calibrate();
}

Vect2D Defender::getPixy(){
    if(pixy.getBlocks()){ //Seeing the goal
        pixyData currentPixy = {pixy.blocks[0].x, pixy.blocks[0].y, pixy.blocks[0].width, pixy.blocks[0].height, (pixy.blocks[0].width/pixy.blocks[0].height)};

        if(currentPixy.blockX >= PIXY_CENTRE_X){
            Vect2D left = {270, (-1*(PIXY_CENTRE_X - currentPixy.blockX))}; //These are flipped from normal because the camera is facing backwards
            return left;
        }else if(currentPixy.blockX <= PIXY_CENTRE_X){
            Vect2D right = {90, (-1*(PIXY_CENTRE_X - currentPixy.blockX))}; //These are flipped from normal because the camera is facing backwards
            return right;
        }
    }
    return nothing; //The goal is gone, wtf (Probs go into attack mode?)
}

double Defender::aimBall(int angle){
    double currentDirection = (int)getCompass();
    double angleToBall = angle < 180 ? (int)getCompass() + angle : (int)getCompass() - angle; //The ammount we need to rotate from current direction to meet the ball
    return angleToBall * DEFENDER_MULTIPLIER; //Make it snappy (Same as compass correction variable)
}

Vect2D Defender::calcScale(){
    //Some pixy shit aye
    if(pixy.getBlocks()){ //Seeing the goal
        // pixyData initial = {0,0,0,0,0};
        pixyData currentPixy = {pixy.blocks[0].x, pixy.blocks[0].y, pixy.blocks[0].width, pixy.blocks[0].height, (pixy.blocks[0].width/pixy.blocks[0].height)};
        if(currentPixy.width >= initial.width){ //Current Goal is bigger than initial
            //Move Forward
            Vect2D forward = {0, (currentPixy.width - initial.width)};
            return forward;
        }else if(currentPixy.width <= initial.width){ //Current goal is smaller than initial
            //Move Backward
            Vect2D backward = {180, (currentPixy.width - initial.width)};
            return backward;
        }
    }else{
        return nothing;
    }
}

Vect2D Defender::calcDirection(int angle){
    //get Y Data (forwards and backwards)
    Vect2D Y = calcScale();
    //get X Data (left and right)
    Vect2D X = getPixy();
    //get Rotation
    double rotation = aimBall(angle);//Fix
    //Move on a direction
    Vect2D direction = calcVector(X,Y,rotation);
    Vect2D finals = {direction.direction, direction.strength};
    return finals;
}

Vect2D Defender::calcVector(Vect2D X, Vect2D Y, double rotation){
    //Calc Hypot with a^2 + b^2 = c^2
    int vectorStrength = sqrt(pow(X.strength, 2) + pow(Y.strength, 2));
    //X on Hypot
    double direction = asin((X.strength/vectorStrength)) * radToAng;
    //This value should be a direction that the robot needs to move in to intercept the ball
    //The strength shouldnt matter, it should just be a set speed
    // Vect2D finals = {direction, DEFENDER_SPEED};
    return {direction, DEFENDER_SPEED};
}

double Defender::getCompassGlobal(){
    return getCompass();
}

double Defender::getCompass(){
    compass.update();
    return compass.getHeading();
}
