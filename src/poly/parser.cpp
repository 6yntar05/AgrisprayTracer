#include "poly/parser.h"

#include <iostream>
#include <kml/dom/kml22.h>
#include <string>

#include <kml/dom.h>
#include <kml/base/file.h>

namespace agris::input {
namespace kml {
    static geo::boundary processLinearRing(kmldom::CoordinatesPtr kmlCoords) {
        geo::boundary boundary;

        for (size_t i = 0; i < kmlCoords->get_coordinates_array_size(); i++) {
            geo::coordinate coord {
                kmlCoords->get_coordinates_array_at(i).get_latitude(),
                kmlCoords->get_coordinates_array_at(i).get_longitude()
            };
            boundary.push_back(coord);
        }

        return boundary;
    }

    static geo::field processPolygon(const kmldom::PolygonPtr poly) {
        geo::field field;

        // Extract outer boundary
        if (!poly->has_outerboundaryis())
            std::cerr << "Unable to find outerBoundary\n";
        auto coords = poly->get_outerboundaryis()->get_linearring()->get_coordinates();
        field.outerBoundary = processLinearRing(coords);

        // Extract inner boundaries
        std::vector<geo::boundary> inner;
        for (size_t i = 0; i < poly->get_innerboundaryis_array_size(); i++)
            inner.push_back(
                processLinearRing(poly->get_innerboundaryis_array_at(i)->get_linearring()->get_coordinates())
            );
        field.innerBoundaries = inner;

        return field;
    }

    static geo::field processMultiGeometry(const kmldom::MultiGeometry* multi_geometry) {
        // Extract single geometry
        if (multi_geometry->get_geometry_array_size() != 1)
            std::cerr << "[!!!] Unsupported geometry count! It only makes sense to process single geometry" << std::endl;
        const kmldom::GeometryPtr& singleGeometry = multi_geometry->get_geometry_array_at(0);

        // Process every geometry derivative
        if (singleGeometry->Type() != kmldom::Type_Polygon)
            std::cerr << "[!!!] Unsupported geometry data! It only makes sense to process polygons" << std::endl;
        
        const kmldom::PolygonPtr& polygon = kmldom::AsPolygon(singleGeometry);
        return processPolygon(polygon);
    }

    static geo::field processGeometry(const kmldom::GeometryPtr geometry) {
        geo::field field;

        switch (geometry.get()->Type()) {
            case kmldom::Type_MultiGeometry:
                field = kml::processMultiGeometry(
                    kmldom::AsMultiGeometry(geometry).get()
                );
                break;

            case kmldom::Type_Polygon:
                field = kml::processPolygon(
                    kmldom::AsPolygon(geometry).get()
                );
                break;
                
            default:
                std::cerr << "[!!!] Unknown geometry type!\n"
                    << "\tSupported: kmldom::Type_MultiGeometry consisting of Polygons or Polygon itself"
                    << std::endl;
        }
        
        return field;
    }
} // namespace kml

static void cropToPlacemarks(
    std::string& code, const std::string_view startTag = "<Placemark", const std::string_view endTag = "</Placemark>"
) {
    // DANGEROUS! Hard-coded XML tags! -> TODO: Get rid
    size_t start = code.find(startTag);
    size_t stop = code.find(endTag);
    size_t stopTagLen = endTag.size();

    code = "<kml>\n" + code.substr(start, stop - start + stopTagLen) + "\n</kml>";
}

geo::field parseFile(const std::string path) {
    // Read .kml code from file
    std::string code;
    kmlbase::File::ReadFileToString(path, &code);
    agris::input::cropToPlacemarks(code); // Temporary! TODO: get rid

    // Parse code
    std::string errors;
    kmldom::ElementPtr element = kmldom::Parse(code, &errors);
    if (errors.size())
        std::cerr << errors << std::endl;

    // Convert the type of the root element of the parse.
    const kmldom::KmlPtr kml = kmldom::AsKml(element);
    const kmldom::PlacemarkPtr placemark = kmldom::AsPlacemark(kml->get_feature());

    // Parse (Multi)Geometry / Polygon if exist
    if (!placemark->has_geometry())
        std::cerr << "[!!!] Placemart has no geometry!\n";
    return kml::processGeometry(placemark->get_geometry());
}

} // namespace agris::input