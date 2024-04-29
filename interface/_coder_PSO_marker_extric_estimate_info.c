/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_PSO_marker_extric_estimate_info.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-04-29 11:40:58
 */

/* Include Files */
#include "_coder_PSO_marker_extric_estimate_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *c_emlrtMexFcnResolvedFunctionsI(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrtMexFcnResolvedFunctionsI(void)
{
  const mxArray *nameCaptureInfo;
  const char_T *data[4] = {
      "789cc5934f4ac34018c527528b9b6a367a0ce9da654b14a5b1c156901a1943f2950ecd64"
      "c26422f110e2d2851770259e47f0061ec23669fed2219560fd365f1e"
      "3f26efe58541cab9ae2084f65132513bd99d9556577b0795a7ca15c94e6717b54ae752fe"
      "bcda36f3044422119e45213be9304a3ccb13e3471f108780b90fe0c4",
      "644a5c18130aa3a2b85c2a7a5a409958a2e5737f06f67c1452c467419ed02d8aac8f0fc9"
      "f7b636ece342d2875ae1b7da9d7662f69903a68040e0c0e6c41726b5"
      "f81c385e34c3898d1780504b80698c86783d3aa6e5fc51c3fc8735f9536e33ea8702f094"
      "080c9c338efd801572dc37ccd196e648482078688bdcefada19f26f5",
      "2bf3dffdb7b52dc5bfacaea7830d73cbee5f07edc5fbfde53346dbf27bfa7efddaa65f3a"
      "ffe5d7f4be1d49fcd40a1ff8fa60721345675d6f72ed76f5ab21ef19"
      "bd3c8751e353970349f45fbfff07bf9780e6",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 1680U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/*
 * Arguments    : void
 * Return Type  : mxArray *
 */
mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *propFieldName[9] = {"Version",
                                    "ResolvedFunctions",
                                    "Checksum",
                                    "EntryPoints",
                                    "CoverageInfo",
                                    "IsPolymorphic",
                                    "PropertyList",
                                    "UUID",
                                    "ClassEntryPointIsHandle"};
  const char_T *epFieldName[8] = {
      "Name",     "NumberOfInputs", "NumberOfOutputs", "ConstantInputs",
      "FullPath", "TimeStamp",      "Constructor",     "Visible"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 8, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 1);
  emlrtSetField(xEntryPoints, 0, "Name",
                emlrtMxCreateString("PSO_marker_extric_estimate"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs",
                emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath",
                emlrtMxCreateString("E:\\Code\\test_script\\marker_extric_"
                                    "estimate\\PSO_marker_extric_estimate.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739368.66618055559));
  emlrtSetField(xEntryPoints, 0, "Constructor",
                emlrtMxCreateLogicalScalar(false));
  emlrtSetField(xEntryPoints, 0, "Visible", emlrtMxCreateLogicalScalar(true));
  xResult =
      emlrtCreateStructMatrix(1, 1, 9, (const char_T **)&propFieldName[0]);
  emlrtSetField(xResult, 0, "Version",
                emlrtMxCreateString("24.1.0.2537033 (R2024a)"));
  emlrtSetField(xResult, 0, "ResolvedFunctions",
                (mxArray *)c_emlrtMexFcnResolvedFunctionsI());
  emlrtSetField(xResult, 0, "Checksum",
                emlrtMxCreateString("jzmem4zMXFgFKXV5dpQNZF"));
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_PSO_marker_extric_estimate_info.c
 *
 * [EOF]
 */
