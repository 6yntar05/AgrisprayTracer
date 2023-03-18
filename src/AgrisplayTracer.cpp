#include <iostream>
#include <string>

#include "poly/reader.h"
#include "kml/dom.h"

int main() {
	const std::string file = agris::readfile("./2.kml");
	std::cerr << file << std::endl;

	std::string errors;
	kmldom::ElementPtr element = kmldom::Parse(file, &errors);

	// Convert the type of the root element of the parse.
	const kmldom::KmlPtr kml = kmldom::AsKml(element);
	const kmldom::PlacemarkPtr placemark =
		kmldom::AsPlacemark(kml->get_feature());

	// Access the value of the <name> element.
	std::cout << "The Placemark name is: " << placemark->get_name() << std::endl;
}