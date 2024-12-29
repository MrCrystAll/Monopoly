#include <Monopoly/Utils.h>

int Random(int lowBound, int highBound){

	if (lowBound >= highBound) {
		ERR("Lower bound '" << lowBound << "' must be lower than higher bound '" << highBound << "'");
	}

	std::random_device device = std::random_device();
	std::uniform_int_distribution distrib = std::uniform_int_distribution(lowBound, highBound - 1);

	return distrib(device);
}
