
typedef enum {
    RELEASE = 0,
    DEBOUNCE = 1,
    PUSH = 2,
    HOLD = 3
} buttonState;

class ButtonStateMachine {
public:
    ButtonStateMachine();    
    buttonState getState();
    void input(int hardwareState);

private:
    void transitionDebounce(int fromState);
    void transitionPush();
    void transitionRelease();
    void transitionHold();

    int lastHardwareState;
    buttonState state;
    unsigned long startTime;

    unsigned long debounceThreshold = 10;
    unsigned long holdThreshold = 3000;
};