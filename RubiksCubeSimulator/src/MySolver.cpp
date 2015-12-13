
#include "MySolver.h"

MySolver::MySolver()
{}

MySolver::~MySolver()
{}

string MySolver::moveRe = "";

// The function to apply the algorithm to transform to the solved state
string MySolver::solveCube(RubikCube* cube)
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

    //cout << "\n----- SOLVING THE WHITE CROSS -----\n";
    while (cube->ptr_facets_buffer_data()[1] != 1 ||
           cube->ptr_facets_buffer_data()[3] != 3 ||
           cube->ptr_facets_buffer_data()[5] != 5 ||
           cube->ptr_facets_buffer_data()[7] != 7)
            solveWhiteCross(cube);
    {cube->applyMoves("XXYY"); moveRe += "XXYY";}

    //cout << "\n----- COMPLETE THE FIRST 2 LAYERS USING F2L REDUCTION -----\n";
    FLLReduction(cube);

    //cout << "\n----- SOLVE THE YELLOW CROSS USING OLL -----\n";

            solveYellowCross(cube);

    //cout << "\n----- COMPLETE THE YELLOW LAYER -----\n";
    solveLastFace(cube);

    //cout << "\n----- PERMUTE LAST LAYER AND COMPLETE THE CUBE -----\n";
    solveLastLayer(cube);

    {cube->applyMoves("XX"); moveRe += "XX";}

    return moveRe;
}

void MySolver::solveLastLayer(RubikCube* cube)
{
    /// Solving the corners first
    while (true)
    {
        int t = 0;
        for (t = 0; t < 4; ++t)
        {
            if (cube->ptr_face_color_buffer_data()[18] !=
                cube->ptr_face_color_buffer_data()[29])
                    {cube->applyMoves("U"); moveRe += "U";}
            else break;
        }
        {cube->applyMoves("XRRDDRUrDDRuRXXX"); moveRe += "XRRDDRUrDDRuRXXX";}
        for (t = 0; t < 4; ++t)
        {
            if (cube->ptr_face_color_buffer_data()[18] !=
                cube->ptr_face_color_buffer_data()[22])
                    {cube->applyMoves("U"); moveRe += "U";}
            else break;
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
                    {cube->applyMoves("Y"); moveRe += "Y";}
            else break;
        }
        if (i < 4) break;
        else {cube->applyMoves("FFULrFFlRUFF"); moveRe += "FFULrFFlRUFF";}
    }

        if (cube->ptr_face_color_buffer_data()[37] == cube->ptr_face_color_buffer_data()[49])
            {cube->applyMoves("FFULrFFlRUFF"); moveRe += "FFULrFFlRUFF";}
        else {cube->applyMoves("FFuLrFFlRuFF"); moveRe += "FFuLrFFlRuFF";}
        if (cube->ptr_face_color_buffer_data()[19] != cube->ptr_face_color_buffer_data()[22])
        {
            if (cube->ptr_face_color_buffer_data()[37] == cube->ptr_face_color_buffer_data()[49])
            {cube->applyMoves("FFULrFFlRUFF"); moveRe += "FFULrFFlRUFF";}
        else {cube->applyMoves("FFuLrFFlRuFF"); moveRe += "FFuLrFFlRuFF";}
        }

}

void MySolver::solveLastFace(RubikCube* cube)
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
    if (tempStr == "134567202947") {{cube->applyMoves("RUrURuur"); moveRe += "RUrURuur";} return;}
    else if (tempStr == "1345720273638") {{cube->applyMoves("RuurruRRurrUUR"); moveRe += "RuurruRRurrUUR";} return;}
    else if (tempStr == "01345672027") {{cube->applyMoves("XruLURulUXXX"); moveRe += "XruLURulUXXX";} return;}
    else if (tempStr == "01234571820") {{cube->applyMoves("rrDrUURdrUUr"); moveRe += "rrDrUURdrUUr";} return;}
    else if (tempStr == "013457182745") {{cube->applyMoves("ruRurUUR"); moveRe += "ruRurUUR";} return;}
    else if (tempStr == "1345736384547") {{cube->applyMoves("RUrURurURUUr"); moveRe += "RUrURurURUUr";} return;}
    else if (tempStr == "01345781847") {{cube->applyMoves("rFRbrfRB"); moveRe += "rFRbrfRB";} return;}
        {cube->applyMoves("Y"); moveRe += "Y";}
    }
}

void MySolver::solveYellowCrossOLL(RubikCube* cube)
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
        if (tempStr == "4") {{cube->applyMoves("rFRfUUrFRffUUF"); moveRe += "rFRfUUrFRffUUF";} return;}
        else if (tempStr == "134") {{cube->applyMoves("FURurf"); moveRe += "FURurf";} return;}
        else if (tempStr == "345") {{cube->applyMoves("FRUruf"); moveRe += "FRUruf";} return;}
        else if (tempStr == "13457") {return;}

        {cube->applyMoves("Y"); moveRe += "Y";}
    }
}

void MySolver::FLLReduction(RubikCube* cube)
{
    int posts[54];
    string cmd;
    /// Solve the first layer
    int corners[4] = {6, 0, 2, 8};
    int edges[4] = {21, 39, 30, 48};
    for (int x = 0; x < 4; ++x)
        {

        while (cube->ptr_facets_buffer_data()[11] != corners[x] ||
               cube->ptr_facets_buffer_data()[23] != edges[x])
        {
            // first, find the corner and put on the top face
        // if it is not yet
        for (int i = 0; i < 4; ++i)
        {
            if (corners[x] == cube->ptr_facets_buffer_data()[26] ||
                corners[x] == cube->ptr_facets_buffer_data()[11] ||
                corners[x] == cube->ptr_facets_buffer_data()[51])
                {
                    {cube->applyMoves("RUr"); moveRe += "RUr";}
                }
            {cube->applyMoves("Y"); moveRe += "Y";}
        }

        // then, find the edge and put on the top face
        // if it is not yet
        for (int i = 0; i < 4; ++i)
        {
            if (edges[x] == cube->ptr_facets_buffer_data()[23] ||
                edges[x] == cube->ptr_facets_buffer_data()[48])
                {
                    {cube->applyMoves("RUr"); moveRe += "RUr";}
                }
            {cube->applyMoves("Y"); moveRe += "Y";}
        }

        int t;
        for (t = 0; t < 4; ++t)
        {
            if (corners[x] == cube->ptr_facets_buffer_data()[8] ||
                corners[x] == cube->ptr_facets_buffer_data()[20] ||
                corners[x] == cube->ptr_facets_buffer_data()[45])
                    break;
            {cube->applyMoves("U"); moveRe += "U";}
        }

            for (int i = 0; i < 54; ++i)
                    posts[cube->ptr_facets_buffer_data()[i]] = i;
            string tempStr = "";
            stringstream ssCorner;
            ssCorner << posts[corners[x]];
            stringstream ssEdge;
            ssEdge << posts[edges[x]];
            tempStr += ssCorner.str();
            tempStr += ssEdge.str();

            // 4 basic case first
         if (tempStr == "451") {{cube->applyMoves("RUr"); moveRe += "RUr";} }
    else if (tempStr == "2037") {{cube->applyMoves("fuF"); moveRe += "fuF";}}
    else if (tempStr == "205") {{cube->applyMoves("URur"); moveRe += "URur";} }
    else if (tempStr == "4519") {{cube->applyMoves("ufUF"); moveRe += "ufUF";} }
            // edge and corner on top
    else if (tempStr == "455") {{cube->applyMoves("uRurU"); moveRe += "uRurU";} }
    else if (tempStr == "2019") {{cube->applyMoves("UfUFu"); moveRe += "UfUFu";} }
    else if (tempStr == "453") {{cube->applyMoves("uRUrU"); moveRe += "uRUrU";} }
    else if (tempStr == "2028") {{cube->applyMoves("UfuFu"); moveRe += "UfuFu";} }
    else if (tempStr == "457") {{cube->applyMoves("UfUUfu"); moveRe += "UfUUfu";} }
    else if (tempStr == "2046") {{cube->applyMoves("uRUUrU"); moveRe += "uRUUrU";} }
    else if (tempStr == "4528") {{cube->applyMoves("UfUUFu"); moveRe += "UfUUFu";} }
    else if (tempStr == "203") {{cube->applyMoves("uRUUrU"); moveRe += "uRUUrU";} }
    else if (tempStr == "4537") {{cube->applyMoves("UfuFu"); moveRe += "UfuFu";}}
    else if (tempStr == "201") {{cube->applyMoves("uRUrU"); moveRe += "uRUrU";} }

    else if (tempStr == "4546") {{cube->applyMoves("Rur"); moveRe += "Rur";} }
    else if (tempStr == "207") {{cube->applyMoves("fUF"); moveRe += "fUF";} }
    else if (tempStr == "85") {{cube->applyMoves("RUUr"); moveRe += "RUUr";} }
    else if (tempStr == "819") {{cube->applyMoves("fUUF"); moveRe += "fUUF";} }
    else if (tempStr == "81") {{cube->applyMoves("URUUr"); moveRe += "URUUr";} }
    else if (tempStr == "837") {{cube->applyMoves("ufUUF"); moveRe += "ufUUF";}}
    else if (tempStr == "83") {{cube->applyMoves("UURUr"); moveRe += "UURUr";} }
    else if (tempStr == "828") {{cube->applyMoves("UUfuF"); moveRe += "UUfuF";} }
    else if (tempStr == "87") {{cube->applyMoves("UURRUUruRuRR"); moveRe += "UURRUUruRuRR";} }
    else if (tempStr == "846") {{cube->applyMoves("YYYUUrrUURUrURRY"); moveRe += "YYYUUrrUURUrURRY";} }

        }
        cube->applyMoves("Y"); moveRe += "Y";
    }
}

void MySolver::solveWhiteCross(RubikCube* cube)
{
    string cmd;
    GLint posts[54];
    int num[4] = {7, 5, 1, 3};
    for (int i = 0; i < 4; ++i){

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
            cube->applyMoves(cmd);
            moveRe += cmd;
            {cube->applyMoves("Y"); moveRe += "Y";}
    }
}

void MySolver::solveYellowCross(RubikCube* cube)
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
            {cube->applyMoves("FURurf"); moveRe += "FURurf";}
        }
    if (cube->ptr_face_color_buffer_data()[1] == 1 &&
             cube->ptr_face_color_buffer_data()[3] == 1)
    {
        {cube->applyMoves("FURurf"); moveRe += "FURurf";}
    }
    else if (cube->ptr_face_color_buffer_data()[1] == 1 &&
             cube->ptr_face_color_buffer_data()[5] == 1)
    {
        for (int i = 0; i < 3; ++i) {cube->applyMoves("Y"); moveRe += "Y";}
        {cube->applyMoves("FURurf"); moveRe += "FURurf";}
        {cube->applyMoves("Y"); moveRe += "Y";}
    }
    else if (cube->ptr_face_color_buffer_data()[3] == 1 &&
             cube->ptr_face_color_buffer_data()[7] == 1)
    {
        {cube->applyMoves("Y"); moveRe += "Y";}
        {cube->applyMoves("FURurf"); moveRe += "FURurf";}
        for (int i = 0; i < 3; ++i) {cube->applyMoves("Y"); moveRe += "Y";}
    }
    else if (cube->ptr_face_color_buffer_data()[5] == 1 &&
             cube->ptr_face_color_buffer_data()[7] == 1)
    {
        for (int i = 0; i < 2; ++i) {cube->applyMoves("Y"); moveRe += "Y";}
        {cube->applyMoves("FURurf"); moveRe += "FURurf";}
        for (int i = 0; i < 2; ++i) {cube->applyMoves("Y"); moveRe += "Y";}
    }
    else if (cube->ptr_face_color_buffer_data()[3] == 1 &&
        cube->ptr_face_color_buffer_data()[5] == 1)
        {cube->applyMoves("FRUruf"); moveRe += "FRUruf";}
    else if (cube->ptr_face_color_buffer_data()[1] == 1 &&
             cube->ptr_face_color_buffer_data()[7] == 1)
    {
        {cube->applyMoves("YFRUrufYYY"); moveRe += "YFRUrufYYY";}
    }
}
