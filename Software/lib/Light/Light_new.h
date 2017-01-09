#ifndef Light_new_h
#define Light_new_h

class Light{
public:

private:
    enum locationRobot{
        regular,
        online_left,
        online_right,
        online_top,
        online_back,
        overline_left,
        overline_right,
        overline_top,
        overline_back,
        lost
    }
    enum locationLine{
        regular,
        small_left,
        small_right,
        small_top,
        small_back,
        big_left,
        big_right,
        big_top,
        big_back,
        lost
    }

    locationRobot prevRobot = regular;
    locationRobot currRobot = regular;
    locationLine prevLine = regular;
    locationLine currLine = regular;
}

#endif
