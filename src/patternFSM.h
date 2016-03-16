typedef enum {
    RED_BUTTON = 1,
    YELLOW_BUTTON = 2,
    BLUE_BUTTON = 4,
    WHITE_BUTTON = 7
} buttonColors;


class PatternStateMachine {
public:
	PatternStateMachine();
	void input();
	void input(buttonColors button, buttonState state);

	int getPushedButtons();

private:
	void handlePush(buttonColors button);
	void handleRelease(buttonColors button);
	void patternComplete();

	const unsigned long pushThreshold = 100;
	const unsigned long patternThreshold = 300;

	unsigned long pushTime;
	unsigned long patternTime;

	unsigned int pushedButtons;

	unsigned int output;

	buttonState lastState_Red;
	buttonState lastState_Blue;
	buttonState lastState_Yellow;
	buttonState lastState_White;
};