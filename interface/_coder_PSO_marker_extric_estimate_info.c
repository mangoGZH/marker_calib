/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_PSO_marker_extric_estimate_info.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024-05-13 17:23:46
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
      "789cc5935d4ec2401485a706d1179417f5cd25b800df4c5309a2422c51a335632d973081"
      "e934335353d884ab30f1d12db80d5723f487fe8449318d785f6e4fbe"
      "4ccfe9690669ed2b0d21b487a209ead16ec4ba19ef2d949f22d7143b996d54cb9d4bf85b"
      "bc1de64a0864245c9bc2f2e48051e2daaeec4f3d401c049bbcc22024",
      "4332813ea16066c5f542d1f30c5a8a055a3ceb2370c6a64f111f8934e1242b967d7c2abe"
      "b7b6661f178a3e9a05fe683c19a796ce06604910120b87134f5ad4e6"
      "63e078de0c270e9e03426d0956cfece2d5e884e6f30715f31f94e44fb8c3a8e74bc04322"
      "3170ce38f604cbe478ae98a3aecc111121b9efc8d4efa3a29fa1f4cb",
      "f3dffdb7952d85bfacaca7fd3573abee5f03ed86fbe8fd3b449bf2fb829de34dfa25f35f"
      "7e55efdba1c2af59e0f6fde5d94db7753b7bd13b33bd23865efbe1ae"
      "95e6e895f894e5400afdd7efff01da907edc",
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
                emlrtMxCreateDoubleScalar(739385.46129629633));
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
                emlrtMxCreateString("NwXw51XNIjZUsqNEzX2f5C"));
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_PSO_marker_extric_estimate_info.c
 *
 * [EOF]
 */
