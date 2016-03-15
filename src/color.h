class Color {
public:
	Color(int r, int g, int b, float scale);
	uint32_t calcRep();
	uint32_t getRep();

private:
	int red;
	int green;
	int blue;
	float scale;
	uint32_t c;
};