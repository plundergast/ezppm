#include "ezppm.hpp"
#include <complex>

using namespace ezppm;
using namespace Colors;
using namespace std;


namespace DrawCommand_Examples {

	class mandlebrot_cmd final : public draw_cmd {
	public:
		int max_iterations = 100;
		float scale = 2.0f;
		float escape_radius = 16.0;

		complex<float> point = complex<float> (-1.5f, 0.0f);
		Image&  image;

		virtual Color operator()(int x, int y) override {
			complex<float> z, c;
			c.real (
				(float)((float)x / image.width ()) * 2.0f - 1.0f
			);
			c.imag (
				((float)((float)y / image.height ()) * 2.0f - 1.0f) * ((float)image.width () / image.height ())
			);
			c *= scale;
			c += point;
			z = c;

			int iteration = 1;
			for (iteration = 1; iteration < max_iterations && (z.real () * z.real () + z.imag () * z.imag ()) < escape_radius; iteration++) {
				z = z * z + c;
			}

			int col = (int)(((float)iteration / max_iterations) * 255.0f) % 255;

			return Color (col, col, col);
		};

		mandlebrot_cmd (Image& img) : image{ img } {}
	};


};

int main (int argc, char* argv[]) {
	using namespace DrawCommand_Examples;
	Image image (512, 512);

	mandlebrot_cmd mandlebrot (image);
	image.fill_expr (mandlebrot, 0, 0, image.width (), image.height ());
	image.write ("Mandlebrot Set");
	return 0;
}