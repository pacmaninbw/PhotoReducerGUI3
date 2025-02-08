#ifndef OPTIONERRORCODE_H_
#define OPTIONERRORCODE_H_

#include <QString>

using OptionErrorCode = unsigned int;

const OptionErrorCode maxWidthError = 0x0001; 
const OptionErrorCode maxHeightError = 0x0002;
const OptionErrorCode scaleFactorError = 0x0004;
const OptionErrorCode maintainRatioError = 0x0008;
const OptionErrorCode missingSizeError = 0x0010;
const OptionErrorCode overwriteWarning = 0x0011;

struct OptionErrorSignalContents
{
    OptionErrorCode errorCode;
    QString errorMessage;
};

#endif // OPTIONERRORCODE_H_
