//
//  scales.h
//  Ambient
//
//  Created by Raúl Ibarra Díez on 04/07/14.
//
//

#include <string>
#include <iostream>
using namespace std;

#ifndef Ambient_scales_h
#define Ambient_scales_h


static const int CMajor[7] = {0, 2, 4, 5, 7, 9, 11};    // 0  //0
static const int CMinor[7] = {0, 2, 3, 5, 7, 8, 10};    // 0  //1
static const int DbMajor[7] = {1, 3, 5, 6, 8, 10, 0};   // 6  //2
static const int CsMinor[7] = {1, 3, 4, 6, 8, 9, 11};   // 0  //3
static const int DMajor[7] = {2, 4, 6, 7, 9, 11, 1};    // 6  //4
static const int DMinor[7] = {2, 4, 5, 7, 9, 10, 0};    // 6  //5
static const int DsMinor[7] = {3, 5, 6, 8, 10, 11, 1};  // 6  //6
static const int EbMajor[7] = {3, 5, 7, 8, 10, 0, 2};   // 5  //7
static const int EMajor[7] = {4, 6, 8, 9, 11, 1, 3};    // 5  //8
static const int EMinor[7] = {2, 4, 6, 7, 9, 11, 0};    // 6  //9
static const int FMajor[7] = {5, 7, 9, 10, 0, 2, 4};    // 4  //10
static const int FMinor[7] = {5, 7, 8, 10, 0, 1, 3};    // 4  //11
static const int FsMajor[7] = {6, 8, 10, 11, 1, 3, 5};  // 4  //12
static const int FsMinor[7] = {6, 8, 9, 11, 1, 2, 4};   // 4  //13
static const int GMajor[7] = {7, 9, 11, 0, 2, 4, 6};    // 3  //14
static const int GMinor[7] = {7, 9, 10, 0, 2, 3, 5};    // 3  //15
static const int AbMajor[7] = {8, 10, 0, 1, 3, 5, 7};   // 2  //16
static const int GsMinor[7] = {8, 10, 11, 1, 3, 4, 6};  // 3  //17
static const int AMajor[7] = {9, 11, 1, 2, 4, 6, 8};    // 2  //18
static const int AMinor[7] = {9, 11, 0, 2, 4, 5, 7};    // 2  //19
static const int BbMajor[7] = {10, 0, 2, 3, 5, 7, 9};   // 1  //20
static const int BbMinor[7] = {10, 0, 1, 3, 5, 6, 8};   // 1  //21
static const int BMajor[7] = {11, 1, 3, 4, 6, 8, 10};   // 1  //22
static const int BMinor[7] = {11, 1, 2, 4, 6, 7, 9};    // 1  //23


static const int* ListOfScales[24] = {CMajor, CMinor, DbMajor, CsMinor, DMajor, DMinor, DsMinor, EbMajor, EMajor, EMinor, FMajor, FMinor, FsMajor, FsMinor, GMajor, GMinor, AbMajor, GsMinor, AMajor, AMinor, BbMajor, BbMinor, BMajor, BMinor};

static const int octaveChange[24] = {0, 0, 6, 0, 6, 6, 6, 5, 5, 6, 4, 4, 4, 4, 3, 3, 2, 3, 2, 2, 1, 1, 1, 1};

static const string NamesOfScales[24] = {"C Major", "C Minor", "Db Major", "C# Minor", "D Major", "D Minor", "D# Minor", "Eb Major", "E Major", "E Minor", "F Major", "F Minor", "F# Major", "F# Minor", "G Major", "G Minor", "Ab Major", "G# Minor", "A Major", "A Minor", "Bb Major", "Bb Minor", "B Major", "B Minor"};

#endif
