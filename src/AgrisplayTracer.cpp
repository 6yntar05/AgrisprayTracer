#include <iostream>
#include <string>
#include "kml/dom.h"  // The KML DOM header.

int main() {
  // Parse KML from a memory buffer.
  std::string errors;
  kmldom::ElementPtr element = kmldom::Parse(
    "<kml>"
      "<Placemark>"
        "<name>hi</name>"
        "<Point>"
          "<coordinates>1,2,3</coordinates>"
        "</Point>"
      "</Placemark>"
    "</kml>",
    &errors);

  // Convert the type of the root element of the parse.
  const kmldom::KmlPtr kml = kmldom::AsKml(element);
  const kmldom::PlacemarkPtr placemark =
    kmldom::AsPlacemark(kml->get_feature());

  // Access the value of the <name> element.
  std::cout << "The Placemark name is: " << placemark->get_name()
    << std::endl;
}