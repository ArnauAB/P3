/// @file

#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>

#include "wavfile_mono.h"
#include "pitch_analyzer.h"

#include "docopt.h"

#define FRAME_LEN   0.030 /* 30 ms. */
#define FRAME_SHIFT 0.015 /* 15 ms. */

using namespace std;
using namespace upc;

static const char USAGE[] = R"(
get_pitch - Pitch Estimator 

Usage:
    get_pitch [options] <input-wav> <output-txt>
    get_pitch (-h | --help)
    get_pitch --version

Options:
    --llindar-pot FLOAT   Decision Threshold for power [default: -45]
    --llindar-r1 FLOAT    Decision Threshold for r1 [default: 0.55]
    --llindar-rmax FLOAT  Decision Threshold for rmax [default: 0.38]
    --thresh_cclip FLOAT  Decision Threshold for cclip [default: 0.0005]
    -h, --help            Show this screen
    --version             Show the version of the project

Arguments:
    input-wav   Wave file with the audio signal
    output-txt  Output file: ASCII file with the result of the estimation:
                    - One line per frame with the estimated f0
                    - If considered unvoiced, f0 must be set to f0 = 0
)";

int main(int argc, const char *argv[]) {
	/// \TODO 
	///  Modify the program syntax and the call to **docopt()** in order to
	///  add options and arguments to the program.
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        {argv + 1, argv + argc},	// array of arguments, without the program name
        true,    // show help if requested
        "2.0");  // version string

	std::string input_wav = args["<input-wav>"].asString();
	std::string output_txt = args["<output-txt>"].asString();
  float llindar_pot = stof(args["--llindar-pot"].asString());
  float llindar_r1 = stof(args["--llindar-r1"].asString());
  float llindar_rmax = stof(args["--llindar-rmax"].asString());
  float llindar_cclip = stof(args["--llindar-cclip"].asString());

  // Read input sound file
  unsigned int rate;
  vector<float> x;
  if (readwav_mono(input_wav, rate, x) != 0) {
    cerr << "Error reading input file " << input_wav << " (" << strerror(errno) << ")\n";
    return -2;
  }

  int n_len = rate * FRAME_LEN;
  int n_shift = rate * FRAME_SHIFT;

  // Define analyzer
  PitchAnalyzer analyzer(n_len, rate, PitchAnalyzer::RECT, 50, 500, llindar_pot, llindar_r1, llindar_rmax); //AÑADIR ARGUMENTO llindar_rmax

  /// \TODO
  /// Preprocess the input signal in order to ease pitch estimation. For instance,
  /// central-clipping or low pass filtering may be used.
  float max = *std::max_element(x.begin(), x.end());
  for(int i = 0; i < (int)x.size(); i++) {
    if(abs(x[i]) < thresh_cclip*max) {
      x[i] = 0.0F;
    } 
  }

  // Iterate for each frame and save values in f0 vector
  vector<float>::iterator iX;
  vector<float> f0;
  for (iX = x.begin(); iX + n_len < x.end(); iX = iX + n_shift) {
    float f = analyzer(iX, iX + n_len);
    f0.push_back(f);
  }

  /// \TODO
  /// Postprocess the estimation in order to supress errors. For instance, a median filter
  /// or time-warping may be used.
  #if 1
  for (unsigned int i = 1; i < f0.size() - 1; i++)
  {
    vector<float> vector(3);
    vector[0] = f0[i];
    vector[1] = f0[i+1];
    vector[2] = f0[i-1];

    if (vector[1] < vector[0])
      swap(vector[0], vector[1]);

    if (vector[2] < vector[1]){
      swap(vector[1], vector[2]);
      if (vector[1] < vector[0])
        swap(vector[1], vector[0]);
    }
    f0[i] = vector[1];
  }
  #endif
  
  // Write f0 contour into the output file
  ofstream os(output_txt);
  if (!os.good()) {
    cerr << "Error reading output file " << output_txt << " (" << strerror(errno) << ")\n";
    return -3;
  }

  os << 0 << '\n'; //pitch at t=0
  for (iX = f0.begin(); iX != f0.end(); ++iX) 
    os << *iX << '\n';
  os << 0 << '\n';//pitch at t=Dur

  return 0;
}
