#include "RubikCubeSolver.h"

RubikCubeSolver::RubikCubeSolver()
{}

RubikCubeSolver::~RubikCubeSolver()
{}

string RubikCubeSolver::moveRe = "";

// The function to apply the algorithm to transform to the solved state
string RubikCubeSolver::solveCube(RubikCube* cube)
{
    moveRe = "";
    string cmd = "";
    GLint posts[54];
    if (cube->ptr_face_color_buffer_data()[22] == 0)
        {cube->applyMoves("X"); moveRe += "X";}
    else if (cube->ptr_face_color_buffer_data()[13] == 0)
        {cube->applyMoves("XX"); moveRe += "XX";}
    else if (cube->ptr_face_color_buffer_data()[31] == 0)
        {cube->applyMoves("x"); moveRe += "x";}
    else if (cube->ptr_face_color_buffer_data()[40] == 0)
        {cube->applyMoves("Z"); moveRe += "Z";}
    if (cube->ptr_face_color_buffer_data()[49] == 0)
        {cube->applyMoves("z"); moveRe += "z";}

    for (int i = 0; i < 4; ++i){
        if (cube->ptr_face_color_buffer_data()[22] == 2)
            break;
        else
        {cube->applyMoves("y"); moveRe += "y";}
    }

    while (cube->ptr_facets_buffer_data()[1] != 1 ||
           cube->ptr_facets_buffer_data()[3] != 3 ||
           cube->ptr_facets_buffer_data()[5] != 5 ||
           cube->ptr_facets_buffer_data()[7] != 7)
            solveCross(cube);
    while (cube->ptr_facets_buffer_data()[8] != 8 ||
           cube->ptr_facets_buffer_data()[2] != 2 ||
           cube->ptr_facets_buffer_data()[0] != 0 ||
           cube->ptr_facets_buffer_data()[6] != 6)
            solveFirstLayer(cube);
    {cube->applyMoves("XXYY"); moveRe +="XXYY";}
    solveSecondLayer(cube);

    while (cube->ptr_face_color_buffer_data()[1] != 1 ||
           cube->ptr_face_color_buffer_data()[3] != 1 ||
           cube->ptr_face_color_buffer_data()[5] != 1 ||
           cube->ptr_face_color_buffer_data()[7] != 1)
        solveYellowCrossOLL(cube);

    while (cube->ptr_face_color_buffer_data()[0] != 1 ||
           cube->ptr_face_color_buffer_data()[2] != 1 ||
           cube->ptr_face_color_buffer_data()[6] != 1 ||
           cube->ptr_face_color_buffer_data()[8] != 1)
        solveLastFace(cube);

    solveLastLayer(cube);
    {cube->applyMoves("XX"); moveRe +="XX";}

    return moveRe;
}

void RubikCubeSolver::solveLastLayer(RubikCube* cube)
{

    /// Solving the corners first
    while (true)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (cube->ptr_face_color_buffer_data()[18] !=
                cube->ptr_face_color_buffer_data()[29])
                    {cube->applyMoves("U"); moveRe +="U";}
        }
        {cube->applyMoves("XRRDDRUrDDRuRXXX"); moveRe +="XRRDDRUrDDRuRXXX";}
        for (int i = 0; i < 4; ++i)
        {
            if (cube->ptr_face_color_buffer_data()[18] !=
                cube->ptr_face_color_buffer_data()[22])
                    {cube->applyMoves("U"); moveRe +="U";}
        }
        if (cube->ptr_face_color_buffer_data()[45] == cube->ptr_face_color_buffer_data()[49] &&
            cube->ptr_face_color_buffer_data()[27] == cube->ptr_face_color_buffer_data()[31] &&
            cube->ptr_face_color_buffer_data()[36] == cube->ptr_face_color_buffer_data()[40] )
        break;
    }
    // Last step: orient the edges
    while (true)
    {
        int i = 0;
        for (i = 0; i < 4; ++i)
        {
            if (cube->ptr_face_color_buffer_data()[28] !=
                cube->ptr_face_color_buffer_data()[31])
                    {cube->applyMoves("Y"); moveRe +="Y";}
            else break;
        }
        if (i < 4) break;
        else {cube->applyMoves("FFULrFFlRUFF"); moveRe +="FFULrFFlRUFF";}
    }

        if (cube->ptr_face_color_buffer_data()[37] == cube->ptr_face_color_buffer_data()[49])
            {cube->applyMoves("FFULrFFlRUFF"); moveRe +="FFULrFFlRUFF";}
        else {cube->applyMoves("FFuLrFFlRuFF"); moveRe +="FFuLrFFlRuFF";}
        if (cube->ptr_face_color_buffer_data()[19] != cube->ptr_face_color_buffer_data()[22])
        {
            if (cube->ptr_face_color_buffer_data()[37] == cube->ptr_face_color_buffer_data()[49])
            {cube->applyMoves("FFULrFFlRUFF"); moveRe +="FFULrFFlRUFF";}
        else {cube->applyMoves("FFuLrFFlRuFF"); moveRe +="FFuLrFFlRuFF";}
        }

}

void RubikCubeSolver::solveLastFace(RubikCube* cube)
{
    /// make all the corners yellow on top face
    for (int t = 0; t < 4; ++t){

    string tempStr = "";
    for (int i = 0; i < 54; ++i)
    {
        stringstream ss;
        if (cube->ptr_face_color_buffer_data()[i] == 1)
            {
                ss << i;
                tempStr += ss.str();
            }
    }
    if (tempStr == "134567202947") {{cube->applyMoves("RUrURuur"); moveRe +="RUrURuur";} return;}
    else if (tempStr == "1345720273638") {{cube->applyMoves("RuurruRRurrUUR"); moveRe +="RuurruRRurrUUR";} return;}
    else if (tempStr == "01345672027") {{cube->applyMoves("XruLURulUXXX"); moveRe +="XruLURulUXXX";} return;}
    else if (tempStr == "01234571820") {{cube->applyMoves("rrDrUURdrUUr"); moveRe +="rrDrUURdrUUr";} return;}
    else if (tempStr == "013457182745") {{cube->applyMoves("ruRurUUR"); moveRe +="ruRurUUR";} return;}
    else if (tempStr == "1345736384547") {{cube->applyMoves("RUrURurURUUr"); moveRe +="RUrURurURUUr";} return;}
    else if (tempStr == "01345781847") {{cube->applyMoves("rFRbrfRB"); moveRe +="rFRbrfRB";} return;}
        {cube->applyMoves("Y"); moveRe +="Y";}
    }
}

void RubikCubeSolver::solveYellowCrossOLL(RubikCube* cube)
{
    /// make all the corners yellow on top face
    for (int t = 0; t < 4; ++t){

    string tempStr = "";
    for (int i = 0; i < 9; ++i)
    {
        if (i != 0 && i != 2 && i != 6 && i != 8)
        if (cube->ptr_face_color_buffer_data()[i] == 1)
            {
                stringstream ss;
                ss << i;
                tempStr += ss.str();
            }
    }
    if (tempStr == "4") {{cube->applyMoves("rFRfUUrFRffUUF"); moveRe +="rFRfUUrFRffUUF";} return;}
    else if (tempStr == "134") {{cube->applyMoves("FURurf"); moveRe +="FURurf";} return;}
    else if (tempStr == "345") {{cube->applyMoves("FRUruf"); moveRe +="FRUruf";} return;}
        {cube->applyMoves("Y"); moveRe +="Y";}
    }
}

void RubikCubeSolver::solveYellowCross(RubikCube* cube)
{
    GLint posts[54];
    /// solve the upper 1 cross
        for (int i = 0; i < 54; ++i)
                posts[cube->ptr_facets_buffer_data()[i]] = i;
    // State 1: No 1 facet on top face
    if (cube->ptr_face_color_buffer_data()[1] == 1 &&
        cube->ptr_face_color_buffer_data()[3] == 1 &&
        cube->ptr_face_color_buffer_data()[7] == 1 &&
        cube->ptr_face_color_buffer_data()[5] == 1)
        return;
    if (cube->ptr_face_color_buffer_data()[1] != 1 &&
        cube->ptr_face_color_buffer_data()[3] != 1 &&
        cube->ptr_face_color_buffer_data()[7] != 1 &&
        cube->ptr_face_color_buffer_data()[5] != 1)
        {
            {cube->applyMoves("FURurf"); moveRe +="FURurf";}
        }
    if (cube->ptr_face_color_buffer_data()[1] == 1 &&
             cube->ptr_face_color_buffer_data()[3] == 1)
    {
        {cube->applyMoves("FURurf"); moveRe +="FURurf";}
    }
    else if (cube->ptr_face_color_buffer_data()[1] == 1 &&
             cube->ptr_face_color_buffer_data()[5] == 1)
    {
        for (int i = 0; i < 3; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
        {cube->applyMoves("FURurf"); moveRe +="FURurf";}
        {cube->applyMoves("Y"); moveRe +="Y";}
    }
    else if (cube->ptr_face_color_buffer_data()[3] == 1 &&
             cube->ptr_face_color_buffer_data()[7] == 1)
    {
        {cube->applyMoves("Y"); moveRe +="Y";}
        {cube->applyMoves("FURurf"); moveRe +="FURurf";}
        for (int i = 0; i < 3; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
    }
    else if (cube->ptr_face_color_buffer_data()[5] == 1 &&
             cube->ptr_face_color_buffer_data()[7] == 1)
    {
        for (int i = 0; i < 2; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
        {cube->applyMoves("FURurf"); moveRe +="FURurf";}
        for (int i = 0; i < 2; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
    }
    else if (cube->ptr_face_color_buffer_data()[3] == 1 &&
        cube->ptr_face_color_buffer_data()[5] == 1)
        {cube->applyMoves("FRUruf"); moveRe +="FRUruf";}
    else if (cube->ptr_face_color_buffer_data()[1] == 1 &&
             cube->ptr_face_color_buffer_data()[7] == 1)
    {
        {cube->applyMoves("Y"); moveRe +="Y";}
        {cube->applyMoves("FRUruf"); moveRe +="FRUruf";}
        for (int i = 0; i < 3; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
    }
}

void RubikCubeSolver::solveSecondLayer(RubikCube* cube)
{
    int posts[54];
    int num[4] = {21, 39, 30, 48};
    for (int i = 0; i < 4; ++i){
        for (int i = 0; i < 54; ++i)
                posts[cube->ptr_facets_buffer_data()[i]] = i;
        while (true){

        switch (posts[num[i]]){
        case 19: {cube->applyMoves("URurufUF"); moveRe +="URurufUF";} break;
        case 5:  {cube->applyMoves("ufUFURur"); moveRe +="ufUFURur";} break;
        case 7:  {cube->applyMoves("uufUFURur"); moveRe +="uufUFURur";} break;
        case 46: {cube->applyMoves("UURurufUF"); moveRe +="UURurufUF";} break;
        case 3: {cube->applyMoves("uuufUFURur"); moveRe +="uuufUFURur";} break;
        case 37: {cube->applyMoves("uURurufUF"); moveRe +="uURurufUF";} break;
        case 1: {cube->applyMoves("UufUFURur"); moveRe +="UufUFURur";} break;
        case 28: {cube->applyMoves("UUURurufUF"); moveRe +="UUURurufUF";} break;
        case 48: {cube->applyMoves("URurufUF"); moveRe +="URurufUF";} break;
        case 21:
            for (int i = 0; i < 3; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
            {cube->applyMoves("URurufUF"); moveRe +="URurufUF";}
            {cube->applyMoves("Y"); moveRe +="Y";}
            break;
        case 41:
            for (int i = 0; i < 3; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
            {cube->applyMoves("URurufUF"); moveRe +="URurufUF";}
            {cube->applyMoves("Y"); moveRe +="Y";}
            break;
        case 30:
            {cube->applyMoves("Y"); moveRe +="Y";}
            {cube->applyMoves("URurufUF"); moveRe +="URurufUF";}
            for (int i = 0; i < 3; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
            break;
        case 50:
            {cube->applyMoves("y"); moveRe +="y";}
            {cube->applyMoves("URurufUF"); moveRe +="URurufUF";}
            for (int i = 0; i < 3; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
            break;
        case 32:
            for (int i = 0; i < 2; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
            {cube->applyMoves("URurufUF"); moveRe +="URurufUF";}
            for (int i = 0; i < 2; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
            break;
        case 39:
            for (int i = 0; i < 2; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
            {cube->applyMoves("URurufUF"); moveRe +="URurufUF";}
            for (int i = 0; i < 2; ++i) {cube->applyMoves("Y"); moveRe +="Y";}
            break;
        }
            for (int i = 0; i < 54; ++i)
                posts[cube->ptr_facets_buffer_data()[i]] = i;

            if (posts[num[i]] == 23) break;
        }
        {cube->applyMoves("Y"); moveRe +="Y";}
    }
}

void RubikCubeSolver::solveFirstLayer(RubikCube* cube)
{
    GLint posts[54];
    string cmd;
    /// Solve the first layer
    int num[4] = {8, 2, 0, 6};
    for (int x = 0; x < 4; ++x)
        {
            for (int i = 0; i < 54; ++i)
                    posts[cube->ptr_facets_buffer_data()[i]] = i;
        while (true)
        {
            if (posts[num[x]] == 8 && cube->ptr_facets_buffer_data()[20] == cube->ptr_facets_buffer_data()[19] + 1) break;
            switch (posts[num[x]]){
            case 24:cmd = "D"; break;
            case 44: cmd = "D"; break;
            case 9: cmd = "D"; break;
            case 53: cmd = "d"; break;
            case 33: cmd = "d"; break;
            case 17: cmd = "d"; break;
            case 35: cmd = "DD"; break;
            case 42: cmd = "DD"; break;
            case 15: cmd = "DD"; break;
            case 2: cmd = "bdB"; break;
            case 47: cmd = "bdB"; break;
            case 27: cmd = "bdB"; break;
            case 0: cmd = "BDDb"; break;
            case 36: cmd = "BDDb"; break;
            case 29: cmd = "BDDb"; break;
            case 6: cmd = "LDl"; break;
            case 18: cmd = "LDl"; break;
            case 38: cmd = "LDl"; break;
            case 26: cmd = "FDf"; break;
            case 51: cmd = "rdR"; break;
            case 11: cmd = "rDRFDDf"; break;
            default: cmd = "rdRD";
            }
            cube->applyMoves(cmd); moveRe +=cmd;
            for (int i = 0; i < 54; ++i)
                posts[cube->ptr_facets_buffer_data()[i]] = i;
            if (posts[num[x]] == 8 && cube->ptr_facets_buffer_data()[20] == cube->ptr_facets_buffer_data()[19] + 1) break;
        }
        {cube->applyMoves("Y"); moveRe +="Y";}
    }
}


/// Solve the white cross
///
void RubikCubeSolver::solveCross(RubikCube* cube)
{
    string cmd;
    GLint posts[54];
    int num[4] = {7, 5, 1, 3};
    for (int i = 0; i < 4; ++i)
        {

        for (int i = 0; i < 54; ++i)
            posts[cube->ptr_facets_buffer_data()[i]] = i;
        switch (posts[num[i]]){
        case 1:
            if (i != 0)
                cmd = "BBDDbbFF";
            else cmd = "UU";
            break;
        case 3:
            if (i != 0)
                cmd = "LLDllFF";
            else cmd = "u";
                break;
        case 5:
            if (i != 0) cmd = "RRdrrFF";
            else cmd = "U"; break;
        case 7: cmd = ""; break;
        case 41: cmd = "F"; break;
        case 48: cmd = "f"; break;
        case 10: cmd = "FF"; break;
        case 19: cmd = "fUlu"; break;
        case 21: cmd = "Ulu"; break;
        case 23: cmd = "ffUlu"; break;
        case 25: cmd = "FUlu"; break;
        case 16: cmd = "DDFF";break;
        case 12: cmd = "DFF"; break;
        case 14: cmd = "dFF"; break;
        case 37: cmd = "LF"; break;
        case 39: cmd = "lDLFUlu"; break;
        case 43: cmd = "DFUlu"; break;
        case 46: cmd = "rf"; break;
        case 50: cmd = "RdrFULu"; break;
        case 52: cmd = "dFUlu"; break;
        case 28: cmd = "BBDDFUlu"; break;
        case 30: cmd = "bDDBFUlu"; break;
        case 32: cmd = "BDDbFUlu"; break;
        case 34: cmd = "DDFUlu"; break;
            }
            {cube->applyMoves(cmd); moveRe +=cmd;}
            {cube->applyMoves("Y"); moveRe +="Y";}
        }
}


