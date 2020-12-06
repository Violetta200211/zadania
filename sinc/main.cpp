# include <fstream>
# include <vector>
# include <cstdint>
# include <cmath>
# include <sstream>
# include <iostream>
# define _USE_MATH_DEFINES
# pragma pack(push, 1)

struct TGA {
	uint8_t id_len;
	uint8_t pal_type;
	uint8_t img_type;
	uint8_t pal_desc[5];
	uint16_t xpos, ypos;
	uint16_t w, h;
	uint8_t bpp;
	uint8_t img_desc;
};
constexpr uint16_t W = 1920, H = 1080;
constexpr double sx = 40, sy = 40, sz = 400, s1 = 0.09, s2 = 0.01, x_min = -30,
		x_max = 30, y_min = -30, y_max = 30;
std::vector<int> hor;

# pragma pack(pop)

double sinc(double x) {
	if (x == 0)
		return 1;
	return sin(x) / x;
}

void plot(std::vector<uint32_t> &p, int x, int y, uint32_t c) {
	if (x < 0 || x >= W)
		return;
	if (y >= hor[x])
		return;
	hor[x] = y;
	if (y < 0 || y >= H)
		return;
	p[y * W + x] = c;
}

int main() {
	TGA h { };
	hor.resize(W);
	for (auto &&a : hor)
		a = H;

	std::vector<uint32_t> img;
	img.resize(W * H);
	for (auto &&c : img)
		c = 0xff00003f;
	for (double x = x_max; x >= x_min; x -= s1) {
		for (double y = y_max; y >= y_min; y -= s2) {
			double z = sinc(sqrt(x * x + y * y));
			int rx = int(
					W / 2 - sx * x * cos(M_PI / 6) + sy * y * cos(M_PI / 6));
			int ry = int(
					H / 2 + sx * x * sin(M_PI / 6) + sy * y * sin(M_PI / 6)
							- sz * z);
			plot(img, rx, ry, 0xffff0000);

		}
	}
	for (auto &&a : hor)
		a = H;
	for (double y = y_max; y >= y_min; y -= s1) {
		for (double x = x_max; x >= x_min; x -= s2) {
			double z = sinc(sqrt(x * x + y * y));
			int rx = int(
					W / 2 - sx * x * cos(M_PI / 6) + sy * y * cos(M_PI / 6));
			int ry = int(
					H / 2 + sx * x * sin(M_PI / 6) + sy * y * sin(M_PI / 6)
							- sz * z);
			plot(img, rx, ry, 0xffff0000);

		}
	}

	std::fstream f;
	h.img_type = 2;
	h.w = W;
	h.h = H;
	h.bpp = 32;
	h.img_desc = 0x28;
	f.open("1.tga", std::ios::out | std::ios::binary);
	f.write(reinterpret_cast<char*>(&h), sizeof(TGA));
	f.write(reinterpret_cast<char*>(&img[0]), W * H * 4);
	f.close();
	return 0;
}
