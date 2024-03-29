#include "pch.h"
#include "jpolygonalmodelcreator.h"
#include "jpolygonalmodel3d_impl.h"
#include "jvector3d.h"
#include <istream>
#include <sstream>
#include <fstream>

namespace Jora {
std::unique_ptr<SceneObject> PolygonalModel3DStreamDirector::create() const {
    PolygonalModel3DStreamBuilder builder;
    std::unique_ptr<SceneObject> result;
    if (builder.createModel() &&
        builder.readData(*_stream) &&
        builder.validate())
        result = builder.get();
    return result;
}

bool PolygonalModel3DStreamBuilder::createModel() noexcept {
    _model = std::make_unique<Model3D>(std::make_shared<PolygonalModel3DImpl>());
    return bool(_model);
}

bool PolygonalModel3DStreamBuilder::readData(std::istream& stream) noexcept {
    std::string line;
    bool result = true;
    while (result && std::getline(stream, line))
        if (!line.empty())
            result = processLine(std::stringstream(line));
    return true;
}

bool PolygonalModel3DStreamBuilder::validate() noexcept {
    return _model->isValid();
}

bool PolygonalModel3DStreamBuilder::processLine(std::istream&& lineStream) {
    bool result = false;
    std::string firstWord;

    if (lineStream >> firstWord) {
        if (firstWord == "v")
            result = processVertex(std::move(lineStream));
        else if (firstWord == "f")
            result = processFace(std::move(lineStream));
        else
            result = true;
    }

    return result;
}

bool PolygonalModel3DStreamBuilder::processVertex(std::istream&& lineStream) {
    Vector3D point;
    bool result = false;

    if (lineStream >> point.x() >> point.y() >> point.z()) {
        auto implPtr = _model->implementation();
        auto& impl = dynamic_cast<PolygonalModel3DImpl&>(*implPtr);
        result = true;
        impl.addVertex(std::move(point));
    }

    return result;
}

bool PolygonalModel3DStreamBuilder::processFace(std::istream&& lineStream) {
    using std::array;
    bool result = true;

    std::string word;
    array<size_t, 3> idx;

    for (int i = 0; result && i < 3; i++) {
        if (lineStream >> word)
            idx[i] = std::stol(word) - 1;
        else
            result = false;
    }

    if (result) {
        auto implPtr = _model->implementation();
        auto& impl = dynamic_cast<PolygonalModel3DImpl&>(*implPtr);

        impl.addFace(array(idx));

        while (lineStream >> word) {
            idx[0] = idx[1];
            idx[1] = idx[2];
            idx[2] = std::stol(word) - 1;
            impl.addFace(array(idx));
        }
    }

    return result;
}

void PolygonalModel3DStreamDirector::assignStream(const std::shared_ptr<std::istream>& stream) noexcept {
    _stream = stream;
}

bool PolygonalModel3DStreamDirector::openStream(const std::string& filename) {
    auto tmp = std::make_shared<std::ifstream>(filename);
    bool result = false;

    if (tmp->is_open()) {
        _stream = tmp;
        result = true;
    }

    return result;
}


}