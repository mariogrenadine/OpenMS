#include <OpenMS/ANALYSIS/SEQUENCE/NeedlemanWunsch.h>
#include <iostream>
#include <OpenMS/CONCEPT/Exception.h>
#include  <utility> //swap

using namespace std;
namespace OpenMS
{
    std::vector<vector<int>> adaptedIdentityNew // Name noch zu ändern
            {

                    //        A  B  C  D  E  F  G  H  I  K  L  M  N  P  Q  R  S  T  V  W  X  Y  Z
                    /* A */   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* B */   {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* C */   {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* D */   {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* E */   {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* F */   {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* G */   {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* H */   {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* I */   {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* K */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* L */   {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* M */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* N */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* P */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* Q */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* R */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                    /* S */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                    /* T */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                    /* V */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                    /* W */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                    /* X */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    /* Y */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                    /* Z */   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
            };

std::vector<int> adaptedIdentity
    {
        //      A  R  N  D  C  Q  E  G  H  I  L  K  M  F  P  S  T  W  Y  V  B  Z  X  *
        /* A */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* R */ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* N */ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* D */ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* C */ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* Q */ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* E */ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* G */ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* H */ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* I */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* L */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* K */ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* M */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* F */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* P */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* S */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -17,
        /* T */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, -17,
        /* W */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -17,
        /* Y */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -17,
        /* V */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, -17,
        /* B */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -17,
        /* Z */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, -17,
        /* X */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -17,
        /* * */ -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, 1
    };
    std::vector<vector<int>> PAM30MSNEW //Name noch zu ändern
            {

        //             A  B  C  D  E  F  G  H  I  K  L  M  N  P  Q  R  S  T  V  W  X  Y  Z
        /* A */        {6, -7, -6, -3, -2, -8, -2, -7, -5, -7, -6, -5, -4, -2, -4, -7, 0, -1, -2, -13, 0, -8, -6},
        /* B */       {-7,  5, -11, -7, -7, -12, -8, -4, -6, 5, -7, -3, -4, -5, -3, 5, -4, -5, -9, -7, 0, -10, 1},
        /* C */       {-6, -11, 10, -14, -14, -13, -9, -7, -6, -14, -11, -13, -11, -8, -14, -8, -3, -8, -6, -15, 0, -4, -14},
        /* D */       {-3, -7, -14, 8, 2, -15, -3, -4, -7, -4, -10, -11, 2, -8, -2, -10, -4, -5, -8, -15, 0, -11, -3},
        /* E */       {-2, -7, -14, 2, 8, -14, -4, -5, -5, -4, -7, -7, -2, -5, 1, -9, -4, -6, -6, -17, 0, -8, -2},
        /* F */       {-8, -12, -13, -15, -14, 9, -9, -6, -2, -14, -3, -4, -9, -10, -13, -9, -6, -9, -8, -4, 0, 2, -14},
        /* G */       {-2, -8, -9, -3, -4, -9, 6, -9, -11, -7, -11, -8, -3, -6, -7, -9, -2, -6, -5, -15, 0, -14, -7},
        /* H */       {-7, -4, -7, -4, -5, -6, -9, 9, -9, -6, -8, -10, 0, -4, 1, -2, -6, -7, -6, -7, 0, -3, -3},
        /* I */       {-5, -6, -6, -7, -5, -2, -11, -9, 8, -6, 5, -1, -5, -8, -8, -5, -7, -2, 2, -14, 0, -6, -7},
        /* K */       {-7,  5, -14, -4, -4, -14, -7, -6, -6, 7, -7, -2, -1, -6, -3, 0, -4, -3, -9, -12, 0, -9, 4},
        /* L */       {-6, -7, -11, -10, -7, -3, -11, -8, 5, -7, 5, 0, -6, -8, -7, -7, -8, -5, 0, -10, 0, -7, -7},
        /* M */       {-5, -3, -13, -11, -7, -4, -8, -10, -1, -2, 0, 11, -9, -8, -4, -4, -5, -4, -1, -13, 0, -11, -3},
        /* N */       {-4, -4, -11, 2, -2, -9, -3, 0, -5, -1, -6, -9, 8, -6, -3, -6, 0, -2, -8, -8, 0, -4, -2},
        /* P */       {-2, -5, -8, -8, -5, -10, -6, -4, -8, -6, -8, -8, -6, 8, -3, -4, -2, -4, -6, -14, 0, -13, -5},
        /* Q */       {-4, -3, -14, -2, 1, -13, -7, 1, -8, -3, -7, -4, -3, -3, 8, -2, -5, -5, -7, -13, 0, -12, 4},
        /* R */       {-7,  5, -8, -10, -9, -9, -9, -2, -5, 0, -7, -4, -6, -4, -2, 8, -3, -6, -8, -2, 0, -10, -1},
        /* S */        {0, -4, -3, -4, -4, -6, -2, -6, -7, -4, -8, -5, 0, -2, -5, -3, 6, 0, -6, -5, 0, -7, -5},
        /* T */       {-1, -5, -8, -5, -6, -9, -6, -7, -2, -3, -5, -4, -2, -4, -5, -6, 0, 7, -3, -13, 0, -6, -4},
        /* V */       {-2, -9, -6, -8, -6, -8, -5, -6, 2, -9, 0, -1, -8, -6, -7, -8, -6, -3, 7, -15, 0, -7, -8},
        /* W */       {-13, -7, -15, -15, -17, -4, -15, -7, -14, -12, -10, -13, -8, -14, -13, -2, -5, -13, -15, 13, 0, -5, -13},
        /* X */        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /* Y */       {-8, -10, -4, -11, -8, 2, -14, -3, -6, -9, -7, -11, -4, -13, -12, -10, -7, -6, -7, -5, 0, 10, -11},
        /* Z */       {-6, 1, -14, -3, -2, -14, -7, -3, -7, 4, -7, -3, -2, -5, 4, -1, -5, -4, -8, -13, 0, -11, 4}

            };

std::vector<int> PAM30MS
    {
        //        A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   *
        /* A */   6, -7, -4, -3, -6, -4, -2, -2, -7, -5, -6, -7, -5, -8, -2,  0, -1,-13, -8, -2, -7, -6,  0,-17,
        /* R */  -7,  8, -6,-10, -8, -2, -9, -9, -2, -5, -7,  0, -4, -9, -4, -3, -6, -2,-10, -8,  5, -1,  0,-17,
        /* N */  -4, -6,  8,  2,-11, -3, -2, -3,  0, -5, -6, -1, -9, -9, -6,  0, -2, -8, -4, -8, -4, -2,  0,-17,
        /* D */  -3,-10,  2,  8,-14, -2,  2, -3, -4, -7,-10, -4,-11,-15, -8, -4, -5,-15,-11, -8, -7, -3,  0,-17,
        /* C */  -6, -8,-11,-14, 10,-14,-14, -9, -7, -6,-11,-14,-13,-13, -8, -3, -8,-15, -4, -6,-11,-14,  0,-17,
        /* Q */  -4, -2, -3, -2,-14,  8,  1, -7,  1, -8, -7, -3, -4,-13, -3, -5, -5,-13,-12, -7, -3,  4,  0,-17,
        /* E */  -2, -9, -2,  2,-14,  1,  8, -4, -5, -5, -7, -4, -7,-14, -5, -4, -6,-17, -8, -6, -7, -2,  0,-17,
        /* G */  -2, -9, -3, -3, -9, -7, -4,  6, -9,-11,-11, -7, -8, -9, -6, -2, -6,-15,-14, -5, -8, -7,  0,-17,
        /* H */  -7, -2,  0, -4, -7,  1, -5, -9,  9, -9, -8, -6,-10, -6, -4, -6, -7, -7, -3, -6, -4, -3,  0,-17,
        /* I */  -5, -5, -5, -7, -6, -8, -5,-11, -9,  8,  5, -6, -1, -2, -8, -7, -2,-14, -6,  2, -6, -7,  0,-17,
        /* L */  -6, -7, -6,-10,-11, -7, -7,-11, -8,  5,  5, -7,  0, -3, -8, -8, -5,-10, -7,  0, -7, -7,  0,-17,
        /* K */  -7,  0, -1, -4,-14, -3, -4, -7, -6, -6, -7,  7, -2,-14, -6, -4, -3,-12, -9, -9,  5,  4,  0,-17,
        /* M */  -5, -4, -9,-11,-13, -4, -7, -8,-10, -1,  0, -2, 11, -4, -8, -5, -4,-13,-11, -1, -3, -3,  0,-17,
        /* F */  -8, -9, -9,-15,-13,-13,-14, -9, -6, -2, -3,-14, -4,  9,-10, -6, -9, -4,  2, -8,-12,-14,  0,-17,
        /* P */  -2, -4, -6, -8, -8, -3, -5, -6, -4, -8, -8, -6, -8,-10,  8, -2, -4,-14,-13, -6, -5, -5,  0,-17,
        /* S */   0, -3,  0, -4, -3, -5, -4, -2, -6, -7, -8, -4, -5, -6, -2,  6,  0, -5, -7, -6, -4, -5,  0,-17,
        /* T */  -1, -6, -2, -5, -8, -5, -6, -6, -7, -2, -5, -3, -4, -9, -4,  0,  7,-13, -6, -3, -5, -4,  0,-17,
        /* W */ -13, -2, -8,-15,-15,-13,-17,-15, -7,-14,-10,-12,-13, -4,-14, -5,-13, 13, -5,-15, -7,-13,  0,-17,
        /* Y */  -8,-10, -4,-11, -4,-12, -8,-14, -3, -6, -7, -9,-11,  2,-13, -7, -6, -5, 10, -7,-10,-11,  0,-17,
        /* V */  -2, -8, -8, -8, -6, -7, -6, -5, -6,  2,  0, -9, -1, -8, -6, -6, -3,-15, -7,  7, -9, -8,  0,-17,
        /* B */  -7,  5, -4, -7,-11, -3, -7, -8, -4, -6, -7,  5, -3,-12, -5, -4, -5, -7,-10, -9,  5,  1,  0,-17,
        /* Z */  -6, -1, -2, -3,-14,  4, -2, -7, -3, -7, -7,  4, -3,-14, -5, -5, -4,-13,-11, -8,  1,  4,  0,-17,
        /* X */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,-17,
        /* * */ -17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,  1
    };

  NeedlemanWunsch::NeedlemanWunsch(NeedlemanWunsch::ScoringMatrix matrix, int penalty)
{
 if (penalty >= 0)
 {
   String msg = "Gap penalty should be negative";
   throw Exception::IllegalArgument(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION,
                                    msg);
 }

  gapPenalty_ = penalty;

  if (matrix == ScoringMatrix::identityMatrix)
  {
    matrixPtr_ = &adaptedIdentity;
  }

  else if (matrix == ScoringMatrix::PAM30MSMatrix)
  {
    matrixPtr_ = &PAM30MS;
  }
  else
  {
    String msg = "Matrix is not known! Valid choices are: "
                                       "'identityMatrix', 'PAM30MSMatrix'.";
    throw Exception::IllegalArgument(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION,
                                     msg);
  }
}

void NeedlemanWunsch::setMatrix_(const NeedlemanWunsch::ScoringMatrix& matrix)
{
  if (matrix == ScoringMatrix::identityMatrix)
  {
    matrixPtr_ = &adaptedIdentity;
  }

  else if (matrix == ScoringMatrix::PAM30MSMatrix)
  {
    matrixPtr_ = &PAM30MS;
  }

  else
  {
    String msg = "Matrix is not known! Valid choices are: "
                                       "'identityMatrix', 'PAM30MSMatrix'.";
    throw Exception::IllegalArgument(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION,
                                     msg);
  }
}

void NeedlemanWunsch::setPenalty_(const int& penalty)
{

    if (penalty >= 0)
    {
      String msg = "Gap penalty should be negative";
      throw Exception::IllegalArgument(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION,
                                       msg);
    }
      gapPenalty_ = penalty;
}

NeedlemanWunsch::ScoringMatrix NeedlemanWunsch::getMatrix_() const
{
    if (*matrixPtr_ == adaptedIdentity)
    {
      return ScoringMatrix::identityMatrix;
    }
    else
    {
      return ScoringMatrix::PAM30MSMatrix;
    }
}

int NeedlemanWunsch::getPenalty_() const
{
    return gapPenalty_;
}
int NeedlemanWunsch::getIndexNEW_(const char&a) const //Falls wir die Matrizen als vector<vector<int>> haben, rufen wir getIndexNEW_ 2x auf (für Matrix[i][j])
{
    //                         0    1    2    3    4    5    6    7    8    9    10   11  12   13    14   15   16   17   18  19   20   21    22
    vector<char> alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z' };
    int index = 0;

    for(Size i=0; i<alphabet.size(); i++)
    {
        if(alphabet[i] == a)
        {  index = i;
             break;
        }
    }
    return index;
}
int NeedlemanWunsch::getIndex_(const char& a, const char& b) const //noch optimieren (Tina)
{

vector<pair<char,int>> vec =
    {
        {'A', 0}, {'R', 1}, {'N', 2},
        {'D', 3}, {'C', 4}, {'Q', 5},
        {'E', 6}, {'G', 7}, {'H', 8},
        {'I', 9}, {'L', 10}, {'K', 11},
        {'M', 12}, {'F', 13}, {'P', 14},
        {'S', 15}, {'T', 16}, {'W', 17},
        {'Y', 18}, {'V', 19}, {'B', 20},
        {'Z', 21}, {'X', 22}, {'*', 23}
    };
int x = -1;
int y = -1;
for (Size i = 0; i < vec.size(); ++i)
{
if (vec[i].first == a)
x = vec[i].second;
if (vec[i].first == b)
y = vec[i].second;
}
if (x == -1)
x = 23;
if (y == -1)
y = 23;
return x + y*vec.size();
}
/*
double NeedlemanWunsch::align_(const String& seq1, const String& seq2) //vollständige matrix
{
  seq1len_ = seq1.length();
  seq2len_ = seq2.length();

  vector<int> matrix((seq1len_+1)*(seq2len_+1), 0);//matrix mit 0en initialisieren
  for (unsigned i = 1; i <= seq1len_; ++i) //vertikale mit gapkkosten initialisieren
    matrix[i*(seq2len_+1)]=i*gapPenalty_;
  for (unsigned i =0; i<=seq2len_;++i)//horizontale mit gapkosten initialieren
    matrix[i]=i*gapPenalty_;
  for (unsigned i=1;i<=seq1len_;++i)
  {
    for (unsigned j=1;j<=seq2len_;++j)
    {
      matrix[i*(seq2len_ +1)+j]=max(max((matrix[i*(seq2len_+1)+j-1]+gapPenalty_), (matrix[(i-1)*(seq2len_+1)+j]+gapPenalty_)),
                                    (matrix[(i-1)*(seq2len_+1)+j-1])+ (*matrixPtr_)[getIndex_(seq1[i-1], seq2[j-1])]);
    }
  }
  cout<<matrix[(seq1len_+1)*(seq2len_+1)-1]<<endl;
  return matrix[(seq1len_+1)*(seq2len_+1)-1];
}
 */

//linear space (2 Zeilen)
 double NeedlemanWunsch::align_(const String& seq1, const String& seq2)
 {
   seq1len_ = seq1.length();
   seq2len_ = seq2.length();

   vector<int> firstRow{};
   vector<int> secondRow(seq2len_+1,0);
   vector<int>* firstRowPtr = &firstRow;
   vector<int>* secondRowPtr = &secondRow;


   for (unsigned i = 0; i <= seq2len_; ++i)//horizontale mit gapkosten initialieren
   {
     firstRow.push_back(i * gapPenalty_);
   }

   for (unsigned i = 1;i <= seq1len_; ++i) //second row berechnen und swappen
   {
     (*secondRowPtr)[0] = i * gapPenalty_; //erster wert in der zeile mit gapkosten
     for (unsigned j = 1; j <= seq2len_; ++j) //secondRow berechnen
     {
       (*secondRowPtr)[j] = (max(max(((*secondRowPtr)[j-1] + gapPenalty_), ((*firstRowPtr)[j] + gapPenalty_)),
                                    ((*firstRowPtr)[j-1]) + (*matrixPtr_)[getIndex_(seq1[i-1], seq2[j-1])]));//statt getIndex: [seq1[i-1] - 'A'] [seq2[j-1] - 'A'] und matrix entsprechend aufbauen
                                    //cout<<(*matrixPtr_)[getIndex_(seq1[i-1], seq2[j-1])]<<endl;
     }
     swap(firstRowPtr, secondRowPtr);
   }
   cout<<(*firstRowPtr)[seq2len_]<<endl;
   return (*firstRowPtr)[seq2len_];
 }

}