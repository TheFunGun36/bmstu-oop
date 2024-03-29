#pragma once
#include <cstring>
#include "Point.hpp"
#include "Exit.hpp"
#include "Projection.hpp"

enum class Command {
    uninitialize,
    modelLoad,
    modelProjectPerspective,
    modelProjectOrhogonal,
    modelMove,
    modelScale,
    modelRotate,
    modelUndoAction,
    getErrorMessage,
};

union UserInput {
    //modelLoad
    const char *filename;

    //modelProjectPerspective
    double cameraDistance;

    //modelMove, modelScale, modelRotate
    Vector3D actionVector;

    //errorGetDescription
    int lineFailed;

    //getErrorMessage
    Exit exitCode;
};

union UserOutput {
    //modelProjectPerspective, modelProjectOrhogonal
    Projection projection;

    //errorMessage
    const char *errorMessage;
};

Exit executeCommand(UserOutput &uOut, const UserInput &uIn, Command cmd);

inline UserInput userInput() {
    UserInput ui; memset(&ui, 0, sizeof(ui));
    return ui;
}
inline UserInput userInput(const char *filename) {
    UserInput ui; ui.filename = filename;
    return ui;
}
inline UserInput userInput(double cameraDistance) {
    UserInput ui; ui.cameraDistance = cameraDistance;
    return ui;
}
inline UserInput userInput(Vector3D actionVector) {
    UserInput ui; ui.actionVector = actionVector;
    return ui;
}
inline UserInput userInput(int lineFailed) {
    UserInput ui; ui.lineFailed = lineFailed;
    return ui;
}
inline UserInput userInput(Exit exitCode) {
    UserInput ui; ui.exitCode = exitCode;
    return ui;
}
